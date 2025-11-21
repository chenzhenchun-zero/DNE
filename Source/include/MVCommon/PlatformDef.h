#pragma once

#if defined(__APPLE__) && defined(__MACH__)
// Apple MAC and iOS (Darwin)
  #include <TargetConditionals.h>

  #if TARGET_IPHONE_SIMULATOR == 1
    //#define MV_IPHONE_SIMULATOR
  #elif TARGET_OS_IPHONE == 1
    #define MV_IPHONE
  #elif TARGET_OS_MAC == 1
    #define MV_MAC
  #endif

#endif
