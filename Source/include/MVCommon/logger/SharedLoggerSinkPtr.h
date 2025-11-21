#pragma once

#include <MVCommon/MVCommonAPI.h>
#include <MVCommon/Memory.h>

#include "ILoggerSink.h"

namespace MVCommon
{
  class SharedLoggerSinkPtrImpl;
  
  /// \brief A shared smart-pointer to a logger sink.
  /// \details
  /// Allows sharing of the same logger sink object by multiple owners and automatically destroys logger sink objects when no more pointers
  /// point to them.
  class SharedLoggerSinkPtr
  {
  public:
    /// \brief A constructor.
    /// \details Initializes the pointer with nullptr.
    MVCOMMON_API SharedLoggerSinkPtr();
    /// \brief A constructor.
    /// \param pLoggerSink  a logger sink to share a pointer to
    MVCOMMON_API SharedLoggerSinkPtr(ILoggerSink * pLoggerSink);
    /// \brief A copy-constructor.
    /// \param other  other pointer to share a pointed-to logger sink with
    MVCOMMON_API SharedLoggerSinkPtr(SharedLoggerSinkPtr const & other);
    /// \brief A destructor.
    /// \details Destroys the pointed-to logger sink if this was the last pointer pointing to it.
    MVCOMMON_API ~SharedLoggerSinkPtr();

    /// \brief Makes the pointer point to a logger sink pointed to by the \p other pointer.
    /// \details Destroys previously pointed-to logger sink if this was the last pointer pointing to it.
    /// \param other  other pointer to share a pointed-to logger sink with
    /// \returns      the pointer itself
    MVCOMMON_API SharedLoggerSinkPtr & operator=(SharedLoggerSinkPtr const & other);
    /// \brief Makes the pointer point to a logger sink.
    /// \details Destroys previously pointed-to logger sink if this was the last pointer pointing to it.
    /// \param pLoggerSink  a logger sink to point to
    /// \returns            the pointer itself
    MVCOMMON_API SharedLoggerSinkPtr & operator=(ILoggerSink * pLoggerSink);

    /// \brief Converts the pointer to a boolean value.
    /// \returns  true in case the pointed-to logger sink is not null
    MVCOMMON_API operator bool() const;
    /// \brief 'Indirection' operator.
    /// \returns  a reference to the pointed-to logger sink
    MVCOMMON_API ILoggerSink & operator*() const;
    /// \brief 'Dereference' operator.
    /// \returns  a raw pointer to the pointed-to logger sink
    MVCOMMON_API ILoggerSink * operator->() const;
    /// \brief Returns a raw pointer to the pointed-to logger sink.
    /// \returns  a raw pointer to the pointed-to logger sink
    MVCOMMON_API ILoggerSink * Get() const;

    DECLARE_CLASS_SPECIFIC_NEW_DELETE(MVCOMMON_API)

    /// \cond
    SharedLoggerSinkPtrImpl * GetImpl() const { return _pImpl; }
    /// \endcond

  private:
    SharedLoggerSinkPtrImpl * _pImpl;
  };
}