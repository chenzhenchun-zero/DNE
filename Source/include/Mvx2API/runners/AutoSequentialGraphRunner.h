#pragma once

#include <Mvx2API/Mvx2API.h>
#include <Mvx2API/core/GraphRunner.h>
#include "RunnerPlaybackMode.h"
#include "RunnerPlaybackState.h"

namespace Mvx2API
{
  class AutoSequentialGraphRunnerImpl;
  class Graph;

  /// \brief A sequential runner of data-processing graphs with automatic (synchronous/asynchronous) updates-invocation.
  class AutoSequentialGraphRunner : public GraphRunner
  {
  public:
    /// \brief A constructor.
    /// \param graph  a graph to create the runner for
    MVX2_API AutoSequentialGraphRunner(Graph * graph);
    /// \brief A destructor.
    MVX2_API virtual ~AutoSequentialGraphRunner();

    /// \brief Starts playback of the graph with a given playback mode.
    /// \details Can be executed synchronously in case \p blockUntilStopped is set to true, or asynchronously when set to false.
    /// \param playbackMode       a playback mode
    /// \param blockUntilStopped  an indication whether to block the call until the execution of the graph stops
    /// \returns                  true if the graph playback successfully started
    MVX2_API bool Play(RunnerPlaybackMode playbackMode, bool blockUntilStopped = false);
    /// \brief Invokes stopping of the graph playback.
    /// \details
    /// The function only invokes stopping of the graph playback, which means that the graph may not be stopped yet when
    /// the function returns (although in case of non-blocking playback, the playback will definitely be stopped when the
    /// function returns).
    /// \returns  true if the graph playback stopping successfully invoked
    MVX2_API bool Stop();
    /// \brief Pauses the graph playback.
    /// \returns  true if the graph playback successfully paused
    MVX2_API bool Pause();
    /// \brief Resumes the graph playback.
    /// \returns  true if the graph playback successfully resumed
    MVX2_API bool Resume();
    /// \brief Determines current playback state of the runner.
    /// \returns  playback state
    MVX2_API RunnerPlaybackState GetPlaybackState() const;

    /// \brief Sets a frame with a given ID as the next to be processed.
    /// \param frameID  an ID of the frame to be processed next
    MVX2_API void SeekFrame(uint32_t frameID);

    MVX2_API virtual SourceInfo * GetSourceInfo() const override;

    DECLARE_CLASS_SPECIFIC_NEW_DELETE(MVX2_API)

  private:
    AutoSequentialGraphRunnerImpl * _pImpl;
  };
}