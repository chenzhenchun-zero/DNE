/// \file
#pragma once

#include <Mvx2API/Mvx2API.h>
#include <MVCommon/guid/Guid.h>

namespace Mvx2API
{
  namespace BasicDataLayersGuids
  {
    /// \brief A getter of audio data layer GUID.
    /// \returns  the data layer GUID
    MVX2_API MVCommon::Guid AUDIO_DATA_LAYER();

    /// \brief A getter of vertex positions data layer GUID.
    /// \returns  the data layer GUID
    MVX2_API MVCommon::Guid VERTEX_POSITIONS_DATA_LAYER();
    /// \brief A getter of vertex colors data layer GUID.
    /// \returns  the data layer GUID
    MVX2_API MVCommon::Guid VERTEX_COLORS_DATA_LAYER();
    /// \brief A getter of vertex normals data layer GUID.
    /// \returns  the data layer GUID
    MVX2_API MVCommon::Guid VERTEX_NORMALS_DATA_LAYER();
    /// \brief A getter of vertex UVs data layer GUID.
    /// \returns  the data layer GUID
    MVX2_API MVCommon::Guid VERTEX_UVS_DATA_LAYER();
    /// \brief A getter of vertex indices data layer GUID.
    /// \returns  the data layer GUID
    MVX2_API MVCommon::Guid VERTEX_INDICES_DATA_LAYER();

    /// \brief A getter of camera params data layer GUID.
    /// \returns  the data layer GUID
    MVX2_API MVCommon::Guid CAMERA_PARAMS_DATA_LAYER();
    /// \brief A getter of transform data layer GUID.
    /// \returns  the data layer GUID
    MVX2_API MVCommon::Guid TRANSFORM_DATA_LAYER();
    /// \brief A getter of segment info data layer GUID.
    /// \returns  the data layer GUID
    MVX2_API MVCommon::Guid SEGMENT_INFO_DATA_LAYER();
    /// \brief A getter of bytearray data layer GUID.
    /// \returns  the data layer GUID
    MVX2_API MVCommon::Guid BYTEARRAY_DATA_LAYER();

    /// \brief A getter of depth map texture data layer GUID.
    /// \returns  the data layer GUID
    MVX2_API MVCommon::Guid DEPTHMAP_TEXTURE_DATA_LAYER();
    /// \brief A getter of IR texture data layer GUID.
    /// \returns  the data layer GUID
    MVX2_API MVCommon::Guid IR_TEXTURE_DATA_LAYER();
    /// \brief A getter of RGB texture data layer GUID.
    /// \returns  the data layer GUID
    MVX2_API MVCommon::Guid RGB_TEXTURE_DATA_LAYER();
    /// \brief A getter of NVX texture data layer GUID.
    /// \returns  the data layer GUID
    MVX2_API MVCommon::Guid NVX_TEXTURE_DATA_LAYER();
    /// \brief A getter of NV12 texture data layer GUID.
    /// \returns  the data layer GUID
    MVX2_API MVCommon::Guid NV12_TEXTURE_DATA_LAYER();
    /// \brief A getter of NV21 texture data layer GUID.
    /// \returns  the data layer GUID
    MVX2_API MVCommon::Guid NV21_TEXTURE_DATA_LAYER();
    /// \brief A getter of DXT5YCOCG texture data layer GUID.
    /// \returns  the data layer GUID
    MVX2_API MVCommon::Guid DXT5YCOCG_TEXTURE_DATA_LAYER();
    /// \brief A getter of DXT1 texture data layer GUID.
    /// \returns  the data layer GUID
    MVX2_API MVCommon::Guid DXT1_TEXTURE_DATA_LAYER();
    /// \brief A getter of ETC2 texture data layer GUID.
    /// \returns  the data layer GUID
    MVX2_API MVCommon::Guid ETC2_TEXTURE_DATA_LAYER();
    /// \brief A getter of ASTC texture data layer GUID.
    /// \returns  the data layer GUID
    MVX2_API MVCommon::Guid ASTC_TEXTURE_DATA_LAYER();
  };
}