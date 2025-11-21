/// \file
#pragma once

namespace Mvx2API
{
  /// \brief Enumeration of indices modes.
  /// \details Determines proper interpretation of indices sequence of a mesh.
  enum MeshIndicesMode
  {
    /// \brief Every index represents a single point primitive.
    MIM_PointList = 0,
    /// \brief Pairs of indices represent line primitives.
    MIM_LineList = 1,
    /// \brief Triplets of indices represent triangle primitives.
    MIM_TriangleList = 2,
    /// \brief Quartets of indices represent quad primitives.
    MIM_QuadList = 3
  };
}