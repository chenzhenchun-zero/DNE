#pragma once

#include "InputEvent.h"

namespace Mvx2API
{
  struct KeyEventImpl;
  
  /// \brief A 'key down' event.
  struct KeyDownEvent : public InputEvent
  {
  public:
    /// \brief A constructor.
    /// \param key  a value of key pressed down
    MVX2_API KeyDownEvent(int32_t key);
    /// \brief A copy constructor.
    /// \param other  an event to make a copy of
    MVX2_API KeyDownEvent(KeyDownEvent const & other);
    /// \brief A move constructor.
    /// \param other  an event to move
    MVX2_API KeyDownEvent(KeyDownEvent && other);
    /// \brief A destructor.
    MVX2_API virtual ~KeyDownEvent();
    /// \cond
    MVX2_API KeyDownEvent & operator=(KeyDownEvent other);
    /// \endcond

    /// \cond
    virtual InputEventImpl* GetImpl() const override;
    /// \endcond

    DECLARE_CLASS_SPECIFIC_NEW_DELETE(MVX2_API)

  private:
    KeyEventImpl * _pImpl;
  };
}