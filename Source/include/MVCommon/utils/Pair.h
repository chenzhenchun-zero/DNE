#pragma once

#include <MVCommon/MVCommonAPI.h>
#include <MVCommon/Memory.h>

namespace MVCommon
{
  /// \brief A pair of values. 
  /// \tparam TFirst  a type of pair's first element
  /// \tparam TSecond a type of pair's second element
  template<typename TFirst, typename TSecond>
  class Pair
  {
  public:
    /// \brief A type of pair's first element. 
    using FirstType = TFirst;
    /// \brief A type of pair's second element. 
    using SecondType = TSecond;

    /// \brief A constructor. 
    /// \param first  a first value
    /// \param second a second value
    Pair(TFirst const & first, TSecond const & second) : first(first), second(second) {}
    /// \brief A destructor. 
    virtual ~Pair() {}

    /// \brief A first value. 
    TFirst first;
    /// \brief A second value. 
    TSecond second;
  };
}