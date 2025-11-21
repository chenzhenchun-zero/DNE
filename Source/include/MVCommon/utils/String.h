#pragma once

#include <MVCommon/MVCommonAPI.h>
#include <MVCommon/Memory.h>

namespace MVCommon
{
  struct StringImpl;

  /// \brief A string implementation.
  /// \details Manages lifetime of a string.
  class String
  {
  public:
    /// \brief A constructor.
    /// \param cString  a C string
    MVCOMMON_API String(char const * cString = "");
    /// \brief A copy constructor.
    /// \param other  a string to make a copy of
    MVCOMMON_API String(String const & other);
    /// \brief A move constructor.
    /// \param other  a string to move
    MVCOMMON_API String(String && other);
    /// \brief A destructor.
    MVCOMMON_API ~String();

    /// \brief Gets a C string.
    /// \returns  a pointer to the C string
    MVCOMMON_API char const * CStr() const;
    /// \brief Gets length of the string.
    /// \returns  string's length
    MVCOMMON_API size_t Length() const;
    /// \brief Generates a substring of the string.
    /// \param pos  a starting position of the string to generate the substring from
    /// \param len  a length of the substring (special value -1 means the rest of the original string)
    /// \returns    the string's substring
    MVCOMMON_API String Substr(size_t pos = 0, size_t len = -1) const;

    /// \cond
    MVCOMMON_API char & operator[] (size_t pos);
    MVCOMMON_API char const & operator[] (size_t pos) const;

    MVCOMMON_API String & operator=(String other);
    MVCOMMON_API String & operator+=(String const & other);
    MVCOMMON_API friend bool operator==(String const & lhs, String const & rhs);
    MVCOMMON_API friend bool operator<(String const & lhs, String const & rhs);
    /// \endcond

    DECLARE_CLASS_SPECIFIC_NEW_DELETE(MVCOMMON_API)

    /// \cond
    friend struct StringHasher;
    /// \endcond

  private:
    StringImpl * _pImpl;
  };

  /// \cond
  MVCOMMON_API bool operator==(MVCommon::String const & lhs, MVCommon::String const & rhs);
  MVCOMMON_API bool operator<(MVCommon::String const & lhs, MVCommon::String const & rhs);
  MVCOMMON_API bool operator!=(MVCommon::String const & lhs, MVCommon::String const & rhs);
  MVCOMMON_API String operator+(MVCommon::String const & lhs, MVCommon::String const & rhs);
  /// \endcond

  /// \brief A hasher for String objects so they can be used in unordered collections.
  struct StringHasher
  {
    /// \brief Calculates a hash value from the object.
    /// \param string an object to calculate the hash value of
    /// \returns      hash value of the object
    MVCOMMON_API size_t operator()(String const & string) const;
  };
}