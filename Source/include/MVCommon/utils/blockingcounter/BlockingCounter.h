#pragma once

#include <MVCommon/MVCommonAPI.h>
#include <MVCommon/Memory.h>

namespace MVCommon
{
  class BlockingCounterImpl;
  class IBlockingCounterCondition;

  /// \brief A counter with a feature of blocking a thread until the counter has a specific value.
  class BlockingCounter : public NonAssignable
  {
  public:
    /// \brief A constructor.
    /// \param initialValue     an initial value of the counter
    /// \param waitersCountHint
    /// a hint about expected count of waiting threads - it allows an optimization of internal memory allocations made per each waiting call
    /// in cases when count of parallel waiters can be predicted. Special value `0` will result in allocations made every time, and `negative`
    /// hint value results in no deallocations (and thus maximum reusability of the memory) during the entire lifetime of the counter.
    MVCOMMON_API BlockingCounter(int32_t initialValue = 0, int32_t waitersCountHint = 1);
    /// \brief A destructor.
    MVCOMMON_API ~BlockingCounter();

    /// \brief Increments the counter by a given value.
    /// \param change a change to increase the counter's value by (may be negative)
    MVCOMMON_API void Increment(int32_t change = 1);

    /// \brief Gets current value of the counter.
    /// \returns  counter's value
    MVCOMMON_API int32_t Value() const;

    /// \brief Blocks current thread until the counter reaches given value.
    /// \param targetValue  a value the counter has to reach in order to unblock the thread
    /// \returns            the target value
    MVCOMMON_API int32_t WaitUntilValue(int32_t targetValue) const;

    /// \brief Blocks current thread until the counter reaches given value or until a timeout expires.
    /// \param targetValue  a value the counter has to reach in order to unblock the thread
    /// \param milliseconds a timeout (in milliseconds) after which the current thread is unblocked at the latest
    /// \returns            the target value when the counter reaches it before the timeout expires, current counter's value otherwise
    MVCOMMON_API int32_t WaitUntilValueFor(int32_t targetValue, uint64_t milliseconds) const;

    /// \brief Blocks current thread until the counter's value is accepted by a condition.
    /// \param condition  a condition that must pass in order to unblock the thread
    /// \returns          the value which was accepted by the condition
    MVCOMMON_API int32_t WaitUntil(IBlockingCounterCondition & condition) const;

    /// \brief Blocks current thread until the counter's value is accepted by a condition or until a timeout expires.
    /// \param condition    a condition that must pass in order to unblock the thread
    /// \param milliseconds a timeout (in milliseconds) after which the current thread is unblocked at the latest
    /// \returns            the value accepted by the condition when the counter reaches it before the timeout expires, current counter's value otherwise
    MVCOMMON_API int32_t WaitUntilFor(IBlockingCounterCondition & condition, uint64_t milliseconds) const;

    /// \brief Increments the counter by a given value.
    /// \param change a change to increase the counter's value by (may be negative)
    /// \returns      this counter
    MVCOMMON_API BlockingCounter & operator+=(int32_t change);

    DECLARE_CLASS_SPECIFIC_NEW_DELETE(MVCOMMON_API)

  private:
    BlockingCounterImpl * _pImpl;
  };
}
