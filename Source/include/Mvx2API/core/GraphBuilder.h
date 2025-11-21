#pragma once

#include <Mvx2API/Mvx2API.h>
#include <MVCommon/Memory.h>

#include "Graph.h"

namespace Mvx2API
{
  class Graph;

  /// \brief A builder of data-processing graphs.
  class GraphBuilder : private NonAssignable
  {
  protected:
    /// \brief A constructor.
    MVX2_API GraphBuilder();

  public:
    /// \brief A destructor.
    MVX2_API virtual ~GraphBuilder();

    /// \brief Compiles a graph being built and resets the builder for another graph to be built.
    /// \details
    /// The graph is being reinitialized during the compilation so filter parameter changes which would potentially
    /// modify its behaviour can take effect. However, since the reinitialization of the graph may fail, the compilation
    /// of the graph may fail as well. In such case the graph being built is not replaced by a new graph in the builder
    /// and after fixing the filter parameters, the graph compilation may be attempted again.
    /// \returns  a compiled graph or nullptr if the graph reinitialization fails
    MVX2_API virtual Graph * CompileGraphAndReset() = 0;
    /// \brief Resets the builder by removing all already appended graph nodes.
    MVX2_API virtual void Reset() = 0;

    DECLARE_CLASS_SPECIFIC_NEW_DELETE(MVX2_API)
  };
}