#pragma once

#include <MVCommon/MVCommonAPI.h>
#include <MVCommon/Memory.h>

namespace MVCommon
{
  struct ByteArrayImpl;

  /// \brief An array of bytes.
  /// \details
  /// The implementation maintains a continuous array (vector) of bytes (uint8_t), which is resized when necessary and under specific
  /// conditions for maximum efficiency. The array provides operations for pushing bytes to the end of the array and for popping
  /// them from the array's front, behaving thus like a queue. The difference from std::queue is that the array's internal storage is
  /// continuous.
	class ByteArray
  {
  public:
    /// \brief A constructor.
    /// \details Creates an empty array of bytes.
    MVCOMMON_API ByteArray();
    /// \brief A constructor.
    /// \param data a pointer to data to initialize the array with
    /// \param size a size of the data to initialize the array with
    /// \details Creates an array of bytes initialized with the given data.
    MVCOMMON_API ByteArray(uint8_t const * data, size_t size);
    /// \brief A constructor.
    /// \param byte   a byte to initialize the array with
    /// \param count  a count of bytes to initialize the array with
    /// \details Creates an array of bytes containing the given amount of the same byte.
    MVCOMMON_API ByteArray(uint8_t byte, size_t count = 1);
    /// \brief A copy constructor.
    /// \param other  an array to make a copy of
    MVCOMMON_API ByteArray(ByteArray const & other);
    /// \brief A move constructor.
    /// \param other  an array to move
    MVCOMMON_API ByteArray(ByteArray && other);
    /// \brief A destructor.
    MVCOMMON_API ~ByteArray();

    /// \brief Gets a pointer to the array's internal continuous memory.
    /// \returns  a pointer to the array's memory
    /// \details
    /// The call may return different pointers at different times, for example when some bytes were already popped. The returned pointer always
    /// points to the next byte that would be popped if such a call took place.
    MVCOMMON_API uint8_t const * Data() const;
    /// \brief Gets size of the array.
    /// \returns  array's size
    MVCOMMON_API size_t Size() const;

    /// \brief Empties the array.
    MVCOMMON_API void Clear();

    /// \brief Pushes another array of bytes to the end of this array.
    /// \param other  an array to push to this array
    /// \returns      this array
    MVCOMMON_API ByteArray & Push(ByteArray const & other);
    /// \brief Pushes an array of the same byte to the end of this array.
    /// \param byte   a byte to push
    /// \param count  a count of bytes to push
    /// \returns      this array
    MVCOMMON_API ByteArray & Push(uint8_t byte, size_t count = 1);
    /// \brief Pushes data to the end of this array.
    /// \param data a pointer to data to push
    /// \param size a size of the data to push
    /// \returns    this array
    MVCOMMON_API ByteArray & Push(uint8_t const * data, size_t size);
    /// \brief Pops and removes a single byte from the front of the array.
    /// \returns  the front byte
    /// \exception std::runtime_error raised when there are no data available in the array
    MVCOMMON_API uint8_t Pop();
    /// \brief Pops an array of bytes from the front of the array.
    /// \param count  a count of bytes to pop
    /// \returns      the array of bytes popped from the front
    /// \details
    /// The call always succeeds, even when there is not enough bytes in the array. The returned array will in such case
    /// contain less bytes than requested.
    MVCOMMON_API ByteArray Pop(size_t count);
    /// \brief Skips an array of bytes from the front of the array.
    /// \param count  a count of bytes to skip
    /// \details The call always succeeds, even when there is not enough bytes in the array.
    MVCOMMON_API void Skip(size_t count = 1);
    /// \brief Creates a subarray of bytes from the array, not removing the bytes from the original array.
    /// \param startPos a position of the first byte
    /// \param count    a count of bytes
    /// \returns        the subarray of bytes
    /// \details
    /// The call always succeeds, even when there is not enough bytes in the original array or when the starting position is outside of 
    /// the valid range. The returned array will in such case contain less bytes than requested or even no bytes at all.
    MVCOMMON_API ByteArray Subarray(size_t startPos = 0, size_t count = 1);

    /// \brief Accesses a specific byte in the array.
    /// \param pos  an index of the byte to access
    /// \returns    a reference to the byte of the array
    /// \details No bounds checking is performed.
    MVCOMMON_API uint8_t & operator[] (size_t pos);
    /// \brief Accesses a specific byte in the array.
    /// \param pos  an index of the byte to access
    /// \returns    a reference to the byte of the array
    /// \details No bounds checking is performed.
    MVCOMMON_API uint8_t const & operator[] (size_t pos) const;

    /// \brief An assignment operator.
    /// \details Replaces the array's content by a copy of another array's content.
    /// \param other  an array to copy the content from
    /// \returns      this array
    MVCOMMON_API ByteArray & operator=(ByteArray other);
    /// \brief Pushes another array of bytes to the end of this array.
    /// \param other  an array to push to this array
    /// \returns      this array
    MVCOMMON_API ByteArray & operator<<=(ByteArray const & other);
    /// \brief Pushes a byte to the end of this array.
    /// \param byte a byte to push
    /// \returns    this array
    MVCOMMON_API ByteArray & operator<<=(uint8_t byte);
    /// \brief Extracts a byte from the front of the array.
    /// \param byte a reference to byte to extract into
    /// \returns    this array
    /// \exception std::runtime_error raised when there are no data available in the array
    MVCOMMON_API ByteArray & operator>>=(uint8_t & byte);

    DECLARE_CLASS_SPECIFIC_NEW_DELETE(MVCOMMON_API)

    /// \cond
    friend struct ByteArrayHasher;
    /// \endcond

  private:
    ByteArrayImpl * _pImpl;
  };

  /// \brief Pushes an array of bytes to the end of another array.
  /// \param lhs  an array to push into
  /// \param rhs  an array to push
  /// \returns    the array that was pushed into
  MVCOMMON_API ByteArray & operator<<(ByteArray & lhs, ByteArray const & rhs);
  /// \brief Pushes a byte to the end of an array.
  /// \param lhs  an array to push into
  /// \param byte a byte to push
  /// \returns    the array that was pushed into
  MVCOMMON_API ByteArray & operator<<(ByteArray & lhs, uint8_t byte);
  /// \brief Extracts a byte from the front of an array.
  /// \param lhs  an array to extract from
  /// \param byte a reference to byte to extract into
  /// \returns    this array
  /// \exception std::runtime_error raised when there are no data available in the array
  MVCOMMON_API ByteArray & operator>>(ByteArray & lhs, uint8_t & byte);
  /// \cond
  MVCOMMON_API bool operator==(ByteArray const & lhs, ByteArray const & rhs);
  MVCOMMON_API bool operator!=(ByteArray const & lhs, ByteArray const & rhs);
  /// \endcond

  /// \brief A hasher for ByteArray objects so they can be used in unordered collections.
  struct ByteArrayHasher
  {
    /// \brief Calculates a hash value from the object.
    /// \param byteArray  an object to calculate the hash value of
    /// \returns          hash value of the object
    MVCOMMON_API size_t operator()(ByteArray const & byteArray) const;
  };
}