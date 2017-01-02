#ifndef SHARED_H
#define SHARED_H

#define ENGINEBUILD_SLOW 1

#ifdef __unix__
#define TT2D_PLATFORM_LINUX
#elif defined(_WIN32) || defined(WIN32)
#define TT2D_PLATFORM_WINDOWS
#endif

#include <stdint.h>
#include <stdio.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef i32 b32;

typedef float r32;
typedef double r64;

#define COUNT_OF(x) ((sizeof(x)/sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x])))))

// Assert
#ifdef ENGINEBUILD_SLOW // debug assert

#ifdef TT2D_PLATFORM_LINUX // linux
#define assert(expr) {if(!(expr)) { printf("Assertion failed at %s:%d in function %s\n",__FILE__,__LINE__,__func__); __builtin_trap(); }}
#else // windows
#define assert(expr) { if(!(expr)) { int *ptr=0; *ptr=1; }}
#endif
#else   // no assert
#define assert(expr)
#endif  // Assert

#ifdef TT2D_PLATFORM_WINDOWS
#define customDebugBreak() DebugBreak();
#define snprintf(a, b, ...) _snprintf(a, b, ##__VA_ARGS__)
#else
#define customDebugBreak() __builtin_trap();
#endif

#endif // SHARED_H
