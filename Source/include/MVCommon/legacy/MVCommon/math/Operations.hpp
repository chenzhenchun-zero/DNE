// --------------------------------------------------------------------
//    _________   _____________                                       
//   /     \   \ /   /\_   ___ \  ____   _____   _____   ____   ____  
//  /  \ /  \   Y   / /    \  \/ /  _ \ /     \ /     \ /  _ \ /    \
// /    Y    \     /  \     \___(  <_> )  Y Y  \  Y Y  (  <_> )   |  \
// \____|__  /\___/    \______  /\____/|__|_|  /__|_|  /\____/|___|  /
//         \/                 \/             \/      \/            \/ 
//
//          Mantis Vision Common Code Library
// --------------------------------------------------------------------

#pragma once

#include <MVCommon/MVCommonAPI.h>
#include <cmath>
#include <limits>

namespace MVCommon
{
  struct Vector3f;
  struct Vector4f;
  struct Matrix4x4f;
	
  MVCOMMON_API void transformVertices(const Matrix4x4f &m, const Vector3f *src, Vector3f *dst, std::size_t n);
  MVCOMMON_API void transformVertices(const Matrix4x4f &m, const Vector3f *src, Vector4f *dst, std::size_t n);
  MVCOMMON_API void calculateBoundingBox(const Vector3f *src, std::size_t n, Vector3f &minimum, Vector3f &maximum);
  MVCOMMON_API void copyIndexedVertices(const Vector4f *src, Vector3f *dst, const std::uint32_t *inds, std::size_t n);
  MVCOMMON_API void uncompressPoints48bit(const uint16_t* src, Vector3f *dst, const Vector3f &invscale, const Vector3f &offset, std::size_t n);
  MVCOMMON_API void compressPoints48bit(const Vector3f *src, uint16_t *dst, const Vector3f &scale, const Vector3f &offset, std::size_t n);

  template<typename TFloat>
  bool AlmostEquals(TFloat x, TFloat y, TFloat presicion = std::numeric_limits<TFloat>::epsilon());
}

template<typename TFloat>
bool MVCommon::AlmostEquals(TFloat x, TFloat y, TFloat presicion)
{
  return std::abs(x - y) < presicion;
}
