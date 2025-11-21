/// \file
#pragma once

#include <Mvx2API/Mvx2API.h>

#include <MVCommon/guid/Guid.h>

namespace Mvx2API
{
  class Frame;
  class MeshData;

  namespace FrameMeshExtractor
  {
    /// \brief Returns a frame's mesh data.
    /// \param frame        a frame
    /// \param purposeGuid  a purpose guid of mesh data to extract (Guid::Nil() is interpreted as 'any' purpose guid)
    /// \returns            frame's mesh
    MVX2_API MeshData * GetMeshData(Frame * frame, MVCommon::Guid const & purposeGuid = MVCommon::Guid::Nil());
  };
}

