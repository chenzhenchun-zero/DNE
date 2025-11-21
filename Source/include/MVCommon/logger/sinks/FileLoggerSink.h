#pragma once

#include <MVCommon/MVCommonAPI.h>
#include <MVCommon/logger/ILoggerSink.h>

namespace MVCommon
{
  class FileLoggerSinkImpl;

  /// \brief A logger sink implementation for logging into a file.
  class FileLoggerSink final : public ILoggerSink
  {
  public:
    /// \brief A constructor.
    /// \param path     a path of the file
    /// \param logLevel an initial log level (default value -> all log messages are processed)
    MVCOMMON_API FileLoggerSink(MVCommon::String const & path, LoggerLogLevel logLevel = LoggerLogLevel::LLL_VERBOSE);
    /// \brief A destructor.
    MVCOMMON_API ~FileLoggerSink();

    DECLARE_CLASS_SPECIFIC_NEW_DELETE(MVCOMMON_API)

  protected:
    virtual void HandleLogEntry(LogEntry const & logEntry) override;

  private:
    FileLoggerSinkImpl * _pImpl;
  };
}