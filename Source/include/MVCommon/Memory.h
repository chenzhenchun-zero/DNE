#ifndef _MVCOMMON_MEMORY_H_
#define _MVCOMMON_MEMORY_H_

#include <new>

#if !defined(NOEXCEPT)
#if defined(_MSC_VER) && _MSC_VER == 1800
// a bug in VS2013 only -> does not support 'noexcept'
#define NOEXCEPT _NOEXCEPT
#else
#define NOEXCEPT noexcept
#endif
#endif

// Class-specific new and delete operators.
// Their purpose is to make sure that allocations are called using Dll's heap memory.
#define DECLARE_CLASS_SPECIFIC_NEW_DELETE(EXPORT_MACRO)                   \
EXPORT_MACRO static void* operator new(std::size_t sz);                   \
EXPORT_MACRO static void* operator new(std::size_t sz, void* p) NOEXCEPT; \
EXPORT_MACRO static void operator delete(void* ptr, std::size_t sz);      \
EXPORT_MACRO static void operator delete(void* ptr, void*) NOEXCEPT;  

#define IMPLEMENT_CLASS_SPECIFIC_NEW_DELETE(className)                                            \
void* className::operator new(std::size_t sz) { return ::operator new(sz); }                      \
void* className::operator new(std::size_t sz, void* p) NOEXCEPT { return ::operator new(sz, p); } \
void className::operator delete(void* ptr, std::size_t sz) { return ::operator delete(ptr); }     \
void className::operator delete(void* ptr, void*) NOEXCEPT { return ::operator delete(ptr); }

/// \cond
class NonAssignable {
  public:
    NonAssignable(NonAssignable const &) = delete;
    NonAssignable& operator=(NonAssignable const &) = delete;
    // move constructor and assignment operator are implicitly deleted
  protected:
    NonAssignable() = default;
    ~NonAssignable() = default;
};
/// \endcond

#endif

