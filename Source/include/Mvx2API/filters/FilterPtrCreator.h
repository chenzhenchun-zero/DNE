/// \file
#pragma once

#include "SharedFilterPtr.h"

namespace MVCommon
{
  struct Guid;
}

namespace Mvx2API
{
  namespace FilterPtrCreator
  {
    /// \brief Creates a filter with a given GUID.
    /// \param filterGuid a GUID of filter to create
    /// \returns          a pointer to a new filter or null pointer if the filter could not be created
    MVX2_API SharedFilterPtr CreateFilter(MVCommon::Guid const & filterGuid);

    /// \brief Creates a filter with a given GUID.
    /// \param filterGuid         a GUID of filter to create
    /// \param spPrecedingFilter  a filter the new filter will be pre-initialized with
    /// \returns                  a pointer to a new filter or null pointer if the filter could not be created
    MVX2_API SharedFilterPtr CreateFilter(MVCommon::Guid const & filterGuid, SharedFilterPtr spPrecedingFilter);
  };
}