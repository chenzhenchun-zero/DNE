// --------------------------------------------------------------------
//    _________   _____________                                       
//   /     \   \ /   /\_   ___ \  ____   _____   _____   ____   ____  
//  /  \ /  \   Y   / /    \  \/ /  _ \ /     \ /     \ /  _ \ /    \
// /    Y    \     /  \     \___(  <_> )  Y Y  \  Y Y  (  <_> )   |  \
// \____|__  /\___/    \______  /\____/|__|_|  /__|_|  /\____/|___|  /
//         \/                 \/             \/      \/            \/ 
//
//          Mantis Vision Common Code Library
// --------------------------------------------------------------------
#pragma once

#include <cstdint>
#include <deque>
#include <thread>
#include <mutex>
#include <string>

#include <MVCommon/data/Color.h>

// don't call PROFILE_CPU in functions that are
// called by static initializers. that might cause the passed
// zone being yet uninitialized and thus having no valid
// profiler thread.

#define TOKENPASTE_DEF(x, y)                x##y
#define TOKENPASTE(x, y)                    TOKENPASTE_DEF(x, y)

#define PROFILER_CPU_THREAD_ADD(name)       if (MVCommon::Profiler::getManager()) MVCommon::Profiler::getManager()->addThisCpuThread(name)
#define PROFILER_CPU_THREAD_REMOVE()        if (MVCommon::Profiler::getManager()) MVCommon::Profiler::getManager()->removeThisCpuThread()
#define PROFILER_CPU_THREAD_FLIP()          if (MVCommon::Profiler::getManager()) MVCommon::Profiler::getManager()->getCpuThread()->flip()
#define PROFILER_CPU_SCOPE_ZONE(id, name)   static MVCommon::ProfilerZone TOKENPASTE(cpuZone, id)(name); MVCommon::ProfilerCpuScope TOKENPASTE(cpuScope, id)(TOKENPASTE(cpuZone, id))
#define PROFILE_CPU(name)                   PROFILER_CPU_SCOPE_ZONE(TOKENPASTE(__LINE__, __COUNTER__), name)
#define PROFILE_CPU_FUNC()                  PROFILE_CPU(__FUNCTION__)

#if defined(__linux__) || defined(__APPLE__)
#define __forceinline __attribute__((always_inline))
#endif

#ifdef _WIN32
#define thread_local  __declspec(thread)
#endif

namespace MVCommon
{  
  class ProfilerZone
  {
  public:
    MVCOMMON_API ProfilerZone(const std::string &name);

    MVCOMMON_API std::string          getName() const;
    MVCOMMON_API Color                getColor() const;

  private:
    std::string                       _name;
    Color                             _color;
  };

  class MVCOMMON_API ProfilerRecord
  {
  public:
    uint32_t                          getParentCount() const;

  public:
    const ProfilerZone *              Zone;
    uint64_t                          EnterTime;
    uint64_t                          LeaveTime;
    uint64_t                          SelfDuration;
    uint64_t                          TotalDuration;
    uint64_t                          TotalChildDuration;
    ProfilerRecord *                  Parent;
  };

  class IProfilerFrame
  {
  public:
    MVCOMMON_API IProfilerFrame();
    MVCOMMON_API virtual ~IProfilerFrame();

    MVCOMMON_API void                 clear();

  public:
    ProfilerRecord                    Records[512];
    uint32_t                          NumRecords;
    uint64_t                          TimerFreq;
  };

  class ProfilerCpuFrame : public IProfilerFrame
  {
  public:
    MVCOMMON_API ProfilerCpuFrame();
  };
  
  // enterZone() and leaveZone() are not part of the base
  // class to guarantee maximum performance by avoiding
  // vtables.
  class IProfilerThread
  {
  public:
    MVCOMMON_API IProfilerThread();
    MVCOMMON_API virtual ~IProfilerThread();

    MVCOMMON_API virtual void                     flip() = 0;
    MVCOMMON_API virtual IProfilerFrame           getLastFrame() = 0;

    MVCOMMON_API const char *                     getThreadName() const;

  protected:
    uint32_t                                      _curFrameIdx;
    const char *                                  _threadName;
    ProfilerRecord *                              _recordStack[32];
    uint32_t                                      _stackIdx;
    ProfilerZone                                  _masterZone;
    std::mutex                                    _lock;
  };

  class ProfilerCpuThread : public IProfilerThread
  {
  public:
    MVCOMMON_API ProfilerCpuThread(const char *threadName, std::thread::id tid);

    MVCOMMON_API void                             enterZone(ProfilerZone &zone);
    MVCOMMON_API void                             leaveZone();
    MVCOMMON_API void                             flip() override final;
    MVCOMMON_API IProfilerFrame                   getLastFrame() override final;
    MVCOMMON_API std::thread::id                  getId() const;

  private:
    const std::thread::id                         _threadId;
    ProfilerCpuFrame                              _frames[32];
    ProfilerCpuFrame *                            _curFrame;
  };

  // profiling system's main class
  class ProfilerManager
  {
  public:
    MVCOMMON_API ProfilerManager();
    MVCOMMON_API ~ProfilerManager();

    MVCOMMON_API void                             addCpuThread(std::thread::id id, const char *name);
    MVCOMMON_API void                             removeCpuThread(std::thread::id id);
    MVCOMMON_API void                             addThisCpuThread(const char *name);
    MVCOMMON_API void                             removeThisCpuThread();

    MVCOMMON_API std::deque<IProfilerThread *> &  getAllThreads();

    MVCOMMON_API ProfilerCpuThread *              getCpuThread();
    MVCOMMON_API void                             setCpuThread(ProfilerCpuThread *thread);

  private:
    std::deque<ProfilerCpuThread *>               _cpuThreads;
    std::deque<IProfilerThread *>                 _allThreads;
    std::mutex                                    _threadLock;
    static thread_local ProfilerCpuThread *       _cpuThread;
  };
  

  class Profiler
  {
  public:
    static MVCOMMON_API void                      init();
    static MVCOMMON_API void                      shutdown();
    static MVCOMMON_API ProfilerManager *         getManager();

  private:
    static ProfilerManager * _manager;
  };


  // classes used to profile a particular CPU code section.
  class ProfilerCpuScope
  {
  public:
    __forceinline ProfilerCpuScope(ProfilerZone &zone)
    {
      auto manager = Profiler::getManager();
      if (manager)
      {
        auto thread = manager->getCpuThread();
        if (thread)
          thread->enterZone(zone);
      }
    }

    __forceinline ~ProfilerCpuScope()
    {
      auto manager = Profiler::getManager();
      if (manager)
      {
        auto thread = manager->getCpuThread();
        if (thread)
          thread->leaveZone();
      }
    }
  };

}
