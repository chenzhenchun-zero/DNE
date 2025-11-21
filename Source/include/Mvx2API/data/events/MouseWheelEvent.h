#pragma once

#include "InputEvent.h"

namespace Mvx2API
{
  struct MouseWheelEventImpl;

  /// \brief A 'mouse wheel' event.
  struct MouseWheelEvent : public InputEvent
  {
  public:
    /// \brief A constructor.
    /// \param delta  a delta value representing mouse wheel movement
    /// \param x      an x-coordinate of mouse during the event
    /// \param y      an y-coordinate of mouse during the event
    MVX2_API MouseWheelEvent(float delta, int32_t x, int32_t y);
    /// \brief A copy constructor.
    /// \param other  an event to make a copy of
    MVX2_API MouseWheelEvent(MouseWheelEvent const & other);
    /// \brief A move constructor.
    /// \param other  an event to move
    MVX2_API MouseWheelEvent(MouseWheelEvent && other);
    /// \brief A destructor.
    MVX2_API virtual ~MouseWheelEvent();
    /// \cond
    MVX2_API MouseWheelEvent & operator=(MouseWheelEvent other);
    /// \endcond

    /// \cond
    virtual InputEventImpl* GetImpl() const override;
    /// \endcond

    DECLARE_CLASS_SPECIFIC_NEW_DELETE(MVX2_API)

  private:
    MouseWheelEventImpl * _pImpl;
  };
}