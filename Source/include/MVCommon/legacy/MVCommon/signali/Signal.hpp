#pragma once

#include <MVCommon/MVCommonAPI.h>
#include <functional>
#include <list>
#include <mutex>
#include "Connection.hpp"
#include <list>

namespace MVCommon
{
namespace signali
{
  template <typename Signature>
  class Signal
  {
    using Slot = std::function<Signature>;
    using Slots = std::list<Slot>;
  
  public:
    Signal()
      : m_Mutex()
      , m_Slots()
    {

    }

    inline Connection connect(Slot &&slot) const
    {
      std::lock_guard<std::recursive_mutex> lock(m_Mutex);
      typename Slots::iterator iSlot = m_Slots.emplace(m_Slots.end(), std::forward<Slot>(slot));
      return Connection([this, iSlot]() -> void
      {
        std::lock_guard<std::recursive_mutex> lock(m_Mutex);
        m_Slots.erase(iSlot);
      });
    }

    template <typename ...Args>
    inline void operator()(Args &&... args)
    {
      Slots callingSlots;
      {
        std::lock_guard<std::recursive_mutex> lock(m_Mutex);
        callingSlots = m_Slots;
      }
      for (auto &slot : callingSlots)
        slot(args...);
    }
    
  private:
    mutable std::recursive_mutex m_Mutex;
    mutable Slots m_Slots;
  };

} //namespace signali
} //namespace MVCommon