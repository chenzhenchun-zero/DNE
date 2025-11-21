#pragma once

#include <MVCommon/MVCommonAPI.h>

namespace MVCommon
{
  /// \brief A utility class for math operations.
  class Math
  {
  public:
    /// \brief A smallest possible difference between two single-precision floating-point values.
    MVCOMMON_API static const float SINGLE_EPSILON;
    /// \brief A smallest possible difference between two double-precision floating-point values.
    MVCOMMON_API static const double DOUBLE_EPSILON;

    /// \brief Compares two single-precision floating-point values with a tolerance.
    /// \param val1       a value to compare
    /// \param val2       a value to compare
    /// \param precision  a required precision
    /// \returns          true in case the difference between the two values is less or equal than a very small value (epsilon)
    MVCOMMON_API static bool AlmostEqual(float val1, float val2, float precision = SINGLE_EPSILON);
    /// \brief Compares two double-precision floating-point values with a tolerance.
    /// \param val1       a value to compare
    /// \param val2       a value to compare
    /// \param precision  a required precision
    /// \returns          true in case the difference between the two values is less or equal than a very small value (epsilon)
    MVCOMMON_API static bool AlmostEqual(double val1, double val2, double precision = DOUBLE_EPSILON);
    
    /// \brief Clamps a value to a minimum-maximum range.
    /// \tparam T     a type of the values
    /// \param value  a value to clamp
    /// \param min    a minimum value
    /// \param max    a maximum value
    /// \returns      a clamped value (in the given range)
    template<class T>
    static T Clamp(T const & value, T const & min, T const & max)
    {
      return (value < min ? min : (value > max ? max : value));
    }

  private:
    /// \brief A private constructor.
    Math();
  };
}