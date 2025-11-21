/// \file
#pragma once

namespace Mvx2API
{
  /// \brief An enumeration of runner playback states.
  enum RunnerPlaybackState
  {
    /// \brief A runner is stopped.
    RPS_Stopped = 0,
    /// \brief A runner is running and is paused.
    RPS_Paused,
    /// \brief A runner is running and playing.
    RPS_Playing
  };
}