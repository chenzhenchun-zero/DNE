#pragma once

#include <Mvx2API/Mvx2API.h>
#include <Mvx2API/core/GraphRunner.h>
#include "RunnerPlaybackMode.h"

namespace Mvx2API
{
  class ManualSequentialGraphRunnerImpl;
  class Graph;

  /// \brief A sequential runner of data-processing graphs with manual updates-invocation.
  class ManualSequentialGraphRunner : public GraphRunner
  {
  public:
    /// \brief A constructor.
    /// \param graph  a graph to create the runner for
    MVX2_API ManualSequentialGraphRunner(Graph * graph);
    /// \brief A destructor.
    MVX2_API virtual ~ManualSequentialGraphRunner();

    /// \brief Restarts the runner with a new playback mode.
    /// \param playbackMode a playback mode to restart with
    /// \returns            true if the playback mode was successfully changed
    MVX2_API bool RestartWithPlaybackMode(RunnerPlaybackMode playbackMode);
    /// \brief Processes a subsequent frame (depending on the current playback mode).
    /// \returns  true if no error occured during the processing
    MVX2_API bool ProcessNextFrame();
    /// \brief Sets a frame with a given ID as the next to be processed.
    /// \param frameID  an ID of the frame to be processed next
    MVX2_API void SeekFrame(uint32_t frameID);

    MVX2_API virtual SourceInfo * GetSourceInfo() const override;

    DECLARE_CLASS_SPECIFIC_NEW_DELETE(MVX2_API)

  private:
    ManualSequentialGraphRunnerImpl * _pImpl;
  };
}