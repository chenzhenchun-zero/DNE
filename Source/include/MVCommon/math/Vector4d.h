#pragma once

#include <MVCommon/MVCommonAPI.h>
#include <MVCommon/Memory.h>

#include "Vector3d.h"
#include <MVCommon/utils/String.h>
#include <MVCommon/utils/ByteArray.h>

namespace MVCommon
{
  /// \brief A 4-dimensional vector with double-precision floating-point values.
  struct Vector4d final
  {
  public:
    /// \brief An x coordinate.
    double x;
    /// \brief A y coordinate.
    double y;
    /// \brief A z coordinate.
    double z;
    /// \brief A w coordinate.
    double w;

    /// \brief A default constructor.
    MVCOMMON_API Vector4d();
    /// \brief A constructor.
    /// \param x  an x coordinate
    /// \param y  a y coordinate
    /// \param z  a z coordinate
    /// \param w  a w coordinate
    MVCOMMON_API Vector4d(double x, double y, double z, double w);
    /// \brief A constructor.
    /// \param vector3  a 3-dimensional vector whose x, y and z coordinates will be grabbed
    /// \param w        a w coordinate
    MVCOMMON_API Vector4d(Vector3d const & vector3, double w = 0.0);

    /// \brief Converts the vector into a human-readable string.
    /// \returns  the vector string
    MVCOMMON_API String ToString() const;
    /// \brief Creates a vector from a human-readable string.
    /// \param str  a vector string
    /// \returns    a vector
    MVCOMMON_API static Vector4d FromString(String const & str);
    /// \brief Serializes the vector into a byte array.
    /// \param bytes  a byte array to serialize into
    MVCOMMON_API void ToRawBytes(ByteArray & bytes) const;
    /// \brief Deserializes vector from a byte array.
    /// \param bytes        an array of vector bytes
    /// \param consumeBytes determines whether bytes of the vector shall be removed from the array
    /// \returns            a vector
    /// \exception std::invalid_argument  raised when there are not enough bytes in the array
    MVCOMMON_API static Vector4d FromRawBytes(ByteArray & bytes, bool consumeBytes = false);
    /// \brief A count of bytes the vector requires in a serialized form.
    MVCOMMON_API static const size_t RAW_BYTES_SIZE;

    /// \brief Gets a length of the vector.
    /// \returns  vector's length
    MVCOMMON_API double Length() const;
    /// \brief Creates a vector with inverted dimensions (1/x).
    /// \returns  an inverted vector
    MVCOMMON_API Vector4d Inverted() const;
    /// \brief Creates a normalized vector (with length equal to 1).
    /// \details Returns an unchanged vector in case its length is equal to 0.
    /// \returns  a normalized vector
    MVCOMMON_API Vector4d Normalized() const;
    /// \brief Creates a vector with dimensions with absolute values of the original vector.
    /// \returns  a vector with absolute-valued dimensions
    MVCOMMON_API Vector4d Abs() const;
    /// \brief Extracts x, y and z coordinates as a 3-dimensional vector.
    /// \returns  a 3-dimensional vector
    MVCOMMON_API Vector3d GetXYZ() const;

    /// \brief Calculates a dot product of two vectors.
    /// \param lhs  a first vector-operand
    /// \param rhs  a second vector-operand
    /// \returns    a dot product
    MVCOMMON_API static double Dot(Vector4d const & lhs, Vector4d const & rhs);

    /// \brief Accesses vector dimension value via index.
    /// \param pos  an index of the dimension to access
    /// \returns    a reference to the dimension value
    /// \exception std::out_of_range  raised when index is out of range (0-3)
    MVCOMMON_API double & operator[] (size_t pos);
    /// \brief Accesses vector dimension value via index.
    /// \param pos  an index of the dimension to access
    /// \returns    a reference to the dimension value
    /// \exception std::out_of_range  raised when index is out of range (0-3)
    MVCOMMON_API double const & operator[] (size_t pos) const;

    /// \cond
    MVCOMMON_API Vector4d & operator+=(Vector4d const & other);
    MVCOMMON_API Vector4d & operator-=(Vector4d const & other);
    MVCOMMON_API Vector4d & operator*=(double factor);
    MVCOMMON_API Vector4d & operator/=(double divisor);
    /// \endcond

    DECLARE_CLASS_SPECIFIC_NEW_DELETE(MVCOMMON_API)
  };

  /// \cond
  MVCOMMON_API Vector4d operator-(Vector4d const & vector);
  MVCOMMON_API Vector4d operator+(Vector4d const & lhs, Vector4d const & rhs);
  MVCOMMON_API Vector4d operator-(Vector4d const & lhs, Vector4d const & rhs);
  MVCOMMON_API Vector4d operator*(Vector4d const & vector, double factor);
  MVCOMMON_API Vector4d operator*(double factor, Vector4d const & vector);
  MVCOMMON_API Vector4d operator/(Vector4d const & vector, double divisor);
  MVCOMMON_API bool operator==(Vector4d const & lhs, Vector4d const & rhs);
  MVCOMMON_API bool operator!=(Vector4d const & lhs, Vector4d const & rhs);
  /// \endcond

  /// \brief A hasher for Vector4d objects so they can be used in unordered collections.
  struct Vector4dHasher
  {
    /// \brief Calculates a hash value from the object.
    /// \param vector an object to calculate the hash value of
    /// \returns      hash value of the object
    MVCOMMON_API size_t operator()(Vector4d const & vector) const;
  };
}