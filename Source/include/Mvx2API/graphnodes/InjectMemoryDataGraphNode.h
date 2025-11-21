#pragma once

#include <Mvx2API/Mvx2API.h>
#include <Mvx2API/core/GraphNode.h>
#include <Mvx2API/filters/FilterList.h>
#include <Mvx2API/filters/SharedFilterPtr.h>
#include <MVCommon/guid/Guid.h>

namespace MVCommon
{
  class ByteArray;
}

namespace Mvx2API
{
  /// \brief A graph node for injecting binary data from memory to frames.
  /// \details
  /// Internally maintains a single data-injecting filter. The same filter is reused even when the graph node
  /// is added to multiple graphs.
  class InjectMemoryDataGraphNode : public GraphNode
  {
  public:
    /// \brief A constructor.
    /// \param dataPurposeGuid  purpose guid of the injected data
    /// \exception std::runtime_error raised in case the creation of the internal filter fails
    MVX2_API InjectMemoryDataGraphNode(MVCommon::Guid const & dataPurposeGuid);
    /// \brief A destructor.
    MVX2_API ~InjectMemoryDataGraphNode();

    /// \cond
    virtual void GetFilters(SharedFilterPtr spPrecedingFilter, FilterList & targetFilterList) override;
    /// \endcond

    /// \brief Sets a new data to inject to frames.
    /// \param data a data
    MVX2_API void SetData(MVCommon::ByteArray const & data);

    DECLARE_CLASS_SPECIFIC_NEW_DELETE(MVX2_API)

  private:
    SharedFilterPtr _spFilter;
  };
}

