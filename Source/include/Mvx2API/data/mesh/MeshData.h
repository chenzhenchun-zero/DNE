#pragma once

#include <Mvx2API/Mvx2API.h>
#include <MVCommon/Memory.h>
#include "MeshDataTypes.h"

namespace Mvx2API
{
  class MeshDataImpl;

  /// \brief A class containing data of a single mesh.
  class MeshData : private NonAssignable
  {
  public:
    /// \cond
    MeshData(MeshDataImpl * pImpl);
    /// \endcond

    /// \brief A destructor.
    MVX2_API virtual ~MeshData();

    /// \brief A getter of the vertices count.
    /// \returns  count of mesh vertices
    MVX2_API uint32_t GetNumVertices() const;
    
    /// \brief A getter of the raw pointer to vertices collection.
    /// \returns  mesh vertices
    MVX2_API float const * GetVertices() const;
    /// \brief Copies vertices collection to the target array.
    /// \param targetVertices an outputted vertex positions array (must be pre-allocated with (3 * vertices count) elements)
    /// \returns              true if the vertex positions were successfully copied
    MVX2_API bool CopyVertices(float * targetVertices) const;
    /// \brief Copies vertices collection to the target array.
    /// \param targetVertices an outputted vertex positions array (must be pre-allocated with (vertices count) elements)
    /// \returns              true if the vertex positions were successfully copied
    MVX2_API bool CopyVerticesVec3(Vec3Data * targetVertices) const;

    /// \brief A getter of the normals count.
    /// \returns  count of mesh normals
    MVX2_API uint32_t GetNumNormals() const;
    /// \brief A getter of the raw pointer to normals collection.
    /// \returns  mesh normals
    MVX2_API float const * GetNormals() const;
    /// \brief Copies vertex normals collection to the target array.
    /// \param targetNormals  an outputted vertex normals array (must be pre-allocated with (3 * normals count) elements)
    /// \returns              true if the vertex normals were successfully copied
    MVX2_API bool CopyNormals(float * targetNormals) const;
    /// \brief Copies vertex normals collection to the target array.
    /// \param targetNormals  an outputted vertex normals array (must be pre-allocated with (normals count) elements)
    /// \returns              true if the vertex normals were successfully copied
    MVX2_API bool CopyNormalsVec3(Vec3Data * targetNormals) const;
    
    /// \brief A getter of the colors count.
    /// \returns  count of mesh colors
    MVX2_API uint32_t GetNumColors() const;
    /// \brief A getter of the raw pointer to RGB colors collection.
    /// \returns  mesh RGB colors
    MVX2_API uint8_t const * GetColorsRGB() const;
    /// \brief Copies vertex RGB colors collection to the target array.
    /// \param targetColors an outputted vertex RGB colors array (must be pre-allocated with (3 * colors count) elements)
    /// \returns            true if the vertex RGB colors were successfully copied
    MVX2_API bool CopyColorsRGB(uint8_t * targetColors) const;
    /// \brief Copies vertex RGBA colors collection to the target array.
    /// \param targetColors an outputted vertex RGBA colors array (must be pre-allocated with (colors count) elements)
    /// \returns            true if the vertex RGBA colors were successfully copied
    MVX2_API bool CopyColorsColRGBA(ColRGBAData * targetColors) const;
    
    /// \brief A getter of the UVs count.
    /// \returns  count of mesh UVs
    MVX2_API uint32_t GetNumUVs() const;
    /// \brief A getter of the raw pointer to UVs collection.
    /// \returns  mesh UVs
    MVX2_API float const * GetUVs() const;
    /// \brief Copies vertex UVs collection to the target array.
    /// \param targetUVs  an outputted vertex UVs array (must be pre-allocated with (2 * UVs count) elements)
    /// \returns          true if the vertex UVs were successfully copied
    MVX2_API bool CopyUVs(float * targetUVs) const;
    /// \brief Copies vertex UVs collection to the target array.
    /// \param targetUVs  an outputted vertex UVs array (must be pre-allocated with (UVs count) elements)
    /// \returns          true if the vertex UVs were successfully copied
    MVX2_API bool CopyUVsVec2(Vec2Data * targetUVs) const;
    
    /// \brief A getter of the indices count.
    /// \returns  count of mesh indices
    MVX2_API uint32_t GetNumIndices() const;
    /// \brief A getter of the raw pointer to indices collection.
    /// \returns  mesh indices
    MVX2_API uint32_t const * GetIndices() const;
    /// \brief Copies vertex indices collection to the target array.
    /// \param targetIndices  an outputted vertex indices array (must be pre-allocated with (indices count) elements)
    /// \returns              true if the vertex indices were successfully copied
    MVX2_API bool CopyIndices(uint32_t * targetIndices) const;

    /// \brief A getter of the raw pointer to bounding box data.
    /// \returns  bounding box (array of 6 values)
    MVX2_API float const * GetBoundingBox() const;
    /// \brief Copies bounding box data to the target array.
    /// \param targetBoundingBox  an outputted bounding box data array (must be pre-allocated with 6 elements)
    /// \returns                  true if the bounding box was successfully copied
    MVX2_API bool CopyBoundingBox(float * targetBoundingBox) const;

    DECLARE_CLASS_SPECIFIC_NEW_DELETE(MVX2_API)

    /// \cond
    MeshDataImpl* GetImpl() const { return _pImpl; }
    /// \endcond

  private:
    MeshDataImpl * _pImpl;
  };
}