#pragma once

#include <cstdint>
#include <cstdlib>

#if defined(_WIN32)
  #ifdef MVX2_EXPORTS
    #define MVX2_API __declspec(dllexport)
  #else
    #define MVX2_API __declspec(dllimport)
  #endif
#else
  #define MVX2_API
#endif

#define NO_EXPORT_API
