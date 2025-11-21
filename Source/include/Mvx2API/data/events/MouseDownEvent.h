#pragma once

#include "InputEvent.h"

namespace Mvx2API
{
  struct MouseButtonEventImpl;

  /// \brief A 'mouse down' event.
  struct MouseDownEvent : public InputEvent
  {
  public:
    /// \brief A constructor.
    /// \param button a mouse button pressed down
    /// \param x      an x-coordinate of mouse during the event
    /// \param y      an y-coordinate of mouse during the event
    MVX2_API MouseDownEvent(int32_t button, int32_t x, int32_t y);
    /// \brief A copy constructor.
    /// \param other  an event to make a copy of
    MVX2_API MouseDownEvent(MouseDownEvent const & other);
    /// \brief A move constructor.
    /// \param other  an event to move
    MVX2_API MouseDownEvent(MouseDownEvent && other);
    /// \brief A destructor.
    MVX2_API virtual ~MouseDownEvent();
    /// \cond
    MVX2_API MouseDownEvent & operator=(MouseDownEvent other);
    /// \endcond

    /// \cond
    virtual InputEventImpl* GetImpl() const override;
    /// \endcond

    DECLARE_CLASS_SPECIFIC_NEW_DELETE(MVX2_API)

  private:
    MouseButtonEventImpl * _pImpl;
  };
}