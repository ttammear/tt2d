#ifndef TTMATH_H
#define TTMATH_H

#include "shared.h"

struct Vec2
{
    r32 x;
    r32 y;

    Vec2() = default;
    Vec2(r32 x, r32 y);

    static Vec2 Zero();
};

typedef struct Mat4
{
    union
    {
           /*struct
           {
                  __m128 m1, m2, m3, m4;
           };*/

           struct
           {
                  float m[16];
           };

           struct
           {
                float m11, m21, m31, m41;
                float m12, m22, m32, m42;
                float m13, m23, m33, m43;
                float m14, m24, m34, m44;
                /*
                float m11, m12, m13, m14;
                float m21, m22, m23, m24;
                float m31, m32, m33, m34;
                float m41, m42, m43, m44;*/
           };
    };
} Mat4;

#endif // TTMATH_H
