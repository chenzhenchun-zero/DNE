#pragma once

#include "CoreMinimal.h"
#include "HAL/Runnable.h"
#include "HAL/RunnableThread.h"
#include "Misc/ScopeTryLock.h"

#include <Mvx2API/frameaccess/extractors/FrameAudioExtractor.h>
#include <Mvx2BasicIO/util/Mvx2FileBasicDataInfo.h>
#include <Mvx2API/frameaccess/AsyncFrameAccessGraphNode.h>
#include <Mvx2API/frameaccess/FrameAccessGraphNode.h>
#include <Mvx2API/frameaccess/FrameListener.h>
#include <Mvx2API/runners/AutoSequentialGraphRunner.h>
#include <Mvx2API/runners/ManualSequentialGraphRunner.h>
#include <Mvx2API/runners/RunnerPlaybackMode.h>
#include <Mvx2API/frameaccess/extractors/FrameTextureExtractor.h>
#include <Mvx2API/data/BasicDataLayersGuids.h>

#include "DNEVAudioComponent.h"

#include <chrono>
#include <functional>
#include <mutex>
#include <queue>
#include <string>
#include <vector>

namespace MVGraphAPI {
	class Frame;
};

class DNEVDataStream : public Mvx2API::FrameListener
{
public:

	DNEVDataStream(std::string const& InFilePath);
	virtual ~DNEVDataStream() override;

	virtual void OnFrameProcessed(Mvx2API::Frame* pNewFrame) override
	{
		if (pNewFrame != nullptr &&
			HasAudio())
		{
			uint32_t frameChannelsCount;
			uint32_t frameBitsPerSample;
			uint32_t frameSampleRate;
			Mvx2API::FrameAudioExtractor::GetAudioSamplingInfo(pNewFrame, frameChannelsCount, frameBitsPerSample, frameSampleRate);

			if (frameBitsPerSample == 8 || frameBitsPerSample == 16 || frameBitsPerSample == 32)
			{
				// Improvement - Change this to a callback which the DNEVAudioComponent subscribes to

				const uint32_t framePCMDataSize = Mvx2API::FrameAudioExtractor::GetPCMDataSize(pNewFrame);

				if (framePCMDataSize != 0)
				{
					uint32_t frameBytesPerSample = frameBitsPerSample / 8;
					uint8_t* frameAudioBytes = new uint8[framePCMDataSize];
					Mvx2API::FrameAudioExtractor::CopyPCMData(pNewFrame, frameAudioBytes);

					if (pDNEVAudioComponent != nullptr &&
						pDNEVAudioComponent->SoundStreaming)
					{
						pDNEVAudioComponent->SoundStreaming->QueueAudio(frameAudioBytes, framePCMDataSize);
					}

					delete[] frameAudioBytes;
				}
			}
		}

		FScopeTryLock Lock(&DataCritSec);

		if (Lock.IsLocked())
		{
			if (pFrameToProcess != nullptr)
			{
				delete pFrameToProcess;
				pFrameToProcess = nullptr;

			}
			
			if (pNewFrame != nullptr)
			{
				pFrameToProcess = pNewFrame;
				currentFrameID = pNewFrame->GetStreamAtomNr();
			}
		}
		else
		{
			if (pNewFrame != nullptr)
				delete pNewFrame;
		}
	}

	
private:



	bool bIsPlaying;

	std::string AssetDataPath;

	uint32_t AssetAudioNumChannels;
	uint32_t AssetAudioBitsPerSample;
	uint32_t AssetAudioNumSamplesPerSec;

	Mvx2BasicIO::Mvx2FileBasicDataInfo* dataInfo;

	TSharedPtr<Mvx2API::AsyncFrameAccessGraphNode> spAsyncFrameAccess;
	TSharedPtr<Mvx2API::AutoSequentialGraphRunner> spAutoGraphRunner;
	TSharedPtr<Mvx2API::SingleFilterGraphNode> h264Decompressor;
	TSharedPtr<Mvx2API::SingleFilterGraphNode> ryskDecompressor;

public:

	void PlaybackPlay();
	void PlaybackPause();
	void PlaybackStop();
	void PlaybackSeek(uint32_t frameID);
	Mvx2API::Frame* ManualSeek(uint32_t frameID) const;

	bool IsPlaying() const { return bIsPlaying; }
	uint32_t GetNumFrames() const { return dataInfo->GetNumFrames(); }
	float GetFPS() const { return dataInfo->GetFPS(); }
	float GetDuration() const { return dataInfo->GetNumFrames() / dataInfo->GetFPS(); }
	bool HasAudio() const { return dataInfo->HasAudio(); }
	uint32_t GetAudioNumChannels() const { return AssetAudioNumChannels; }
	uint32_t GetAudioNumSamplesPerSec() const { return AssetAudioNumSamplesPerSec; }
	uint32_t GetAssetAudioBitsPerSample() const { return AssetAudioBitsPerSample; }

	Mvx2API::RunnerPlaybackMode PlaybackMode;
	UDNEVAudioComponent* pDNEVAudioComponent;
	Mvx2API::Frame* pFrameToProcess;
	uint32_t currentFrameID;
	uint16_t texWidth;
	uint16_t texHeight;
	bool textureSupported;
	uint32 bytesPerPixel = 2;
	Mvx2API::FrameTextureExtractor::TextureType mvTexFormat;
	EPixelFormat pixelFormat;
	uint32_t texArraySize;

	mutable FCriticalSection DataCritSec;
};
