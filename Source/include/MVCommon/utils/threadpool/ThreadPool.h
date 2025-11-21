#pragma once

#include <MVCommon/MVCommonAPI.h>
#include <MVCommon/Memory.h>

#include "SharedThreadPoolJobPtr.h"

namespace MVCommon
{
  class ThreadPoolImpl;
  class IThreadPoolJob;

  /// \brief A pool of threads.
  /// \details
  /// The pool maintains a fixed-size collection of threads usable for executing jobs. It hides the details about creation and maintenance 
  /// of threads and about dispatching of jobs to them, allowing a user to focus on the jobs themselves.
  class ThreadPool : public NonAssignable
  {
  public:
    /// \brief A constructor.
    /// \details Instantiates the threads.
    /// \param threadsCount a count of threads the pool maintains
    /// \param waitersForUnoccupiedThreadsCountHint
    /// a hint about expected count of threads calling \ref WaitForAnUnoccupiedThread - it allows an optimization of internal memory allocations
    /// made per each waiting call in cases when count of parallel waiters can be predicted. Special value `0` will result in allocations made
    /// every time, and `negative` hint value results in no deallocations (and thus maximum reusability of the memory) during the entire lifetime
    /// of the thread pool.
    MVCOMMON_API ThreadPool(uint32_t threadsCount = 1, int32_t waitersForUnoccupiedThreadsCountHint = 1);
    /// \brief A destructor.
    /// \details Shuts down all maintained threads and waits until they complete their execution.
    MVCOMMON_API ~ThreadPool();

    /// \brief Gets the threads count.
    /// \returns  the count of threads in the pool
    MVCOMMON_API uint32_t GetThreadsCount() const;

    /// \brief Instructs the pool to execute a job on an unoccupied thread.
    /// \param spJob  a job to execute
    /// \returns      true in case there is an unoccupied thread that will execute the job, false otherwise
    MVCOMMON_API bool DoJob(SharedThreadPoolJobPtr spJob);
    
    /// \brief Determines whether there are unoccupied threads available in the pool.
    /// \returns  true if there is at least one unoccupied thread, false otherwise
    MVCOMMON_API bool HasUnoccupiedThreads() const;
    /// \brief Determines a count of unoccupied threads in the pool.
    /// \returns  a count of currently unoccupied threads
    MVCOMMON_API uint32_t GetUnoccupiedThreadsCount() const;
    /// \brief Blocks current thread until there is at least one unoccupied thread in the pool.
    MVCOMMON_API void WaitForAnUnoccupiedThread() const;

    /// \brief Resets all jobs and threads executed by the pool.
    /// \details Waits until all jobs are completed, shuts down all the threads and reinitializes them.
    MVCOMMON_API void ResetJobs();

    DECLARE_CLASS_SPECIFIC_NEW_DELETE(MVCOMMON_API)

  private:
    ThreadPoolImpl * _pImpl;
  };
}