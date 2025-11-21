#pragma once

#include "InputEvent.h"

namespace Mvx2API
{
  struct MouseMoveEventImpl;

  /// \brief A 'mouse move' event.
  struct MouseMoveEvent : public InputEvent
  {
  public:
    /// \brief A constructor.
    /// \param x  an x-coordinate of mouse during the event
    /// \param y  an y-coordinate of mouse during the event
    MVX2_API MouseMoveEvent(int32_t x, int32_t y);
    /// \brief A copy constructor.
    /// \param other  an event to make a copy of
    MVX2_API MouseMoveEvent(MouseMoveEvent const & other);
    /// \brief A move constructor.
    /// \param other  an event to move
    MVX2_API MouseMoveEvent(MouseMoveEvent && other);
    /// \brief A destructor.
    MVX2_API virtual ~MouseMoveEvent();
    /// \cond
    MVX2_API MouseMoveEvent & operator=(MouseMoveEvent other);
    /// \endcond

    /// \cond
    virtual InputEventImpl* GetImpl() const override;
    /// \endcond

    DECLARE_CLASS_SPECIFIC_NEW_DELETE(MVX2_API)

  private:
    MouseMoveEventImpl * _pImpl;
  };
}