#pragma once

#include <Mvx2API/Mvx2API.h>
#include "BlockGraphNode.h"

namespace Mvx2API
{
  /// \brief A blocking graph node with an automatized framerate-based frames-pulling capability.
  /// \details
  /// Internally maintains a single blocking filter. The same filter is reused even when the graph node is added to multiple graphs.
  class BlockFPSGraphNode : public BlockGraphNode
  {
  public:
    /// \brief A special framerate value indicating that the maximal possible framerate shall be used.
    MVX2_API static const float FPS_MAX;
    /// \brief A special framerate value indicating that the framerate of an open source shall be used.
    MVX2_API static const float FPS_FROM_SOURCE;
    /// \brief A special framerate value indicating that the half of the framerate of an open source shall be used.
    MVX2_API static const float FPS_HALF_FROM_SOURCE;
    /// \brief A special framerate value indicating that the double of the framerate of an open source shall be used.
    MVX2_API static const float FPS_DOUBLE_FROM_SOURCE;

    /// \brief A constructor.
    /// \param bufferSize     a size of internal frames buffer
    /// \param fps            a framerate to follow with frames-pulling
    /// \param fullBehaviour  an initial full-behaviour
    /// \exception std::runtime_error raised in case the creation of the internal filter fails
    MVX2_API BlockFPSGraphNode(uint32_t bufferSize = 3, float fps = -1.0f, FullBehaviour fullBehaviour = FB_DROP_FRAMES);
    /// \brief A destructor.
    MVX2_API virtual ~BlockFPSGraphNode();

    /// \brief Sets a new framerate to follow with frames-pulling.
    /// \param fps  a framerate to follow
    MVX2_API void SetFPS(float fps);

    DECLARE_CLASS_SPECIFIC_NEW_DELETE(MVX2_API)

  protected:
    /// \cond
    virtual SharedFilterPtr GetBlockFilter() const override;
    /// \endcond

  private:
    SharedFilterPtr _spMutateBlock;
  };
}

