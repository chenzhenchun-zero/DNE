/// \file
#pragma once

#include <Mvx2API/Mvx2API.h>

#include <MVCommon/guid/Guid.h>

namespace Mvx2API
{
  class Frame;

  namespace FrameTextureExtractor
  {
    /// \brief An enumeration of texture types.
    enum TextureType
    {
      /// \brief Depth map texture type.
      TT_DEPTH = 0,
      /// \brief IR texture type.
      TT_IR = 1,
      /// \brief RGB texture type.
      TT_RGB = 2,
      /// \brief NVX texture type.
      TT_NVX = 3,
      /// \brief DXT5YCOCG texture type.
      TT_DXT5YCOCG = 4,
      /// \brief DXT1 texture type.
      TT_DXT1 = 5,
      /// \brief ETC texture type.
      TT_ETC2 = 6,
      /// \brief ASTC texture type.
      TT_ASTC = 7,
      /// \brief NV12 texture type.
      TT_NV12 = 8,
      /// \brief NV21 texture type.
      TT_NV21 = 9
    };

    /// \brief Returns resolution of a frame's texture.
    /// \param frame        a frame
    /// \param textureType  a type of the texture to extract
    /// \param width        an outputted width of the texture
    /// \param height       an outputted height of the texture
    /// \param purposeGuid  a purpose guid of texture to extract (Guid::Nil() is interpreted as 'any' purpose guid)
    /// \returns            true if the texture resolution was successfully retrieved
    MVX2_API bool GetTextureResolution(Frame * frame, TextureType textureType, uint16_t& width, uint16_t& height,
      MVCommon::Guid const & purposeGuid = MVCommon::Guid::Nil());
    /// \brief Returns size (in bytes) of a frame's texture data.
    /// \param frame        a frame
    /// \param textureType  a type of the texture to extract
    /// \param purposeGuid  a purpose guid of texture to extract (Guid::Nil() is interpreted as 'any' purpose guid)
    /// \returns            texture data size
    MVX2_API uint32_t GetTextureDataSizeInBytes(Frame * frame, TextureType textureType, MVCommon::Guid const & purposeGuid = MVCommon::Guid::Nil());
    /// \brief Returns raw pointer to the texture data owned by a frame.
    /// \param frame        a frame
    /// \param textureType  a type of the texture to extract
    /// \param purposeGuid  a purpose guid of texture to extract (Guid::Nil() is interpreted as 'any' purpose guid)
    /// \returns            texture data
    MVX2_API uint8_t const * GetTextureData(Frame * frame, TextureType textureType, MVCommon::Guid const & purposeGuid = MVCommon::Guid::Nil());
    /// \brief Copies a frame's texture data.
    /// \param frame        a frame
    /// \param textureType  a type of the texture to extract
    /// \param targetData   an outputted texture data array (must be pre-allocated with (texture data size) elements)
    /// \param purposeGuid  a purpose guid of texture to extract (Guid::Nil() is interpreted as 'any' purpose guid)
    /// \returns            true if the texture data were successfully copied
    MVX2_API bool CopyTextureData(Frame * frame, TextureType textureType, uint8_t * targetData, MVCommon::Guid const & purposeGuid = MVCommon::Guid::Nil());
  };
}

