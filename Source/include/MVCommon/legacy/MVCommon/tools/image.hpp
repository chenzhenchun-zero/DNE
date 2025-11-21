// --------------------------------------------------------------------
//    _________   _____________                                       
//   /     \   \ /   /\_   ___ \  ____   _____   _____   ____   ____  
//  /  \ /  \   Y   / /    \  \/ /  _ \ /     \ /     \ /  _ \ /    \
// /    Y    \     /  \     \___(  <_> )  Y Y  \  Y Y  (  <_> )   |  \
// \____|__  /\___/    \______  /\____/|__|_|  /__|_|  /\____/|___|  /
//         \/                 \/             \/      \/            \/ 
//
//          Mantis Vision Common Code Library
// --------------------------------------------------------------------
#pragma once

#include <cstdint>
#include <vector>
#include <memory>

#include <MVCommon/MVCommonAPI.h>
#include "size.hpp"

namespace MVCommon
{
  typedef std::shared_ptr<class Image> SpImage;

  class Image
  {
  public:
    MVCOMMON_API Image();
    MVCOMMON_API Image(Size size);
    MVCOMMON_API Image(Size size, std::vector<uint8_t> const & data);
    MVCOMMON_API Image(Size size, std::vector<uint8_t> && data);
    MVCOMMON_API Image(Image const &img);
    MVCOMMON_API Image(Image && img);
    MVCOMMON_API ~Image();
    
    MVCOMMON_API Size size() const;
    MVCOMMON_API void setSize(Size size);

    MVCOMMON_API uint8_t const* data() const;
    MVCOMMON_API uint8_t* data();
    
    MVCOMMON_API std::size_t dataSize() const;

    MVCOMMON_API void scale(Size size);

    MVCOMMON_API void save(std::vector<uint8_t> &data) const;
    MVCOMMON_API void load(std::vector<uint8_t> const &data);
    MVCOMMON_API void load(uint8_t* pData, unsigned long numBytes);

  private:
    Size _size;
    std::vector<uint8_t> _data;

  };
}
