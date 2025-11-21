#pragma once

#include <Mvx2BasicIO/Mvx2BasicIO.h>
#include <Mvx2API/graphnodes/SingleFilterGraphNode.h>

namespace Mvx2BasicIO
{
  /// \brief A target graph node for asynchronous writing frames to an MVX2 file.
  /// \details
  /// \par 
  /// Asynchronous writing means that frames are pushed to a buffer from the pipeline thread and are pulled from the buffer and
  /// written to a file from a standalone writing thread.
  /// \par 
  /// Internally maintains a single writing filter. The same filter is reused even when the graph node is added to multiple graphs.
  class Mvx2FileAsyncWriterGraphNode : public Mvx2API::SingleFilterGraphNode
	{
  public:
    /// \brief Enumeration of supported behaviours when the buffer of frames is full.
    enum FullBehaviour
    {
      /// \brief When buffer is full, new frames from pipeline are dropped and pipeline continues its execution.
      FB_DROP_FRAMES,
      /// \brief When buffer is full, pipeline thread is blocked until there is some free space in the buffer.
      FB_BLOCK_FRAMES
    };

    /// \brief A constructor.
    /// \param filePath         a path of the MVX2 file to write to
    /// \param enableRecording  an indication whether the recording shall be enabled right away
    /// \param bufferSize       a size of frames buffer
    /// \param fullBehaviour    an initial full-behaviour
    MVX2BASICIO_API Mvx2FileAsyncWriterGraphNode(MVCommon::String const & filePath, bool enableRecording = true,
      uint32_t bufferSize = 3, FullBehaviour fullBehaviour = FB_DROP_FRAMES);
    /// \brief A destructor.
    MVX2BASICIO_API virtual ~Mvx2FileAsyncWriterGraphNode();

    /// \brief Enables/disables actual recording to the MVX2 file.
    /// \param enable true in order to enable recording, false in order to disable it
    MVX2BASICIO_API void EnableRecording(bool enable = true) const;

    /// \brief Changes the path of the MVX2 file to write to.
    /// \param filePath a new path of the MVX2 file
    MVX2BASICIO_API void SetFilePath(MVCommon::String const & filePath) const;

    /// \brief Sets a full-behaviour - action to perform when the buffer of frames becomes full.
    /// \param fullBehaviour  a behaviour to set
    MVX2BASICIO_API void SetFullBehaviour(FullBehaviour fullBehaviour);
    
    /// \brief Gets a value of internal counter of dropped frames.
    /// \returns  dropped frames count
    MVX2BASICIO_API uint64_t GetDroppedFramesCount() const;
    
    /// \brief Resets the internal counter of dropped frames to zero.
    MVX2BASICIO_API void ResetDroppedFramesCounter() const;

    DECLARE_CLASS_SPECIFIC_NEW_DELETE(MVX2BASICIO_API)
	};
}

