#pragma once

#include <Mvx2API/Mvx2API.h>
#include <MVCommon/Memory.h>
#include <MVCommon/utils/String.h>

namespace Mvx2API
{
  class GraphNode;

  /// \brief A listener for changes of graph nodes' parameters.
  class IParameterValueChangedListener : private NonAssignable
  {
  public:
    /// \brief A destructor.
    MVX2_API virtual ~IParameterValueChangedListener();

    /// \brief A callback executed when a parameter of a graph node changes its value.
    /// \param pGraphNode         a graph node containing the changed parameter
    /// \param parameterName      name of the changed parameter
    /// \param parameterValueStr  parameter's new value in a string form
    MVX2_API virtual void OnParameterValueChanged(GraphNode * pGraphNode,
      MVCommon::String const & parameterName, MVCommon::String const & parameterValueStr) = 0;

    DECLARE_CLASS_SPECIFIC_NEW_DELETE(MVX2_API)
  };
}