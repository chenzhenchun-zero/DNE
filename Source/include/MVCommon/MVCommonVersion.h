/// \file
#pragma once

/// \brief Current value of the most-significant MVCommon version component.
#define MVCOMMON_VERSION_MAJOR 4
/// \brief Current value of the medium-significant MVCommon version component.
#define MVCOMMON_VERSION_MINOR 0
/// \brief Current value of the least-significant MVCommon version component.
#define MVCOMMON_VERSION_PATCH 0

#include "utils/VersionInfo.h"

namespace MVCommon
{
  /// \brief An MVCommon version.
  const VersionInfo MVCOMMON_VERSION = { MVCOMMON_VERSION_MAJOR, MVCOMMON_VERSION_MINOR, MVCOMMON_VERSION_PATCH };
}