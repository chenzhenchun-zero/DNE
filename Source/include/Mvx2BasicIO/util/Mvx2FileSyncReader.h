#pragma once

#include <Mvx2BasicIO/Mvx2BasicIO.h>
#include <MVCommon/Memory.h>

#include <Mvx2API/core/Graph.h>
#include <Mvx2API/core/ManualGraphBuilder.h>
#include <Mvx2API/runners/ManualSequentialGraphRunner.h>
#include <Mvx2BasicIO/graphnodes/Mvx2FileReaderGraphNode.h>
#include <Mvx2API/graphnodes/AutoDecompressorGraphNode.h>
#include <Mvx2API/frameaccess/FrameAccessGraphNode.h>

namespace Mvx2BasicIO
{
  /// \brief A sequential reader of MVX2 files with a synchronous access to processed frames.
  class Mvx2FileSyncReader : private NonAssignable
  {
  public:
    /// \brief A constructor.
    /// \param filePath     a path of the MVX2 file to read
    /// \param playbackMode a playback mode of the reading
    /// \exception std::runtime_error raised in case the internal graph could not be created
    MVX2BASICIO_API Mvx2FileSyncReader(MVCommon::String const & filePath, Mvx2API::RunnerPlaybackMode playbackMode);
    /// \brief A destructor.
    MVX2BASICIO_API ~Mvx2FileSyncReader();

    /// \brief Reads next frame from the file.
    /// \returns  next processed frame or nullptr if there is none
    MVX2BASICIO_API Mvx2API::Frame * ReadNextFrame();
    
  private:
    Mvx2API::ManualSequentialGraphRunner * _pGraphRunner;
    Mvx2API::FrameAccessGraphNode * _pFrameAccessGraphNode;
  };

  inline Mvx2FileSyncReader::Mvx2FileSyncReader(MVCommon::String const & filePath, Mvx2API::RunnerPlaybackMode playbackMode)
    : _pFrameAccessGraphNode(new Mvx2API::FrameAccessGraphNode())
  {
    Mvx2API::ManualGraphBuilder graphBuilder;
    graphBuilder << Mvx2FileReaderGraphNode(filePath) << Mvx2API::AutoDecompressorGraphNode() << *_pFrameAccessGraphNode;
    Mvx2API::Graph * graph = graphBuilder.CompileGraphAndReset();

    if (graph)
    {
      _pGraphRunner = new Mvx2API::ManualSequentialGraphRunner(graph);
      _pGraphRunner->RestartWithPlaybackMode(playbackMode);
      delete graph;
    }
  }

  inline Mvx2FileSyncReader::~Mvx2FileSyncReader()
  {
    if (_pGraphRunner)
      delete _pGraphRunner;

    if (_pFrameAccessGraphNode)
      delete _pFrameAccessGraphNode;
  }

  inline Mvx2API::Frame * Mvx2FileSyncReader::ReadNextFrame()
  {
    if (!_pGraphRunner)
      return nullptr;

    if (!_pGraphRunner->ProcessNextFrame())
      return nullptr;

    return _pFrameAccessGraphNode->GetRecentProcessedFrame();
  }
}