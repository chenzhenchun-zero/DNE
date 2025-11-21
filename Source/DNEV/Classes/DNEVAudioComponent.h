#pragma once

#include "CoreMinimal.h"
#include "Misc/CoreMisc.h"
#include "Containers/Ticker.h"
#include "AudioDevice.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundWaveProcedural.h"

#include "DNEVAudioComponent.generated.h"

UCLASS(ClassGroup = (Common))
class DNEV_API UDNEVAudioComponent : public UAudioComponent
{
	GENERATED_UCLASS_BODY()

	//~ Begin UObject Interface
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;
	//~ End UObject Interface

	//~ Begin UActorComponent Interface.
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	//~ End UActorComponent Interface.

public:

	/** First time initialization of all components */
	bool Init(int32 InSampleRate, int32 InChannels);

	/** Add new data */
	void AddData(const uint8* VoiceDataPtr, uint32 VoiceDataSize);

	/** Internal reference to audio component's streaming wave object */
	USoundWaveProcedural* SoundStreaming;

private:

	/** Buffer for audio data (valid during Tick only) */
	TArray<uint8> Data;
	/** Maximum size of a single decoded packet */
	int32 MaxDataSize;

	/** Buffer for outgoing audio intended for procedural streaming */
	mutable FCriticalSection QueueLock;
	TArray<uint8> DataQueue;
	/** Amount of data currently in the outgoing playback queue */
	int32 CurrentDataQueueSize;
	/** Maximum size of the outgoing playback queue */
	int32 MaxDataQueueSize;

	/** Name of current device under capture */
	FString DeviceName;
	/** Desired output sample rate */
	int32 SampleRate;
	/** Desired number of output channels */
	int32 Channels;
	/** Is Active */
	bool bIsActive;

	/** Cleanup and shutdown the entire object */
	void Shutdown();

	/**
	 * Callback from streaming audio when data is requested for playback
	 *
	 * @param InProceduralWave SoundWave requesting more data
	 * @param SamplesRequired number of samples needed for immediate playback
	 */
	void GenerateData(USoundWaveProcedural* InProceduralWave, int32 SamplesRequired);
};
