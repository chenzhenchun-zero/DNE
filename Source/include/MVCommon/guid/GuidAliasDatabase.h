#pragma once

#include <MVCommon/MVCommonAPI.h>
#include <MVCommon/Memory.h>

#include "Guid.h"
#include "GuidAliasDatabaseIterator.h"
#include <MVCommon/utils/String.h>

namespace MVCommon
{
  struct Guid;
  class String;

  class GuidAliasDatabaseImpl;

  /// \brief A database of Guid aliases.
  /// \details 
  /// The database keeps pairs of \ref Guid and \ref String alias objects and provides fast bi-directional mapping
  /// between them. Each Guid can only have a single alias assigned and each alias can only be assigned to a single Guid.
  class GuidAliasDatabase
  {
  public:
    /// \brief A constructor.
    MVCOMMON_API GuidAliasDatabase();
    /// \brief A copy constructor.
    /// \param other  a database to make a copy of
    MVCOMMON_API GuidAliasDatabase(GuidAliasDatabase const & other);
    /// \brief A move constructor.
    /// \param other  a database to move
    MVCOMMON_API GuidAliasDatabase(GuidAliasDatabase && other);
    /// \brief A destructor.
    MVCOMMON_API virtual ~GuidAliasDatabase();

    /// \brief Registers a new Guid alias.
    /// \param guid   a Guid to register alias for
    /// \param alias  an alias of the Guid
    /// \exception std::invalid_argument
    /// raised when there already is a different alias registered for the given Guid or the alias is already registered with another Guid
    MVCOMMON_API void RegisterGuidAlias(MVCommon::Guid const & guid, MVCommon::String const & alias);

    /// \brief Unregisters a Guid alias.
    /// \param guid a Guid to unregister alias of
    MVCOMMON_API void UnregisterGuidAlias(MVCommon::Guid const & guid);
    /// \brief Unregisters a Guid alias.
    /// \param alias  an alias to unregister
    MVCOMMON_API void UnregisterGuidAlias(MVCommon::String const & alias);

    /// \brief Tries to get an alias registered for a given Guid.
    /// \param guid   a Guid to get the alias for
    /// \param alias  a target to store the alias to
    /// \returns      true in case there is an alias registered for the Guid
    MVCOMMON_API bool TryGetGuidAlias(MVCommon::Guid const & guid, MVCommon::String & alias) const;

    /// \brief Tries to get a Guid with an alias registered.
    /// \param alias  an alias to look a Guid registered with for
    /// \param guid   a target to store the Guid to
    /// \returns      true in case there is a Guid registered with the alias
    MVCOMMON_API bool TryGetGuidWithAlias(MVCommon::String const & alias, MVCommon::Guid & guid) const;

    /// \brief Gets an alias registered for a given Guid.
    /// \param guid           a Guid to get the alias for
    /// \param fallbackAlias  a string returned in case there is no alias registered for the Guid
    /// \returns              an alias of the Guid or the fallback string in case there is none
    MVCOMMON_API MVCommon::String GetGuidAlias(MVCommon::Guid const & guid, MVCommon::String const & fallbackAlias = "") const;

    /// \brief Gets a Guid with an alias registered.
    /// \param alias        an alias to look a Guid registered with for
    /// \param fallbackGuid a Guid returned in case there is no Guid registered with the alias
    /// \returns            a Guid registered with the alias or fallback Guid in case there is none
    MVCOMMON_API MVCommon::Guid GetGuidWithAlias(MVCommon::String const & alias, MVCommon::Guid const & fallbackGuid = MVCommon::Guid::Nil()) const;

    /// \brief Checks whether a Guid has already an alias registered.
    /// \param guid a Guid to check
    /// \returns    true in case the Guid already has an alias registered
    MVCOMMON_API bool GuidRegistered(MVCommon::Guid const & guid) const;
    
    /// \brief Checks whether there already is a Guid with an alias registered.
    /// \param alias  an alias to check
    /// \returns      true in case there already is a Guid registered with the alias
    MVCOMMON_API bool AliasRegistered(MVCommon::String const & alias) const;

    /// \brief An alternative type name declaration for \ref GuidAliasDatabaseIterator.
    typedef GuidAliasDatabaseIterator Iterator;

    /// \brief Returns an iterator to the first entry of the database.
    /// \returns  an iterator
    /// \details The returned iterator is equal to End() iterator when the database is empty.
    MVCOMMON_API Iterator Begin() const;
    /// \brief Returns an iterator to the last entry of the database.
    /// \returns  an iterator
    MVCOMMON_API Iterator End() const;

    /// \cond
    MVCOMMON_API GuidAliasDatabase & operator=(GuidAliasDatabase other);
    /// \endcond
    
    DECLARE_CLASS_SPECIFIC_NEW_DELETE(MVCOMMON_API)

  private:
    GuidAliasDatabaseImpl * _pImpl;
  };
}