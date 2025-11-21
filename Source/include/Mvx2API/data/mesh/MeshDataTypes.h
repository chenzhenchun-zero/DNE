/// \file
#pragma once

#include <cstdint>

namespace Mvx2API
{
  /// \brief A structure containing 2D position data.
  struct Vec2Data
  {
    /// \brief A x-coordinate.
    float x;
    /// \brief A y-coordinate.
    float y;
  };

  /// \brief A structure containing 3D position data.
  struct Vec3Data
  {
    /// \brief A x-coordinate.
    float x;
    /// \brief A y-coordinate.
    float y;
    /// \brief A z-coordinate.
    float z;
  };

  /// \brief A structure containing color data.
  struct ColRGBAData
  {
    /// \brief A red color component.
    uint8_t r;
    /// \brief A green color component.
    uint8_t g;
    /// \brief A blue color component.
    uint8_t b;
    /// \brief An alpha color component.
    uint8_t a;
  };
}