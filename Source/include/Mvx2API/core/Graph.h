#pragma once

#include <Mvx2API/Mvx2API.h>
#include <MVCommon/Memory.h>

namespace Mvx2API
{
  class GraphImpl;

  /// \brief A graph of data-processing nodes.
  class Graph : private NonAssignable
  {
  public:
    /// \cond
    Graph(GraphImpl * pImpl);
    /// \endcond
    /// \brief A destructor.
    MVX2_API virtual ~Graph();

    /// \brief Reinitializes the graph.
    /// \details 
    /// \par
    /// Fails if the graph is currently in a running state. Otherwise all filters of the graph are deinitialized, removed from it,
    /// reinitialized and readded to the graph. If any of the actions on any of the filters fails, the graph may remain in an
    /// invalid state and may not be usable anymore.
    /// \par
    /// The purpose of the function is to allow modification of 'hard' parameters of filters, which normally have no impact on
    /// the graph once they have been initialized. These parameters may significantly change behaviour of filters and the whole
    /// graph.
    /// \returns  true if the reinitialization succeeds
    MVX2_API bool Reinitialize();

    DECLARE_CLASS_SPECIFIC_NEW_DELETE(MVX2_API)
  
    /// \cond
    GraphImpl * GetImpl() const { return _pImpl; }
    /// \endcond

  private:
    GraphImpl * _pImpl;
  };
}