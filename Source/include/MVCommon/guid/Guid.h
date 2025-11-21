#pragma once

#include <MVCommon/MVCommonAPI.h>
#include <MVCommon/Memory.h>
#include <MVCommon/utils/String.h>
#include <MVCommon/utils/ByteArray.h>

namespace MVCommon
{
  struct GuidImpl;

  /// \brief A globally-unique identifier implementation.
  struct Guid
  {
  public:
    /// \brief A constructor of a Guid with all bytes set to 0.
    MVCOMMON_API Guid();
    /// \brief A copy constructor.
    /// \param other  a Guid to make a copy of
    MVCOMMON_API Guid(Guid const & other);
    /// \brief A move constructor.
    /// \param other  a Guid to move
    MVCOMMON_API Guid(Guid && other);
    /// \brief A destructor.
    MVCOMMON_API virtual ~Guid();
    
    /// \brief Constructs a new Nil Guid (with all bytes set to 0).
    /// \returns  a Nil Guid
    MVCOMMON_API static Guid Nil();

    /// \brief Parses a string in hexadecimal format 00000000-0000-0000-0000-000000000000 into a Guid.
    /// \param str  a string to parse
    /// \returns    a Guid
    /// \details
    /// The input string must be at least 32 characters long (i.e. 32 hexa characters). It can optionally contain an opening
    /// and a closing bracket ('{' and '}') and 4 hyphens on specific positions of the string.
    /// \exception std::invalid_argument  raised when the format of the string is invalid and can not be parsed
    MVCOMMON_API static Guid FromHexString(String const & str);

    /// \brief Constructs a Guid using a raw bytes array (must contain 16 elements).
    /// \param bytes        an array of 16 bytes
    /// \param consumeBytes an indication whether the bytes of the array shall be consumed
    /// \returns            a Guid
    /// \exception std::invalid_argument  raised when there are not enough bytes in the array
    MVCOMMON_API static Guid FromRawBytes(ByteArray & bytes, bool consumeBytes = false);

    /// \brief Constructs a Guid using an array of bytes in RFC 4122 format (must contain 16 elements).
    /// \param bytes        an array of 16 bytes in RFC 4122 format
    /// \param consumeBytes an indication whether the bytes of the array shall be consumed
    /// \returns            a Guid
    /// \exception std::invalid_argument  raised when there are not enough bytes in the array
    MVCOMMON_API static Guid FromRfc4122(ByteArray & bytes, bool consumeBytes = false);

    /// \brief Formats the Guid to hexadecimal 00000000-0000-0000-0000-000000000000 format.
    /// \returns  a string of 36 characters (32 for hexa characters and 4 for hyphens)
    MVCOMMON_API String ToHexString() const;

    /// \brief Formats the Guid into a raw bytes array.
    /// \param bytes  an array to store 16 raw bytes in
    MVCOMMON_API void ToRawBytes(ByteArray & bytes) const;

    /// \brief Formats the Guid into RFC 4122 format.
    /// \param bytes  an array to store 16 raw bytes in RFC 4122 format in
    MVCOMMON_API void ToRfc4122(ByteArray & bytes) const;

    /// \brief A constant indicating the size of raw bytes of the Guid.
    MVCOMMON_API static const size_t RAW_BYTES_SIZE;

    /// \brief A constant indicating the size of bytes in RFC 4122 format of the Guid.
    MVCOMMON_API static const size_t RFC4122_BYTES_SIZE;

    /// \brief Checks whether the Guid is a Nil Guid (with all bytes set to 0).
    /// \returns  true when the Guid is a Nil Guid
    MVCOMMON_API bool IsNil() const;

    /// \cond
    MVCOMMON_API Guid & operator=(Guid other);
    MVCOMMON_API friend bool operator==(Guid const & lhs, Guid const & rhs);
    MVCOMMON_API friend bool operator<(Guid const & lhs, Guid const & rhs);
    /// \endcond

    DECLARE_CLASS_SPECIFIC_NEW_DELETE(MVCOMMON_API)

    /// \cond
    friend struct GuidHasher;
    /// \endcond

  private:
    GuidImpl * _pImpl;
  };

  /// \cond
  MVCOMMON_API bool operator==(MVCommon::Guid const & lhs, MVCommon::Guid const & rhs);
  MVCOMMON_API bool operator!=(MVCommon::Guid const & lhs, MVCommon::Guid const & rhs);
  MVCOMMON_API bool operator<(MVCommon::Guid const & lhs, MVCommon::Guid const & rhs);
  /// \endcond

  /// \brief A hasher for Guid objects so they can be used in unordered collections.
  struct GuidHasher
  {
    /// \brief Calculates a hash value from the object.
    /// \param guid an object to calculate the hash value of
    /// \returns    hash value of the object
    MVCOMMON_API size_t operator()(Guid const & guid) const;
  };
}