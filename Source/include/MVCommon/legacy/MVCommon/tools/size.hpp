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

#include <MVCommon/MVCommonAPI.h>

namespace MVCommon
{
  class MVCOMMON_API Size
  {
  public:
    Size();
    Size(int32_t width, int32_t height);

    int32_t width() const;
    int32_t height() const;

    void    setWidth(int32_t width);
    void    setHeight(int32_t height);

    inline bool empty() const { return area() == 0; }
    inline int32_t area() const { return _width*_height; }

    Size    operator + (const Size& other) const;
    void    operator += (const Size& other);
    Size    operator - (const Size& other) const;
    void    operator -= (const Size& other);
    bool    operator == (const Size& other) const;
    bool    operator != (const Size& other) const;

  private:
    int32_t _width;
    int32_t _height;
  };
}
