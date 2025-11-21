#pragma once

#include <cstdint>
#include <cstdlib>

#if defined(WINDOWS)
  #ifdef MVCOMMON_API_EXPORTS
    #define MVCOMMON_API __declspec(dllexport)
  #else
    #define MVCOMMON_API __declspec(dllimport)
  #endif
#else
  #define MVCOMMON_API
#endif