#pragma once

#include <Mvx2BasicIO/Mvx2BasicIO.h>
#include <MVCommon/Memory.h>

#include <Mvx2API/core/Graph.h>
#include <Mvx2API/core/ManualGraphBuilder.h>
#include <Mvx2API/runners/RandomAccessGraphRunner.h>
#include <Mvx2BasicIO/graphnodes/Mvx2FileReaderGraphNode.h>
#include <Mvx2API/graphnodes/AutoDecompressorGraphNode.h>
#include <Mvx2API/frameaccess/FrameAccessGraphNode.h>

namespace Mvx2BasicIO
{
  /// \brief A sequential reader of MVX2 files with a random access to processed frames.
  class Mvx2FileRandomAccessReader : private NonAssignable
  {
  public:
    /// \brief A constructor.
    /// \param filePath a path of the MVX2 file to read
    /// \exception std::runtime_error raised in case the internal graph could not be created
    MVX2BASICIO_API Mvx2FileRandomAccessReader(MVCommon::String const & filePath);
    /// \brief A destructor.
    MVX2BASICIO_API ~Mvx2FileRandomAccessReader();

    /// \brief Reads a frame from the file.
    /// \param frameID  an ID of the frame to read
    /// \returns        a frame with the ID or nullptr if there is none
    MVX2BASICIO_API Mvx2API::Frame * ReadFrame(uint32_t frameID);
    
  private:
    Mvx2API::RandomAccessGraphRunner * _pGraphRunner;
    Mvx2API::FrameAccessGraphNode * _pFrameAccessGraphNode;
  };

  inline Mvx2FileRandomAccessReader::Mvx2FileRandomAccessReader(MVCommon::String const & filePath)
    : _pFrameAccessGraphNode(new Mvx2API::FrameAccessGraphNode())
  {
    Mvx2API::ManualGraphBuilder graphBuilder;
    graphBuilder << Mvx2FileReaderGraphNode(filePath) << Mvx2API::AutoDecompressorGraphNode() << *_pFrameAccessGraphNode;
    Mvx2API::Graph * graph = graphBuilder.CompileGraphAndReset();

    if (graph)
    {
      _pGraphRunner = new Mvx2API::RandomAccessGraphRunner(graph);
      delete graph;
    }
  }

  inline Mvx2FileRandomAccessReader::~Mvx2FileRandomAccessReader()
  {
    if (_pGraphRunner)
      delete _pGraphRunner;

    if (_pFrameAccessGraphNode)
      delete _pFrameAccessGraphNode;
  }

  inline Mvx2API::Frame * Mvx2FileRandomAccessReader::ReadFrame(uint32_t frameID)
  {
    if (!_pGraphRunner)
      return nullptr;

    if (!_pGraphRunner->ProcessFrame(frameID))
      return nullptr;

    return _pFrameAccessGraphNode->GetRecentProcessedFrame();
  }
}