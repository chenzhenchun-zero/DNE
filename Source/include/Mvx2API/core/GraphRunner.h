#pragma once

#include <Mvx2API/Mvx2API.h>
#include <MVCommon/Memory.h>

#include "Graph.h"

namespace Mvx2API
{
  class SourceInfo;

  /// \brief A runner of data-processing graphs.
  class GraphRunner : private NonAssignable
  {
  public:
    /// \brief A destructor.
    MVX2_API virtual ~GraphRunner();

    /// \brief Retrieves source information about the currently open MVX source.
    /// \returns  information about the current MVX source or null if no source is open
    MVX2_API virtual SourceInfo* GetSourceInfo() const = 0;

    DECLARE_CLASS_SPECIFIC_NEW_DELETE(MVX2_API)
  };
}