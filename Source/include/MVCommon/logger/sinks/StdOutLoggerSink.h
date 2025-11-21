#pragma once

#include <MVCommon/MVCommonAPI.h>
#include <MVCommon/logger/ILoggerSink.h>

namespace MVCommon
{
  /// \brief A logger sink implementation for logging into a standard output.
  class StdOutLoggerSink final : public ILoggerSink
  {
  public:
    /// \brief A constructor.
    /// \param colorizeByLevel  determines whether log messages shall be colorized based on their level - actual behaviour depends on the console used
    /// \param logLevel         an initial log level (default value -> all log messages are processed)
    MVCOMMON_API StdOutLoggerSink(bool colorizeByLevel = false, LoggerLogLevel logLevel = LoggerLogLevel::LLL_VERBOSE);
    /// \brief A destructor.
    MVCOMMON_API ~StdOutLoggerSink();

    DECLARE_CLASS_SPECIFIC_NEW_DELETE(MVCOMMON_API)

  protected:
    virtual void HandleLogEntry(LogEntry const & logEntry) override;

  private:
    bool _colorizeByLevel;
  };
}