#pragma once

#include <Mvx2API/Mvx2API.h>
#include <Mvx2API/core/GraphNode.h>
#include <Mvx2API/filters/FilterList.h>
#include <Mvx2API/filters/SharedFilterPtr.h>

namespace Mvx2API
{
  /// \brief A graph node with a buffering and execution-blocking capabilities.
  /// \details
  /// Internally maintains a single blocking filter. The same filter is reused even when the graph node is added to multiple graphs.
  class BlockGraphNode : public GraphNode
  {
  public:
    /// \brief Enumeration of supported behaviours when the buffer of the node is full.
    enum FullBehaviour
    {
      /// \brief Additional frames are dropped.
      FB_DROP_FRAMES,
      /// \brief Execution of additional frames is blocked.
      FB_BLOCK_FRAMES
    };

    /// \cond
    BlockGraphNode();
    virtual ~BlockGraphNode();

    virtual void GetFilters(SharedFilterPtr spPrecedingFilter, FilterList & targetFilterList) override;
    /// \endcond

    /// \brief Sets a full-behaviour - action to perform when the internal buffer of frames becomes full.
    /// \param fullBehaviour  a behaviour to set
    MVX2_API void SetFullBehaviour(FullBehaviour fullBehaviour);
    /// \brief Gets a value of internal counter of dropped frames.
    /// \returns  dropped frames count
    MVX2_API uint64_t GetDroppedFramesCount() const;
    /// \brief Resets the internal counter of dropped frames to zero.
    MVX2_API void ResetDroppedFramesCounter() const;

    DECLARE_CLASS_SPECIFIC_NEW_DELETE(MVX2_API)

  protected:
    /// \cond
    virtual SharedFilterPtr GetBlockFilter() const = 0;

    void SetBufferSize(uint32_t bufferSize);
    /// \endcond
  };
}

