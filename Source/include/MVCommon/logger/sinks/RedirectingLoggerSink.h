#pragma once

#include <MVCommon/MVCommonAPI.h>
#include <MVCommon/logger/ILoggerSink.h>
#include <MVCommon/logger/SharedLoggerPtr.h>

namespace MVCommon
{
  /// \brief A logger sink implementation for redirecting log messages to another logger.
  /// \details All properties of log messages (timestamp, thread ID, ...) received from a logger are preserved when redirected to the target logger.
  class RedirectingLoggerSink final : public ILoggerSink
  {
  public:
    /// \brief A constructor.
    /// \param spLogger a logger to redirect log messages to
    /// \param logLevel an initial log level (default value -> all log messages are processed)
    MVCOMMON_API RedirectingLoggerSink(SharedLoggerPtr spLogger, LoggerLogLevel logLevel = LoggerLogLevel::LLL_VERBOSE);
    /// \brief A destructor.
    MVCOMMON_API ~RedirectingLoggerSink();

    DECLARE_CLASS_SPECIFIC_NEW_DELETE(MVCOMMON_API)

  protected:
    virtual void HandleLogEntry(LogEntry const & logEntry) override;

  private:
    SharedLoggerPtr _spLogger;
  };
}