#pragma once

#include <MVCommon/MVCommonAPI.h>

namespace MVCommon
{
namespace concurrency
{
  template <typename T> struct BarrierYielder;

  template <typename T>
  class Barrier
  {
  public:

    using Yielder = BarrierYielder<T>;

    Barrier()
      : m_Count(0)
      , m_Generation(0)
      , m_Participants(0)
    {
    }

    void participate()
    {
      m_Participants++;
      m_Count++;
    }

    void leave()
    {
      if(!m_Participants)
      {
        throw std::system_error(
          std::make_error_code(std::errc::operation_not_permitted),
          "Barrier: can't leave, not participating!"
        );
      }

      m_Participants--;
      
      if(m_Count)
      {
        if(!--m_Count)
        {
          m_Generation++;
          m_Count = m_Participants;
        }
      }
    }

    void arriveAndWait()
    {
      if(!m_Count)
      {
        throw std::system_error(
          std::make_error_code(std::errc::operation_not_permitted),
          "Barrier: already arrived or no participants!"
        );
      }

      std::size_t gen = m_Generation.load();
      
      if(--m_Count == 0)
      {
        if(m_Generation.compare_exchange_weak(gen, gen + 1))
        {
          m_Count = m_Participants;
        }
        return;
      }
      
      while((gen == m_Generation) && m_Count != 0)
        Yielder::yield();
    }

    class Participation
    {
    public:
      Participation() = delete;

      Participation(Barrier &barrier)
        : m_Barrier(&barrier)
        , m_Parent(nullptr)
      {
        m_Barrier->participate();
      }

      Participation(Participation &parent)
        : m_Barrier(&parent.m_Barrier)
        , m_Parent(&parent)
      {
      }

      Participation(Participation &&that)
        : m_Barrier(nullptr)
        , m_Parent(nullptr)
      {
        std::swap(m_Barrier, that.m_Barrier);
        std::swap(m_Parent, that.m_Parent);
      }

      ~Participation()
      {
        if(m_Barrier && !m_Parent) m_Barrier->leave();
      }

      void arriveAndWait()
      {
        if(m_Barrier)
          m_Barrier->arriveAndWait();
      }

    private:
      Barrier                     *m_Barrier;
      Participation               *m_Parent;
    };
  
  private:
    std::atomic<std::size_t>       m_Count;
    std::atomic<std::size_t>       m_Generation;
    std::size_t                    m_Participants;
  };

} //namespace concurrency
} //namespace MVCommon
