#pragma once

#include <cstdint>
#include <cstdlib>

#if defined(_WIN32)
  #ifdef MVX2BASICIO_EXPORTS
    #define MVX2BASICIO_API __declspec(dllexport)
  #else
    #define MVX2BASICIO_API __declspec(dllimport)
  #endif
#else
  #define MVX2BASICIO_API
#endif
