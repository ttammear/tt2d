#ifndef SHARED_H
#define SHARED_H

#define ENGINEBUILD_SLOW 1

#include <stdint.h>

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

#ifdef ENGINEBUILD_SLOW
#define assert(expr) {if(!(expr)) { printf("Assertion failed at %s:%d in function %s\n",__FILE__,__LINE__,__func__); __builtin_trap(); }}
#else
#define assert(expr)
#endif

#endif // SHARED_H
