#pragma once

#include <Mvx2API/Mvx2API.h>
#include <MVCommon/Memory.h>

namespace MVX
{
  class Filter;
}

namespace Mvx2API
{
  class SharedFilterPtrImpl;
  
  /// \brief A shared smart-pointer to a filter.
  /// \details
  /// Allows sharing of the same filter object by multiple owners and automatically destroys filter objects when no more pointers
  /// point to them.
  class SharedFilterPtr
  {
  public:
    /// \cond
    SharedFilterPtr(SharedFilterPtrImpl * pImpl);
    /// \endcond
    /// \brief A constructor.
    /// \details Initializes the pointer with nullptr.
    MVX2_API SharedFilterPtr();
    /// \brief A constructor.
    /// \param pFilter  a filter to share a pointer to
    MVX2_API SharedFilterPtr(MVX::Filter * pFilter);
    /// \brief A copy-constructor.
    /// \param other  other pointer to share a pointed-to filter with
    MVX2_API SharedFilterPtr(SharedFilterPtr const & other);
    /// \brief A destructor.
    /// \details Destroys the pointed-to filter if this was the last pointer pointing to it.
    MVX2_API ~SharedFilterPtr();

    /// \brief Makes the pointer point to a filter pointed to by the \p other pointer.
    /// \details Destroys previously pointed-to filter if this was the last pointer pointing to it.
    /// \param other  other pointer to share a pointed-to filter with
    /// \returns      the pointer itself
    MVX2_API SharedFilterPtr & operator=(SharedFilterPtr const & other);
    /// \brief Makes the pointer point to a filter.
    /// \details Destroys previously pointed-to filter if this was the last pointer pointing to it.
    /// \param pFilter  a filter to point to
    /// \returns        the pointer itself
    MVX2_API SharedFilterPtr & operator=(MVX::Filter * pFilter);

    /// \brief Converts the pointer to a boolean value.
    /// \returns  true in case the pointed-to filter is not null
    MVX2_API operator bool() const;
    /// \brief 'Indirection' operator.
    /// \returns  a reference to the pointed-to filter
    MVX2_API MVX::Filter & operator*() const;
    /// \brief 'Dereference' operator.
    /// \returns  a raw pointer to the pointed-to filter
    MVX2_API MVX::Filter * operator->() const;
    /// \brief Returns a raw pointer to the pointed-to filter.
    /// \returns  a raw pointer to the pointed-to filter
    MVX2_API MVX::Filter * Get() const;

    DECLARE_CLASS_SPECIFIC_NEW_DELETE(MVX2_API)

    /// \cond
    SharedFilterPtrImpl * GetImpl() const { return _pImpl; }
    /// \endcond

  private:
    SharedFilterPtrImpl * _pImpl;
  };
}