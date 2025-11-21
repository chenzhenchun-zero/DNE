#pragma once

#include <Mvx2BasicIO/Mvx2BasicIO.h>
#include <Mvx2API/graphnodes/SingleFilterGraphNode.h>

namespace Mvx2BasicIO
{
  /// \brief A target graph node for writing frames to an MVX2 file.
  /// \details
  /// Internally maintains a single writing filter. The same filter is reused even when the graph node is added to multiple graphs.
  class Mvx2FileWriterGraphNode : public Mvx2API::SingleFilterGraphNode
	{
  public:
    /// \brief A constructor.
    /// \param filePath         a path of the MVX2 file to write to
    /// \param enableRecording  an indication whether the recording shall be enabled right away
    MVX2BASICIO_API Mvx2FileWriterGraphNode(MVCommon::String const & filePath, bool enableRecording = true);
    /// \brief A destructor.
    MVX2BASICIO_API virtual ~Mvx2FileWriterGraphNode();

    /// \brief Enables/disables actual recording to the MVX2 file.
    /// \param enable true in order to enable recording, false in order to disable it
    MVX2BASICIO_API void EnableRecording(bool enable = true) const;

    /// \brief Changes the path of the MVX2 file to write to.
    /// \param filePath a new path of the MVX2 file
    MVX2BASICIO_API void SetFilePath(MVCommon::String const & filePath) const;

    DECLARE_CLASS_SPECIFIC_NEW_DELETE(MVX2BASICIO_API)
	};
}

