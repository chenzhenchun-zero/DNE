#pragma once

#include <MVCommon/MVCommonAPI.h>
#include <MVCommon/Memory.h>

#include "Vector2f.h"
#include <MVCommon/utils/String.h>
#include <MVCommon/utils/ByteArray.h>

namespace MVCommon
{
  /// \brief A 3-dimensional vector with single-precision floating-point values.
  struct Vector3f final
  {
  public:
    /// \brief An x coordinate.
    float x;
    /// \brief A y coordinate.
    float y;
    /// \brief A z coordinate.
    float z;

    /// \brief A default constructor.
    MVCOMMON_API Vector3f();
    /// \brief A constructor.
    /// \param x  an x coordinate
    /// \param y  a y coordinate
    /// \param z  a z coordinate
    MVCOMMON_API Vector3f(float x, float y, float z);
    /// \brief A constructor.
    /// \param vector2  a 2-dimensional vector whose x and y coordinates will be grabbed
    /// \param z        a z coordinate
    MVCOMMON_API Vector3f(Vector2f const & vector2, float z = 0.0f);

    /// \brief Converts the vector into a human-readable string.
    /// \returns  the vector string
    MVCOMMON_API String ToString() const;
    /// \brief Creates a vector from a human-readable string.
    /// \param str  a vector string
    /// \returns    a vector
    MVCOMMON_API static Vector3f FromString(String const & str);
    /// \brief Serializes the vector into a byte array.
    /// \param bytes  a byte array to serialize into
    MVCOMMON_API void ToRawBytes(ByteArray & bytes) const;
    /// \brief Deserializes vector from a byte array.
    /// \param bytes        an array of vector bytes
    /// \param consumeBytes determines whether bytes of the vector shall be removed from the array
    /// \returns            a vector
    /// \exception std::invalid_argument  raised when there are not enough bytes in the array
    MVCOMMON_API static Vector3f FromRawBytes(ByteArray & bytes, bool consumeBytes = false);
    /// \brief A count of bytes the vector requires in a serialized form.
    MVCOMMON_API static const size_t RAW_BYTES_SIZE;

    /// \brief Gets a length of the vector.
    /// \returns  vector's length
    MVCOMMON_API float Length() const;
    /// \brief Creates a vector with inverted dimensions (1/x).
    /// \returns  an inverted vector
    MVCOMMON_API Vector3f Inverted() const;
    /// \brief Creates a normalized vector (with length equal to 1).
    /// \details Returns an unchanged vector in case its length is equal to 0.
    /// \returns  a normalized vector
    MVCOMMON_API Vector3f Normalized() const;
    /// \brief Creates a vector with dimensions with absolute values of the original vector.
    /// \returns  a vector with absolute-valued dimensions
    MVCOMMON_API Vector3f Abs() const;
    /// \brief Extracts x and y coordinates as a 2-dimensional vector.
    /// \returns  a 2-dimensional vector
    MVCOMMON_API Vector2f GetXY() const;

    /// \brief Calculates a dot product of two vectors.
    /// \param lhs  a first vector-operand
    /// \param rhs  a second vector-operand
    /// \returns    a dot product
    MVCOMMON_API static float Dot(Vector3f const & lhs, Vector3f const & rhs);
    /// \brief Calculates a cross product of two vectors.
    /// \param lhs  a left-hand-side vector-operand
    /// \param rhs  a right-hand-side vector-operand
    /// \returns    a vector representing the cross product
    MVCOMMON_API static Vector3f Cross(Vector3f const & lhs, Vector3f const & rhs);

    /// \brief Accesses vector dimension value via index.
    /// \param pos  an index of the dimension to access
    /// \returns    a reference to the dimension value
    /// \exception std::out_of_range  raised when index is out of range (0-2)
    MVCOMMON_API float & operator[] (size_t pos);
    /// \brief Accesses vector dimension value via index.
    /// \param pos  an index of the dimension to access
    /// \returns    a reference to the dimension value
    /// \exception std::out_of_range  raised when index is out of range (0-2)
    MVCOMMON_API float const & operator[] (size_t pos) const;

    /// \cond
    MVCOMMON_API Vector3f & operator+=(Vector3f const & other);
    MVCOMMON_API Vector3f & operator-=(Vector3f const & other);
    MVCOMMON_API Vector3f & operator*=(float factor);
    MVCOMMON_API Vector3f & operator/=(float divisor);
    /// \endcond

    DECLARE_CLASS_SPECIFIC_NEW_DELETE(MVCOMMON_API)
  };

  /// \cond
  MVCOMMON_API Vector3f operator-(Vector3f const & vector);
  MVCOMMON_API Vector3f operator+(Vector3f const & lhs, Vector3f const & rhs);
  MVCOMMON_API Vector3f operator-(Vector3f const & lhs, Vector3f const & rhs);
  MVCOMMON_API Vector3f operator*(Vector3f const & vector, float factor);
  MVCOMMON_API Vector3f operator*(float factor, Vector3f const & vector);
  MVCOMMON_API Vector3f operator/(Vector3f const & vector, float divisor);
  MVCOMMON_API bool operator==(Vector3f const & lhs, Vector3f const & rhs);
  MVCOMMON_API bool operator!=(Vector3f const & lhs, Vector3f const & rhs);
  /// \endcond

  /// \brief A hasher for Vector3f objects so they can be used in unordered collections.
  struct Vector3fHasher
  {
    /// \brief Calculates a hash value from the object.
    /// \param vector an object to calculate the hash value of
    /// \returns      hash value of the object
    MVCOMMON_API size_t operator()(Vector3f const & vector) const;
  };
}
