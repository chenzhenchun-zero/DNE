#pragma once

#include <MVCommon/MVCommonAPI.h>
#include <MVCommon/Memory.h>

#include <MVCommon/utils/String.h>

namespace MVCommon
{
  struct Vector4f;

  /// \brief An RGBA color.
  struct Color final
  {
  public:
    /// \brief A constructor of the black color.
    MVCOMMON_API Color();
    /// \brief A constructor.
    /// \param redByte    a red element byte value
    /// \param greenByte  a green element byte value
    /// \param blueByte   a blue element byte value
    /// \param alphaByte  an alpha element byte value
    MVCOMMON_API Color(uint8_t redByte, uint8_t greenByte, uint8_t blueByte, uint8_t alphaByte = 255);
    /// \brief A constructor.
    /// \param red    a red element value in range <0.0, 1.0>
    /// \param green  a green element value in range <0.0, 1.0>
    /// \param blue   a blue element value in range <0.0, 1.0>
    /// \param alpha  an alpha element value in range <0.0, 1.0>
    MVCOMMON_API Color(float red, float green, float blue, float alpha = 1.0f);
    /// \brief A constructor.
    /// \param color  a vector containing color element values in range <0.0, 1.0> (x -> red, y -> green, z -> blue, w -> alpha)
    MVCOMMON_API Color(Vector4f const & color);
    /// \brief A destructor.
    MVCOMMON_API ~Color();

    /// \brief Converts the color into a human-readable string.
    /// \returns  the color string
    MVCOMMON_API String ToString() const;
    /// \brief Creates a color from a human-readable string.
    /// \param str  a color string
    /// \returns    a color
    MVCOMMON_API static Color FromString(String const & str);
    /// \brief Converts the RGB part of the color into a HTML hexadecimal string in format \#rrggbb.
    /// \returns  the RGB HTML hexadecimal string
    MVCOMMON_API String ToRGB_HTMLString() const;

    /// \brief Returns a red element byte value.
    /// \returns  a red element byte value
    MVCOMMON_API uint8_t GetRedByte() const;
    /// \brief Returns a green element byte value.
    /// \returns  a green element byte value
    MVCOMMON_API uint8_t GetGreenByte() const;
    /// \brief Returns a blue element byte value.
    /// \returns  a blue element byte value
    MVCOMMON_API uint8_t GetBlueByte() const;
    /// \brief Returns an alpha element byte value.
    /// \returns  an alpha element byte value
    MVCOMMON_API uint8_t GetAlphaByte() const;

    /// \brief Returns a red element value in range <0.0, 1.0>.
    /// \returns  a red element value
    MVCOMMON_API float GetRed() const;
    /// \brief Returns a green element value in range <0.0, 1.0>.
    /// \returns  a green element value
    MVCOMMON_API float GetGreen() const;
    /// \brief Returns a blue element value in range <0.0, 1.0>.
    /// \returns  a blue element value
    MVCOMMON_API float GetBlue() const;
    /// \brief Returns an alpha element value in range <0.0, 1.0>.
    /// \returns  an alpha element value
    MVCOMMON_API float GetAlpha() const;

    /// \brief Sets value of the color.
    /// \param redByte    a new red element byte value
    /// \param greenByte  a new green element byte value
    /// \param blueByte   a new blue element byte value
    /// \param alphaByte  a new alpha element byte value
    MVCOMMON_API void SetValue(uint8_t redByte, uint8_t greenByte, uint8_t blueByte, uint8_t alphaByte = 255);
    /// \brief Sets value of the color.
    /// \param red    a new red element value in range <0.0, 1.0>
    /// \param green  a new green element value in range <0.0, 1.0>
    /// \param blue   a new blue element value in range <0.0, 1.0>
    /// \param alpha  a new alpha element value in range <0.0, 1.0>
    MVCOMMON_API void SetValue(float red, float green, float blue, float alpha = 1.0f);
    /// \brief Sets value of the color.
    /// \param color  a vector containing new color element values in range <0.0, 1.0> (x -> red, y -> green, z -> blue, w -> alpha)
    MVCOMMON_API void SetValue(Vector4f const & color);

    /// \brief Sets red element byte value.
    /// \param redByte  a new red element byte value
    MVCOMMON_API void SetRedByte(uint8_t redByte);
    /// \brief Sets green element byte value.
    /// \param greenByte  a new green element byte value
    MVCOMMON_API void SetGreenByte(uint8_t greenByte);
    /// \brief Sets blue element byte value.
    /// \param blueByte a new blue element byte value
    MVCOMMON_API void SetBlueByte(uint8_t blueByte);
    /// \brief Sets alpha element byte value.
    /// \param alphaByte  a new alpha element byte value
    MVCOMMON_API void SetAlphaByte(uint8_t alphaByte);
    /// \brief Sets red element value in range <0.0, 1.0>.
    /// \param red  a new red element value
    MVCOMMON_API void SetRed(float red);
    /// \brief Sets green element value in range <0.0, 1.0>.
    /// \param green  a new green element value
    MVCOMMON_API void SetGreen(float green);
    /// \brief Sets blue element value in range <0.0, 1.0>.
    /// \param blue a new blue element value
    MVCOMMON_API void SetBlue(float blue);
    /// \brief Sets alpha element value in range <0.0, 1.0>.
    /// \param alpha  a new alpha element value
    MVCOMMON_API void SetAlpha(float alpha);

    /// \brief Calculates an RGB brightness byte value of the color.
    /// \returns  an RGB brightness byte value
    MVCOMMON_API uint8_t GetRGBBrightnessByte() const;
    /// \brief Calculates an RGB brightness value of the color in range <0.0, 1.0>.
    /// \returns  an RGB brightness value
    MVCOMMON_API float GetRGBBrightness() const;

    /// \cond
    MVCOMMON_API friend bool operator==(Color const & lhs, Color const & rhs);
    /// \endcond

    DECLARE_CLASS_SPECIFIC_NEW_DELETE(MVCOMMON_API)

    /// \cond
    friend struct ColorHasher;
    /// \endcond

  private:
    uint8_t _redByte;
    uint8_t _greenByte;
    uint8_t _blueByte;
    uint8_t _alphaByte;
  };

  /// \cond
  MVCOMMON_API bool operator==(Color const & lhs, Color const & rhs);
  MVCOMMON_API bool operator!=(Color const & lhs, Color const & rhs);
  /// \endcond

  /// \brief A hasher for Color objects so they can be used in unordered collections.
  struct ColorHasher
  {
    /// \brief Calculates a hash value from the object.
    /// \param color  an object to calculate the hash value of
    /// \returns      hash value of the object
    MVCOMMON_API size_t operator()(Color const & color) const;
  };
}
