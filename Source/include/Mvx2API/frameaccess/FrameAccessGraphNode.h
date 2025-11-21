#pragma once

#include <Mvx2API/Mvx2API.h>
#include <Mvx2API/graphnodes/SingleFilterGraphNode.h>

#include "Frame.h"

namespace Mvx2API
{
  class Frame;

  /// \brief A graph node for direct access to processed MVX frames.
  /// \details
  /// Internally maintains a single filter for synchronous access to frames. The same filter is reused even when
  /// the graph node is added to multiple graphs.
  class FrameAccessGraphNode : public SingleFilterGraphNode
  {
  public:
    /// \brief A constructor.
    MVX2_API FrameAccessGraphNode();
    /// \brief A destructor.
    MVX2_API virtual ~FrameAccessGraphNode();

    /// \brief Returns the most recent frame processed by a containing graph.
    /// \details It is a responsibility of the client to dispose the returned frame.
    /// \returns  the most recent processed frame (may be null, e.g. when MVX stream is over or there was no frame processed in the recent update)
    MVX2_API Frame * GetRecentProcessedFrame();

    DECLARE_CLASS_SPECIFIC_NEW_DELETE(MVX2_API)
  };
}

