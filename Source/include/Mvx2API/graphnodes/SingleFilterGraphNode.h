#pragma once

#include <Mvx2API/Mvx2API.h>
#include <Mvx2API/core/GraphNode.h>
#include <Mvx2API/filters/FilterList.h>
#include <Mvx2API/filters/SharedFilterPtr.h>
#include <Mvx2API/filters/FilterParameterNameIterator.h>
#include <MVCommon/utils/String.h>

namespace MVCommon
{
  struct Guid;
}

namespace Mvx2API
{
  class IParameterValueChangedListener;
  struct SingleFilterGraphNodeImpl;

  /// \brief A graph node with a single custom, explicitly specified, processing filter.
  /// \details
  /// Allows to maintain internally a single filter reused when the graph node is added to multiple graphs, or to
  /// create a new filter every time the graph node is added to a graph.
  class SingleFilterGraphNode : public GraphNode
  {
  public:
    /// \brief A constructor.
    /// \param filterGuid a GUID of filter
    /// \param singleFilterInstance
    /// determines whether a single instance of the internal filter shall be created and reused, or a new instance shall be created
    /// whenever the graph node is added to a graph
    /// \param filterName a custom name of the filter
    MVX2_API SingleFilterGraphNode(MVCommon::Guid const & filterGuid, bool singleFilterInstance = false, MVCommon::String const & filterName = "");
    /// \brief A destructor.
    MVX2_API virtual ~SingleFilterGraphNode();
    
    /// \cond
    /// \exception std::runtime_error raised in case the creation of the internal filter fails
    MVX2_API virtual void GetFilters(SharedFilterPtr spPrecedingFilter, FilterList & targetFilterList) override;
    /// \endcond

    /// \brief Sets a value of the filter's parameter.
    /// \param paramName  a name of the parameter to set
    /// \param value      a string representation of the value to set
    /// \returns          true if the parameter exists and its value was set, false otherwise
    /// \exception std::runtime_error raised in case the internal filter is supposed to exist already but does not
    /// \details
    /// Parameters are set to the latest created filter in case a new filter instance is supposed to be created
    /// for each graph. Before the creation of the first filter, the parameters are cached and set when the filter is created.
    MVX2_API bool SetFilterParameterValue(MVCommon::String const & paramName, MVCommon::String const & value) const;
    /// \brief Returns a value of the filter's parameter.
    /// \param paramName  a name of the parameter to get
    /// \param value      a resulting parameter value after the call in case true is returned
    /// \returns          true if the parameter exists and its value was retrieved
    /// \exception std::runtime_error raised in case the internal filter does not exist yet
    MVX2_API bool TryGetFilterParameterValue(MVCommon::String const & paramName, MVCommon::String & value) const;

    /// \brief Registers a listener for a parameter value changed event.
    /// \param paramName                      a name of the parameter to listen to changes of
    /// \param pParameterValueChangedListener a listener for the value change event
    /// \returns                              true if the parameter exists and the listener was successfully attached to its changes
    /// \exception std::runtime_error raised in case the internal filter is supposed to exist already but does not
    MVX2_API bool RegisterParameterValueChangedListener(MVCommon::String const & paramName,
      IParameterValueChangedListener * pParameterValueChangedListener);

    /// \brief Unregisters a listener for a parameter value changed event.
    /// \param paramName                      a name of the parameter to stop listening to changes of
    /// \param pParameterValueChangedListener a listener to unregister
    MVX2_API void UnregisterParameterValueChangedListener(MVCommon::String const & paramName,
      IParameterValueChangedListener * pParameterValueChangedListener);

    /// \brief Unregisters all registered listeners for any parameter value changed events.
    MVX2_API void UnregisterAllParameterValueChangedListeners();

    /// \brief An alternative type name declaration for \ref FilterParameterNameIterator.
    typedef FilterParameterNameIterator Iterator;

    /// \brief Returns an iterator to the first entry of the internal filter's parameters collection.
    /// \returns  an iterator
    /// \details 
    /// \par
    /// The collection of the same filter's parameters may vary depending on its current internal state and on the state of its
    /// preceeding filters in a graph. Filter parameters are generally created when the graph node is added to a graph via a graph
    /// builder, so enumerating them before that may result in an empty collection. Even further modifications of graph nodes
    /// after they were added to a graph may cause changes in the collection of parameters - especially when hard parameters are
    /// modified and followed by the graph reinitialization.
    /// \par
    /// The returned iterator is equal to ParameterNamesEnd() iterator when the filter does not have any filter parameters.
    /// \exception std::runtime_error raised in case the internal filter does not exist yet
    MVX2_API Iterator ParameterNamesBegin() const;
    /// \brief Returns an iterator to the last entry of the internal filter's parameters collection.
    /// \returns  an iterator
    /// \exception std::runtime_error raised in case the internal filter does not exist yet
    MVX2_API Iterator ParameterNamesEnd() const;

    DECLARE_CLASS_SPECIFIC_NEW_DELETE(MVX2_API)

  protected:
    /// \cond
    SharedFilterPtr _spFilter;
    /// \endcond

  private:
    SingleFilterGraphNodeImpl * _pImpl;
    
    void CreateFilter(SharedFilterPtr spPrecedingFilter);
  };
}