/// \file
#pragma once

namespace MVCommon
{
  /// \brief An enumeration of log levels.
  enum LogLevel
  {
    /// \brief A critical message log level.
    LL_CRITICAL = 1,
    /// \brief An error message log level.
    LL_ERROR = 2,
    /// \brief A warning message log level.
    LL_WARNING = 3,
    /// \brief An info message log level.
    LL_INFO = 4,
    /// \brief A debug message log level.
    LL_DEBUG = 5,
    /// \brief A verbose message log level.
    LL_VERBOSE = 6
  };
}

#define LOG_LEVEL_FULL_QUALIFIED_NAME(level) MVCommon::LogLevel::level