#pragma once

#include <MVCommon/MVCommonAPI.h>
#include <MVCommon/Memory.h>

#include "Logger.h"
#include "SharedLoggerPtr.h"

namespace MVCommon
{
  class WeakLoggerPtrImpl;
  
  /// \brief A weak smart-pointer to a logger.
  /// \details 
  /// Allows access to a logger object whose lifetime is maintained by a \ref SharedLoggerPtr smart-pointers,
  /// but does not influence the lifetime itself.
  class WeakLoggerPtr
  {
  public:
    /// \brief A constructor.
    /// \details Initializes the pointer with nullptr.
    MVCOMMON_API WeakLoggerPtr();
    /// \brief A constructor.
    /// \param spPtr  a shared smart-pointer to be linked to
    MVCOMMON_API WeakLoggerPtr(SharedLoggerPtr spPtr);
    /// \brief A copy-constructor.
    /// \param other  other pointer to share a pointed-to logger with
    MVCOMMON_API WeakLoggerPtr(WeakLoggerPtr const & other);
    /// \brief A destructor.
    MVCOMMON_API ~WeakLoggerPtr();

    /// \brief Makes the pointer point to a logger pointed to by the \p other pointer.
    /// \param other  other pointer to share a pointed-to logger with
    /// \returns      the pointer itself
    MVCOMMON_API WeakLoggerPtr & operator=(WeakLoggerPtr const & other);
    /// \brief Links the pointer to a shared smart-pointer.
    /// \param spPtr  a shared smart-pointer to be linked to
    /// \returns      the pointer itself
    MVCOMMON_API WeakLoggerPtr & operator=(SharedLoggerPtr spPtr);

    /// \brief Resets the pointer to not point to any logger (i.e. nullptr).
    MVCOMMON_API void Reset();
    /// \brief Determines whether the pointed-to logger still exists, e.g. when there are no more shared smart-pointers pointing to it.
    /// \returns  true if the pointed-to logger does not exist anymore
    MVCOMMON_API bool Expired() const;
    /// \brief
    /// Creates a new shared smart-pointer pointing to a logger pointed to by the pointer, increasing thus number of shared
    /// smart-pointers pointing to it.
    /// \returns  shared smart-pointer pointing to the pointer-to logger or nullptr in case the pointer has expired already
    MVCOMMON_API SharedLoggerPtr Lock() const;

    DECLARE_CLASS_SPECIFIC_NEW_DELETE(MVCOMMON_API)

  private:
    WeakLoggerPtrImpl * _pImpl;
  };
}

#define LOGGER_WP_LOG(wpLogger, level, tag, format, ...)                                                    \
  {                                                                                                         \
    MVCommon::SharedLoggerPtr spLogger = wpLogger.Lock();                                                   \
    if (spLogger) spLogger->LogMessage(LOG_LEVEL_FULL_QUALIFIED_NAME(level), tag, format, ##__VA_ARGS__);   \
  }
#define LOGGER_WP_LOG_C(wpLogger, tag, format, ...) LOGGER_WP_LOG(wpLogger, LL_CRITICAL, tag, format, ##__VA_ARGS__)
#define LOGGER_WP_LOG_E(wpLogger, tag, format, ...) LOGGER_WP_LOG(wpLogger, LL_ERROR, tag, format, ##__VA_ARGS__)
#define LOGGER_WP_LOG_W(wpLogger, tag, format, ...) LOGGER_WP_LOG(wpLogger, LL_WARNING, tag, format, ##__VA_ARGS__)
#define LOGGER_WP_LOG_I(wpLogger, tag, format, ...) LOGGER_WP_LOG(wpLogger, LL_INFO, tag, format, ##__VA_ARGS__)
#define LOGGER_WP_LOG_D(wpLogger, tag, format, ...) LOGGER_WP_LOG(wpLogger, LL_DEBUG, tag, format, ##__VA_ARGS__)
#define LOGGER_WP_LOG_V(wpLogger, tag, format, ...) LOGGER_WP_LOG(wpLogger, LL_VERBOSE, tag, format, ##__VA_ARGS__)