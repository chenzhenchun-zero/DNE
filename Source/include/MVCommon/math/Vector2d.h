#pragma once

#include <MVCommon/MVCommonAPI.h>
#include <MVCommon/Memory.h>

#include <MVCommon/utils/String.h>
#include <MVCommon/utils/ByteArray.h>

namespace MVCommon
{
  /// \brief A 2-dimensional vector with double-precision floating-point values.
  struct Vector2d final
  {
  public:
    /// \brief An x coordinate.
    double x;
    /// \brief A y coordinate.
    double y;

    /// \brief A default constructor.
    MVCOMMON_API Vector2d();
    /// \brief A constructor.
    /// \param x  an x coordinate
    /// \param y  a y coordinate
    MVCOMMON_API Vector2d(double x, double y);

    /// \brief Converts the vector into a human-readable string.
    /// \returns  the vector string
    MVCOMMON_API String ToString() const;
    /// \brief Creates a vector from a human-readable string.
    /// \param str  a vector string
    /// \returns    a vector
    MVCOMMON_API static Vector2d FromString(String const & str);
    /// \brief Serializes the vector into a byte array.
    /// \param bytes  a byte array to serialize into
    MVCOMMON_API void ToRawBytes(ByteArray & bytes) const;
    /// \brief Deserializes vector from a byte array.
    /// \param bytes        an array of vector bytes
    /// \param consumeBytes determines whether bytes of the vector shall be removed from the array
    /// \returns            a vector
    /// \exception std::invalid_argument  raised when there are not enough bytes in the array
    MVCOMMON_API static Vector2d FromRawBytes(ByteArray & bytes, bool consumeBytes = false);
    /// \brief A count of bytes the vector requires in a serialized form.
    MVCOMMON_API static const size_t RAW_BYTES_SIZE;

    /// \brief Gets a length of the vector.
    /// \returns  vector's length
    MVCOMMON_API double Length() const;
    /// \brief Creates a vector with inverted dimensions (1/x).
    /// \returns  an inverted vector
    MVCOMMON_API Vector2d Inverted() const;
    /// \brief Creates a normalized vector (with length equal to 1).
    /// \details Returns an unchanged vector in case its length is equal to 0.
    /// \returns  a normalized vector
    MVCOMMON_API Vector2d Normalized() const;
    /// \brief Creates a vector with dimensions with absolute values of the original vector.
    /// \returns  a vector with absolute-valued dimensions
    MVCOMMON_API Vector2d Abs() const;

    /// \brief Calculates a dot product of two vectors.
    /// \param lhs  a first vector-operand
    /// \param rhs  a second vector-operand
    /// \returns    a dot product
    MVCOMMON_API static double Dot(Vector2d const & lhs, Vector2d const & rhs);

    /// \brief Accesses vector dimension value via index.
    /// \param pos  an index of the dimension to access
    /// \returns    a reference to the dimension value
    /// \exception std::out_of_range  raised when index is out of range (0-1)
    MVCOMMON_API double & operator[] (size_t pos);
    /// \brief Accesses vector dimension value via index.
    /// \param pos  an index of the dimension to access
    /// \returns    a reference to the dimension value
    /// \exception std::out_of_range  raised when index is out of range (0-1)
    MVCOMMON_API double const & operator[] (size_t pos) const;

    /// \cond
    MVCOMMON_API Vector2d & operator+=(Vector2d const & other);
    MVCOMMON_API Vector2d & operator-=(Vector2d const & other);
    MVCOMMON_API Vector2d & operator*=(double factor);
    MVCOMMON_API Vector2d & operator/=(double divisor);
    /// \endcond

    DECLARE_CLASS_SPECIFIC_NEW_DELETE(MVCOMMON_API)
  };

  /// \cond
  MVCOMMON_API Vector2d operator-(Vector2d const & vector);
  MVCOMMON_API Vector2d operator+(Vector2d const & lhs, Vector2d const & rhs);
  MVCOMMON_API Vector2d operator-(Vector2d const & lhs, Vector2d const & rhs);
  MVCOMMON_API Vector2d operator*(Vector2d const & vector, double factor);
  MVCOMMON_API Vector2d operator*(double factor, Vector2d const & vector);
  MVCOMMON_API Vector2d operator/(Vector2d const & vector, double divisor);
  MVCOMMON_API bool operator==(Vector2d const & lhs, Vector2d const & rhs);
  MVCOMMON_API bool operator!=(Vector2d const & lhs, Vector2d const & rhs);
  /// \endcond

  /// \brief A hasher for Vector2d objects so they can be used in unordered collections.
  struct Vector2dHasher
  {
    /// \brief Calculates a hash value from the object.
    /// \param vector an object to calculate the hash value of
    /// \returns      hash value of the object
    MVCOMMON_API size_t operator()(Vector2d const & vector) const;
  };
}