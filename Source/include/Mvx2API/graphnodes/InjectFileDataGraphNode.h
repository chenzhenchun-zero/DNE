#pragma once

#include <Mvx2API/Mvx2API.h>
#include <Mvx2API/graphnodes/SingleFilterGraphNode.h>

namespace Mvx2API
{
  /// \brief A graph node for injecting binary data from files to frames.
  /// \details 
  /// Internally maintains a single data-injecting filter. The same filter is reused even when the graph node
  /// is added to multiple graphs.
  class InjectFileDataGraphNode : public SingleFilterGraphNode
  {
  public:
    /// \brief A constructor.
    /// \param dataPurposeGuid  purpose guid of the injected data
    MVX2_API InjectFileDataGraphNode(MVCommon::Guid const & dataPurposeGuid);
    /// \brief A destructor.
    MVX2_API ~InjectFileDataGraphNode();

    /// \brief Sets a new file to inject the binary content of to frames.
    /// \param filePath a path of the file
    MVX2_API void SetFile(MVCommon::String const & filePath);

    DECLARE_CLASS_SPECIFIC_NEW_DELETE(MVX2_API)
  };
}