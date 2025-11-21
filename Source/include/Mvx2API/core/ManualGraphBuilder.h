#pragma once

#include <Mvx2API/Mvx2API.h>
#include <MVCommon/Memory.h>
#include "GraphBuilder.h"

namespace Mvx2API
{
  class GraphNode;
  class Graph;
  class ManualGraphBuilderImpl;

  /// \brief A manual builder of data-processing graphs.
  class ManualGraphBuilder : public GraphBuilder
  {
  public:
    /// \brief A constructor.
    MVX2_API ManualGraphBuilder();
    /// \brief A destructor.
    MVX2_API ~ManualGraphBuilder();

    /// \brief Appends a graph node to the graph being built.
    /// \param graphNode  a graph node to append
    /// \returns          the builder itself
    /// \exception std::runtime_error raised when the graph builder fails to append the graph node to the graph
    MVX2_API ManualGraphBuilder & operator<<(GraphNode & graphNode);
    /// \brief Appends a graph node to the graph being built.
    /// \param graphNode  a graph node to append
    /// \returns          the builder itself
    /// \exception std::runtime_error raised when the graph builder fails to append the graph node to the graph
    MVX2_API ManualGraphBuilder & operator<<(GraphNode && graphNode);
    /// \brief Appends a graph node to the graph being built.
    /// \param graphNode  a graph node to append
    /// \exception std::runtime_error raised when the graph builder fails to append the graph node to the graph
    MVX2_API void AppendGraphNode(GraphNode & graphNode);

    /// \brief Compiles a graph being built and resets the builder for another graph to be built.
    /// \details
    /// The graph is being reinitialized during the compilation so filter parameter changes which would potentially
    /// modify its behaviour can take effect. However, since the reinitialization of the graph may fail, the compilation
    /// of the graph may fail as well. In such case the graph being built is not replaced by a new graph in the builder
    /// and after fixing the filter parameters, the graph compilation may be attempted again.
    /// \returns  a compiled graph or nullptr if the graph reinitialization fails
    MVX2_API virtual Graph * CompileGraphAndReset() override;
    /// \brief Resets the builder by removing all already appended graph nodes.
    MVX2_API virtual void Reset() override;

    DECLARE_CLASS_SPECIFIC_NEW_DELETE(MVX2_API)

  private:
    ManualGraphBuilderImpl * _pImpl;
  };
}