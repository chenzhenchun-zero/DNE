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
  class MVCOMMON_API Point
  {
  public:
    Point();
    Point(int32_t x, int32_t y);

    int32_t x() const;
    int32_t y() const;

    void    setX(int32_t x);
    void    setY(int32_t y);

    Point   operator + (const Point& other) const;
    void    operator += (const Point& other);
    Point   operator - (const Point& other) const;
    void    operator -= (const Point& other);
    bool    operator == (const Point& other) const;
    bool    operator != (const Point& other) const;

  private:
    int32_t _x;
    int32_t _y;
  };
}
