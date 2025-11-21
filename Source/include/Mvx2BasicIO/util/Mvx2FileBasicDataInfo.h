#pragma once

#include <Mvx2BasicIO/Mvx2BasicIO.h>
#include <MVCommon/Memory.h>

namespace MVCommon
{
  class String;
}

namespace MVX
{
  class MVX2FileRenderInfo;
}

namespace Mvx2API
{
  class Frame;
}

namespace Mvx2BasicIO
{
  /// \brief A provider of basic data information about an MVX2 file.
  class Mvx2FileBasicDataInfo : private NonAssignable
  {
  public:
    /// \brief A constructor.
    /// \param filePath a path to the MVX2 file to provide info about
    MVX2BASICIO_API Mvx2FileBasicDataInfo(MVCommon::String const & filePath);
    /// \brief A destructor.
    MVX2BASICIO_API virtual ~Mvx2FileBasicDataInfo();

    /// \brief Indicates whether the specified file is a valid MVX2 file.
    /// \returns  true if the file is a valid MVX2 file
    MVX2BASICIO_API bool IsValid() const;
    /// \brief Indicates whether the MVX2 file contains only a single frame.
    /// \returns  true if the file contains only a single frame
    MVX2BASICIO_API bool IsSingleFrame() const;
    /// \brief Returns a number of frames in the MVX2 file.
    /// \returns  frames count
    MVX2BASICIO_API uint32_t GetNumFrames() const;
    /// \brief Returns framerate of the MVX2 file.
    /// \returns  framerate
    MVX2BASICIO_API float GetFPS() const;

    /// \brief Checks the presence of depth map data in the MVX2 file.
    /// \returns  true if the depth map data are available
    MVX2BASICIO_API bool HasDepthMap() const;
    /// \brief Checks the presence of IR texture data in the MVX2 file.
    /// \returns  true if the IR texture data are available
    MVX2BASICIO_API bool HasIRTexture() const;
    /// \brief Checks the presence of a color texture data in the MVX2 file.
    /// \returns  true if a color texture data are available
    MVX2BASICIO_API bool HasColorTexture() const;
    /// \brief Checks the presence of vertex positions data in the MVX2 file.
    /// \returns  true if the vertex positions data are available
    MVX2BASICIO_API bool HasVertices() const;
    /// \brief Checks the presence of vertex normals data in the MVX2 file.
    /// \returns  true if the vertex normals data are available
    MVX2BASICIO_API bool HasNormals() const;
    /// \brief Checks the presence of vertex colors data in the MVX2 file.
    /// \returns  true if the vertex colors data are available
    MVX2BASICIO_API bool HasColors() const;
    /// \brief Checks the presence of vertex UVs data in the MVX2 file.
    /// \returns  true if the vertex UVs data are available
    MVX2BASICIO_API bool HasUVs() const;
    /// \brief Checks the presence of vertex indices data in the MVX2 file.
    /// \returns  true if the vertex indices data are available
    MVX2BASICIO_API bool HasIndices() const;
    /// \brief Checks the presence of audio data in the MVX2 file.
    /// \returns  true if the audio data are available
    MVX2BASICIO_API bool HasAudio() const;

    /// \brief Returns the first frame of the MVX2 file.
    /// \returns  the first frame
    MVX2BASICIO_API Mvx2API::Frame * GetFirstFrame() const;

    /// \brief Indicates whether it is possible to render a thumbnail image of the MVX2 file.
    /// \returns  true if the thumbnail image is available
    MVX2BASICIO_API bool CanRenderThumbnail() const;
    /// \brief Renders a thumbnail image of the MVX2 file.
    /// \param targetBufferRGBA a pre-allocated buffer for the thumbnail image
    /// \param targetWidth      width of the image buffer
    /// \param targetHeight     height of the image buffer
    MVX2BASICIO_API void RenderThumbnail(uint8_t* targetBufferRGBA, uint32_t targetWidth, uint32_t targetHeight) const;
    /// \brief Allocates a new image buffer and renders a thumbnail image of the MVX2 file to it.
    /// \param targetWidth  width of the image buffer
    /// \param targetHeight height of the image buffer
    /// \returns            the new image buffer
    MVX2BASICIO_API uint8_t * CreateAndRenderThumbnail(uint32_t targetWidth, uint32_t targetHeight) const;

    DECLARE_CLASS_SPECIFIC_NEW_DELETE(MVX2BASICIO_API)

  private:
    MVX::MVX2FileRenderInfo * _pRenderInfo;
  };
}
