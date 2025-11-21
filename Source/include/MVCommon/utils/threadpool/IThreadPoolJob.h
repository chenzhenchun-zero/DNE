#pragma once

#include <MVCommon/MVCommonAPI.h>
#include <MVCommon/Memory.h>

namespace MVCommon
{
  /// \brief An interface of thread pool jobs.
  class IThreadPoolJob
  {
  public:
    /// \brief A destructor.
    MVCOMMON_API virtual ~IThreadPoolJob();

    /// \brief The job-executing operator.
    /// \param threadID an ID of the thread that executes the job
    MVCOMMON_API virtual void operator()(uint32_t threadID) = 0;

    DECLARE_CLASS_SPECIFIC_NEW_DELETE(MVCOMMON_API)
  };
}