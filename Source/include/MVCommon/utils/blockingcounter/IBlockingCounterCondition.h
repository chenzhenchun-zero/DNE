#pragma once

#include <MVCommon/MVCommonAPI.h>
#include <MVCommon/Memory.h>

namespace MVCommon
{
  /// \brief An interface of conditions usable with blocking counters.
  class IBlockingCounterCondition
  {
  public:
    /// \brief A destructor.
    MVCOMMON_API virtual ~IBlockingCounterCondition();

    /// \brief An operator executed for checking the condition with a value.
    /// \param value  a value the condition is checked with
    /// \returns      true in case the condition passes with the value, false otherwise
    MVCOMMON_API virtual bool operator()(int32_t value) = 0;
    
    DECLARE_CLASS_SPECIFIC_NEW_DELETE(MVCOMMON_API)
  };
}
