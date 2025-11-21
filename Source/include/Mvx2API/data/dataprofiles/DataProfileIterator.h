#pragma once

#include <Mvx2API/Mvx2API.h>
#include <MVCommon/Memory.h>

namespace Mvx2API
{
  class DataProfile;
  class DataProfileIteratorImpl;

  /// \brief An iterator over profiles of data contained in a frame.
  class DataProfileIterator
  {
  public:
    /// \brief A type of iterated-over elements.
    using ValueType = DataProfile;

    /// \cond
    explicit DataProfileIterator(DataProfileIteratorImpl * pImpl);
    /// \endcond

    /// \brief A copy constructor.
    /// \param other  an iterator to make a copy of
    MVX2_API DataProfileIterator(DataProfileIterator const & other);
    /// \brief A move constructor.
    /// \param other  an iterator to move
    MVX2_API DataProfileIterator(DataProfileIterator && other);
    /// \brief A destructor.
    MVX2_API virtual ~DataProfileIterator();

    /// \brief A prefix incrementation operator.
    /// \details Moves the iterator to the next element and returns this updated iterator.
    /// \returns  this iterator after it was updated
    MVX2_API DataProfileIterator& operator++();
    /// \brief A postfix incrementation operator.
    /// \details Moves the iterator to the next element, but returns the original iterator.
    /// \returns  the original unupdated iterator
    MVX2_API DataProfileIterator operator++(int);

    /// \brief Dereferences the iterator.
    /// \returns  a name of the filter parameter
    /// \exception std::runtime_error raised when the iterator is invalid
    MVX2_API ValueType operator*() const;

    /// \cond
    MVX2_API DataProfileIterator & operator=(DataProfileIterator other);
    MVX2_API friend bool operator==(DataProfileIterator const & lhs, DataProfileIterator const & rhs);
    /// \endcond

    DECLARE_CLASS_SPECIFIC_NEW_DELETE(MVX2_API)

  private:
    DataProfileIteratorImpl * _pImpl;
  };

  /// \cond
  MVX2_API bool operator==(Mvx2API::DataProfileIterator const & lhs, Mvx2API::DataProfileIterator const & rhs);
  MVX2_API bool operator!=(Mvx2API::DataProfileIterator const & lhs, Mvx2API::DataProfileIterator const & rhs);
  /// \endcond
}