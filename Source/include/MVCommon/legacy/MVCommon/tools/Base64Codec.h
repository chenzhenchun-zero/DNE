#pragma once

#include <string>

namespace MVCommon
{
  class Base64Codec
  {
  public:
    static std::string encode(unsigned char const*, unsigned int len);
    static std::string decode(std::string const& s);
  };
}

