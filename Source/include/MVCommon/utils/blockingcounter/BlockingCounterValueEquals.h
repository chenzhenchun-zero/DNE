#pragma once

#include "IBlockingCounterCondition.h"

namespace MVCommon
{
  /// \brief A counter condition for checking equality of its value with a target value.
  class BlockingCounterValueEquals : public IBlockingCounterCondition
  {
  public:
    /// \brief A constructor.
    /// \param targetValue  a target value
    MVCOMMON_API BlockingCounterValueEquals(int32_t targetValue);
    
    /// \brief An operator executed for checking the condition with a value.
    /// \param value  a value the condition is checked with
    /// \returns      true in case the value is equal to the target value, false otherwise
    MVCOMMON_API virtual bool operator()(int32_t value) override;
    
    DECLARE_CLASS_SPECIFIC_NEW_DELETE(MVCOMMON_API)
  
  private:
    int32_t _targetValue;
  };
}
