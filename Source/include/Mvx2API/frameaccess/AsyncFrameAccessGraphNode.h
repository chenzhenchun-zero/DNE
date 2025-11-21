#pragma once

#include <Mvx2API/Mvx2API.h>
#include <Mvx2API/graphnodes/SingleFilterGraphNode.h>

namespace Mvx2API
{
  class TargetAtomsListener;
  class Frame;
  class FrameListener;

  /// \brief A graph node for asynchronous notifications about processed MVX frames.
  /// \details
  /// Internally maintains a single filter for asynchronous access to frames. The same filter is reused even when
  /// the graph node is added to multiple graphs.
  class AsyncFrameAccessGraphNode : public SingleFilterGraphNode
  {
  public:
    /// \brief A constructor.
    /// \param pFrameListener an asynchronous frames listener
    MVX2_API AsyncFrameAccessGraphNode(FrameListener * pFrameListener = nullptr);
    /// \brief A destructor.
    MVX2_API virtual ~AsyncFrameAccessGraphNode();

    /// \brief Sets an asynchronous frame listener to be used.
    /// \param pFrameListener an asynchronous frames listener
    MVX2_API void SetFrameListener(FrameListener * pFrameListener);
    /// \cond
    FrameListener * GetFrameListener() const;
    /// \endcond

    DECLARE_CLASS_SPECIFIC_NEW_DELETE(MVX2_API)

  private:
    TargetAtomsListener * _pTargetAtomsListener;

    FrameListener * _pFrameListener;
  };
}