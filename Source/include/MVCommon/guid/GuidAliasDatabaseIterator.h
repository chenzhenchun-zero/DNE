#pragma once

#include <MVCommon/MVCommonAPI.h>
#include <MVCommon/Memory.h>

#include <MVCommon/utils/Pair.h>
#include "Guid.h"
#include <MVCommon/utils/String.h>

namespace MVCommon
{
  class GuidAliasDatabaseIteratorImpl;

  /// \brief An iterator over elements of \ref GuidAliasDatabase collections.
  class GuidAliasDatabaseIterator
  {
  public:
    /// \brief A type of iterated-over elements of \ref GuidAliasDatabase collection.
    using ValueType = Pair<Guid const, String const>;

    /// \cond
    explicit GuidAliasDatabaseIterator(GuidAliasDatabaseIteratorImpl * pImpl);
    /// \endcond

    /// \brief A copy constructor.
    /// \param other  an iterator to make a copy of
    MVCOMMON_API GuidAliasDatabaseIterator(GuidAliasDatabaseIterator const & other);
    /// \brief A move constructor.
    /// \param other  an iterator to move
    MVCOMMON_API GuidAliasDatabaseIterator(GuidAliasDatabaseIterator && other);
    /// \brief A destructor.
    MVCOMMON_API virtual ~GuidAliasDatabaseIterator();

    /// \brief A prefix incrementation operator.
    /// \details Moves the iterator to the next element and returns this updated iterator.
    /// \returns  this iterator after it was updated
    MVCOMMON_API GuidAliasDatabaseIterator& operator++();
    /// \brief A postfix incrementation operator.
    /// \details Moves the iterator to the next element, but returns the original iterator.
    /// \returns  the original unupdated iterator
    MVCOMMON_API GuidAliasDatabaseIterator operator++(int);

    /// \brief Dereferences the iterator.
    /// \returns  a pair of Guid and its alias
    MVCOMMON_API ValueType operator*() const;

    /// \cond
    MVCOMMON_API GuidAliasDatabaseIterator & operator=(GuidAliasDatabaseIterator other);
    MVCOMMON_API friend bool operator==(GuidAliasDatabaseIterator const & lhs, GuidAliasDatabaseIterator const & rhs);
    /// \endcond

    DECLARE_CLASS_SPECIFIC_NEW_DELETE(MVCOMMON_API)

  private:
    GuidAliasDatabaseIteratorImpl * _pImpl;
  };

  /// \cond
  MVCOMMON_API bool operator==(MVCommon::GuidAliasDatabaseIterator const & lhs, MVCommon::GuidAliasDatabaseIterator const & rhs);
  MVCOMMON_API bool operator!=(MVCommon::GuidAliasDatabaseIterator const & lhs, MVCommon::GuidAliasDatabaseIterator const & rhs);
  /// \endcond
}