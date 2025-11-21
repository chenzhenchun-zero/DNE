#pragma once

#include <Mvx2API/Mvx2API.h>
#include <Mvx2API/core/GraphNode.h>
#include <Mvx2API/filters/FilterList.h>
#include <Mvx2API/filters/SharedFilterPtr.h>

namespace Mvx2API
{
  /// \brief A graph node for auto-decompression of MVX data.
  /// \details Internally creates a new decompression filter every time the graph node is added to a new graph.
  class AutoDecompressorGraphNode : public GraphNode
  {
  public:
    /// \brief A constructor.
    /// \param dropCompressedInput  an indication whether the original compressed data shall be dropped
    MVX2_API AutoDecompressorGraphNode(bool dropCompressedInput = true);
    /// \brief A destructor.
    MVX2_API virtual ~AutoDecompressorGraphNode();

    /// \cond
    /// \exception std::runtime_error raised in case the creation of the internal filter fails
    virtual void GetFilters(SharedFilterPtr spPrecedingFilter, FilterList & targetFilterList) override;
    /// \endcond

    DECLARE_CLASS_SPECIFIC_NEW_DELETE(MVX2_API)

  private:
    bool _dropCompressedInput;
  };
}

