#pragma once

#include <Mvx2BasicIO/Mvx2BasicIO.h>
#include <Mvx2API/graphnodes/SingleFilterGraphNode.h>

namespace Mvx2BasicIO
{
  /// \brief A source graph node for reading frames from an MVX2 file.
  /// \details
  /// Internally maintains a single reading filter. The same filter is reused even when the graph node is added to multiple graphs.
  class Mvx2FileReaderGraphNode : public Mvx2API::SingleFilterGraphNode
	{
  public:
    /// \brief A constructor.
    /// \param filePath a path of the MVX2 file to read from
    MVX2BASICIO_API Mvx2FileReaderGraphNode(MVCommon::String const & filePath);
    /// \brief A destructor.
    MVX2BASICIO_API virtual ~Mvx2FileReaderGraphNode();

    /// \brief Changes the path of the MVX2 file to read from.
    /// \param filePath a new path of the MVX2 file
    MVX2BASICIO_API void SetFilePath(MVCommon::String const & filePath) const;

    DECLARE_CLASS_SPECIFIC_NEW_DELETE(MVX2BASICIO_API)
	};
}

