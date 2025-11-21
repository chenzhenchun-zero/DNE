#pragma once

#include <Mvx2API/Mvx2API.h>
#include <MVCommon/Memory.h>

#include <MVCommon/guid/Guid.h>
#include <Mvx2API/data/dataprofiles/DataProfileIterator.h>

namespace Mvx2API
{
  class SourceInfoImpl;

  /// \brief An information provider about an MVX source.
  class SourceInfo : private NonAssignable
  {
  public:
    /// \cond
    SourceInfo(SourceInfoImpl* pImpl);
    /// \endcond
    /// \brief A destructor.
    MVX2_API virtual ~SourceInfo();

    /// \brief Returns number of frames in the source.
    /// \returns  frames count
    MVX2_API uint32_t GetNumFrames() const;
    /// \brief Returns source's framerate.
    /// \returns  framerate
    MVX2_API float GetFPS() const;
    /// \brief Checks whether the source contains a data layer with a given guid.
    /// \param dataLayerGuid                a guid of the data layer to check
    /// \param purposeGuid                  a purpose guid of the data layer to check (Guid::Nil() is interpreted as 'any' purpose guid)
    /// \param checkCompressedDataLayersToo an indication whether to check also compressed data layers
    /// \returns                            true in case the data layer (compressed and/or uncompressed) is present in the source
    MVX2_API bool ContainsDataLayer(MVCommon::Guid const & dataLayerGuid,
      MVCommon::Guid const & purposeGuid = MVCommon::Guid::Nil(), bool checkCompressedDataLayersToo = true) const;

    /// \brief An alternative type name declaration for \ref DataProfileIterator.
    using Iterator = DataProfileIterator;

    /// \brief Returns an iterator to the first data profile entry of the source.
    /// \details The returned iterator is equal to DataProfilesEnd() iterator when the source does not have any data.
    /// \returns  an iterator
    MVX2_API Iterator DataProfilesBegin() const;
    /// \brief Returns an iterator to the last data profile entry of the source.
    /// \returns  an iterator
    MVX2_API Iterator DataProfilesEnd() const;

    DECLARE_CLASS_SPECIFIC_NEW_DELETE(MVX2_API)

  private:
    SourceInfoImpl * _pImpl;
  };
}