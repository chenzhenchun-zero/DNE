#pragma once

#include <Mvx2API/Mvx2API.h>
#include <Mvx2API/core/GraphNode.h>
#include <Mvx2API/filters/FilterList.h>
#include <Mvx2API/filters/SharedFilterPtr.h>

namespace Mvx2API
{
  /// \brief A graph node for auto-compression of MVX data.
  /// \details Internally creates a new compression filter every time the graph node is added to a new graph.
  class AutoCompressorGraphNode : public GraphNode
  {
  public:
    /// \brief A constructor.
    /// \param dropUncompressedInput  an indication whether the original uncompressed data shall be dropped
    MVX2_API AutoCompressorGraphNode(bool dropUncompressedInput = true);
    /// \brief A destructor.
    MVX2_API virtual ~AutoCompressorGraphNode();

    /// \cond
    /// \exception std::runtime_error raised in case the creation of the internal filter fails
    virtual void GetFilters(SharedFilterPtr spPrecedingFilter, FilterList & targetFilterList) override;
    /// \endcond

    DECLARE_CLASS_SPECIFIC_NEW_DELETE(MVX2_API)

  private:
    bool _dropUncompressedInput;
  };
}

