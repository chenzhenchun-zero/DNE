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

#include <string>

#include <MVCommon/MVCommonAPI.h>

namespace MVCommon
{
  class Property
  {
  public:
    MVCOMMON_API Property();
    MVCOMMON_API Property(const std::string &name, const std::string &value);

    MVCOMMON_API void setName(std::string name) { _name = name; }
    MVCOMMON_API std::string Name() const { return _name; }
    MVCOMMON_API void setValue(std::string value) { _value = value; }
    MVCOMMON_API std::string Value() const { return _value; }

  private:
    std::string _name;
    std::string _value;
  };
}
