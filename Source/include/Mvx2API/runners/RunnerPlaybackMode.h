/// \file
#pragma once

namespace Mvx2API
{
  /// \brief An enumeration of supported MVX stream playback modes.
  enum RunnerPlaybackMode
  {
    /// \brief A stream is only played once in a forward direction.
    RPM_FORWARD_ONCE = 0,
    /// \brief A stream is played in a loop in a forward direction.
    RPM_FORWARD_LOOP = 1,
    /// \brief A stream is only played once in a backward direction.
    RPM_BACKWARD_ONCE = 2,
    /// \brief A stream is played in a loop in a backward direction.
    RPM_BACKWARD_LOOP = 3,
    /// \brief A stream is played in a loop in the alternating directions (ping-pong), starting with the forward direction.
    RPM_PINGPONG = 4,
    /// \brief A stream is played in a loop in the alternating directions (ping-pong), starting with the backward direction.
    RPM_PINGPONG_INVERSE = 5,
    /// \brief A stream is played real-time as a 'live' data source produces frames.
    RPM_REALTIME = 255
  };
}