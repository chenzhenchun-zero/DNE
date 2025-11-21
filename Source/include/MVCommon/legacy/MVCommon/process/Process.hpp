#pragma once

#include <MVCommon/MVCommonAPI.h>
#include <deque>
#include <string>


namespace MVCommon
{
namespace process
{
  class Process
  {
  public:
    using Id = std::uint64_t;
    static Id const INVALID_ID = static_cast<Id>(-1);

    MVCOMMON_API Process();
    MVCOMMON_API Process(Process const &that);
    MVCOMMON_API Process(Id pid);

    MVCOMMON_API bool                       operator==(Process const &rhs) const;

    MVCOMMON_API Id                         getId() const;
    MVCOMMON_API std::string                getPath() const;


    MVCOMMON_API bool                       isValid() const;
    MVCOMMON_API bool                       isRunning() const;
    MVCOMMON_API bool                       isSame(Process const &rhs) const;

    MVCOMMON_API bool                       terminate(bool force = false);
    
#ifdef ANDROID
    MVCOMMON_API bool                       isApp(); //true -> app, false -> cmd.
#endif

    MVCOMMON_API static Process             getCurrent();
    MVCOMMON_API static std::deque<Process> getAll();

  private:
    Id                                      m_Id;
  };

} //namespace process
} //namespace MVCommon
