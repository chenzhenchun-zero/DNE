/// \file
#pragma once

#include <MVCommon/MVCommonAPI.h>
#include <MVCommon/Memory.h>
#include "String.h"

namespace MVCommon
{
  /// \brief A structure holding module version information.
  struct VersionInfo
  {
    /// \brief A constructor.
    /// \param major  most-significant version component
    /// \param minor  medium-significant version component
    /// \param patch  least-significant version component
    MVCOMMON_API VersionInfo(uint32_t major = 0, uint32_t minor = 0, uint32_t patch = 0);

    /// \brief Most-significant version component.
    /// \details Difference indicates binary-incompatibility.
    uint32_t major;
    /// \brief Medium-significant version component.
    /// \details Increased whenever a new official version is released.
    uint32_t minor;
    /// \brief Least-significant version component.
    /// \details Increased whenever an officially released version is patched and re-released.
    uint32_t patch;
    
    /// \brief Converts the version info into a string with format 'major.minor.patch'.
    /// \returns  a string containing version
    MVCOMMON_API MVCommon::String ToString() const;

    DECLARE_CLASS_SPECIFIC_NEW_DELETE(MVCOMMON_API)
  };

  /// \cond
  MVCOMMON_API bool operator==(VersionInfo const & lhs, VersionInfo const & rhs);
  MVCOMMON_API bool operator!=(VersionInfo const & lhs, VersionInfo const & rhs);
  /// \endcond

  /// \brief A hasher for VersionInfo objects so they can be used in unordered collections.
  struct VersionInfoHasher
  {
    /// \brief Calculates a hash value from the object.
    /// \param versionInfo  an object to calculate the hash value of
    /// \returns            hash value of the object
    MVCOMMON_API size_t operator()(VersionInfo const & versionInfo) const;
  };
}