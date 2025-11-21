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
#include <cstdint>
#include <map>

#include <MVCommon/MVCommonAPI.h>

namespace MVCommon
{
  class ParamString
  {
  public:
    MVCOMMON_API ParamString();
    MVCOMMON_API ParamString(const std::string &input);

    MVCOMMON_API void        parse(const std::string &input);
    MVCOMMON_API std::string toString();

    MVCOMMON_API void        addParam(const std::string &name, const std::string &value);
    MVCOMMON_API void        addParam(const std::string &name, const int64_t &value);
    MVCOMMON_API void        addParam(const std::string &name, const float &value);
    MVCOMMON_API void        addParam(const std::string &name, const bool &value);

    MVCOMMON_API std::string getParamString(const std::string &name, const std::string &defaultValue = "");
    MVCOMMON_API int64_t     getParamInt(const std::string &name, int64_t defaultValue = 0);
    MVCOMMON_API float       getParamFloat(const std::string &name, float defaultValue = 0.0f);
    MVCOMMON_API bool        getParamBool(const std::string &name, bool defaultValue = false);

  private:
    std::map<std::string, std::string> _params;
  };
}
