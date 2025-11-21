#pragma once

#include <Mvx2API/Mvx2API.h>
#include <MVCommon/Memory.h>

namespace Mvx2API
{
  class FilterListImpl;
  class SharedFilterPtr;

  /// \brief A collection of filters.
  class FilterList
  {
  public:
    /// \brief A constructor.
    MVX2_API FilterList();
    /// \brief A copy-constructor.
    /// \param other  another collection to copy filters from
    MVX2_API FilterList(FilterList const & other);
    /// \brief A destructor.
    MVX2_API ~FilterList();

    /// \brief Pushes a filter to the collection.
    /// \param filter a filter to push
    MVX2_API void PushBack(SharedFilterPtr const & filter);

    /// \brief Returns a filter at a given index in the collection.
    /// \param pos  an index of index to return
    /// \returns    a filter at the index
    MVX2_API SharedFilterPtr & operator[](uint32_t pos);
    /// \brief Returns a filter at a given index in the collection.
    /// \param pos  an index of index to return
    /// \returns    a filter at the index
    MVX2_API SharedFilterPtr const & operator[](uint32_t pos) const;

    /// \brief Returns a count of filters in the collection.
    /// \returns  filters count
    MVX2_API uint32_t Count() const;
    /// \brief Empties the collection.
    MVX2_API void Clear();

    DECLARE_CLASS_SPECIFIC_NEW_DELETE(MVX2_API)

  private:
    FilterListImpl * _pImpl;
  };
}