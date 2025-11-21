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
#include <math.h>

#include <MVCommon/MVCommonAPI.h>

#define ALMOST_ZERO             0.00001f

namespace MVCommon
{
  bool        MVCOMMON_API IsFloatZero(float x, float thresh = ALMOST_ZERO);
  bool        MVCOMMON_API AreFloatsEqual(float x, float y, float thresh = ALMOST_ZERO);
  void        MVCOMMON_API LeakDetectorStart();
  void        MVCOMMON_API LeakDetectorStop();
  
  inline bool ClosedIntervalsOverlap(int32_t start0, int32_t end0, int32_t start1, int32_t end1)
  {
    return (start1 <= end0 && start0 <= end1);
  }

  inline float RoundNearest(float x)
  {
    return floorf(x+0.5f);
  }

  inline uint32_t Wrap(int32_t offset, int32_t size)
  {
    return ((offset % size) + size) % size;
  }

  inline float Wrap(float offset, float size)
  {
    return fmodf(fmodf(offset, size) + size, size);
  }

  inline float Lerp(float v1, float v2, float t)
  {
    return v1 + (v2 - v1) * t;
  }

  template<class T> T Min(const T &a, const T &b)
  {
    return (a < b) ? a : b;
  }

  template<class T> T Max(const T &a, const T &b)
  {
    return (a > b) ? a : b;
  }

  template<class T> T Clamp(const T &min, const T &x, const T &max)
  {
    return (x < min ? min : (x > max ? max : x));
  }

  template<typename T> void SafeDelete(T*& p)
  {
    delete p;
    p = nullptr;
  }

  template<typename T> void SafeDeleteArray(T*& p)
  {
    delete [] p;
    p = nullptr;
  }

  template<typename T> void RemoveFromDeque(std::deque<T> &deque, T item)
  {
    typename std::deque<T>::iterator it = deque.begin();

    while (it != deque.end())
    {
      if (*it == item)
      {
        deque.erase(it);
        return;
      }
      ++it;
    }
  }

  template<typename T> bool IsInDeque(const std::deque<T> &deque, T item)
  {
    typename std::deque<T>::const_iterator it = deque.begin();

    while (it != deque.end())
    {
      if (*it == item)
      {
        return true;
      }
      ++it;
    }

    return false;
  }

}


