#pragma once

#include <list>
#include <mutex>
#include <algorithm>

namespace MVCommon
{
namespace signali
{
  template <typename T>
  class Delegate
  {
  protected:
    using ThisType = Delegate<T>;
    using Subscribers = std::list<T*>;

  public:
    Delegate()
      : m_Mutex()
      , m_Subscribers()
    {
    }

    virtual ~Delegate()
    {
    }

    void operator+=(T *sub)
    {
      add(sub);
    }

    void operator-=(T *sub)
    {
      remove(sub);
    }

    template <typename Method, typename ...Args>
    void call(Method method, Args &&... args)
    {
      Subscribers subscribers;
      {
        std::lock_guard<std::recursive_mutex> lock(m_Mutex);
        subscribers = m_Subscribers;
      }

      for(auto sub : subscribers)
      {
        (sub->*method)(args...);
      };
    }

  private:
    void add(T *sub)
    {
      std::lock_guard<std::recursive_mutex> lock(m_Mutex);
      m_Subscribers.emplace_front(sub);
    }

    void remove(T *sub)
    {
      std::lock_guard<std::recursive_mutex> lock(m_Mutex);
      typename Subscribers::iterator itSubscriber = std::find_if(
        m_Subscribers.begin(),
        m_Subscribers.end(),
        [sub](T *t) -> bool
      {
        return t == sub;
      });

      if(itSubscriber != m_Subscribers.end())
        m_Subscribers.erase(itSubscriber);
    }

    mutable std::recursive_mutex m_Mutex;
    mutable Subscribers m_Subscribers;
  };

} //namespace signali
} //namespace MVCommon