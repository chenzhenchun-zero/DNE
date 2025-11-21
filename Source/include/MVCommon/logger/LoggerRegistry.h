#pragma once

#include <MVCommon/MVCommonAPI.h>
#include <MVCommon/Memory.h>

#include "SharedLoggerPtr.h"

namespace MVCommon
{
  struct LoggerRegistryImpl;

  /// \brief A global registry of loggers.
  /// \details Serves as a global accessor to \ref Logger instances in cases where direct access is not possible.
  class LoggerRegistry final : private NonAssignable
  {
  public:
    /// \brief A destructor.
    MVCOMMON_API ~LoggerRegistry();

    /// \brief Returns the only instance of the registry.
    /// \returns  the registry instance
    MVCOMMON_API static LoggerRegistry & GetInstance();

    /// \brief Registers a logger instance to the registry.
    /// \param loggerAlias  an alias to register the logger with
    /// \param spLogger     a logger to register
    /// \details Replaces the previous logger registered with the same alias in case there was one.
    MVCOMMON_API void RegisterLogger(MVCommon::String const & loggerAlias, SharedLoggerPtr spLogger);

    /// \brief Unregisters a logger registered with an alias from the registry.
    /// \param loggerAlias  an alias to unregister a logger registered with
    MVCOMMON_API void UnregisterLogger(MVCommon::String const & loggerAlias);

    /// \brief Returns a logger registered with an alias.
    /// \param loggerAlias  an alias the logger to return is supposed to be registered with
    /// \returns            a logger with the alias or nullptr if there is none
    MVCOMMON_API SharedLoggerPtr GetLogger(MVCommon::String const & loggerAlias) const;

    /// \brief Clears the registry - removes all registered loggers.
    MVCOMMON_API void ClearRegistry();

    DECLARE_CLASS_SPECIFIC_NEW_DELETE(MVCOMMON_API)

  private:
    LoggerRegistry();

    LoggerRegistryImpl * _pImpl;
  };
}