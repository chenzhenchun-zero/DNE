#pragma once

#include <Mvx2API/Mvx2API.h>
#include <Mvx2API/core/GraphNode.h>
#include <Mvx2API/filters/SharedFilterPtr.h>

namespace Mvx2API
{
  class Frame;

  /// \brief A source graph node for manual production of MVX frames.
  /// \details
  /// \par
  /// Allows to add frames on the fly, while the graph node is in a running graph.
  /// \par
  /// Internally maintains a single filter for synchronous access to frames. The same filter is reused even when
  /// the graph node is added to multiple graphs.
  class ManualLiveFrameSourceGraphNode : public GraphNode
  {
  public:
    /// \brief A constructor.
    /// \exception std::runtime_error raised in case the creation of the internal filter fails
    MVX2_API ManualLiveFrameSourceGraphNode();
    /// \brief A destructor.
    MVX2_API virtual ~ManualLiveFrameSourceGraphNode();

    /// \cond
    virtual void GetFilters(SharedFilterPtr spPrecedingFilter, FilterList & targetFilterList) override;
    /// \endcond

    /// \brief Clears the queue of frames and reinitializes the internal filter's properties based on the first stream of a provided frame.
    /// \details
    /// \par
    /// Graph node can only be reinitialized while it was not yet added to a graph. Reinitialization causes the remaining 
    /// cached frames to be destroyed, since they may not be valid after the reinitialization.
    /// \par
    /// The properties of the filter that are initialized include the filter's output profile and stream information.
    /// \param pFrame       a frame to reinitialize the internal filter's properties with
    /// \param declaredFPS  declared rate of frames production
    /// \param reassignSequentialFrameNumbers
    /// determines whether the graph node should assign new (sequential) numbers to frames pushed to its output, or leave original numbers
    /// in place
    /// \returns  true if the reinitialization was successful
    MVX2_API bool ClearCacheAndReinitializeProperties(Frame const * pFrame, float declaredFPS, bool reassignSequentialFrameNumbers = true);

    /// \brief Checks whether the internal filter's properties have been initialized already.
    /// \returns  true if the properties have been already initialized
    MVX2_API bool PropertiesAreInitialized() const;

    /// \brief Clears the queue of frames.
    /// \param revertReassignedFrameNumbers
    /// in case the reassignment of frame numbers is enabled, determines whether frame numbers assigned to the to-be removed frames
    /// shall be reused for potential new frames pushed to the filter afterwards
    MVX2_API void ClearCache(bool revertReassignedFrameNumbers = true);

    /// \brief Pushes another frame to the queue.
    /// \details 
    /// A frame will only be pushed if it has exactly the same number of streams as was declared during the initialization of the graph node,
    /// and if data layers of all its streams satisfy the output profile of the internal filter (i.e. the filter's properties must be
    /// initialized already).
    /// \param pFrame a frame to push
    /// \returns      true if the frame was pushed to the queue
    MVX2_API bool PushFrame(Frame const * pFrame);

    DECLARE_CLASS_SPECIFIC_NEW_DELETE(MVX2_API)

  private:
    SharedFilterPtr _spSource;
  };
}

