#pragma once

#include <MVCommon/MVCommonAPI.h>
#include <map>
#include <vector>
#include <memory>
#include <string>

namespace MVCommon
{
  class StringVar;

  class VarManager
  {
    VarManager();
    std::map<std::string, std::string> _varMap;

  public:
    MVCOMMON_API static VarManager* getInstance();
    MVCOMMON_API void addStringVar(std::shared_ptr<StringVar> spStringVar);
    MVCOMMON_API std::string getValue(const char* key);
    MVCOMMON_API void setValue(const char* key, const char* value);
    MVCOMMON_API std::string translateFromVars(const char* input);
    MVCOMMON_API std::string translateToVars(const char* input);

    std::vector<std::shared_ptr<StringVar>> Vars;

    MVCOMMON_API static std::string getNowKey();
    MVCOMMON_API static std::string getNowValue();

    MVCOMMON_API static std::string getRootKey();
    MVCOMMON_API static std::string getRootValue();

    MVCOMMON_API static std::string getSettingsKey();
    MVCOMMON_API static std::string getSettingsValue();

    MVCOMMON_API static std::string translateFromRoot(const char* path);
    MVCOMMON_API static std::string translateToRoot(const char* path);
  };
}
