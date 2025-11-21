#pragma once

#include <Mvx2API/Mvx2API.h>
#include "AtomList.h"
#include <MVCommon/Memory.h>

#include <MVCommon/guid/Guid.h>
#include <Mvx2API/data/dataprofiles/DataProfileIterator.h>

namespace Mvx2API
{
  class FrameImpl;

  /// \brief A frame of data.
  class Frame : private NonAssignable
  {
  public:
    /// \cond
    Frame(FrameImpl * pImpl);
    /// \endcond
    /// \brief A constructor.
    /// \param streams  a collection of streams to compose the frame from
    MVX2_API Frame(AtomList const & streams);
    /// \brief A destructor.
    MVX2_API ~Frame();

    /// \brief Returns streams count of the frame.
    /// \returns  streams count
    MVX2_API uint32_t GetNumStreams() const;
    /// \brief Sets a stream of the frame to be active.
    /// \param activeStreamIndex  an index of the stream to activate
    /// \returns                  true if the stream was successfully activated
    MVX2_API bool ActivateStreamWithIndex(uint32_t activeStreamIndex);
    /// \brief Returns index of the currently active stream of the frame.
    /// \returns  currently active stream's index
    MVX2_API uint32_t GetActiveStreamIndex() const;

    /// \brief Returns ID of the currently active stream of the frame.
    /// \returns  currently active stream's ID
    MVX2_API uint16_t GetStreamId() const;
    /// \brief Returns the atom number in the currently active stream of the frame.
    /// \returns  atom number in the currently active stream
    MVX2_API uint32_t GetStreamAtomNr() const;
    /// \brief Returns the atom timestamp in the currently active stream of the frame.
    /// \returns  atom timestamp in the currently active stream
    MVX2_API uint64_t GetStreamAtomTimestamp() const;

    /// \brief Checks whether the currently active stream contains a data layer with a given guid.
    /// \param dataLayerGuid                a guid of the data layer to check
    /// \param purposeGuid                  a purpose guid of the data layer to check (Guid::Nil() is interpreted as 'any' purpose guid)
    /// \param checkCompressedDataLayersToo an indication whether to check also compressed data layers
    /// \returns                            true in case the data layer (compressed and/or uncompressed) is present in the stream
    MVX2_API bool StreamContainsDataLayer(MVCommon::Guid const & dataLayerGuid,
      MVCommon::Guid const & purposeGuid = MVCommon::Guid::Nil(), bool checkCompressedDataLayersToo = true);

    /// \brief An alternative type name declaration for \ref DataProfileIterator.
    using Iterator = DataProfileIterator;

    /// \brief Returns an iterator to the first data profile entry of the active stream.
    /// \details The returned iterator is equal to DataProfilesEnd() iterator when the active stream does not have any data.
    /// \returns  an iterator
    MVX2_API Iterator DataProfilesBegin() const;
    /// \brief Returns an iterator to the last data profile entry of the active stream.
    /// \returns  an iterator
    MVX2_API Iterator DataProfilesEnd() const;

    /// \brief Returns the collection of streams the frame is composed of.
    /// \returns  the streams collection
    MVX2_API AtomList GetStreams() const;
    /// \brief Returns currently active stream.
    /// \returns  active stream
    MVX2_API SharedAtomPtr GetActiveStream() const;

    DECLARE_CLASS_SPECIFIC_NEW_DELETE(MVX2_API)

  private:
    FrameImpl * _pImpl;
  };
}