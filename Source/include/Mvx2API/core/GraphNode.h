#pragma once

#include <Mvx2API/Mvx2API.h>
#include <MVCommon/Memory.h>
#include <Mvx2API/filters/FilterList.h>

namespace Mvx2API
{
  /// \brief A processing node.
  /// \details
  /// \par
  /// Each node can be added to multiple graphs as long as at any point in time it only is added to only one. A graph that the graph node
  /// is currently in must first be completely destroyed before the graph node can be added to another graph. Attempts to add the same
  /// graph node to multiple graphs at the same time will end with a failure. 
  /// \par
  /// What happens when a graph node was in a graph and is then added to another graph depends on its implementation. Some graph nodes
  /// may permanently keep the same collection of processing filters, reusing them this way effectively in multiple graphs. Other 
  /// implementations may create a new collection of filters each time they are added to a graph.
  class GraphNode : private NonAssignable
  {
  public:
    /// \brief A constructor.
    MVX2_API GraphNode();
    /// \brief A destructor.
    MVX2_API virtual ~GraphNode();

    /// \brief A getter of all MVX filters created and managed internally by the node.
    /// \param spPrecedingFilter
    /// a pointer to the last filter preceding the filters to be added by the graph node, so the added filters 
    /// can be initialized with it in case they need to be
    /// \param targetFilterList a collection to add filters to
    /// \exception std::runtime_error raised when there is an error getting filters from the graph node
    MVX2_API virtual void GetFilters(SharedFilterPtr spPrecedingFilter, FilterList & targetFilterList) = 0;

    DECLARE_CLASS_SPECIFIC_NEW_DELETE(MVX2_API)
  };
}