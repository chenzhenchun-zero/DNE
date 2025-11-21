#pragma once

#include <MVCommon/MVCommonAPI.h>
#include <MVCommon/Memory.h>

#include "IThreadPoolJob.h"

namespace MVCommon
{
  class SharedThreadPoolJobPtrImpl;

  /// \brief A shared smart-pointer to a thread pool job.
  /// \details
  /// Allows sharing of the same job object by multiple owners and automatically destroys job objects when no more pointers
  /// point to them.
  class SharedThreadPoolJobPtr
  {
  public:
    /// \brief A constructor.
    /// \details Initializes the pointer with nullptr.
    MVCOMMON_API SharedThreadPoolJobPtr();
    /// \brief A constructor.
    /// \param pJob a thread pool job to share a pointer to
    MVCOMMON_API SharedThreadPoolJobPtr(IThreadPoolJob * pJob);
    /// \brief A copy-constructor.
    /// \param other  other pointer to share a pointed-to thread pool job with
    MVCOMMON_API SharedThreadPoolJobPtr(SharedThreadPoolJobPtr const & other);
    /// \brief A destructor.
    /// \details Destroys the pointed-to thread pool job if this was the last pointer pointing to it.
    MVCOMMON_API ~SharedThreadPoolJobPtr();

    /// \brief Makes the pointer point to a thread pool job pointed to by the \p other pointer.
    /// \details Destroys previously pointed-to thread pool job if this was the last pointer pointing to it.
    /// \param other  other pointer to share a pointed-to thread pool job with
    /// \returns      the pointer itself
    MVCOMMON_API SharedThreadPoolJobPtr & operator=(SharedThreadPoolJobPtr const & other);
    /// \brief Makes the pointer point to a thread pool job.
    /// \details Destroys previously pointed-to thread pool job if this was the last pointer pointing to it.
    /// \param pJob a thread pool job to point to
    /// \returns    the pointer itself
    MVCOMMON_API SharedThreadPoolJobPtr & operator=(IThreadPoolJob * pJob);

    /// \brief Converts the pointer to a boolean value.
    /// \returns  true in case the pointed-to thread pool job is not null
    MVCOMMON_API operator bool() const;
    /// \brief 'Indirection' operator.
    /// \returns  a reference to the pointed-to thread pool job
    MVCOMMON_API IThreadPoolJob & operator*() const;
    /// \brief 'Dereference' operator.
    /// \returns  a raw pointer to the pointed-to thread pool job
    MVCOMMON_API IThreadPoolJob * operator->() const;
    /// \brief Returns a raw pointer to the pointed-to thread pool job.
    /// \returns  a raw pointer to the pointed-to job
    MVCOMMON_API IThreadPoolJob * Get() const;

    DECLARE_CLASS_SPECIFIC_NEW_DELETE(MVCOMMON_API)

    /// \cond
    SharedThreadPoolJobPtrImpl * GetImpl() const { return _pImpl; }
    /// \endcond

  private:
    SharedThreadPoolJobPtrImpl * _pImpl;
  };
}