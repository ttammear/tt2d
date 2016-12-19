#include "ttmath.h"

Vec2::Vec2(r32 x, r32 y)
{
    this->x = x;
    this->y = y;
}

Vec2 Vec2::Zero()
{
    Vec2 ret;
    ret.x = 0.0f;
    ret.y = 0.0f;
    return ret;
}

Mat4 ortho(r32 left, r32 right, r32 bottom, r32 top, r32 near, r32 far)
{
    Mat4 ret;

    ret.m11 = 2.f/(right-left);
    ret.m12 = 0.f;
    ret.m13 = 0.f;
    ret.m14 = -(right+left)/(right-left);
    ret.m21 = 0.f;
    ret.m22 = 2.f/(top-bottom);
    ret.m23 = 0.f;
    ret.m24 = -(top+bottom)/(top-bottom);
    ret.m31 = 0.f;
    ret.m32 = 0.f;
    ret.m33 = -2.f/(far-near);
    ret.m34 = 0.0f;
    ret.m41 = 0.f;
    ret.m42 = 0.f;
    ret.m43 = 0.f;
    ret.m44 = 1.0f;

    return ret;
}
