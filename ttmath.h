#ifndef TTMATH_H
#define TTMATH_H

#include "shared.h"
#include <math.h>

struct Vec2
{
    r32 x;
    r32 y;

    Vec2() = default;
    Vec2(r32 x, r32 y);

    static Vec2 Zero();
    Vec2 operator + (Vec2 const & in);
    Vec2 operator * (Vec2 const & in);
};

struct IVec2
{
    i32 x;
    i32 y;

    IVec2() = default;
    IVec2(i32 x, i32 y);
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
           };
    };
    Mat4 operator * (Mat4 const & in);
} Mat4;

Mat4 scale(Vec2 scale);
Mat4 translate(Vec2 scale);
Mat4 rotate(r32 rot);
Mat4 ortho(r32 left, r32 right, r32 bottom, r32 top);

#endif // TTMATH_H
