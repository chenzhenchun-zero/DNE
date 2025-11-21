#pragma once

#include <Mvx2API/Mvx2API.h>
#include <MVCommon/Memory.h>

namespace Mvx2API
{
  class AtomListImpl;
  class SharedAtomPtr;

  /// \brief A collection of streams.
  class AtomList
  {
  public:
    /// \brief A constructor.
    MVX2_API AtomList();
    /// \brief A copy-constructor.
    /// \param other  another collection to copy streams from
    MVX2_API AtomList(AtomList const & other);
    /// \brief A destructor.
    MVX2_API ~AtomList();

    /// \brief Pushes a stream to the collection.
    /// \param atom a stream to push
    MVX2_API void PushBack(SharedAtomPtr const & atom);

    /// \brief Returns a stream at a given index in the collection.
    /// \param pos  an index of stream to return
    /// \returns    a stream at the index
    MVX2_API SharedAtomPtr & operator[](uint32_t pos);
    /// \brief Returns a stream at a given index in the collection.
    /// \param pos  an index of stream to return
    /// \returns    a stream at the index
    MVX2_API SharedAtomPtr const & operator[](uint32_t pos) const;

    /// \brief Returns a count of streams in the collection.
    /// \returns  streams count
    MVX2_API uint32_t Count() const;
    /// \brief Empties the collection.
    MVX2_API void Clear();

    DECLARE_CLASS_SPECIFIC_NEW_DELETE(MVX2_API)

  private:
    AtomListImpl * _pImpl;
  };
}