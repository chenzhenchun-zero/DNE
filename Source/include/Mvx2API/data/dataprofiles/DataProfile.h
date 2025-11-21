#pragma once

#include <Mvx2API/Mvx2API.h>

#include <MVCommon/guid/Guid.h>

namespace Mvx2API
{
  struct DataProfileImpl;

  /// \brief A profile of a single data item.
  /// \details A data profile is represented as an MVCommon::Guid triplet:
  ///   - a data type guid (mandatory), 
  ///   - a compressed data type guid (optional - in case the data is a 'wrapper' over actual compressed data),
  ///   - a purpose guid (mandatory).
  class DataProfile
  {
  public:
    /// \brief A constructor.
    /// \param typeGuid           a data type guid
    /// \param compressedTypeGuid a compressed data type guid
    /// \param purposeGuid        a purpose guid
    MVX2_API DataProfile(MVCommon::Guid const & typeGuid, MVCommon::Guid const & compressedTypeGuid, MVCommon::Guid const & purposeGuid);
    /// \brief A copy constructor.
    /// \param other  an instance to make a copy of
    MVX2_API DataProfile(DataProfile const & other);
    /// \brief A move constructor.
    /// \param other  an instance to move
    MVX2_API DataProfile(DataProfile && other);
    /// \brief A destructor.
    MVX2_API virtual ~DataProfile();
    /// \cond
    MVX2_API DataProfile & operator=(DataProfile other);
    /// \endcond

    /// \brief A getter of the data type guid.
    /// \returns  data type guid
    MVX2_API MVCommon::Guid const & GetTypeGuid() const;

    /// \brief A getter of the compressed data type guid.
    /// \returns  compressed data type guid
    MVX2_API MVCommon::Guid const & GetCompressedTypeGuid() const;

    /// \brief A getter of the purpose guid.
    /// \returns  purpose guid
    MVX2_API MVCommon::Guid const & GetPurposeGuid() const;

    /// \cond
    MVX2_API friend bool operator==(DataProfile const & lhs, DataProfile const & rhs);
    /// \endcond

    DECLARE_CLASS_SPECIFIC_NEW_DELETE(MVX2_API)

  private:
    DataProfileImpl * _pImpl;
  };

  /// \cond
  MVX2_API bool operator==(Mvx2API::DataProfile const & lhs, Mvx2API::DataProfile const & rhs);
  MVX2_API bool operator!=(Mvx2API::DataProfile const & lhs, Mvx2API::DataProfile const & rhs);
  /// \endcond

  /// \brief A hasher for DataProfile objects so they can be used in unordered collections.
  struct DataProfileHasher
  {
    /// \brief Calculates a hash value from the object.
    /// \param dataProfile  an object to calculate the hash value of
    /// \returns            hash value of the object
    MVX2_API size_t operator()(DataProfile const & dataProfile) const;
  };
}