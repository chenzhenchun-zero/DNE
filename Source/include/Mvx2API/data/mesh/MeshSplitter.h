#pragma once

#include <Mvx2API/Mvx2API.h>
#include <MVCommon/Memory.h>
#include "MeshIndicesMode.h"

namespace Mvx2API
{
  class MeshData;
  class MeshSplitterImpl;

  /// \brief 
  /// A helper class for splitting provided mesh data into multiple meshes, depending on the maximal count of vertices the
  /// resulting meshes are allowed to contain.
  /// The splitting is based on indices collection, so in case there are none, there will be no meshes in the result.
  class MeshSplitter : private NonAssignable
  {
  public:
    /// \brief A constructor.
    /// \param maxVerticesCount a maximal count of vertices contained in the resulting split meshes
    MVX2_API MeshSplitter(uint32_t maxVerticesCount);

    /// \brief A destructor.
    MVX2_API virtual ~MeshSplitter();

    /// \brief Clears results of the previous mesh splitting.
    MVX2_API void ClearResults();

    /// \brief Splits a given mesh into submeshes, so each contains only given maximal count of vertices at most.
    /// \details Resulting submeshes are stored in the collection.
    /// \param mesh           a mesh to split
    /// \param indicesMode    an interpretation of indices collection (will be preserved in split meshes)
    /// \param includeNormals indication whether normals of the mesh shall be included in the splitting process and thus in the resulting submeshes
    /// \param includeColors  indication whether colors of the mesh shall be included in the splitting process and thus in the resulting submeshes
    /// \param includeUVs     indication whether texture UVs of the mesh shall be included in the splitting process and thus in the resulting submeshes
    MVX2_API void SplitMesh(MeshData const * mesh, MeshIndicesMode indicesMode,
      bool includeNormals = true, bool includeColors = true, bool includeUVs = true);

    /// \brief A getter of split meshes count.
    /// \returns  count of meshes
    MVX2_API uint32_t GetSplitMeshesCount() const;
    /// \brief Returns a split submesh with a given index.
    /// \param meshIndex  an index of the submesh to return
    /// \returns          a split submesh at the given index or null in case the index is out of bounds
    MVX2_API MeshData * GetSplitMeshData(uint32_t meshIndex) const;

    DECLARE_CLASS_SPECIFIC_NEW_DELETE(MVX2_API)

  private:
    MeshSplitterImpl* _pImpl;
  };
}