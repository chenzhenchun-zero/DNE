#pragma once

#include <Mvx2API/Mvx2API.h>
#include <MVCommon/Memory.h>

#include <MVCommon/utils/String.h>

namespace Mvx2API
{
  class FilterParameterNameIteratorImpl;

  /// \brief An iterator over names of filter parameters of a \ref SingleFilterGraphNode.
  class FilterParameterNameIterator
  {
  public:
    /// \brief A type of iterated-over elements.
    using ValueType = MVCommon::String;

    /// \cond
    explicit FilterParameterNameIterator(FilterParameterNameIteratorImpl * pImpl);
    /// \endcond

    /// \brief A copy constructor.
    /// \param other  an iterator to make a copy of
    MVX2_API FilterParameterNameIterator(FilterParameterNameIterator const & other);
    /// \brief A move constructor.
    /// \param other  an iterator to move
    MVX2_API FilterParameterNameIterator(FilterParameterNameIterator && other);
    /// \brief A destructor.
    MVX2_API virtual ~FilterParameterNameIterator();

    /// \brief A prefix incrementation operator.
    /// \details Moves the iterator to the next element and returns this updated iterator.
    /// \returns  this iterator after it was updated
    MVX2_API FilterParameterNameIterator& operator++();
    /// \brief A postfix incrementation operator.
    /// \details Moves the iterator to the next element, but returns the original iterator.
    /// \returns  the original unupdated iterator
    MVX2_API FilterParameterNameIterator operator++(int);

    /// \brief Dereferences the iterator.
    /// \returns  a name of the filter parameter
    MVX2_API ValueType operator*() const;

    /// \cond
    MVX2_API FilterParameterNameIterator & operator=(FilterParameterNameIterator other);
    MVX2_API friend bool operator==(FilterParameterNameIterator const & lhs, FilterParameterNameIterator const & rhs);
    /// \endcond

    DECLARE_CLASS_SPECIFIC_NEW_DELETE(MVX2_API)

  private:
    FilterParameterNameIteratorImpl * _pImpl;
  };

  /// \cond
  MVX2_API bool operator==(Mvx2API::FilterParameterNameIterator const & lhs, Mvx2API::FilterParameterNameIterator const & rhs);
  MVX2_API bool operator!=(Mvx2API::FilterParameterNameIterator const & lhs, Mvx2API::FilterParameterNameIterator const & rhs);
  /// \endcond
}