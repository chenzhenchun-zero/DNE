#pragma once

#include <MVCommon/MVCommonAPI.h>
#include <string>

namespace MVCommon
{
namespace concurrency
{
  class Thread
  {
  public:
    using Id = void *;

    MVCOMMON_API static Id getCurrentThreadId();
    MVCOMMON_API static void setCurrentThreadName(std::string const &name);
    MVCOMMON_API static std::size_t getCurrentThreadStackSize();
  };

} //namespace concurrency
} //namespace MVCommon
