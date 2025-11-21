#pragma once

#include <Mvx2API/Mvx2API.h>
#include <Mvx2API/graphnodes/SingleFilterGraphNode.h>

namespace Mvx2API
{
  struct InputEvent;

  namespace Experimental
  {
    /// \brief A graph node for rendering visual Mvx2 data.
    /// \details 
    /// \par
    /// The rendering algorithm of rendering filters is not executed from the pipeline processing thread - instead it is
    /// invoked manually whenever rendering is appropriate and requested from a client's code. During the pipeline execution
    /// the rendering filters only 'cache' visual data they work with.
    /// \par
    /// Internally maintains a single rendering filter. The same filter is reused even when the graph node
    /// is added to multiple graphs.
    class RendererGraphNode : public SingleFilterGraphNode
    {
    public:
      /// \brief A constructor.
      /// \param rendererGuid a Guid of renderer filter to instantiate
      /// \exception std::invalid_argument raised when a filter with the given Guid is not registered or it is not a renderer
      MVX2_API RendererGraphNode(MVCommon::Guid const & rendererGuid);
      /// \brief A destructor.
      MVX2_API virtual ~RendererGraphNode();

      /// \brief Invokes rendering of cached data using internal rendering facility.
      /// \param width      a width of the frame buffer object (or screen) to render into
      /// \param height     a height of the frame buffer object (or screen) to render into
      /// \param reinit     forces reinitialization of the internal rendering facility (e.g. resources, shaders) if it was initialized already
      /// \param fbo        a frame buffer object to render into (0 to render to default buffer object)
      /// \exception std::runtime_error raised when internal filter does not exist yet or it is not a renderer
      MVX2_API void Render(int32_t width, int32_t height, bool reinit, int32_t fbo = 0);

      /// \brief Destroys internal rendering facility (e.g. resources).
      /// \exception std::runtime_error raised when internal filter does not exist yet or it is not a renderer
      MVX2_API void DestroyRenderer();

      /// \brief Gives internal rendering facility an opportunity to handle input events and customize its behaviour.
      /// \param evt  an input event
      /// \exception std::runtime_error raised when internal filter does not exist yet or it is not a renderer
      MVX2_API void HandleInputEvent(InputEvent const & evt);

      DECLARE_CLASS_SPECIFIC_NEW_DELETE(MVX2_API)
    };
  }
}