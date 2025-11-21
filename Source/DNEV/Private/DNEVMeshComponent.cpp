#include "DNEVMeshComponent.h"

#include "DNEVPrivatePCH.h"
#include "Utils.h"

#include "AudioDevice.h"
#include "Components/AudioComponent.h"
#include "Engine/CollisionProfile.h"
#include "Materials/Material.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Math/UnrealMathUtility.h"

#include "Misc/ScopeTryLock.h"

#include <Mvx2API/frameaccess/extractors/FrameMeshExtractor.h>
#include <Mvx2API/frameaccess/extractors/FrameTextureExtractor.h>
#include <Mvx2API/data/mesh/MeshData.h>
#include <Mvx2API/data/BasicDataLayersGuids.h>

#define LOCTEXT_NAMESPACE "DNEVMeshComponent"

// Sets default values
UDNEVMeshComponent::UDNEVMeshComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryComponentTick.bStartWithTickEnabled = true;
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickGroup = TG_PrePhysics;

	PlaybackMode = EPlaybackMode::FORWARD_ONCE;
	bPlayOnStart = true;
	bInvertNormals = false;
	NormalMode = EDNEVNormalMode::NM_DEFAULT;
	RenderedFrameID = -1;
	MaterialInstance = nullptr;
	MaterialTextureName = "Diffuse";

	ProcMeshComponent = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("ProcMeshComponent"));
	ProcMeshComponent->SetMobility(EComponentMobility::Movable);
	ProcMeshComponent->SetupAttachment(this);
	ProcMeshComponent->SetCollisionProfileName(UCollisionProfile::BlockAll_ProfileName);
	ProcMeshComponent->SetGenerateOverlapEvents(false);

	DNEVAudioComponent = CreateDefaultSubobject<UDNEVAudioComponent>(TEXT("DNEVAudioComponent"));
	DNEVAudioComponent->SetMobility(EComponentMobility::Movable);
	DNEVAudioComponent->SetupAttachment(this);
	DNEVAudioComponent->bAutoActivate = true;
	DNEVAudioComponent->bStopWhenOwnerDestroyed = true;
	DNEVAudioComponent->bShouldRemainActiveIfDropped = true;

	if (Material == nullptr)
	{
		static ConstructorHelpers::FObjectFinder<UMaterial> MaterialMaster(TEXT("/DNEV/example/materials/M_DNEV_Master"));

		if (MaterialMaster.Object != nullptr)
		{
			Material = MaterialMaster.Object;
		}
	}

	const FSoftObjectPath SoundClassName = GetDefault<UAudioSettings>()->DefaultMediaSoundClassName;
	if (SoundClassName.IsValid())
	{
		DNEVAudioComponent->SoundClassOverride = LoadObject<USoundClass>(nullptr, *SoundClassName.ToString());
	}
}

void UDNEVMeshComponent::BeginDestroy()
{
	Super::BeginDestroy();
}

void UDNEVMeshComponent::OnRegister()
{
	Super::OnRegister();

	SetData(Data);

	if (DataStream != nullptr)
	{
		ManualSeek(0);

		// If it's in the game
		if (IsInGameMode(GetWorld()))
		{
			if (bPlayOnStart)
			{
				DataStream->PlaybackMode = PlaybackModeConvert(PlaybackMode);
				DataStream->PlaybackPlay();
			}
		}
	}
}

void UDNEVMeshComponent::OnUnregister()
{
	Super::OnUnregister();
	ReleaseResources();
}

void UDNEVMeshComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	CheckDataStream();
}

void UDNEVMeshComponent::CheckDataStream()
{
	CheckResources();

	// Update render
	if (DataStream != nullptr)
	{
		if (!bIsWorking)
		{
			const FScopeTryLock Lock(&DataStream->DataCritSec);

			if (DataStream->pFrameToProcess != nullptr)
			{
				if (Lock.IsLocked())
				{
					// Capture this frame
					// TODO: Find a better way to do this.
					pFrame = DataStream->pFrameToProcess;
					DataStream->pFrameToProcess = nullptr;

					bIsWorking = true;

					// Start import thread
					WorkingThread = Async(EAsyncExecution::Thread, [this]()
					{
						ExtractMeshVertexData();
						ExtractMeshTextureData();

						// main job done here
						AsyncTask(ENamedThreads::GameThread, [this]()
						{
							if (this != nullptr)
							{
								if (!bIsWorking)
									return;
								
								// Update render object on the main thread
								UpdateRenderable();
								MarkRenderStateDirty();

								RenderedFrameID = pFrame->GetStreamAtomNr();

								// Delete this frame
								delete pFrame;
								pFrame = nullptr;

								// Flip buffer
								Activebuffer = (Activebuffer + 1) % RenderDataFlip.Num();

								// Mark work complete
								bIsWorking = false;
							}
						});
					});
				}
			}
		}
	}
}

void UDNEVMeshComponent::ManualSeek(const int32 InFrameIdx)
{
	if (DataStream != nullptr)
	{
		const FScopeTryLock Lock(&DataStream->DataCritSec);

		if (Lock.IsLocked())
		{
			pFrame = DataStream->ManualSeek(InFrameIdx);
			CheckResources();
			ExtractMeshVertexData();
			ExtractMeshTextureData();
			UpdateRenderable();
			MarkRenderStateDirty();

			RenderedFrameID = pFrame->GetStreamAtomNr();
			delete pFrame;
			pFrame = nullptr;
			Activebuffer = (Activebuffer + 1) % RenderDataFlip.Num();
		}
	}
}

void UDNEVMeshComponent::ExtractMeshVertexData()
{
	const Mvx2API::MeshData* frameMeshData = Mvx2API::FrameMeshExtractor::GetMeshData(pFrame);

	MeshData* md = RenderDataFlip[Activebuffer];

	if (pFrame->StreamContainsDataLayer(Mvx2API::BasicDataLayersGuids::VERTEX_POSITIONS_DATA_LAYER()))
	{
		md->MeshVertices.SetNum(frameMeshData->GetNumVertices());
		float const* pVertices = frameMeshData->GetVertices();

		// Cast float* to FVector*
		for (std::size_t i = 0; i < md->MeshVertices.Num(); ++i)
		{
			FVector v = FVector(pVertices[i * 3], pVertices[i * 3 + 1], pVertices[i * 3 + 2]);
			v = DNEVToUnrealPosition(v);
			v = DNEVToUnrealScale(v);
			md->MeshVertices[i] = v;
		}
	}

	if (pFrame->StreamContainsDataLayer(Mvx2API::BasicDataLayersGuids::VERTEX_INDICES_DATA_LAYER()))
	{
		md->MeshIndices.SetNum(frameMeshData->GetNumIndices());
		uint32 const* pIndices = frameMeshData->GetIndices();
		// Iterate through indices and assign them to the array
		for (std::size_t i = 0; i < md->MeshIndices.Num(); ++i)
		{
			md->MeshIndices[i] = pIndices[i];
		}
	}

	if (pFrame->StreamContainsDataLayer(Mvx2API::BasicDataLayersGuids::VERTEX_NORMALS_DATA_LAYER()))
	{
		md->MeshNormals.SetNum(frameMeshData->GetNumNormals());
		float const* pNormals = frameMeshData->GetNormals();
		//Iterate through normals and assign them to the array
		for (std::size_t i = 0; i < md->MeshNormals.Num(); ++i)
		{
			const FVector v = FVector(pNormals[i * 3], pNormals[i * 3 + 1], pNormals[i * 3 + 2]);
			md->MeshNormals[i] = v;
		}

		const float invert = bInvertNormals ? -1 : 1;

		switch (NormalMode)
		{
		case EDNEVNormalMode::NM_DEFAULT:
			for (std::size_t i = 0; i < md->MeshNormals.Num(); ++i)
			{
				const float x = md->MeshNormals[i].X;
				const float y = md->MeshNormals[i].Y;
				const float z = md->MeshNormals[i].Z;

				md->MeshNormals[i].X = -z * invert;
				md->MeshNormals[i].Y = x * invert;
				md->MeshNormals[i].Z = y * invert;
			}
			break;
		case EDNEVNormalMode::NM_LEGACY2:
			for (std::size_t i = 0; i < md->MeshNormals.Num(); ++i)
			{
				const float x = md->MeshNormals[i].X;
				const float y = md->MeshNormals[i].Y;
				const float z = md->MeshNormals[i].Z;

				md->MeshNormals[i].X = -z * invert;
				md->MeshNormals[i].Y = -y * invert;
				md->MeshNormals[i].Z = x * invert;
			}
			break;
		case EDNEVNormalMode::NM_LEGACY1:
			for (std::size_t i = 0; i < md->MeshNormals.Num(); ++i)
			{
				const float x = md->MeshNormals[i].X;
				const float y = md->MeshNormals[i].Y;
				const float z = md->MeshNormals[i].Z;

				md->MeshNormals[i].X = z * invert;
				md->MeshNormals[i].Y = -y * invert;
				md->MeshNormals[i].Z = -x * invert;
			}
			break;
		}
	}

	if (pFrame->StreamContainsDataLayer(Mvx2API::BasicDataLayersGuids::VERTEX_UVS_DATA_LAYER()))
	{
		md->MeshUVs.SetNum(frameMeshData->GetNumUVs());
		float const* pData = frameMeshData->GetUVs();
		for (std::size_t i = 0; i < md->MeshUVs.Num(); ++i)
		{
			const FVector2D v = FVector2D(pData[i * 2], pData[i * 2 + 1]);
			md->MeshUVs[i] = v;
		}
	}

	delete frameMeshData;
}

void UDNEVMeshComponent::ExtractMeshTextureData()
{
	if (DataStream->textureSupported)
	{
		MeshData* md = RenderDataFlip[Activebuffer];

		bool TextureDataCopied = false;

		if (md->TextureData == nullptr)
			md->TextureData = new uint8[DataStream->texArraySize];

		// Extract data
		if (Mvx2API::FrameTextureExtractor::CopyTextureData(pFrame, DataStream->mvTexFormat, md->TextureData))
		{
			TextureDataCopied = true;
		}

		// If failed to copy data, then clear TextureData
		if (!TextureDataCopied)
		{
			md->TextureData = nullptr;
		}
	}
}

void UDNEVMeshComponent::UpdateRenderable()
{
	// Get frame data
	const MeshData* md = RenderDataFlip[Activebuffer];

	ProcMeshComponent->ClearAllMeshSections();

	ProcMeshComponent->CreateMeshSection(
		0,
		md->MeshVertices,
		md->MeshIndices,
		md->MeshNormals,
		md->MeshUVs,
		md->MeshVertexColors,
		md->MeshTangents,
		false
	);

	if (MaterialInstance != nullptr)
	{
		if (md->TextureData != nullptr &&
			md->Texture != nullptr)
		{
			UpdateTextureRegion = FUpdateTextureRegion2D(0, 0, 0, 0, DataStream->texWidth, DataStream->texHeight);

			md->Texture->UpdateTextureRegions(
				0,
				1,
				&UpdateTextureRegion,
				(uint32)(DataStream->bytesPerPixel * DataStream->texWidth),
				(uint32)DataStream->bytesPerPixel,
				md->TextureData);
			
			MaterialInstance->SetTextureParameterValue(FName(MaterialTextureName), md->Texture);

			if (md->Texture->GetPixelFormat() == PF_DXT1)
			{
				MaterialInstance->SetScalarParameterValue(FName(TEXT("TextureType")), 0);
			}
			else if (md->Texture->GetPixelFormat() == PF_A8)
			{
				MaterialInstance->SetScalarParameterValue(FName(TEXT("TextureType")), 1);
				MaterialInstance->SetScalarParameterValue(FName(TEXT("NV12TextureWidth")), md->Texture->GetSurfaceWidth());
				MaterialInstance->SetScalarParameterValue(FName(TEXT("NV12TextureHeight")), md->Texture->GetSurfaceHeight());
			}
		}

		ProcMeshComponent->SetMaterial(0, MaterialInstance);
	}
}

void UDNEVMeshComponent::CheckResources()
{
	// Create resources

	// TODO: handle when material is changed dynamically
	if (Material != nullptr &&
		MaterialInstance == nullptr)
	{
		MaterialInstance = UMaterialInstanceDynamic::Create(Material, this);
		MaterialInstance->AddToRoot();
	}

	if (DataStream != nullptr)
	{
		if (RenderDataFlip.Num() != 2)
		{
			RenderDataFlip.Add(new MeshData);
			RenderDataFlip.Add(new MeshData);

			if (DataStream->texWidth != 0 &&
				DataStream->texHeight != 0)
			{
				for (int i = 0; i < RenderDataFlip.Num(); i++)
				{
					MeshData* MD = RenderDataFlip[i];

					if (MD->Texture == nullptr)
					{
						// Create a dynamic texture
						MD->Texture = UTexture2D::CreateTransient(
							DataStream->texWidth,
							DataStream->texHeight,
							DataStream->pixelFormat
						);
						// Make sure it won't be compressed
						MD->Texture->CompressionSettings = TextureCompressionSettings::TC_VectorDisplacementmap;
						// Turn off Gamma-correction
						MD->Texture->SRGB = 0;
						// Update the texture with these new settings
						MD->Texture->UpdateResource();
						// Make sure it never gets garbage collected
						MD->Texture->AddToRoot();
					}
				}
			}
		}
	}
}

void UDNEVMeshComponent::ReleaseResources()
{
	// Reset variables
	RenderedFrameID = -1;

	if (DataStream)
	{
		DataStream->PlaybackStop();
		delete DataStream;
		DataStream = nullptr;
	}

	if (bIsWorking &&
		WorkingThread.IsValid())
	{
		bIsWorking = false;
		WorkingThread.Reset();
	}

	// Delete MaterialInstance
	if (MaterialInstance != nullptr)
	{
		MaterialInstance->RemoveFromRoot();
		MaterialInstance = nullptr;
	}
	
	// Delete RenderDataFlip
	for (int i = 0; i < RenderDataFlip.Num(); i++)
	{
		MeshData* MD = RenderDataFlip[i];

		if (MD->Texture != nullptr)
		{
			MD->Texture->RemoveFromRoot();
			MD->Texture = nullptr;
		}

		delete MD;
	}
	
	RenderDataFlip.Empty();
}

#if WITH_EDITOR

void UDNEVMeshComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	MarkRenderStateDirty();
	//FName PropertyName = (PropertyChangedEvent.Property != nullptr) ? PropertyChangedEvent.Property->GetFName() : NAME_None;
	Super::PostEditChangeProperty(PropertyChangedEvent);
}

#endif

void UDNEVMeshComponent::Play()
{
	if (DataStream)
		DataStream->PlaybackPlay();
}

void UDNEVMeshComponent::Pause()
{
	if (DataStream)
		DataStream->PlaybackStop();
}

void UDNEVMeshComponent::Seek(int32 frameID)
{
	if (DataStream)
		DataStream->PlaybackSeek(frameID);
}

bool UDNEVMeshComponent::IsPlaying() const
{
	if (DataStream)
		return DataStream->IsPlaying();

	return false;
}

void UDNEVMeshComponent::SetPlaybackMode(EPlaybackMode NewPlaybackMode)
{
	PlaybackMode = NewPlaybackMode;
}

void UDNEVMeshComponent::SetData(FString NewDataPath)
{
	ReleaseResources();
	ProcMeshComponent->ClearAllMeshSections();

	Data = NewDataPath;

	bool FileExists = false;
	FString FullDataPath;

	if (DoesFileExistInContentDirectory(Data))
	{
		FullDataPath = GetContentDNEVDataPath(Data);
		FileExists = true;
	}
	else if (DoesFileExist(Data))
	{
		FullDataPath = Data;
		FileExists = true;
	}
	else if (Data.StartsWith(FString("tcp")))
	{
		FullDataPath = Data;
		FileExists = true;
	}
	else
	{
		UE_LOG(LogDNEV, Log, TEXT("%s %s %s"), *FString(__FUNCTION__), *FString("Could not find data : "), *Data);
	}

	if (FileExists)
	{
		UE_LOG(LogDNEV, Log, TEXT("%s %s %s"), *FString(__FUNCTION__), *FString("Found Data : "), *FullDataPath);

		DataStream = new DNEVDataStream(std::string(TCHAR_TO_UTF8(*FullDataPath)));

		// Reset values
		RenderedFrameID = -1;

		if (DataStream->HasAudio())
		{
			DNEVAudioComponent->Init(DataStream->GetAudioNumSamplesPerSec(), DataStream->GetAudioNumChannels());
			DataStream->pDNEVAudioComponent = DNEVAudioComponent;
		}
	}
}

float UDNEVMeshComponent::GetDuration() const
{
	if (DataStream)
		return DataStream->GetDuration();

	return 0;
}

int32 UDNEVMeshComponent::GetFrameAtTime(const float Time) const
{
	const float FrameTime = GetNumberOfFrames() > 1 ? GetDuration() / static_cast<float>(GetNumberOfFrames() - 1) : 0.0f;
	const int32 NormalizedFrame = FMath::Clamp(FMath::RoundToInt(Time / FrameTime), 0, GetNumberOfFrames() - 1);
	return NormalizedFrame;
}

float UDNEVMeshComponent::GetTimeAtFrame(const int32 Frame) const
{
	const float FrameTime = GetNumberOfFrames() > 1 ? GetDuration() / static_cast<float>(GetNumberOfFrames() - 1) : 0.0f;
	return FMath::Clamp(FrameTime * (Frame), 0.0f, GetDuration());
}

int32 UDNEVMeshComponent::GetNumberOfFrames() const
{
	if (DataStream)
		return DataStream->GetNumFrames();

	return 0;
}

#if WITH_EDITOR
void UDNEVMeshComponent::PreEditUndo()
{
	//MarkRenderStateDirty();
}

void UDNEVMeshComponent::PostEditUndo()
{
	//MarkRenderStateDirty();
}
#endif

#undef LOCTEXT_NAMESPACE
