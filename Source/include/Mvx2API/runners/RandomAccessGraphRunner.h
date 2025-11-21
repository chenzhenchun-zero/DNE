#pragma once

#include <Mvx2API/Mvx2API.h>
#include <Mvx2API/core/GraphRunner.h>

namespace Mvx2API
{
  class RandomAccessGraphRunnerImpl;
  class Graph;

  /// \brief A random-access runner of data-processing graphs.
  class RandomAccessGraphRunner : public GraphRunner
  {
  public:
    /// \brief A constructor.
    /// \param graph  a graph to create the runner for
    MVX2_API RandomAccessGraphRunner(Graph * graph);
    /// \brief A destructor.
    MVX2_API virtual ~RandomAccessGraphRunner();

    /// \brief Processes a frame with the given ID.
    /// \param frameID  an ID of the frame to process
    /// \returns        true if no error occured during the processing
    MVX2_API bool ProcessFrame(uint32_t frameID);

    MVX2_API virtual SourceInfo * GetSourceInfo() const override;

    DECLARE_CLASS_SPECIFIC_NEW_DELETE(MVX2_API)

  private:
    RandomAccessGraphRunnerImpl * _pImpl;
  };
}