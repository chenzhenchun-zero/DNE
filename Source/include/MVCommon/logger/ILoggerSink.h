#pragma once

#include <MVCommon/MVCommonAPI.h>
#include <MVCommon/Memory.h>

#include "LoggerLogLevel.h"
#include "LogEntry.h"
#include <MVCommon/utils/String.h>

namespace MVCommon
{
  /// \brief An interface of logger sinks.
  /// \details
  /// When a logger sink is attached to a logger, it will receive all log messages logged via that logger, assuming that the log message is not
  /// filtered by the sink's own log level setting.
  class ILoggerSink : private NonAssignable
  {
  public:
    /// \brief A constructor.
    /// \param logLevel an initial log level (default value -> all log messages are processed)
    MVCOMMON_API ILoggerSink(LoggerLogLevel logLevel = LoggerLogLevel::LLL_VERBOSE);
    /// \brief A destructor.
    MVCOMMON_API virtual ~ILoggerSink();

    /// \brief Changes log level of the sink for log messages filtering.
    /// \param logLevel a new log level
    MVCOMMON_API void SetLogLevel(LoggerLogLevel logLevel);
    /// \brief Returns current log level of the sink.
    /// \returns  sink's log level
    MVCOMMON_API LoggerLogLevel GetLogLevel() const;

    /// \brief Adds a new log entry to the sink.
    /// \param logEntry a new log entry
    /// \details A log level of the entry is compared with log level of the sink so entries with lesser log levels than the sink's log level are ignored.
    void AddLogEntry(LogEntry const & logEntry);

    /// \brief A default formatter of timestamps usable in logger sink implementations.
    /// \details A format of the resulting string is "1900-Jan-01 00:00:00.000" when date is included and "00:00:00.000" when date is ommited.
    /// \param timestamp    a timestamp to format
    /// \param includeDate  indicates whether a date shall be included in the formatted string
    /// \returns            a formatted timestamp
    MVCOMMON_API static MVCommon::String TimestampToString(LogEntry::Timestamp timestamp, bool includeDate = true);
    /// \brief A default formatter of log levels usable in logger sink implementations.
    /// \param level        a log level to format
    /// \param shortVersion indicates whether a short (single character) or a long (whole level name) version shall be used
    /// \returns            a formatted log level
    MVCOMMON_API static MVCommon::String LogLevelToString(LogLevel level, bool shortVersion = false);

    DECLARE_CLASS_SPECIFIC_NEW_DELETE(MVCOMMON_API)

  protected:
    /// \brief A callback executed when a new log entry is added.
    /// \param logEntry a new log entry
    MVCOMMON_API virtual void HandleLogEntry(LogEntry const & logEntry) = 0;

  private:
    LoggerLogLevel _logLevel;
  };
}