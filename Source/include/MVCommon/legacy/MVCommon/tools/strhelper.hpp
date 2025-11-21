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
#include <string>
#include <deque>
#include <vector>
#include <sstream>

#include <MVCommon/MVCommonAPI.h>

namespace MVCommon
{
  class StringHelper 
  {
  public:
    template <typename T>
    static std::string to_string(T value)
    {
      std::ostringstream ss;
      ss << value;
      return ss.str();
    }

    MVCOMMON_API static int32_t                  toInt(const std::string &str);
    MVCOMMON_API static uint32_t                 toUInt(const std::string &str);
    MVCOMMON_API static int64_t                  toInt64(const std::string &str);
    MVCOMMON_API static uint64_t                 toUInt64(const std::string &str);
    MVCOMMON_API static uint32_t                 toUIntHex(const std::string &str);
    MVCOMMON_API static uint16_t                 toUShort(const std::string &str);
    MVCOMMON_API static uint16_t                 toUShortHex(const std::string &str);
    MVCOMMON_API static float                    toFloat(const std::string &str);
    MVCOMMON_API static std::string              to_string(int value, int numDigits);
    MVCOMMON_API static std::string              rightJustified(const std::string &str, uint32_t length, char fill);
    MVCOMMON_API static bool                     startsWith(const std::string &str, const std::string &start);
    MVCOMMON_API static bool                     startsWith(const char* str, const char* start);
    MVCOMMON_API static bool                     startsWith_CaseSensitive(const char* str, const char* start);
    MVCOMMON_API static bool                     endsWith(const std::string &str, const std::string &end);
    MVCOMMON_API static bool                     endsWith(const char* str, const char* ending);
    MVCOMMON_API static bool                     endsWith_CaseSensitive(std::string const& str, std::string const& ending);
    MVCOMMON_API static std::string              toLower(const std::string &str);
    MVCOMMON_API static std::string              toLower(const char* str);
    MVCOMMON_API static std::string              toUpper(const std::string &str);
    MVCOMMON_API static std::string              toUpper(const char* str);
    MVCOMMON_API static std::string              capitalize(const std::string &str);
    MVCOMMON_API static std::vector<std::string> split(const std::string& s, char delim);
    MVCOMMON_API static std::vector<std::string> split(const char* s, char delim);
    MVCOMMON_API static std::deque<std::string>  split_q(const std::string &str, char separator, bool skipEmptyParts = false);
    MVCOMMON_API static void                     chop(std::string &str, uint32_t count);
    MVCOMMON_API static void                     remove(std::string &str, uint32_t start, uint32_t count);
    MVCOMMON_API static std::string              hexNumber(int32_t value);
    MVCOMMON_API static std::string              hexNumber(uint32_t value);
    MVCOMMON_API static std::string              number(int32_t value);
    MVCOMMON_API static std::string              number(uint32_t value);
    MVCOMMON_API static std::string              number(int64_t value);
    MVCOMMON_API static std::string              number(uint64_t value);
    MVCOMMON_API static std::string              number(float value);
    MVCOMMON_API static std::string              number(double value);
    MVCOMMON_API static std::string              dateTime(uint64_t value, const char *strftimeFormat);

    MVCOMMON_API static std::string              trim_start_end(const std::string &s);
    MVCOMMON_API static bool                     replace(std::string& str, const std::string& from, const std::string& to);
    MVCOMMON_API static bool                     replace_first_of(std::string& str, const std::string& from, const std::string& to);
    MVCOMMON_API static bool                     replace_at_begin(std::string& str, const std::string& from, const std::string& to);
    MVCOMMON_API static std::string              float_to_string(float value, int digitsAfterComma = 2);
    MVCOMMON_API static bool                     equals(const char* str1, const char* str2, bool caseSensitive);
    MVCOMMON_API static std::vector<std::string> ReadLine(std::string& str, char delim = ' ', bool trimStartEnd = true, bool removeAllSpaces = false);
    MVCOMMON_API static std::vector<int>         getInts(const char* commaSeparatedInts, const char delim = ',');

  protected:
    MVCOMMON_API static std::vector<std::string>& split(const std::string& s, char delim, std::vector<std::string>& elems);
    MVCOMMON_API static std::vector<std::string>& split(const char* s, char delim, std::vector<std::string>& elems);
  };
}
