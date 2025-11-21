#pragma once

#include <MVCommon/MVCommonAPI.h>
#include <MVCommon/Memory.h>

#include "Vector4f.h"

#include <MVCommon/utils/String.h>
#include <MVCommon/utils/ByteArray.h>

namespace MVCommon
{
  struct Vector3f;
  struct Versorf;

  /// \brief A 4x4 matrix with single-precision floating-point values.
  struct Matrix4x4f final
  {
  public:
    /// \brief A constructor of an identity matrix (with all elements on main diagonal set to 1 and the rest set to 0).
    MVCOMMON_API Matrix4x4f();
    /// \brief A constructor.
    /// \param a00  an m[0][0] value
    /// \param a01  an m[0][1] value
    /// \param a02  an m[0][2] value
    /// \param a03  an m[0][3] value
    /// \param a10  an m[1][0] value
    /// \param a11  an m[1][1] value
    /// \param a12  an m[1][2] value
    /// \param a13  an m[1][3] value
    /// \param a20  an m[2][0] value
    /// \param a21  an m[2][1] value
    /// \param a22  an m[2][2] value
    /// \param a23  an m[2][3] value
    /// \param a30  an m[3][0] value
    /// \param a31  an m[3][1] value
    /// \param a32  an m[3][2] value
    /// \param a33  an m[3][3] value
    MVCOMMON_API Matrix4x4f(
      float a00, float a01, float a02, float a03,
      float a10, float a11, float a12, float a13,
      float a20, float a21, float a22, float a23,
      float a30, float a31, float a32, float a33);
    /// \brief A constructor.
    /// \param row0 a row 0
    /// \param row1 a row 1
    /// \param row2 a row 2
    /// \param row3 a row 3
    MVCOMMON_API Matrix4x4f(
      Vector4f const & row0,
      Vector4f const & row1,
      Vector4f const & row2,
      Vector4f const & row3);

    /// \brief Converts the matrix into a human-readable string.
    /// \returns  the matrix string
    MVCOMMON_API String ToString() const;
    /// \brief Creates a matrix from a human-readable string.
    /// \param str  a matrix string
    /// \returns    a matrix
    MVCOMMON_API static Matrix4x4f FromString(String const & str);
    /// \brief Serializes the matrix into a byte array.
    /// \param bytes  a byte array to serialize into
    MVCOMMON_API void ToRawBytes(ByteArray & bytes) const;
    /// \brief Deserializes matrix from a byte array.
    /// \param bytes        an array of matrix bytes
    /// \param consumeBytes determines whether bytes of the matrix shall be removed from the array
    /// \returns            a matrix
    /// \exception std::invalid_argument  raised when there are not enough bytes in the array
    MVCOMMON_API static Matrix4x4f FromRawBytes(ByteArray & bytes, bool consumeBytes = false);
    /// \brief A count of bytes the matrix requires in a serialized form.
    MVCOMMON_API static const size_t RAW_BYTES_SIZE;
    /// \brief Serializes the matrix into an elements array.
    /// \param elements an array of 4x4 elements
    MVCOMMON_API void ToRawElements(float * elements) const;
    /// \brief Deserializes matrix from an elements array.
    /// \param elements an array of 4x4 elements
    /// \returns        a matrix
    MVCOMMON_API static Matrix4x4f FromRawElements(float const * elements);

    /// \brief Creates a transposed matrix.
    /// \returns  a transposed matrix
    MVCOMMON_API Matrix4x4f Transposed() const;
    /// \brief Creates an inverted matrix.
    /// \param ok indicates whether the inverted matrix was successfully created, since it is not always possible to create one
    /// \returns  an inverted matrix
    MVCOMMON_API Matrix4x4f Inverted(bool & ok) const;
    /// \brief Creates an inverted matrix of a rotation-translation matrix.
    /// \details
    /// It is always possible to create an inverted matrix of a rotation-translation matrix and the algorithm is much simpler and 
    /// more effective than generic inversion algorithm. However, it is up to user to know what matrices he calls the function on
    /// - the function assumes the matrix is a rotation-translation matrix.
    /// \returns  an inverted matrix
    MVCOMMON_API Matrix4x4f RotationTranslationMatrixInverted() const;

    /// \brief Creates a matrix with all elements set to zero.
    /// \returns  a zero matrix
    MVCOMMON_API static Matrix4x4f CreateZero();

    /// \brief Creates a translation matrix.
    /// \param translation  a vector describing the translation
    /// \returns            a translation matrix
    MVCOMMON_API static Matrix4x4f CreateTranslation(Vector3f const & translation);
    /// \brief Creates a scaling matrix.
    /// \param scale  a vector describing the scale
    /// \returns      a scaling matrix
    MVCOMMON_API static Matrix4x4f CreateScale(Vector3f const & scale);
    /// \brief Creates a rotation matrix from Euler angles (in degrees) in eulerAngles.z -> eulerAngles.y -> eulerAngles.x order.
    /// \param eulerAngles  Euler angles of Z-Y-X rotation
    /// \returns            a rotation matrix
    MVCOMMON_API static Matrix4x4f CreateRotationFromEulerAnglesZYX(Vector3f const & eulerAngles);
    /// \brief Creates a rotation matrix from axis of rotation and an angle (in degrees).
    /// \param axis   an axis of rotation
    /// \param angle  an angle
    /// \returns      a rotation matrix
    MVCOMMON_API static Matrix4x4f CreateRotationAroundAxis(Vector3f const & axis, float angle);
    /// \brief Creates a rotation matrix from a versor.
    /// \param versor a versor describing rotation
    /// \returns      a rotation matrix
    MVCOMMON_API static Matrix4x4f CreateRotationFromVersor(Versorf const & versor);

    /// \brief Creates a matrix for ortographic projection.
    /// \param left   a left coordinate
    /// \param right  a right coordinate
    /// \param bottom a bottom coordinate
    /// \param top    a top coordinate
    /// \param near   a near coordinate
    /// \param far    a far coordinate
    /// \returns      an ortographic-projection matrix
    MVCOMMON_API static Matrix4x4f CreateOrtographic(float left, float right, float bottom, float top, float near, float far);
    /// \brief Creates a matrix for perspective projection.
    /// \param fieldOfView  a field of view (in degrees)
    /// \param aspectRatio  an aspect ratio
    /// \param near         a near coordinate
    /// \param far          a far coordinate
    /// \returns            a perspective-projection matrix
    MVCOMMON_API static Matrix4x4f CreatePerspective(float fieldOfView, float aspectRatio, float near, float far);
    /// \brief Creates a viewing transformation matrix.
    /// \param eyePosition  a position of the viewing camera
    /// \param centerPoint  a point the camera is looking at
    /// \param upDirection  an up-direction of the viewing camera
    /// \returns            a viewing transformation matrix
    /// \details
    /// The resulting 'look-at' matrix follows the same principle as OpenGL's gluLookAt utility function:
    /// the matrix maps the reference (center) point to the negative z axis and the eye position to the origin.
    /// similarly, the up direction projected onto the viewing plane is mapped to the positive y axis. The UP vector
    /// must not be parallel to the line of sight from the eye position to the reference point.
    MVCOMMON_API static Matrix4x4f CreateLookAt(Vector3f const & eyePosition, Vector3f const & centerPoint, Vector3f const & upDirection);

    /// \brief Accesses a specific row in the matrix.
    /// \param pos  an index of the row to access
    /// \returns    a reference to the row of the matrix
    /// \exception std::out_of_range  raised when the index of the row is out of range (0-3)
    MVCOMMON_API Vector4f & operator[] (size_t pos);
    /// \brief Accesses a specific row in the matrix.
    /// \param pos  an index of the row to access
    /// \returns    a reference to the row of the matrix
    /// \exception std::out_of_range  raised when the index of the row is out of range (0-3)
    MVCOMMON_API Vector4f const & operator[] (size_t pos) const;

    DECLARE_CLASS_SPECIFIC_NEW_DELETE(MVCOMMON_API)

    /// \cond
    friend struct Matrix4x4fHasher;
    /// \endcond

  private:
    Vector4f _row0;
    Vector4f _row1;
    Vector4f _row2;
    Vector4f _row3;
  };

  /// \cond
  MVCOMMON_API bool operator==(Matrix4x4f const & lhs, Matrix4x4f const & rhs);
  MVCOMMON_API bool operator!=(Matrix4x4f const & lhs, Matrix4x4f const & rhs);

  MVCOMMON_API Matrix4x4f operator*(Matrix4x4f const & lhs, Matrix4x4f const & rhs);
  MVCOMMON_API Vector4f operator*(Matrix4x4f const & matrix, Vector4f const & vector);
  MVCOMMON_API Vector3f operator*(Matrix4x4f const & matrix, Vector3f const & vector);
  /// \endcond

  /// \brief A hasher for Matrix4x4f objects so they can be used in unordered collections.
  struct Matrix4x4fHasher
  {
    /// \brief Calculates a hash value from the object.
    /// \param matrix an object to calculate the hash value of
    /// \returns      hash value of the object
    MVCOMMON_API size_t operator()(Matrix4x4f const & matrix) const;
  };
}