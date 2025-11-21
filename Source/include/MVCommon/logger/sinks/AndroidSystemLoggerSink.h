#pragma once

#include <MVCommon/MVCommonAPI.h>
#include <MVCommon/logger/ILoggerSink.h>

namespace MVCommon
{
  /// \brief A logger sink implementation for logging log messages via Android system logging facility.
  /// \details In case the sink is instantiated on a non-Android platform, log messages are not handled at all.
  class AndroidSystemLoggerSink final : public ILoggerSink
  {
  public:
    /// \brief A constructor.
    /// \param logLevel an initial log level (default value -> all log messages are processed)
    MVCOMMON_API AndroidSystemLoggerSink(LoggerLogLevel logLevel = LoggerLogLevel::LLL_VERBOSE);
    /// \brief A destructor.
    MVCOMMON_API ~AndroidSystemLoggerSink();

    DECLARE_CLASS_SPECIFIC_NEW_DELETE(MVCOMMON_API)

  protected:
    virtual void HandleLogEntry(LogEntry const & logEntry) override;
  };
}