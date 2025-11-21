#pragma once

#include <MVCommon/MVCommonAPI.h>
#include <MVCommon/Memory.h>

#include "Vector4f.h"

#include <MVCommon/utils/String.h>
#include <MVCommon/utils/ByteArray.h>

namespace MVCommon
{
  struct Matrix4x4f;

  /// \brief A rotational quaternion (i.e. versor) with single-precision floating-point values.
	struct Versorf final
  {
  public:
    /// \brief A constructor of an identity versor (i.e. no rotation).
    MVCOMMON_API Versorf();

    /// \brief Converts the versor into a human-readable string.
    /// \returns  the versor string
    MVCOMMON_API String ToString() const;
    /// \brief Creates a versor from a human-readable string.
    /// \param str  a versor string
    /// \returns    a versor
    /// \exception std::invalid_argument  raied when the string does not represent a rotational quaternion
    MVCOMMON_API static Versorf FromString(String const & str);
    /// \brief Serializes the versor into a byte array.
    /// \param bytes  a byte array to serialize into
    MVCOMMON_API void ToRawBytes(ByteArray & bytes) const;
    /// \brief Deserializes versor from a byte array.
    /// \param bytes        an array of versor bytes
    /// \param consumeBytes determines whether bytes of the versor shall be removed from the array
    /// \returns            a versor
    /// \exception std::invalid_argument  raised when there are not enough bytes in the array or the bytes do not represent a rotational quaternion
    MVCOMMON_API static Versorf FromRawBytes(ByteArray & bytes, bool consumeBytes = false);
    /// \brief A count of bytes the versor requires in a serialized form.
    MVCOMMON_API static const size_t RAW_BYTES_SIZE;
    /// \brief Converts the versor into a vector with values of versor's internal elements.
    /// \returns  a vector of versor's elements
    MVCOMMON_API Vector4f ToElementsVector() const;
    /// \brief Creates a versor from a vector with values of versor's internal elements.
    /// \param elements a vector with versor's internal elements
    /// \returns        a versor
    /// \exception std::invalid_argument  raied when the vector does not represent a rotational quaternion
    MVCOMMON_API static Versorf FromElementsVector(Vector4f const & elements);
    /// \brief Serializes the versor into an elements array.
    /// \param elements an array of 4 elements
    MVCOMMON_API void ToRawElements(float * elements) const;
    /// \brief Deserializes versor from an elements array.
    /// \param elements an array of 4 elements
    /// \returns        a versor
    /// \exception std::invalid_argument  raied when the elements do not represent a rotational quaternion
    MVCOMMON_API static Versorf FromRawElements(float const * elements);

    /// \brief Creates an inverted versor. 
    /// \returns  an inverted versor
    MVCOMMON_API Versorf Inverted() const;

    /// \brief Creates a versor from axis of rotation and an angle (in degrees).
    /// \param axis   an axis of rotation
    /// \param angle  an angle
    /// \returns      a versor
    MVCOMMON_API static Versorf CreateRotationAroundAxis(Vector3f const & axis, float angle);
    /// \brief Creates a versor from a rotational part of transformation matrix.
    /// \param matrix a matrix to extract the rotation from
    /// \returns      a versor
    MVCOMMON_API static Versorf CreateRotationFromMatrix(Matrix4x4f const & matrix);

    /// \brief Creates a versor from Euler angles (in degrees) in eulerAngles.z -> eulerAngles.y -> eulerAngles.x order.
    /// \param eulerAngles  Euler angles of Z-Y-X rotation
    /// \returns            a versor
    MVCOMMON_API static Versorf CreateRotationFromEulerAnglesZYX(Vector3f const & eulerAngles);
    /// \brief Converts the versor to Euler angles (in degrees) in z -> y -> x order.
    /// \returns  Euler angles of Z-Y-X rotation
    MVCOMMON_API Vector3f ToEulerAnglesZYX() const;

    /// \cond
    MVCOMMON_API Versorf & operator*=(Versorf const & other);
    MVCOMMON_API friend bool operator==(Versorf const & lhs, Versorf const & rhs);
    /// \endcond

    DECLARE_CLASS_SPECIFIC_NEW_DELETE(MVCOMMON_API)

    /// \cond
    friend struct VersorfHasher;
    /// \endcond

  private:
    Vector4f _elements;
  };

  /// \cond
  MVCOMMON_API bool operator==(Versorf const & lhs, Versorf const & rhs);
  MVCOMMON_API bool operator!=(Versorf const & lhs, Versorf const & rhs);
  MVCOMMON_API Versorf operator*(Versorf const & lhs, Versorf const & rhs);
  MVCOMMON_API Vector3f operator*(Versorf const & versor, Vector3f const & vector);
  /// \endcond

  /// \brief A hasher for Versorf objects so they can be used in unordered collections.
  struct VersorfHasher
  {
    /// \brief Calculates a hash value from the object.
    /// \param versor an object to calculate the hash value of
    /// \returns      hash value of the object
    MVCOMMON_API size_t operator()(Versorf const & versor) const;
  };
}