#pragma once

#include <MVCommon/MVCommonAPI.h>
#include <MVCommon/Memory.h>

#include <MVCommon/utils/String.h>
#include "LoggerLogLevel.h"
#include "LogLevel.h"
#include "SharedLoggerSinkPtr.h"

namespace MVCommon
{
  class LoggerImpl;

  /// \brief A logger.
  /// \details
  /// A logger receives requests for messages logging, filters them according to its log level setting and asynchronously pushes them to all
  /// attached logger sinks for customized handling.
  class Logger final : private NonAssignable
  {
  public:
    /// \brief A constructor.
    /// \param logLevel an initial log level (default value -> debug and higher level messages are processed)
    MVCOMMON_API Logger(LoggerLogLevel logLevel = LoggerLogLevel::LLL_DEBUG);
    /// \brief A destructor.
    MVCOMMON_API ~Logger();

    /// \brief Changes log level of the logger for log messages filtering.
    /// \param logLevel a new log level
    MVCOMMON_API void SetLogLevel(LoggerLogLevel logLevel);
    /// \brief Returns current log level of the logger.
    /// \returns  logger's log level
    MVCOMMON_API LoggerLogLevel GetLogLevel() const;

    /// \brief Registers a logger sink.
    /// \param spLoggerSink a logger sink to register
    MVCOMMON_API void AddLoggerSink(SharedLoggerSinkPtr spLoggerSink);
    /// \brief Unregisters a logger sink.
    /// \param spLoggerSink a logger sink to unregister
    MVCOMMON_API void RemoveLoggerSink(SharedLoggerSinkPtr spLoggerSink);
    /// \brief Unregisters all logger sinks.
    MVCOMMON_API void RemoveAllLoggerSinks();

    /// \brief Logs a new message.
    /// \param level  a level of the log message
    /// \param tag    a tag of the log message
    /// \param format a C-style formatting directive of the message in case there are additional arguments
    /// \details
    /// \par
    /// A log level of the entry is compared with log level of the sink so entries with lesser log levels than the sink's log level are ignored.
    /// \par
    /// Current time and the caller's thread is used for the log message.
    MVCOMMON_API void LogMessage(LogLevel level, char const * tag, char const * format, ...);

    /// \brief Logs a new message.
    /// \param timestamp  a timestamp of the log message (as number of milliseconds since the epoch - 1970-01-01 00:00:00.000)
    /// \param threadID   a thread ID of the log message
    /// \param level      a level of the log message
    /// \param tag        a tag of the log message
    /// \param format     a C-style formatting directive of the message in case there are additional arguments
    /// \details A log level of the entry is compared with log level of the sink so entries with lesser log levels than the sink's log level are ignored.
    MVCOMMON_API void LogMessage(LogEntry::Timestamp timestamp, LogEntry::ThreadID threadID, LogLevel level, char const * tag, char const * format, ...);

    DECLARE_CLASS_SPECIFIC_NEW_DELETE(MVCOMMON_API)

  private:
    LoggerImpl * _pImpl;
  };
}

#define LOGGER_LOG(logger, level, tag, format, ...) logger.LogMessage(LOG_LEVEL_FULL_QUALIFIED_NAME(level), tag, format, ##__VA_ARGS__);
#define LOGGER_LOG_C(logger, tag, format, ...) LOGGER_LOG(logger, LL_CRITICAL, tag, format, ##__VA_ARGS__)
#define LOGGER_LOG_E(logger, tag, format, ...) LOGGER_LOG(logger, LL_ERROR, tag, format, ##__VA_ARGS__)
#define LOGGER_LOG_W(logger, tag, format, ...) LOGGER_LOG(logger, LL_WARNING, tag, format, ##__VA_ARGS__)
#define LOGGER_LOG_I(logger, tag, format, ...) LOGGER_LOG(logger, LL_INFO, tag, format, ##__VA_ARGS__)
#define LOGGER_LOG_D(logger, tag, format, ...) LOGGER_LOG(logger, LL_DEBUG, tag, format, ##__VA_ARGS__)
#define LOGGER_LOG_V(logger, tag, format, ...) LOGGER_LOG(logger, LL_VERBOSE, tag, format, ##__VA_ARGS__)