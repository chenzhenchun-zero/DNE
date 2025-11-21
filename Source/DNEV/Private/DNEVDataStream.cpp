#include "DNEVDataStream.h"

#include "DNEVPrivatePCH.h"
#include "Utils.h"

#include <Mvx2API/frameaccess/extractors/FrameAudioExtractor.h>
#include <Mvx2API/graphnodes/AutoDecompressorGraphNode.h>
#include <Mvx2BasicIO/graphnodes/Mvx2FileReaderGraphNode.h>
#include <Mvx2BasicIO/util/Mvx2FileAsyncReader.h>
#include <Mvx2API/core/Graph.h>

#include <iomanip>
#include <memory>
#include <algorithm>
#include <mutex>

DNEVDataStream::DNEVDataStream(std::string const& InFilePath)
{
	bIsPlaying = false;
	pFrameToProcess = nullptr;
	pDNEVAudioComponent = nullptr;
	currentFrameID = -1;
	textureSupported = false;
	texWidth = 0;
	texHeight = 0;
	pixelFormat = EPixelFormat::PF_Unknown;
	mvTexFormat = Mvx2API::FrameTextureExtractor::TT_IR;
	bytesPerPixel = 0;

	AssetDataPath = InFilePath;
	PlaybackMode = Mvx2API::RunnerPlaybackMode::RPM_FORWARD_ONCE;

	dataInfo = new Mvx2BasicIO::Mvx2FileBasicDataInfo(AssetDataPath.c_str());

	if (dataInfo->HasAudio())
	{
		Mvx2API::Frame* firstFrame = dataInfo->GetFirstFrame();
		Mvx2API::FrameAudioExtractor::GetAudioSamplingInfo(firstFrame, AssetAudioNumChannels, AssetAudioBitsPerSample, AssetAudioNumSamplesPerSec);
		delete firstFrame;
	}

	Mvx2API::Frame* tempFrame = ManualSeek(0);

	if (tempFrame->StreamContainsDataLayer(Mvx2API::BasicDataLayersGuids::DXT1_TEXTURE_DATA_LAYER()))
	{
		textureSupported = true;
		mvTexFormat = Mvx2API::FrameTextureExtractor::TT_DXT1;
		pixelFormat = PF_DXT1;
		bytesPerPixel = 2;
	}
	 else if (tempFrame->StreamContainsDataLayer(Mvx2API::BasicDataLayersGuids::NV12_TEXTURE_DATA_LAYER()))
	 {
	 	textureSupported = true;
	 	mvTexFormat = Mvx2API::FrameTextureExtractor::TT_NV12;
	 	pixelFormat = PF_A8;
	 	bytesPerPixel = 1;
	 }
	 else
	{
		UE_LOG(LogDNEV, Warning, TEXT("Unsupported texture format!"));
	}

	if (textureSupported)
	{
		if (Mvx2API::FrameTextureExtractor::GetTextureResolution(tempFrame, mvTexFormat, texWidth, texHeight))
			texArraySize = texWidth * texHeight * bytesPerPixel;
	}

	delete tempFrame;

	const uint32_t BUFFER_SIZE = 3;

	h264Decompressor = MakeShareable(new Mvx2API::SingleFilterGraphNode(MVCommon::Guid::FromHexString("57A38625-A0DD-46C3-B030-51B044301E45"), true));
	ryskDecompressor = MakeShareable(new Mvx2API::SingleFilterGraphNode(MVCommon::Guid::FromHexString("D52FE894-0CCE-41CE-831F-88D28CA06793"), true));

	// bool dropCompressedInput = true;
	// uint32_t startDecodingTimeout = 3000u;
	// uint32_t decompressedAtomsBufferSizePerStream = 20;
	// const std::string DROP_COMPRESSED_INPUT = "Drop compressed data";
  	// const std::string DECOMPRESSED_ATOMS_BUFFER_SIZE = "Decompressed atoms buffer size per stream";
  	// const std::string START_DECODING_TIMEOUT = "Start decoding timeout";
	// h264Decompressor->SetFilterParameterValue(DROP_COMPRESSED_INPUT.c_str(), dropCompressedInput ? "true" : "false");
	// h264Decompressor->SetFilterParameterValue(DECOMPRESSED_ATOMS_BUFFER_SIZE.c_str(), std::to_string(decompressedAtomsBufferSizePerStream).c_str());
	// h264Decompressor->SetFilterParameterValue(START_DECODING_TIMEOUT.c_str(), std::to_string(startDecodingTimeout).c_str());

  	// const std::string DROP_DECODED_LAYERS = "Drop decoded layers";
	// ryskDecompressor = MakeShareable(new Mvx2API::SingleFilterGraphNode(MVCommon::Guid::FromHexString("D52FE894-0CCE-41CE-831F-88D28CA06793"), true));
	// ryskDecompressor->SetFilterParameterValue(DROP_DECODED_LAYERS.c_str(), "true");

	Mvx2API::ManualGraphBuilder graphBuilder;
	spAsyncFrameAccess = MakeShareable(new Mvx2API::AsyncFrameAccessGraphNode(this));
	graphBuilder
		<< Mvx2BasicIO::Mvx2FileReaderGraphNode(AssetDataPath.c_str())
		<< Mvx2API::AutoDecompressorGraphNode()
		<< Mvx2API::BlockFPSGraphNode(BUFFER_SIZE, -1.0f, Mvx2API::BlockFPSGraphNode::FB_BLOCK_FRAMES)
		<< *h264Decompressor
		<< *ryskDecompressor
		<< *spAsyncFrameAccess;

	const TSharedPtr<Mvx2API::Graph> spGraph = MakeShareable(graphBuilder.CompileGraphAndReset());

	spAutoGraphRunner = MakeShareable(new Mvx2API::AutoSequentialGraphRunner(spGraph.Get()));
}

DNEVDataStream::~DNEVDataStream()
{
	spAutoGraphRunner->Stop();

	spAutoGraphRunner = nullptr;
	spAsyncFrameAccess = nullptr;

	if (pFrameToProcess != nullptr)
	{
		delete pFrameToProcess;
		pFrameToProcess = nullptr;
	}

	delete dataInfo;
}

void DNEVDataStream::PlaybackPlay()
{
	bIsPlaying = true;
	spAutoGraphRunner->Play(PlaybackMode, false);
}

void DNEVDataStream::PlaybackPause()
{
	bIsPlaying = false;
	spAutoGraphRunner->Pause();
}

void DNEVDataStream::PlaybackStop()
{
	bIsPlaying = false;
	spAutoGraphRunner->Stop();
}

void DNEVDataStream::PlaybackSeek(uint32_t frameID)
{
	spAutoGraphRunner->SeekFrame(frameID);
}

Mvx2API::Frame* DNEVDataStream::ManualSeek(uint32_t frameID) const
{
	const TSharedPtr<Mvx2API::SingleFilterGraphNode> h264Decompressor2 = MakeShareable(new Mvx2API::SingleFilterGraphNode(MVCommon::Guid::FromHexString("57A38625-A0DD-46C3-B030-51B044301E45"), true));
	const TSharedPtr<Mvx2API::SingleFilterGraphNode> ryskDecompressor2 = MakeShareable(new Mvx2API::SingleFilterGraphNode(MVCommon::Guid::FromHexString("D52FE894-0CCE-41CE-831F-88D28CA06793"), true));

	Mvx2API::ManualGraphBuilder graphBuilder;
	const TSharedPtr<Mvx2API::FrameAccessGraphNode> spFrameAccess = MakeShareable(new Mvx2API::FrameAccessGraphNode());
	graphBuilder
		<< Mvx2BasicIO::Mvx2FileReaderGraphNode(AssetDataPath.c_str())
		<< Mvx2API::AutoDecompressorGraphNode()
		<< *h264Decompressor2
		<< *ryskDecompressor2
		<< *spFrameAccess.Get();

	const TSharedPtr<Mvx2API::Graph> spGraph = MakeShareable(graphBuilder.CompileGraphAndReset());
	const TSharedPtr<Mvx2API::ManualSequentialGraphRunner> spGraphRunner = MakeShareable(new Mvx2API::ManualSequentialGraphRunner(spGraph.Get()));
	spGraphRunner->SeekFrame(frameID);
	spGraphRunner->ProcessNextFrame();
	return spFrameAccess->GetRecentProcessedFrame();
}
