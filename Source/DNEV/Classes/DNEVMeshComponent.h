#pragma once

#include "CoreMinimal.h"
#include "Async/Future.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "DNEVAudioComponent.h"
#include "DNEVDataStream.h"

#include <mutex>

#include "DNEVMeshComponent.generated.h"

UENUM(BlueprintType)
enum class EPlaybackMode : uint8
{
	/// \brief A stream is only played once in a forward direction.
	FORWARD_ONCE = 0		UMETA(DisplayName = "Forward Once"),
	/// \brief A stream is played in a loop in a forward direction.
	FORWARD_LOOP = 1		UMETA(DisplayName = "Forward Loop"),
	/// \brief A stream is only played once in a backward direction.
	BACKWARD_ONCE = 2		UMETA(DisplayName = "Backward Once"),
	/// \brief A stream is played in a loop in a backward direction.
	BACKWARD_LOOP = 3		UMETA(DisplayName = "Backward Loop"),
	/// \brief A stream is played in a loop in the alternating directions (ping-pong), starting with the forward direction.
	PINGPONG = 4			UMETA(DisplayName = "Pingpong"),
	/// \brief A stream is played in a loop in the alternating directions (ping-pong), starting with the backward direction.
	PINGPONG_INVERSE = 5	UMETA(DisplayName = "Pingpong Inverse"),
	/// \brief A stream is played real-time as a 'live' data source produces frames.
	REALTIME = 255			UMETA(DisplayName = "Realtime"),
};

UENUM(BlueprintType)
enum class EDNEVNormalMode : uint8
{
	NM_DEFAULT = 0			UMETA(DisplayName = "Default"),
	NM_LEGACY2 = 1			UMETA(DisplayName = "Legacy2"),
	NM_LEGACY1 = 2			UMETA(DisplayName = "Legacy1"),
};

UCLASS(ClassGroup = (Rendering, Common), hidecategories = (Object, LOD), meta = (BlueprintSpawnableComponent))
class DNEV_API UDNEVMeshComponent : public UPrimitiveComponent
{
	GENERATED_UCLASS_BODY()

	//~ Begin UObject Interface
	virtual void BeginDestroy() override;
#if WITH_EDITOR
	virtual void PreEditUndo() override;
	virtual void PostEditUndo() override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif // WITH_EDITOR
	//~ End UObject Interface

	//~ Begin UActorComponent Interface.
	virtual void OnRegister() override;
	virtual void OnUnregister() override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	//~ End UActorComponent Interface.

public:

	/** Start playback of DNEV */
	UFUNCTION(BlueprintCallable, Category = "DNEV")
	void Play();

	/** Pause playback of DNEV */
	UFUNCTION(BlueprintCallable, Category = "DNEV")
	void Pause();

	/** Seek playback of DNEV */
	UFUNCTION(BlueprintCallable, Category = "DNEV")
	void Seek(int32 frameID);

	/** Get whether this DNEV is playing or not. */
	UFUNCTION(BlueprintCallable, Category = "DNEV")
	bool IsPlaying() const;

	/** Get Playback mode. */
	UFUNCTION(BlueprintCallable, Category = "DNEV")
	EPlaybackMode GetPlaybackMode() { return PlaybackMode; }

	/** Set Playback mode. */
	UFUNCTION(BlueprintCallable, Category = "DNEV")
	void SetPlaybackMode(EPlaybackMode NewPlaybackMode);

	/** Get data path. */
	UFUNCTION(BlueprintCallable, Category = "DNEV")
	FString GetDataPath() { return Data; }

	/** Set data path. */
	UFUNCTION(BlueprintCallable, Category = "DNEV")
	void SetData(FString NewDataPath);

	/** Get the duration of the playback */
	UFUNCTION(BlueprintCallable, Category = "DNEV")
	float GetDuration() const;

	/** Get the number of frames */
	UFUNCTION(BlueprintCallable, Category = "DNEV")
	int32 GetNumberOfFrames() const;

	UPROPERTY()
	bool bIsWorking;


public:

	/** Helper to get the frame of the stream at this time*/
	UFUNCTION(BlueprintCallable, Category = "DNEV")
	int32 GetFrameAtTime(const float Time) const;

	/** Helper to get the time at this frame */
	UFUNCTION(BlueprintCallable, Category = "DNEV")
	float GetTimeAtFrame(const int32 Frame) const;

public:

	UFUNCTION(BlueprintCallable, Category = "DNEV")
	int GetRenderedFrameID() { return RenderedFrameID; }

	void CheckDataStream();
	
	UFUNCTION(BlueprintCallable, Category = "DNEV")
	void ManualSeek(const int32 Frame);

	void ExtractMeshVertexData();
	void ExtractMeshTextureData();
	void UpdateRenderable();

private:

	void CheckResources();

	/** ReleaseResources, clears and removes data stored/copied from DNEV instance */
	void ReleaseResources();

	UMaterialInstanceDynamic* MaterialInstance;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DNEV")
	FString Data;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DNEV")
	FString MaterialTextureName;

	UPROPERTY(EditAnywhere, Interp, Category = "DNEV")
	EPlaybackMode PlaybackMode;

	UPROPERTY(EditAnywhere, Interp, Category = "DNEV")
	bool bPlayOnStart;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DNEV")
	UMaterialInterface* Material;

	UPROPERTY(EditAnywhere, Interp, Category = "DNEV|Options")
	bool bInvertNormals;

	UPROPERTY(EditAnywhere, Interp, Category = "DNEV|Options")
	EDNEVNormalMode NormalMode;

	class MeshData
	{
	public:

		TArray<FVector> MeshVertices;
		TArray<FColor> MeshVertexColors;
		TArray<FVector> MeshNormals;
		TArray<FVector2D> MeshUVs;
		TArray<int32> MeshIndices;
		TArray<FProcMeshTangent> MeshTangents;

		uint8* TextureData;
		UTexture2D* Texture;

		MeshData()
		{
			MeshVertices.Empty();
			MeshVertexColors.Empty();
			MeshNormals.Empty();
			MeshUVs.Empty();
			MeshVertices.Empty();
			MeshTangents.Empty();

			TextureData = nullptr;
			Texture = nullptr;
		}
	};

	TArray<MeshData*> RenderDataFlip;
	
	TFuture<void> WorkingThread;

	/**DNEV instance referenced by the component */
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DNEV")
	DNEVDataStream* DataStream;

	UProceduralMeshComponent* ProcMeshComponent;

	UPROPERTY(VisibleAnywhere, Category = "DNEV", BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UDNEVAudioComponent* DNEVAudioComponent;

	FUpdateTextureRegion2D UpdateTextureRegion;

	uint32_t RenderedFrameID = -1;

	uint32_t Activebuffer = 0;

	Mvx2API::Frame* pFrame;
};
