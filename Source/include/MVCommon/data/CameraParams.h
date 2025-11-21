#pragma once

#include <MVCommon/MVCommonAPI.h>
#include <MVCommon/Memory.h>

#include <MVCommon/math/Vector2f.h>
#include <MVCommon/math/Vector3f.h>
#include <MVCommon/math/Matrix4x4f.h>
#include <MVCommon/utils/String.h>
#include <MVCommon/utils/ByteArray.h>

namespace MVCommon
{
  /// \brief A data structure containing intrinsic and extrinsic parameters of cameras.
  struct CameraParams final
  {
    public:
      /// \brief A constructor.
      /// \param width  a width (in pixels)
      /// \param height a height (in pixels)
      /// \param F      focal lengths (in pixels) in x and y directions
      /// \details
      /// Constructs the camera params with default values - principal point offsets equal
      /// to [width/2, height/2], and distortion, translation and rotation set to identities.
      MVCOMMON_API CameraParams(uint32_t width = 0, uint32_t height = 0, Vector2f F = Vector2f(1.0f, 1.0f));
      /// \brief A destructor.
      MVCOMMON_API ~CameraParams();
      
      /// \brief A width (in pixels).
      uint32_t width;
      /// \brief A height (in pixels).
      uint32_t height;
      /// \brief Focal lengths (in pixels) in x and y directions.
      Vector2f F;
      /// \brief Principal point offsets (in pixels) in x and y directions.
      Vector2f C;
      /// \brief Principal point offsets for distortion operations (in pixels) in x and y directions.
      /// \details Its value may be slightly different than the value of \ref C.
      Vector2f distortionC;

      /// \brief Distortion coefficients.
      float distortion[5];
      
      /// \brief Translation offset of the origin in the camera's coordinate system.
      Vector3f translation;
      /// \brief Rotation matrix offset of the origin in the camera's coordinate system.
      Matrix4x4f rotation;

      /// \brief Converts the camera params into a human-readable string.
      /// \returns  the camera params string
      MVCOMMON_API String ToString() const;
      /// \brief Serializes the camera params into a byte array.
      /// \param bytes  a byte array to serialize into
      MVCOMMON_API void ToRawBytes(ByteArray & bytes) const;
      /// \brief Deserializes camera params from a byte array.
      /// \param bytes        an array of camera params bytes
      /// \param consumeBytes determines whether bytes of the camera params shall be removed from the array
      /// \returns            camera params
      /// \exception std::invalid_argument  raised when there are not enough bytes in the array
      MVCOMMON_API static CameraParams FromRawBytes(ByteArray & bytes, bool consumeBytes = false);
      /// \brief A count of bytes the camera params requires in a serialized form.
      MVCOMMON_API static const size_t RAW_BYTES_SIZE;

      /// \brief Normalizes a point coordinates using focal lengths and principal point offsets of camera.
      /// \param point  a point to normalize
      MVCOMMON_API void NormalizePoint(Vector2f & point) const;
      /// \brief Normalizes a point x and y coordinates using focal lengths and principal point offsets of camera.
      /// \param point  a point to normalize
      MVCOMMON_API void NormalizePoint(Vector3f & point) const;
      
      /// \brief Denormalizes a point coordinates using focal lengths and principal point offsets of camera.
      /// \param point  a point to denormalize
      MVCOMMON_API void DenormalizePoint(Vector2f & point) const;
      /// \brief Denormalizes a point x and y coordinates using focal lengths and principal point offsets of camera.
      /// \param point  a point to denormalize
      MVCOMMON_API void DenormalizePoint(Vector3f & point) const;
      
      /// \brief Transforms a point coordinates to compensate camera lens distortion.
      /// \param point  a point to undistort
      MVCOMMON_API void UndistortPoint(Vector2f & point) const;
      /// \brief Transforms a point x and y coordinates to compensate camera lens distortion.
      /// \param point  a point to undistort
      MVCOMMON_API void UndistortPoint(Vector3f & point) const;

      /// \brief Creates a new camera params with focal lengths and principal point offsets scaled for a target resolution.
      /// \param targetWidth  target width
      /// \param targetHeight target height
      /// \returns            a new camera params
      /// \details
      /// Vertical (y) and horizontal (x) elements are scaled independently. Distortion, translation and rotation are preserved
      /// in the new camera params.
      MVCOMMON_API CameraParams ScaleToResolution(uint32_t targetWidth, uint32_t targetHeight) const;

      DECLARE_CLASS_SPECIFIC_NEW_DELETE(MVCOMMON_API)
  };

  MVCOMMON_API bool operator==(CameraParams const & lhs, CameraParams const & rhs);
  MVCOMMON_API bool operator!=(CameraParams const & lhs, CameraParams const & rhs);

  /// \brief A hasher for CameraParams objects so they can be used in unordered collections.
  struct CameraParamsHasher
  {
    /// \brief Calculates a hash value from the object.
    /// \param cameraParams an object to calculate the hash value of
    /// \returns            hash value of the object
    MVCOMMON_API size_t operator()(CameraParams const & cameraParams) const;
  };
}