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

Vec2 Vec2::operator + (Vec2 const & in)
{
    Vec2 ret;
    ret.x = this->x + in.x;
    ret.y = this->y + in.y;
    return ret;
}

Vec2 Vec2::operator * (Vec2 const & in)
{
    Vec2 ret;
    ret.x = this->x * in.x;
    ret.y = this->y * in.y;
    return ret;
}

IVec2::IVec2(i32 x, i32 y)
{
    this->x = x;
    this->y = y;
}

Mat4 Mat4::operator * (Mat4 const & in)
{
    Mat4 ret;
    ret.m11 = m11 * in.m11 + m12 * in.m21 + m13 * in.m31 + m14 * in.m41;
    ret.m12 = m11 * in.m12 + m12 * in.m22 + m13 * in.m32 + m14 * in.m42;
    ret.m13 = m11 * in.m13 + m12 * in.m23 + m13 * in.m33 + m14 * in.m43;
    ret.m14 = m11 * in.m14 + m12 * in.m24 + m13 * in.m34 + m14 * in.m44;
    ret.m21 = m21 * in.m11 + m22 * in.m21 + m23 * in.m31 + m24 * in.m41;
    ret.m22 = m21 * in.m12 + m22 * in.m22 + m23 * in.m32 + m24 * in.m42;
    ret.m23 = m21 * in.m13 + m22 * in.m23 + m23 * in.m33 + m24 * in.m43;
    ret.m24 = m21 * in.m14 + m22 * in.m24 + m23 * in.m34 + m24 * in.m44;
    ret.m31 = m31 * in.m11 + m32 * in.m21 + m33 * in.m31 + m34 * in.m41;
    ret.m32 = m31 * in.m12 + m32 * in.m22 + m33 * in.m32 + m34 * in.m42;
    ret.m33 = m31 * in.m13 + m32 * in.m23 + m33 * in.m33 + m34 * in.m43;
    ret.m34 = m31 * in.m14 + m32 * in.m24 + m33 * in.m34 + m34 * in.m44;
    ret.m41 = m41 * in.m11 + m42 * in.m21 + m43 * in.m31 + m44 * in.m41;
    ret.m42 = m41 * in.m12 + m42 * in.m22 + m43 * in.m32 + m44 * in.m42;
    ret.m43 = m41 * in.m13 + m42 * in.m23 + m43 * in.m33 + m44 * in.m43;
    ret.m44 = m41 * in.m14 + m42 * in.m24 + m43 * in.m34 + m44 * in.m44;
    return ret;
}

Mat4 ortho(r32 left, r32 right, r32 bottom, r32 top)
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
    ret.m33 = 0.0f;
    ret.m34 = 0.0f;
    ret.m41 = 0.f;
    ret.m42 = 0.f;
    ret.m43 = 0.f;
    ret.m44 = 1.0f;

    return ret;
}

Mat4 scale(Vec2 scale)
{
    Mat4 ret;
    ret.m[0] = scale.x;
    ret.m[1] = 0.0f;
    ret.m[2] = 0.0f;
    ret.m[3] = 0.0f;

    ret.m[4] = 0.0f;
    ret.m[5] = scale.y;
    ret.m[6] = 0.0f;
    ret.m[7] = 0.0f;

    ret.m[8] = 0.0f;
    ret.m[9] = 0.0f;
    ret.m[10] = 0.0f;
    ret.m[11] = 0.0f;

    ret.m[12] = 0.0f;
    ret.m[13] = 0.0f;
    ret.m[14] = 0.0f;
    ret.m[15] = 1.0f;
    return ret;
}

Mat4 translate(Vec2 pos)
{
    Mat4 ret;
    ret.m[0] = 1.0f;
    ret.m[1] = 0.0f;
    ret.m[2] = 0.0f;
    ret.m[3] = 0.0f;

    ret.m[4] = 0.0f;
    ret.m[5] = 1.0f;
    ret.m[6] = 0.0f;
    ret.m[7] = 0.0f;

    ret.m[8] = 0.0f;
    ret.m[9] = 0.0f;
    ret.m[10] = 1.0f;
    ret.m[11] = 0.0f;

    ret.m[12] = pos.x;
    ret.m[13] = pos.y;
    ret.m[14] = 0.0f;
    ret.m[15] = 1.0f;
    return ret;
}

Mat4 rotate(r32 rot)
{
    Mat4 ret;
    ret.m[0] = cosf(rot);
    ret.m[1] = sinf(rot);
    ret.m[2] = 0.0f;
    ret.m[3] = 0.0f;

    ret.m[4] = -sinf(rot);
    ret.m[5] = cosf(rot);
    ret.m[6] = 0.0f;
    ret.m[7] = 0.0f;

    ret.m[8] = 0.0f;
    ret.m[9] = 0.0f;
    ret.m[10] = 1.0f;
    ret.m[11] = 0.0f;

    ret.m[12] = 0.0f;
    ret.m[13] = 0.0f;
    ret.m[14] = 0.0f;
    ret.m[15] = 1.0f;
    return ret;
}
