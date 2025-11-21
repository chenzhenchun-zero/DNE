#pragma once

#include <Mvx2BasicIO/Mvx2BasicIO.h>
#include <MVCommon/Memory.h>

#include <Mvx2API/core/Graph.h>
#include <Mvx2API/core/ManualGraphBuilder.h>
#include <Mvx2API/runners/AutoSequentialGraphRunner.h>
#include <Mvx2BasicIO/graphnodes/Mvx2FileReaderGraphNode.h>
#include <Mvx2API/graphnodes/AutoDecompressorGraphNode.h>
#include <Mvx2API/frameaccess/AsyncFrameAccessGraphNode.h>
#include <Mvx2API/graphnodes/BlockFPSGraphNode.h>

namespace Mvx2API
{
  class FrameListener;
}

namespace Mvx2BasicIO
{
  /// \brief A sequential reader of MVX2 files with an asynchronous access to processed frames.
  class Mvx2FileAsyncReader : private NonAssignable
  {
  public:
    /// \brief A special framerate value indicating that the maximal possible framerate shall be used.
    static const float FPS_MAX;
    /// \brief A special framerate value indicating that the framerate of an open source shall be used.
    static const float FPS_FROM_SOURCE;
    /// \brief A special framerate value indicating that the half of the framerate of an open source shall be used.
    static const float FPS_HALF_FROM_SOURCE;
    /// \brief A special framerate value indicating that the double of the framerate of an open source shall be used.
    static const float FPS_DOUBLE_FROM_SOURCE;

    /// \brief A constructor.
    /// \param filePath       a path of the MVX2 file to read
    /// \param pFrameListener an asynchronous frames listener
    /// \param fps            a framerate to follow
    /// \exception std::runtime_error raised in case the internal graph could not be created
    MVX2BASICIO_API Mvx2FileAsyncReader(MVCommon::String const & filePath, Mvx2API::FrameListener * pFrameListener, float fps = -1.0f);
    /// \brief A destructor.
    MVX2BASICIO_API ~Mvx2FileAsyncReader();

    /// \brief Starts the file reading.
    /// \details Can be executed synchronously in case \p blockUntilStopped is set to true, or asynchronously when set to false.
    /// \param playbackMode       a playback mode of the reading
    /// \param blockUntilStopped  an indication whether to block the call until the reading is stopped implicitly
    /// \returns                  true if the file reading successfully started
    MVX2BASICIO_API bool Play(Mvx2API::RunnerPlaybackMode playbackMode, bool blockUntilStopped = false);
    /// \brief Stops the file reading.
    /// \returns  true if the file reading successfully stopped
    MVX2BASICIO_API bool Stop();

  private:
    Mvx2API::AutoSequentialGraphRunner * _pGraphRunner;
    Mvx2API::AsyncFrameAccessGraphNode * _pFrameAccessGraphNode;
  };

  const float Mvx2FileAsyncReader::FPS_MAX = 0.0f;
  const float Mvx2FileAsyncReader::FPS_FROM_SOURCE = -1.0f;
  const float Mvx2FileAsyncReader::FPS_HALF_FROM_SOURCE = -2.0f;
  const float Mvx2FileAsyncReader::FPS_DOUBLE_FROM_SOURCE = -3.0f;

  inline Mvx2FileAsyncReader::Mvx2FileAsyncReader(MVCommon::String const & filePath, Mvx2API::FrameListener * pFrameListener, float fps)
    : _pFrameAccessGraphNode(new Mvx2API::AsyncFrameAccessGraphNode(pFrameListener))
  {
    Mvx2API::ManualGraphBuilder graphBuilder;
    graphBuilder << Mvx2FileReaderGraphNode(filePath) 
      << Mvx2API::AutoDecompressorGraphNode() 
      << Mvx2API::BlockFPSGraphNode(3, fps, Mvx2API::BlockFPSGraphNode::FB_BLOCK_FRAMES)
      << *_pFrameAccessGraphNode;
    Mvx2API::Graph * graph = graphBuilder.CompileGraphAndReset();

    if (graph)
    {
      _pGraphRunner = new Mvx2API::AutoSequentialGraphRunner(graph);
      delete graph;
    }
  }

  inline Mvx2FileAsyncReader::~Mvx2FileAsyncReader()
  {
    if (_pGraphRunner)
      delete _pGraphRunner;

    if (_pFrameAccessGraphNode)
      delete _pFrameAccessGraphNode;
  }

  inline bool Mvx2FileAsyncReader::Play(Mvx2API::RunnerPlaybackMode playbackMode, bool blockUntilStopped)
  {
    return _pGraphRunner != nullptr ? _pGraphRunner->Play(playbackMode, blockUntilStopped) : false;
  }

  inline bool Mvx2FileAsyncReader::Stop()
  {
    return _pGraphRunner != nullptr ? _pGraphRunner->Stop() : false;
  }
}