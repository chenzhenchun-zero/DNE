#pragma once

#include <Mvx2API/Mvx2API.h>
#include <MVCommon/Memory.h>

namespace Mvx2API
{
  struct InputEventImpl;

  /// \brief An input event structure.
  struct InputEvent
  {
  protected:
    /// \brief A constructor.
    MVX2_API InputEvent();

  public:
    /// \brief A destructor.
    MVX2_API virtual ~InputEvent();

    /// \cond
    virtual InputEventImpl* GetImpl() const = 0;
    /// \endcond

    DECLARE_CLASS_SPECIFIC_NEW_DELETE(MVX2_API)
  };
}