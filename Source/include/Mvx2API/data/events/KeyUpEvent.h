#pragma once

#include "InputEvent.h"

namespace Mvx2API
{
  struct KeyEventImpl;

  /// \brief A 'key up' event.
  struct KeyUpEvent : public InputEvent
  {
  public:
    /// \brief A constructor.
    /// \param key  a value of key released
    MVX2_API KeyUpEvent(int32_t key);
    /// \brief A copy constructor.
    /// \param other  an event to make a copy of
    MVX2_API KeyUpEvent(KeyUpEvent const & other);
    /// \brief A move constructor.
    /// \param other  an event to move
    MVX2_API KeyUpEvent(KeyUpEvent && other);
    /// \brief A destructor.
    MVX2_API virtual ~KeyUpEvent();
    /// \cond
    MVX2_API KeyUpEvent & operator=(KeyUpEvent other);
    /// \endcond

    /// \cond
    virtual InputEventImpl* GetImpl() const override;
    /// \endcond

    DECLARE_CLASS_SPECIFIC_NEW_DELETE(MVX2_API)

  private:
    KeyEventImpl * _pImpl;
  };
}