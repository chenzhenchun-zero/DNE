#pragma once

#include <MVCommon/MVCommonAPI.h>
#include <MVCommon/Memory.h>

#include "LogLevel.h"
#include <MVCommon/utils/String.h>

namespace MVCommon
{
  /// \brief A log entry data structure.
  struct LogEntry final
  {
  public:
    /// \brief A type of log entry timestamps.
    typedef uint64_t Timestamp;
    /// \brief A type of log entry thread IDs.
    typedef MVCommon::String ThreadID;

    /// \brief A constructor.
    /// \param timestamp  a timestamp (as number of milliseconds since the epoch - 1970-01-01 00:00:00.000)
    /// \param threadID   a thread ID
    /// \param level      a log level
    /// \param tag        a log tag
    /// \param message    a log message
    LogEntry(Timestamp timestamp, ThreadID threadID, LogLevel level, MVCommon::String const & tag, MVCommon::String const & message);

    /// \brief Returns level of the log entry.
    /// \returns  log entry level
    MVCOMMON_API LogLevel GetLevel() const;
    /// \brief Returns tag of the log entry.
    /// \returns  log entry tag
    MVCOMMON_API MVCommon::String GetTag() const;
    /// \brief Returns message of the log entry.
    /// \returns  log entry message
    MVCOMMON_API MVCommon::String GetMessage() const;
    /// \brief Returns timestamp of the log entry.
    /// \details Timestamp is stored as number of milliseconds since the epoch - 1970-01-01 00:00:00.000.
    /// \returns  log entry timestamp
    MVCOMMON_API Timestamp GetTimestamp() const;
    /// \brief Returns originating thread ID of the log entry.
    /// \returns  log entry thread ID
    MVCOMMON_API ThreadID GetThreadID() const;

    DECLARE_CLASS_SPECIFIC_NEW_DELETE(MVCOMMON_API)

  private:
    LogLevel _level;
    MVCommon::String _tag;
    MVCommon::String _message;
    Timestamp _timestamp;
    ThreadID _threadID;
  };
}