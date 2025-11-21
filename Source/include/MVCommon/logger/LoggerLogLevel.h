/// \file
#pragma once

#include "LogLevel.h"

namespace MVCommon
{
  /// \brief An enumeration of logger log levels for filtering log messages.
  /// \details Only log messages that are classified with higher log level than the logger is set to are actually logged.
  enum LoggerLogLevel
  {
    /// \brief No log messages are logged.
    LLL_SILENT = 0,
    /// \brief Only critical log messages are logged.
    LLL_CRITICAL = LL_CRITICAL,
    /// \brief Only error or higher level log messages are logged.
    LLL_ERROR = LL_ERROR,
    /// \brief Only warning and higher level log messages are logged.
    LLL_WARNING = LL_WARNING,
    /// \brief Only info and higher level log messages are logged.
    LLL_INFO = LL_INFO,
    /// \brief Only debug and higher level log messages are logged.
    LLL_DEBUG = LL_DEBUG,
    /// \brief All log messages are logged.
    LLL_VERBOSE = LL_VERBOSE,
  };
}