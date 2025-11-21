#pragma once

#include <MVCommon/MVCommonAPI.h>
#include <MVCommon/Memory.h>

#include <MVCommon/utils/String.h>
#include <MVCommon/utils/ByteArray.h>

namespace MVCommon
{
  /// \brief A 2-dimensional vector with single-precision floating-point values.
  struct Vector2f final
  {
  public:
    /// \brief An x coordinate.
    float x;
    /// \brief A y coordinate.
    float y;

    /// \brief A default constructor.
    MVCOMMON_API Vector2f();
    /// \brief A constructor.
    /// \param x  an x coordinate
    /// \param y  a y coordinate
    MVCOMMON_API Vector2f(float x, float y);

    /// \brief Converts the vector into a human-readable string.
    /// \returns  the vector string
    MVCOMMON_API String ToString() const;
    /// \brief Creates a vector from a human-readable string.
    /// \param str  a vector string
    /// \returns    a vector
    MVCOMMON_API static Vector2f FromString(String const & str);
    /// \brief Serializes the vector into a byte array.
    /// \param bytes  a byte array to serialize into
    MVCOMMON_API void ToRawBytes(ByteArray & bytes) const;
    /// \brief Deserializes vector from a byte array.
    /// \param bytes        an array of vector bytes
    /// \param consumeBytes determines whether bytes of the vector shall be removed from the array
    /// \returns            a vector
    /// \exception std::invalid_argument  raised when there are not enough bytes in the array
    MVCOMMON_API static Vector2f FromRawBytes(ByteArray & bytes, bool consumeBytes = false);
    /// \brief A count of bytes the vector requires in a serialized form.
    MVCOMMON_API static const size_t RAW_BYTES_SIZE;

    /// \brief Gets a length of the vector.
    /// \returns  vector's length
    MVCOMMON_API float Length() const;
    /// \brief Creates a vector with inverted dimensions (1/x).
    /// \returns  an inverted vector
    MVCOMMON_API Vector2f Inverted() const;
    /// \brief Creates a normalized vector (with length equal to 1).
    /// \details Returns an unchanged vector in case its length is equal to 0.
    /// \returns  a normalized vector
    MVCOMMON_API Vector2f Normalized() const;
    /// \brief Creates a vector with dimensions with absolute values of the original vector.
    /// \returns  a vector with absolute-valued dimensions
    MVCOMMON_API Vector2f Abs() const;

    /// \brief Calculates a dot product of two vectors.
    /// \param lhs  a first vector-operand
    /// \param rhs  a second vector-operand
    /// \returns    a dot product
    MVCOMMON_API static float Dot(Vector2f const & lhs, Vector2f const & rhs);

    /// \brief Accesses vector dimension value via index.
    /// \param pos  an index of the dimension to access
    /// \returns    a reference to the dimension value
    /// \exception std::out_of_range  raised when index is out of range (0-1)
    MVCOMMON_API float & operator[] (size_t pos);
    /// \brief Accesses vector dimension value via index.
    /// \param pos  an index of the dimension to access
    /// \returns    a reference to the dimension value
    /// \exception std::out_of_range  raised when index is out of range (0-1)
    MVCOMMON_API float const & operator[] (size_t pos) const;

    /// \cond
    MVCOMMON_API Vector2f & operator+=(Vector2f const & other);
    MVCOMMON_API Vector2f & operator-=(Vector2f const & other);
    MVCOMMON_API Vector2f & operator*=(float factor);
    MVCOMMON_API Vector2f & operator/=(float divisor);
    /// \endcond

    DECLARE_CLASS_SPECIFIC_NEW_DELETE(MVCOMMON_API)
  };

  /// \cond
  MVCOMMON_API Vector2f operator-(Vector2f const & vector);
  MVCOMMON_API Vector2f operator+(Vector2f const & lhs, Vector2f const & rhs);
  MVCOMMON_API Vector2f operator-(Vector2f const & lhs, Vector2f const & rhs);
  MVCOMMON_API Vector2f operator*(Vector2f const & vector, float factor);
  MVCOMMON_API Vector2f operator*(float factor, Vector2f const & vector);
  MVCOMMON_API Vector2f operator/(Vector2f const & vector, float divisor);
  MVCOMMON_API bool operator==(Vector2f const & lhs, Vector2f const & rhs);
  MVCOMMON_API bool operator!=(Vector2f const & lhs, Vector2f const & rhs);
  /// \endcond

  /// \brief A hasher for Vector2f objects so they can be used in unordered collections.
  struct Vector2fHasher
  {
    /// \brief Calculates a hash value from the object.
    /// \param vector an object to calculate the hash value of
    /// \returns      hash value of the object
    MVCOMMON_API size_t operator()(Vector2f const & vector) const;
  };
}