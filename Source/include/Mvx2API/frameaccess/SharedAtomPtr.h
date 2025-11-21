#pragma once

#include <Mvx2API/Mvx2API.h>
#include <MVCommon/Memory.h>

namespace MVX
{
  class Atom;
}

namespace Mvx2API
{
  class SharedAtomPtrImpl;
  
  /// \brief A shared smart-pointer to a stream.
  /// \details
  /// Allows sharing of the same stream object by multiple owners and automatically destroys stream objects when no more pointers
  /// point to them.
  class SharedAtomPtr
  {
  public:
    /// \cond
    SharedAtomPtr(SharedAtomPtrImpl * pImpl);
    /// \endcond
    /// \brief A constructor.
    /// \details Initializes the pointer with nullptr.
    MVX2_API SharedAtomPtr();
    /// \brief A constructor.
    /// \param pAtom  a stream to share a pointer to
    MVX2_API SharedAtomPtr(MVX::Atom * pAtom);
    /// \brief A copy-constructor.
    /// \param other  other pointer to share a pointed-to stream with
    MVX2_API SharedAtomPtr(SharedAtomPtr const & other);
    /// \brief A destructor.
    /// \details Destroys the pointed-to stream if this was the last pointer pointing to it.
    MVX2_API ~SharedAtomPtr();

    /// \brief Makes the pointer point to a stream pointed to by the \p other pointer.
    /// \details Destroys previously pointed-to stream if this was the last pointer pointing to it.
    /// \param other  other pointer to share a pointed-to stream with
    /// \returns      the pointer itself
    MVX2_API SharedAtomPtr & operator=(SharedAtomPtr const & other);
    /// \brief Makes the pointer point to a stream.
    /// \details Destroys previously pointed-to stream if this was the last pointer pointing to it.
    /// \param pAtom  a stream to point to
    /// \returns      the pointer itself
    MVX2_API SharedAtomPtr & operator=(MVX::Atom * pAtom);

    /// \brief Converts the pointer to a boolean value.
    /// \returns  true in case the pointed-to stream is not null
    MVX2_API operator bool() const;
    /// \brief 'Indirection' operator.
    /// \returns  a reference to the pointed-to stream
    MVX2_API MVX::Atom & operator*() const;
    /// \brief 'Dereference' operator.
    /// \returns  a raw pointer to the pointed-to stream
    MVX2_API MVX::Atom * operator->() const;
    /// \brief Returns a raw pointer to the pointed-to stream.
    /// \returns  a raw pointer to the pointed-to stream
    MVX2_API MVX::Atom * Get() const;

    DECLARE_CLASS_SPECIFIC_NEW_DELETE(MVX2_API)
    
    /// \cond
    SharedAtomPtrImpl * GetImpl() const { return _pImpl; }
    /// \endcond

  private:
    SharedAtomPtrImpl * _pImpl;
  };
}