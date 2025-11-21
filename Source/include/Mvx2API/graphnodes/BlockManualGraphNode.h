#pragma once

#include <Mvx2API/Mvx2API.h>
#include "BlockGraphNode.h"

namespace Mvx2API
{
  /// \brief A blocking graph node with a manual frames-pulling capability.
  /// \details
  /// Internally maintains a single blocking filter. The same filter is reused even when the graph node is added to multiple graphs.
  class BlockManualGraphNode : public BlockGraphNode
  {
  public:
    /// \brief A constructor.
    /// \param bufferSize     a size of internal frames buffer
    /// \param fullBehaviour  an initial full-behaviour
    /// \exception std::runtime_error raised in case the creation of the internal filter fails
    MVX2_API BlockManualGraphNode(uint32_t bufferSize = 3, FullBehaviour fullBehaviour = FB_DROP_FRAMES);
    /// \brief A destructor.
    MVX2_API virtual ~BlockManualGraphNode();

    /// \brief Releases the oldest of the buffered frames for further processing.
    /// \details Effectively makes a space for another processed frame.
    MVX2_API void PullNextProcessedFrame();

    DECLARE_CLASS_SPECIFIC_NEW_DELETE(MVX2_API)

  protected:
    /// \cond
    virtual SharedFilterPtr GetBlockFilter() const override;
    /// \endcond

  private:
    SharedFilterPtr _spMutateBlock;
  };
}