#pragma once

#include <MVCommon/MVCommonAPI.h>
#include <MVCommon/Memory.h>

#include "GuidAliasDatabase.h"

namespace MVCommon
{
  class SharedGuidAliasDatabasePtrImpl;

  /// \brief A shared smart-pointer to a guid alias database.
  /// \details
  /// Allows sharing of the same guid alias database object by multiple owners and automatically destroys guid alias database objects when
  /// no more pointers point to them.
  class SharedGuidAliasDatabasePtr
  {
  public:
    /// \brief A constructor.
    /// \details Initializes the pointer with nullptr.
    MVCOMMON_API SharedGuidAliasDatabasePtr();
    /// \brief A constructor.
    /// \param pGuidAliasDatabase a guid alias database to share a pointer to
    MVCOMMON_API SharedGuidAliasDatabasePtr(GuidAliasDatabase * pGuidAliasDatabase);
    /// \brief A copy-constructor.
    /// \param other  other pointer to share a pointed-to guid alias database with
    MVCOMMON_API SharedGuidAliasDatabasePtr(SharedGuidAliasDatabasePtr const & other);
    /// \brief A destructor.
    /// \details Destroys the pointed-to guid alias database if this was the last pointer pointing to it.
    MVCOMMON_API ~SharedGuidAliasDatabasePtr();

    /// \brief Makes the pointer point to a guid alias database pointed to by the \p other pointer.
    /// \details Destroys previously pointed-to guid alias database if this was the last pointer pointing to it.
    /// \param other  other pointer to share a pointed-to guid alias database with
    /// \returns      the pointer itself
    MVCOMMON_API SharedGuidAliasDatabasePtr & operator=(SharedGuidAliasDatabasePtr const & other);
    /// \brief Makes the pointer point to a guid alias database.
    /// \details Destroys previously pointed-to guid alias database if this was the last pointer pointing to it.
    /// \param pGuidAliasDatabase a guid alias database to point to
    /// \returns                  the pointer itself
    MVCOMMON_API SharedGuidAliasDatabasePtr & operator=(GuidAliasDatabase * pGuidAliasDatabase);

    /// \brief Converts the pointer to a boolean value.
    /// \returns  true in case the pointed-to guid alias database is not null
    MVCOMMON_API operator bool() const;
    /// \brief 'Indirection' operator.
    /// \returns  a reference to the pointed-to guid alias database
    MVCOMMON_API GuidAliasDatabase & operator*() const;
    /// \brief 'Dereference' operator.
    /// \returns  a raw pointer to the pointed-to guid alias database
    MVCOMMON_API GuidAliasDatabase * operator->() const;
    /// \brief Returns a raw pointer to the pointed-to guid alias database.
    /// \returns  a raw pointer to the pointed-to guid alias database
    MVCOMMON_API GuidAliasDatabase * Get() const;

    DECLARE_CLASS_SPECIFIC_NEW_DELETE(MVCOMMON_API)

  private:
    SharedGuidAliasDatabasePtrImpl * _pImpl;
  };
}