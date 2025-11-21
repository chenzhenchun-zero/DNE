#pragma once

#include <MVCommon/MVCommonAPI.h>
#include <MVCommon/Memory.h>

#include "Logger.h"

namespace MVCommon
{
  class SharedLoggerPtrImpl;
  
  /// \brief A shared smart-pointer to a logger.
  /// \details
  /// Allows sharing of the same logger object by multiple owners and automatically destroys logger objects when no more pointers
  /// point to them.
  class SharedLoggerPtr
  {
  public:
    /// \cond
    SharedLoggerPtr(SharedLoggerPtrImpl * pImpl);
    /// \endcond
    /// \brief A constructor.
    /// \details Initializes the pointer with nullptr.
    MVCOMMON_API SharedLoggerPtr();
    /// \brief A constructor.
    /// \param pLogger  a logger to share a pointer to
    MVCOMMON_API SharedLoggerPtr(Logger * pLogger);
    /// \brief A copy-constructor.
    /// \param other  other pointer to share a pointed-to logger with
    MVCOMMON_API SharedLoggerPtr(SharedLoggerPtr const & other);
    /// \brief A destructor.
    /// \details Destroys the pointed-to logger if this was the last pointer pointing to it.
    MVCOMMON_API ~SharedLoggerPtr();

    /// \brief Makes the pointer point to a logger pointed to by the \p other pointer.
    /// \details Destroys previously pointed-to logger if this was the last pointer pointing to it.
    /// \param other  other pointer to share a pointed-to logger with
    /// \returns      the pointer itself
    MVCOMMON_API SharedLoggerPtr & operator=(SharedLoggerPtr const & other);
    /// \brief Makes the pointer point to a logger.
    /// \details Destroys previously pointed-to logger if this was the last pointer pointing to it.
    /// \param pLogger  a logger to point to
    /// \returns        the pointer itself
    MVCOMMON_API SharedLoggerPtr & operator=(Logger * pLogger);

    /// \brief Converts the pointer to a boolean value.
    /// \returns  true in case the pointed-to logger is not null
    MVCOMMON_API operator bool() const;
    /// \brief 'Indirection' operator.
    /// \returns  a reference to the pointed-to logger
    MVCOMMON_API Logger & operator*() const;
    /// \brief 'Dereference' operator.
    /// \returns  a raw pointer to the pointed-to logger
    MVCOMMON_API Logger * operator->() const;
    /// \brief Returns a raw pointer to the pointed-to logger.
    /// \returns  a raw pointer to the pointed-to logger
    MVCOMMON_API Logger * Get() const;

    DECLARE_CLASS_SPECIFIC_NEW_DELETE(MVCOMMON_API)

    /// \cond
    SharedLoggerPtrImpl * GetImpl() const { return _pImpl; }
    /// \endcond

  private:
    SharedLoggerPtrImpl * _pImpl;
  };
}

#define LOGGER_SP_LOG(spLogger, level, tag, format, ...) spLogger->LogMessage(LOG_LEVEL_FULL_QUALIFIED_NAME(level), tag, format, ##__VA_ARGS__);
#define LOGGER_SP_LOG_C(spLogger, tag, format, ...) LOGGER_SP_LOG(spLogger, LL_CRITICAL, tag, format, ##__VA_ARGS__)
#define LOGGER_SP_LOG_E(spLogger, tag, format, ...) LOGGER_SP_LOG(spLogger, LL_ERROR, tag, format, ##__VA_ARGS__)
#define LOGGER_SP_LOG_W(spLogger, tag, format, ...) LOGGER_SP_LOG(spLogger, LL_WARNING, tag, format, ##__VA_ARGS__)
#define LOGGER_SP_LOG_I(spLogger, tag, format, ...) LOGGER_SP_LOG(spLogger, LL_INFO, tag, format, ##__VA_ARGS__)
#define LOGGER_SP_LOG_D(spLogger, tag, format, ...) LOGGER_SP_LOG(spLogger, LL_DEBUG, tag, format, ##__VA_ARGS__)
#define LOGGER_SP_LOG_V(spLogger, tag, format, ...) LOGGER_SP_LOG(spLogger, LL_VERBOSE, tag, format, ##__VA_ARGS__)