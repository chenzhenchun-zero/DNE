#pragma once
#include <MVCommon/MVCommonAPI.h>
#include <string>

namespace MVCommon
{
  class StringVar
  {
  public:
    MVCOMMON_API StringVar(const char* key);
    MVCOMMON_API StringVar(const char* key, const char* value);
    MVCOMMON_API virtual ~StringVar() {};
    MVCOMMON_API virtual std::string GetValue();
    MVCOMMON_API virtual void SetValue(const char* value);
    std::string Key;

  protected:
    std::string _value;
  };

  class StringVarRoot : public StringVar
  {
  public:
    MVCOMMON_API StringVarRoot();
    MVCOMMON_API std::string GetValue() override;
  };

  class StringVarNow : public StringVar
  {
  public:
    MVCOMMON_API StringVarNow();
    MVCOMMON_API std::string GetValue() override;
  };

  class StringVarHostId : public MVCommon::StringVar
  {
  public:
    MVCOMMON_API StringVarHostId();
    MVCOMMON_API std::string GetValue() override;
    MVCOMMON_API static std::string TheKey();
  };

  class StringVarHostName : public MVCommon::StringVar
  {
  public:
    MVCOMMON_API StringVarHostName();
    MVCOMMON_API std::string GetValue() override;
    MVCOMMON_API static std::string TheKey();
  };

  class StringVarSettings : public StringVar
  {
  public:
    MVCOMMON_API StringVarSettings();
    MVCOMMON_API std::string GetValue() override;
  };

  class StringVarLocalStorage : public MVCommon::StringVar
  {
  public:
    MVCOMMON_API StringVarLocalStorage();
    MVCOMMON_API std::string GetValue() override;
    MVCOMMON_API static std::string TheKey();
  };


  class StringVarLocalGraphs : public MVCommon::StringVar
  {
  public:
    MVCOMMON_API StringVarLocalGraphs();
    MVCOMMON_API std::string GetValue() override;
    MVCOMMON_API static std::string TheKey();
  };
}
