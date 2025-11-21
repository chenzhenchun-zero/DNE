// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "DNEVAudioComponent.h"
#include "Utils.h"
#include "DNEVPrivatePCH.h"

#if !UE_BUILD_SHIPPING
#define VOICE_BUFFER_CHECK(Buffer, Size) \
	check(Buffer.Num() >= (int32)(Size))
#else
#define VOICE_BUFFER_CHECK(Buffer, Size)
#endif

UDNEVAudioComponent::UDNEVAudioComponent(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer),
	SoundStreaming(nullptr),
	MaxDataSize(0),
	CurrentDataQueueSize(0),
	MaxDataQueueSize(0),
	SampleRate(0),
	Channels(0),
	bIsActive(false)
{
	PrimaryComponentTick.bStartWithTickEnabled = true;
	PrimaryComponentTick.bCanEverTick = true;
}

void UDNEVAudioComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UDNEVAudioComponent::BeginDestroy()
{
	Super::BeginDestroy();

	Shutdown();
}

bool UDNEVAudioComponent::Init(int32 InSampleRate, int32 InChannels)
{
	bIsActive = true;

	SampleRate = InSampleRate;
	Channels = InChannels;

	DeviceName = TEXT("DNEV Audio");

	// Approx 1 sec worth of data
	MaxDataSize = Channels * SampleRate * sizeof(uint16);

	Data.Empty(MaxDataSize);
	Data.AddUninitialized(MaxDataSize);

	MaxDataQueueSize = MaxDataSize * 5;
	{
		FScopeLock ScopeLock(&QueueLock);
		DataQueue.Empty(MaxDataQueueSize);
	}

	return true;
}

void UDNEVAudioComponent::Shutdown()
{
	bIsActive = false;

	this->Stop();
	this->SetSound(nullptr);

	Data.Empty();

	{
		FScopeLock ScopeLock(&QueueLock);
		DataQueue.Empty();
	}

	if (SoundStreaming != nullptr)
	{
		SoundStreaming->OnSoundWaveProceduralUnderflow.Unbind();
		SoundStreaming = nullptr;
	}
}

void UDNEVAudioComponent::GenerateData(USoundWaveProcedural* InProceduralWave, int32 SamplesRequired)
{
	FScopeLock ScopeLock(&QueueLock);

	const int32 SampleSize = sizeof(uint16) * Channels;

	CurrentDataQueueSize = DataQueue.Num();
	const int32 AvailableSamples = CurrentDataQueueSize / SampleSize;
	if (AvailableSamples >= SamplesRequired)
	{
		InProceduralWave->QueueAudio(DataQueue.GetData(), AvailableSamples * SampleSize);
		DataQueue.RemoveAt(0, AvailableSamples * SampleSize, false);
		CurrentDataQueueSize -= (AvailableSamples * SampleSize);
	}
}

void UDNEVAudioComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	QUICK_SCOPE_CYCLE_COUNTER(STAT_FDNEVAudio_Tick);

	if (bIsActive)
	{
		if (SoundStreaming == nullptr)
		{
			if (GEngine != nullptr)
			{
				if (FAudioDeviceHandle AudioDevice = GEngine->GetMainAudioDevice())
				{
					SoundStreaming = NewObject<USoundWaveProcedural>();
					SoundStreaming->SetSampleRate(SampleRate);
					SoundStreaming->NumChannels = Channels;
					SoundStreaming->Duration = INDEFINITELY_LOOPING_DURATION;
					SoundStreaming->SoundGroup = SOUNDGROUP_Default;
					SoundStreaming->bLooping = false;

					// Turn off async generation in old audio engine on mac.
#if PLATFORM_MAC
					if (!AudioDevice->IsAudioMixerEnabled())
					{
						SoundStreaming->bCanProcessAsync = false;
					}
					else
#endif // #if PLATFORM_MAC
					{
						SoundStreaming->bCanProcessAsync = true;
					}

					// Bind the GenerateData callback with FOnSoundWaveProceduralUnderflow object
					//SoundStreaming->OnSoundWaveProceduralUnderflow.BindUObject(this, &UDNEVAudioComponent::GenerateData);

					SetSound(SoundStreaming);
				}
			}
		}

		if (SoundStreaming)
		{
			FScopeLock ScopeLock(&QueueLock);

			if (CurrentDataQueueSize > MaxDataSize / 4)
			{
				CurrentDataQueueSize = 0;
				DataQueue.SetNum(0);
			}

			if (IsInGameMode(GetWorld()))
			{
				if (!IsPlaying() &&
					(CurrentDataQueueSize > 0))
				{
					UE_LOG(LogDNEV, Log, TEXT("Playback started"));
					this->Play();
				}
			}
		}
	}
}

void UDNEVAudioComponent::AddData(const uint8* AudioDataPtr, uint32 AudioDataSize)
{
	if (!bIsActive)
		return;

	if (AudioDataPtr && AudioDataSize > 0)
	{
		FScopeLock ScopeLock(&QueueLock);

		const int32 OldSize = DataQueue.Num();
		const int32 AmountToBuffer = (OldSize + static_cast<int32>(AudioDataSize));
		if (AmountToBuffer <= MaxDataQueueSize)
		{
			DataQueue.AddUninitialized(AudioDataSize);

			VOICE_BUFFER_CHECK(DataQueue, AmountToBuffer);
			FMemory::Memcpy(DataQueue.GetData() + OldSize, AudioDataPtr, AudioDataSize);
			CurrentDataQueueSize += AudioDataSize;
		}
		else
		{
			UE_LOG(LogDNEV, Warning, TEXT("DataQueue Overflow!"));
		}
	}
}
