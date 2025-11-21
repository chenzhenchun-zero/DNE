#pragma once

#include <Mvx2API/Mvx2API.h>
#include <MVCommon/Memory.h>

#include "Frame.h"

namespace Mvx2API
{
  class Frame;

  /// \brief A listener for asynchronous reception of frames.
  class FrameListener : private NonAssignable
  {
  public:
    /// \brief A destructor.
    MVX2_API virtual ~FrameListener();

    /// \brief A callback executed when a new frame is processed.
    /// \param pFrame a new frame (it is a responsibility of the client to dispose it)
    MVX2_API virtual void OnFrameProcessed(Frame* pFrame) = 0;

    DECLARE_CLASS_SPECIFIC_NEW_DELETE(MVX2_API)
  };
}
