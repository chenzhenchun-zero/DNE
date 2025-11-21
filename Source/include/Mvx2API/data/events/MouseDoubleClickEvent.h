#pragma once

#include "InputEvent.h"

namespace Mvx2API
{
  struct MouseButtonEventImpl;

  /// \brief A 'mouse double-click' event.
  struct MouseDoubleClickEvent : public InputEvent
  {
  public:
    /// \brief A constructor.
    /// \param button a mouse button double-clicked
    /// \param x      an x-coordinate of mouse during the event
    /// \param y      an y-coordinate of mouse during the event
    MVX2_API MouseDoubleClickEvent(int32_t button, int32_t x, int32_t y);
    /// \brief A copy constructor.
    /// \param other  an event to make a copy of
    MVX2_API MouseDoubleClickEvent(MouseDoubleClickEvent const & other);
    /// \brief A move constructor.
    /// \param other  an event to move
    MVX2_API MouseDoubleClickEvent(MouseDoubleClickEvent && other);
    /// \brief A destructor.
    MVX2_API virtual ~MouseDoubleClickEvent();
    /// \cond
    MVX2_API MouseDoubleClickEvent & operator=(MouseDoubleClickEvent other);
    /// \endcond

    /// \cond
    virtual InputEventImpl* GetImpl() const override;
    /// \endcond

    DECLARE_CLASS_SPECIFIC_NEW_DELETE(MVX2_API)

  private:
    MouseButtonEventImpl * _pImpl;
  };
}