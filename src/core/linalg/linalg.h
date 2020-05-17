#ifndef CXXRAY_LINALG_H
#define CXXRAY_LINALG_H

#include "vec2.h"
#include "vec3.h"
#include "vec4.h"

#include "mat2.h"
#include "mat3.h"
#include "mat4.h"

#include "basis.h"

#include <cmath>
#include <iostream>

namespace CxxRay {

// vectors {{{
inline Vec2 operator+(Vec2 const & a, Vec2 const & b) { return { a.x + b.x, a.y + b.y }; }
inline Vec3 operator+(Vec3 const & a, Vec3 const & b) { return { a.x + b.x, a.y + b.y, a.z + b.z }; }
inline Vec4 operator+(Vec4 const & a, Vec4 const & b) { return { a.x + b.x, a.y + b.y, a.z + b.z, 1.0 }; }
inline Vec2 operator-(Vec2 const & a, Vec2 const & b) { return { a.x - b.x, a.y - b.y }; }
inline Vec3 operator-(Vec3 const & a, Vec3 const & b) { return { a.x - b.x, a.y - b.y, a.z - b.z }; }
inline Vec4 operator-(Vec4 const & a, Vec4 const & b) { return { a.x - b.x, a.y - b.y, a.z - b.z, 1.0 }; }

inline Vec2 operator*(Vec2 const & a, Real const val) { return { a.x * val, a.y * val }; }
inline Vec3 operator*(Vec3 const & a, Real const val) { return { a.x * val, a.y * val, a.z * val }; }
inline Vec4 operator*(Vec4 const & a, Real const val) { return { a.x * val, a.y * val, a.z * val, 1.0 }; }
inline Vec2 operator*(Real const val, Vec2 const & a) { return { a.x * val, a.y * val }; }
inline Vec3 operator*(Real const val, Vec3 const & a) { return { a.x * val, a.y * val, a.z * val }; }
inline Vec4 operator*(Real const val, Vec4 const & a) { return { a.x * val, a.y * val, a.z * val, 1.0 }; }

inline Vec2 operator/(Vec2 const & a, Real const val) { return { a.x / val, a.y / val }; }
inline Vec3 operator/(Vec3 const & a, Real const val) { return { a.x / val, a.y / val, a.z / val }; }
inline Vec4 operator/(Vec4 const & a, Real const val) { return { a.x / val, a.y / val, a.z / val, 1.0 }; }

inline Real dot(Vec2 const & a, Vec2 const & b) { return a.x * b.x + a.y * b.y; }
inline Real dot(Vec3 const & a, Vec3 const & b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
inline Real dot3(Vec4 const & a, Vec4 const & b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
inline Real dot(Vec4 const & a, Vec4 const & b) { return a.x * b.x + a.y * b.y + a.z * b.z + a.h * b.h; }

inline Real length(Vec2 const & a) { return std::sqrt(a.x*a.x + a.y*a.y); }
inline Real length(Vec3 const & a) { return std::sqrt(a.x*a.x + a.y*a.y + a.z*a.z); }
inline Real length3(Vec4 const & a) { return std::sqrt(a.x*a.x + a.y*a.y + a.z*a.z); }
inline Real length(Vec4 const & a) { return std::sqrt(a.x*a.x + a.y*a.y + a.z*a.z + a.h*a.h); }

inline Vec2 unit(Vec2 const & a) { return a / length(a); }
inline Vec3 unit(Vec3 const & a) { return a / length(a); }
inline Vec4 unit3(Vec4 const & a)
{
    auto const b = a / length3(a);

    // preserve the homogenous co-ordinate
    return { b.x, b.y, b.z, a.h };
}

inline Vec4 unit(Vec4 const & a)
{
    auto const b = a / length(a);
    return { b.x, b.y, b.z, b.h };
}

inline Real lenprod(Vec2 const & a, Vec2 const & b) { return length(a) * length(b); }
inline Real lenprod(Vec3 const & a, Vec3 const & b) { return length(a) * length(b); }
inline Real lenprod(Vec4 const & a, Vec4 const & b) { return length(a) * length(b); }

inline Real angle(Vec2 const & a, Vec2 const & b) { return std::acos(dot(a, b) / lenprod(a, b)); }
inline Real angle(Vec3 const & a, Vec3 const & b) { return std::acos(dot(a, b) / lenprod(a, b)); }

inline Vec3 cross(Vec3 const & a, Vec3 const & b) { return { a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x }; }
inline Vec4 cross3(Vec4 const & a, Vec4 const & b) { return { a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x, 1.0 }; }

inline Real area(Vec3 const & a, Vec3 const & b) { return length(cross(a, b)); }
inline Real area3(Vec4 const & a, Vec4 const & b) { return length3(cross3(a, b)); }

inline Vec3 normal(Vec3 const & a, Vec3 const & b) { return unit(cross(a, b)); }
inline Vec4 normal3(Vec4 const & a, Vec4 const & b) { return unit3(cross3(a, b)); }

inline Vec3 triangle_normal(Vec3 const & a, Vec3 const & b, Vec3 const & c) { return unit(cross(b-a, c-a)); }
inline Vec4 triangle_normal3(Vec4 const & a, Vec4 const & b, Vec4 const & c) { return unit3(cross3(b-a, c-a)); }
inline Vec3 sphere_normal(Vec3 const & p, Vec3 const & c, Real r) { return unit(Vec3{ (p.x-c.x)/r, (p.y-c.y)/r, (p.z-c.z)/r }); }
inline Vec4 sphere_normal3(Vec4 const & p, Vec4 const & c, Real r) { return unit3(Vec4{ (p.x-c.x)/r, (p.y-c.y)/r, (p.z-c.z)/r, 1.0 }); }
// vectors }}}

// matrix arithmetic {{{
inline Mat2 operator+(Mat2 const & m, Mat2 const & q) {
    return {
        m.ax + q.ax, m.ay + q.ay,
        m.bx + q.bx, m.by + q.by
    };
}

inline Mat3 operator+(Mat3 const & m, Mat3 const & q) {
    return {
        m.ax + q.ax, m.ay + q.ay, m.az + q.az,
        m.bx + q.bx, m.by + q.by, m.bz + q.bz,
        m.cx + q.cx, m.cy + q.cy, m.cz + q.cz
    };
}

inline Mat4 operator+(Mat4 const & m, Mat4 const & q) {
    return {
        m.ax + q.ax, m.ay + q.ay, m.az + q.az, m.ah + q.ah,
        m.bx + q.bx, m.by + q.by, m.bz + q.bz, m.bh + q.bh,
        m.cx + q.cx, m.cy + q.cy, m.cz + q.cz, m.ch + q.ch,
        m.dx + q.dx, m.dy + q.dy, m.dz + q.dz, m.dh + q.dh
    };
}

inline Mat2 operator-(Mat2 const & m, Mat2 const & q) {
    return {
        m.ax - q.ax, m.ay - q.ay,
        m.bx - q.bx, m.by - q.by
    };
}

inline Mat3 operator-(Mat3 const & m, Mat3 const & q) {
    return {
        m.ax - q.ax, m.ay - q.ay, m.az - q.az,
        m.bx - q.bx, m.by - q.by, m.bz - q.bz,
        m.cx - q.cx, m.cy - q.cy, m.cz - q.cz
    };
}

inline Mat4 operator-(Mat4 const & m, Mat4 const & q) {
    return {
        m.ax - q.ax, m.ay - q.ay, m.az - q.az, m.ah - q.ah,
        m.bx - q.bx, m.by - q.by, m.bz - q.bz, m.bh - q.bh,
        m.cx - q.cx, m.cy - q.cy, m.cz - q.cz, m.ch - q.ch,
        m.dx - q.dx, m.dy - q.dy, m.dz - q.dz, m.dh - q.dh
    };
}

inline Mat2 operator*(Real const val, Mat2 const & m) {
    return {
        m.ax * val, m.ay * val,
        m.bx * val, m.by * val
    };
}

inline Mat2 operator*(Mat2 const & m, Real const val) {
    return {
        m.ax * val, m.ay * val,
        m.bx * val, m.by * val
    };
}

inline Mat2 operator/(Mat2 const & m, Real const val) {
    return {
        m.ax / val, m.ay / val,
        m.bx / val, m.by / val
    };
}

inline Vec2 operator*(Mat2 const & m, Vec2 const & vec) {
    return {
        dot(m.a(), vec),
        dot(m.b(), vec)
    };
}

inline Mat2 operator*(Mat2 const & m, Mat2 const & q) {
    // rows by columns
    Vec2 const row1 = m.a();
    Vec2 const row2 = m.b();

    Vec2 const col1 = q.x();
    Vec2 const col2 = q.y();

    return {
        dot(row1, col1), dot(row1, col2),
        dot(row2, col1), dot(row2, col2)
    };
}

inline Mat3 operator*(Real const val, Mat3 const & m) {
    return {
        m.ax * val, m.ay * val, m.az * val,
        m.bx * val, m.by * val, m.bz * val,
        m.cx * val, m.cy * val, m.cz * val
    };
}

inline Mat3 operator*(Mat3 const & m, Real const val) {
    return {
        m.ax * val, m.ay * val, m.az * val,
        m.bx * val, m.by * val, m.bz * val,
        m.cx * val, m.cy * val, m.cz * val
    };
}

inline Mat3 operator/(Mat3 const & m, Real const val) {
    return {
        m.ax / val, m.ay / val, m.az / val,
        m.bx / val, m.by / val, m.bz / val,
        m.cx / val, m.cy / val, m.cz / val
    };
}

inline Vec3 operator*(Mat3 const & m, Vec3 const & vec) {
    return {
        dot(m.a(), vec),
        dot(m.b(), vec),
        dot(m.c(), vec)
    };
}

inline Mat3 operator*(Mat3 const & m, Mat3 const & q) {
    // rows by columns
    auto const row1 = m.a();
    auto const row2 = m.b();
    auto const row3 = m.c();

    auto const col1 = q.x();
    auto const col2 = q.y();
    auto const col3 = q.z();

    return {
        dot(row1, col1), dot(row1, col2), dot(row1, col3),
        dot(row2, col1), dot(row2, col2), dot(row2, col3),
        dot(row3, col1), dot(row3, col2), dot(row3, col3)
    };
}

inline Mat4 operator*(Real const val, Mat4 const & m) {
    return {
        m.ax * val, m.ay * val, m.az * val, m.ah * val,
        m.bx * val, m.by * val, m.bz * val, m.bh * val,
        m.cx * val, m.cy * val, m.cz * val, m.ch * val,
        m.dx * val, m.dy * val, m.dz * val, m.dh * val
    };
}

inline Mat4 operator/(Mat4 const & m, Real const val) {
    return {
        m.ax / val, m.ay / val, m.az / val, m.ah / val,
        m.bx / val, m.by / val, m.bz / val, m.bh / val,
        m.cx / val, m.cy / val, m.cz / val, m.ch / val,
        m.dx / val, m.dy / val, m.dz / val, m.dh / val
    };
}

inline Mat4 operator*(Mat4 const & m, Real const val) {
    return {
        m.ax * val, m.ay * val, m.az * val, m.ah * val,
        m.bx * val, m.by * val, m.bz * val, m.bh * val,
        m.cx * val, m.cy * val, m.cz * val, m.ch * val,
        m.dx * val, m.dy * val, m.dz * val, m.dh * val
    };
}

inline Vec4 operator*(Mat4 const & m, Vec3 const & v) {
    auto const vec = Vec4{v.x, v.y, v.z, 1.0};

    return {
        dot(m.a(), vec),
        dot(m.b(), vec),
        dot(m.c(), vec),
        dot(m.d(), vec)
    };
}

inline Vec4 operator*(Mat4 const & m, Vec4 const & vec) {
    return {
        dot(m.a(), vec),
        dot(m.b(), vec),
        dot(m.c(), vec),
        dot(m.d(), vec)
    };
}

inline Mat4 operator*(Mat4 const & m, Mat4 const & q) {
    // rows by columns
    Vec4 const row1 = m.a();
    Vec4 const row2 = m.b();
    Vec4 const row3 = m.c();
    Vec4 const row4 = m.d();

    auto const col1 = q.x();
    auto const col2 = q.y();
    auto const col3 = q.z();
    auto const col4 = q.h();

    return {
        dot(row1, col1), dot(row1, col2), dot(row1, col3), dot(row1, col4),
        dot(row2, col1), dot(row2, col2), dot(row2, col3), dot(row2, col4),
        dot(row3, col1), dot(row3, col2), dot(row3, col3), dot(row3, col4),
        dot(row4, col1), dot(row4, col2), dot(row4, col3), dot(row4, col4)
    };
}
// matrix arithmetic }}}

// matrix operations {{{
inline Mat2 tpose(Mat2 const & m) {
    return {
        m.ax, m.bx,
        m.ay, m.by
    };
}

inline Mat3 tpose(Mat3 const & m) {
    return {
        m.ax, m.bx, m.cx,
        m.ay, m.by, m.cy,
        m.az, m.bz, m.cz,
    };
}

inline Mat4 tpose(Mat4 const & m) {
    return {
        m.ax, m.bx, m.cx, m.dx,
        m.ay, m.by, m.cy, m.dy,
        m.az, m.bz, m.cz, m.dz,
        m.ah, m.bh, m.ch, m.dh
    };
}

inline Real det(Mat2 const & m) {
    return m.ax*m.by - m.ay*m.bx;
}

inline Real det(Mat3 const & m) {
    return m.ax*m.by*m.cz + m.ay*m.bz*m.cx + m.az*m.bx*m.cy -
        m.az*m.by*m.cx - m.ay*m.bx*m.cz - m.ax*m.bz*m.cy;
}

inline Real det(Mat4 const & m) {
    auto const a0m = Mat3{
        m.by, m.bz, m.bh,
        m.cy, m.cz, m.ch,
        m.dy, m.dz, m.dh
    };

    auto const a1m = Mat3{
        m.bx, m.bz, m.bh,
        m.cx, m.cz, m.ch,
        m.dx, m.dz, m.dh
    };

    auto const a2m = Mat3{
        m.bx, m.by, m.bh,
        m.cx, m.cy, m.ch,
        m.dx, m.dy, m.dh
    };

    auto const a3m = Mat3{
        m.bx, m.by, m.bz,
        m.cx, m.cy, m.cz,
        m.dx, m.dy, m.dz
    };

    return m.ax*det(a0m) - m.ay*det(a1m) + m.az*det(a2m) - m.ah*det(a3m);
}

inline Mat3 cofac(Mat3 const & m) {
    auto const fac00 = Mat2{
        m.by, m.bz,
        m.cy, m.cz
    };

    auto const fac01 = Mat2{
        m.bx, m.bz,
        m.cx, m.cz
    };

    auto const fac02 = Mat2{
        m.bx, m.by,
        m.cx, m.cy
    };

    auto const fac10 = Mat2{
        m.ay, m.az,
        m.cy, m.cz
    };

    auto const fac11 = Mat2{
        m.ax, m.az,
        m.cx, m.cz
    };

    auto const fac12 = Mat2{
        m.ax, m.ay,
        m.cx, m.cy
    };

    auto const fac20 = Mat2{
        m.ay, m.az,
        m.by, m.bz
    };

    auto const fac21 = Mat2{
        m.ax, m.az,
        m.bx, m.bz
    };

    auto const fac22 = Mat2{
        m.ax, m.ay,
        m.bx, m.by
    };

    return {
           det(fac00), -1*det(fac01),    det(fac02),
        -1*det(fac10),    det(fac11), -1*det(fac12),
           det(fac20), -1*det(fac21),    det(fac22)
    };
}

inline Mat4 cofac(Mat4 const & m) {
    // row 1
    auto const fac00 = Mat3{
        m.by, m.bz, m.bh,
        m.cy, m.cz, m.ch,
        m.dy, m.dz, m.dh
    };

    auto const fac01 = Mat3{
        m.bx, m.bz, m.bh,
        m.cx, m.cz, m.ch,
        m.dx, m.dz, m.dh
    };

    auto const fac02 = Mat3{
        m.bx, m.by, m.bh,
        m.cx, m.cy, m.ch,
        m.dx, m.dy, m.dh
    };

    auto const fac03 = Mat3{
        m.bx, m.by, m.bz,
        m.cx, m.cy, m.cz,
        m.dx, m.dy, m.dz
    };

    // row 2
    auto const fac10 = Mat3{
        m.ay, m.az, m.ah,
        m.cy, m.cz, m.ch,
        m.dy, m.dz, m.dh
    };

    auto const fac11 = Mat3{
        m.ax, m.az, m.ah,
        m.cx, m.cz, m.ch,
        m.dx, m.dz, m.dh
    };

    auto const fac12 = Mat3{
        m.ax, m.ay, m.ah,
        m.cx, m.cy, m.ch,
        m.dx, m.dy, m.dh
    };

    auto const fac13 = Mat3{
        m.ax, m.ay, m.az,
        m.cx, m.cy, m.cz,
        m.dx, m.dy, m.dz
    };

    // row 3
    auto const fac20 = Mat3{
        m.ay, m.az, m.ah,
        m.by, m.bz, m.bh,
        m.dy, m.dz, m.dh
    };

    auto const fac21 = Mat3{
        m.ax, m.az, m.ah,
        m.bx, m.bz, m.bh,
        m.dx, m.dz, m.dh
    };

    auto const fac22 = Mat3{
        m.ax, m.ay, m.ah,
        m.bx, m.by, m.bh,
        m.dx, m.dy, m.dh
    };

    auto const fac23 = Mat3{
        m.ax, m.ay, m.az,
        m.bx, m.by, m.bz,
        m.dx, m.dy, m.dz
    };

    // row 4
    auto const fac30 = Mat3{
        m.ay, m.az, m.ah,
        m.by, m.bz, m.bh,
        m.cy, m.cz, m.ch
    };

    auto const fac31 = Mat3{
        m.ax, m.az, m.ah,
        m.bx, m.bz, m.bh,
        m.cx, m.cz, m.ch
    };

    auto const fac32 = Mat3{
        m.ax, m.ay, m.ah,
        m.bx, m.by, m.bh,
        m.cx, m.cy, m.ch
    };

    auto const fac33 = Mat3{
        m.ax, m.ay, m.az,
        m.bx, m.by, m.bz,
        m.cx, m.cy, m.cz
    };

    return {
           det(fac00), -1*det(fac01),    det(fac02), -1*det(fac03),
        -1*det(fac10),    det(fac11), -1*det(fac12),    det(fac13),
           det(fac20), -1*det(fac21),    det(fac22), -1*det(fac23),
        -1*det(fac30),    det(fac31), -1*det(fac32),    det(fac33)
    };
}

inline Mat3 adjoint(Mat3 const & m) {
    return tpose(cofac(m));
}

inline Mat3 inverse(Mat3 const & m) {
    return adjoint(m) / det(m);
}

inline Mat4 adjoint(Mat4 const & m) {
    return tpose(cofac(m));
}

inline Mat4 inverse(Mat4 const & m) {
    return adjoint(m) / det(m);
}
// matrix operations }}}

// affine transforms {{{
inline Mat2 mat2_scale(Real const val) {
    return {
        val, 0.0,
        0.0, val
    };
}

inline Mat3 mat2h_scale(Real const val) {
    return {
        val, 0.0, 0.0,
        0.0, val, 0.0,
        0.0, 0.0, 1.0
    };
}

inline Mat2 mat2_scale(Real const x, Real const y) {
    return {
        x, 0.0,
        0.0, y
    };
}

inline Mat3 mat2h_scale(Real const x, Real const y) {
    return {
        x, 0.0, 0.0,
        0.0, y, 0.0,
        0.0, 0.0, 1.0
    };
}

inline Mat3 mat3_scale(Real const val) {
    return {
        val, 0.0, 0.0,
        0.0, val, 0.0,
        0.0, 0.0, val
    };
}

inline Mat4 mat3h_scale(Real const val) {
    return {
        val, 0.0, 0.0, 0.0,
        0.0, val, 0.0, 0.0,
        0.0, 0.0, val, 0.0,
        0.0, 0.0, 0.0, 1.0
    };
}

inline Mat3 mat3_scale(Real const x, Real const y, Real const z) {
    return {
        x, 0.0, 0.0,
        0.0, y, 0.0,
        0.0, 0.0, z
    };
}

inline Mat4 mat3h_scale(Real const x, Real const y, Real const z) {
    return {
        x,   0.0, 0.0, 0.0,
        0.0, y,   0.0, 0.0,
        0.0, 0.0, z,   0.0,
        0.0, 0.0, 0.0, 1.0
    };
}

inline Mat2 mat2_rot(Real const a) {
    using std::sin;
    using std::cos;

    return {
        cos(a), -sin(a),
        sin(a),  cos(a)
    };
}

inline Mat3 mat3_rot_z(Real const a) {
    using std::sin;
    using std::cos;

    return {
         cos(a), -sin(a), 0.0,
         sin(a),  cos(a), 0.0,
         0.0,     0.0,    1.0
    };
}

inline Mat3 mat3_rot_x(Real const a) {
    using std::sin;
    using std::cos;

    return {
         1.0,   0.0,     0.0   ,
         0.0,   cos(a), -sin(a),
         0.0,   sin(a),  cos(a)
    };
}

inline Mat3 mat3_rot_y(Real const a) {
    using std::sin;
    using std::cos;

    return {
         cos(a),   0.0,   sin(a),
         0.0,      1.0,   0.0   ,
         -sin(a),  0.0,   cos(a)
    };
}
// affine transforms }}}

// viewing transforms {{{
inline Mat3 win_tform(
    Real const xl, Real const yl,
    Real const xh, Real const yh,
    Real const xl1, Real const yl1,
    Real const xh1, Real const yh1)
{
    auto const xs = (xh1 - xl1) / xh - xl;
    auto const ys = (yh1 - yl1) / yh - yl;

    auto const xt = (xl1*xh - xh1*xl) / (xh - xl);
    auto const yt = (yl1*yh - yh1*yl) / (yh - yl);

    return {
        xs,  0.0, xt,
        0.0, ys,  yt,
        0.0, 0.0, 1.0
    };
}

inline Mat3 win_tform(
    Vec2 const & l, Vec2 const & h,
    Vec2 const & l1, Vec2 const & h1)
{
    return win_tform(
        l.x,  l.y,
        h.x,  h.y,
        l1.x, l1.y,
        h1.x, h1.y);
}

inline Mat4 win_tform(
    Real const xl,  Real const yl,  Real const zl,
    Real const xh,  Real const yh,  Real const zh,
    Real const xl1, Real const yl1, Real const zl1,
    Real const xh1, Real const yh1, Real const zh1)
{
    auto const xs = (xh1 - xl1) / xh - xl;
    auto const ys = (yh1 - yl1) / yh - yl;
    auto const zs = (zh1 - zl1) / zh - zl;

    auto const xt = (xl1*xh - xh1*xl) / (xh - xl);
    auto const yt = (yl1*yh - yh1*yl) / (yh - yl);
    auto const zt = (zl1*zh - zh1*zl) / (zh - zl);

    return {
        xs,  0.0, 0.0, xt,
        0.0, ys,  0.0, yt,
        0.0, 0.0, zs,  zt,
        0.0, 0.0, 0.0, 1.0
    };
}

inline Mat4 win_tform(
    Vec3 const & l, Vec3 const & h,
    Vec3 const & l1, Vec3 const & h1)
{
    return win_tform(
        l.x,  l.y,  l.z,
        h.x,  h.y,  h.z,
        l1.x, l1.y, l1.z,
        h1.x, h1.y, h1.z);
}

inline Mat3 frame_to_canon(
    Vec2 const & e,
    Vec2 const & u,
    Vec2 const & v)
{
    return (
        Mat3{
            1.0, 0.0, e.x,
            0.0, 1.0, e.y,
            0.0, 0.0, 1.0
        }

        *

        Mat3{
            u.x, v.x, 0.0,
            u.y, v.y, 0.0,
            0.0,  0.0,  1.0
        }
    );
}

inline Mat3 canon_to_frame(
    Vec2 const & e,
    Vec2 const & u,
    Vec2 const & v)
{
    return (
        Mat3{
            u.x, v.x, 0.0,
            u.y, v.y, 0.0,
            0.0,  0.0,  1.0
        }

        *

        Mat3{
            1.0, 0.0, -e.x,
            0.0, 1.0, -e.y,
            0.0, 0.0,  1.0
        }
    );
}

inline Mat4 frame_to_canon(
    Vec3 const & e,
    Vec3 const & w,
    Vec3 const & u,
    Vec3 const & v)
{
    return (
        Mat4{
            1.0, 0.0, 0.0, e.x,
            0.0, 1.0, 0.0, e.y,
            0.0, 0.0, 1.0, e.z,
            0.0, 0.0, 0.0, 1.0
        }

        *

        Mat4{
            u.x, v.x, w.x, 0.0,
            u.y, v.y, w.y, 0.0,
            u.z, v.z, w.z, 0.0,
            0.0, 0.0, 0.0, 1.0
        }
    );
}

inline Mat4 canon_to_frame(
    Vec3 const & e,
    Vec3 const & w,
    Vec3 const & u,
    Vec3 const & v)
{
    auto const lhs = Mat4{
        u.x, u.y, u.z, 0.0,
        v.x, v.y, v.z, 0.0,
        w.x, w.y, w.z, 0.0,
        0.0, 0.0, 0.0, 1.0
    };

    auto const rhs = Mat4{
        1.0, 0.0, 0.0, -1.0 * e.x,
        0.0, 1.0, 0.0, -1.0 * e.y,
        0.0, 0.0, 1.0, -1.0 * e.z,
        0.0, 0.0, 0.0, 1.0
    };

    return lhs * rhs;
}

inline Mat4 frame_to_canon(
    Vec4 const & e,
    Vec4 const & w,
    Vec4 const & u,
    Vec4 const & v)
{
    auto const lhs = Mat4{
        1.0, 0.0, 0.0, e.x,
        0.0, 1.0, 0.0, e.y,
        0.0, 0.0, 1.0, e.z,
        0.0, 0.0, 0.0, 1.0
    };

    auto const rhs = Mat4{
        u.x, v.x, w.x, 0.0,
        u.y, v.y, w.y, 0.0,
        u.z, v.z, w.z, 0.0,
        0.0, 0.0, 0.0, 1.0
    };

    return lhs * rhs;
}

inline Mat4 canon_to_frame(
    Vec4 const & e,
    Vec4 const & w,
    Vec4 const & u,
    Vec4 const & v)
{
    auto const lhs = Mat4{
        u.x, u.y, u.z, 0.0,
        v.x, v.y, v.z, 0.0,
        w.x, w.y, w.z, 0.0,
        0.0, 0.0, 0.0, 1.0
    };

    auto const rhs = Mat4{
        1.0, 0.0, 0.0, -1.0 * e.x,
        0.0, 1.0, 0.0, -1.0 * e.y,
        0.0, 0.0, 1.0, -1.0 * e.z,
        0.0, 0.0, 0.0, 1.0
    };

    return lhs * rhs;
}

inline Mat4 frame_to_canon(
    Basis const & B)
{
    return frame_to_canon(B.e, B.w, B.u, B.v);
}

inline Mat4 canon_to_frame(
    Basis const & B)
{
    return canon_to_frame(B.e, B.w, B.u, B.v);
}

inline Mat4 tform_vp(Real const nx, Real const ny)
{
    return {
        nx/2, 0.0,  0.0,  (nx-1)/2,
        0.0,  ny/2, 0.0,  (ny-1)/2,
        0.0,  0.0,  1.0,  0.0,
        0.0,  0.0,  0.0,  1.0
    };
}

inline Mat4 tform_orth(
    Real const r, Real const l,
    Real const t, Real const b,
    Real const n, Real const f)
{
    return {
         2/(r-l), 0.0,     0.0,     -1.0 * ((r+l)/(r-l)),
         0.0,     2/(t-b), 0.0,     -1.0 * ((t+b)/(t-b)),
         0.0,     0.0,     2/(n-f), -1.0 * ((n+f)/(n-f)),
         0.0,     0.0,     0.0,      1.0
    };
}

inline Mat4 tform_perspec(Real const n, Real const f)
{
    return {
         n,    0.0,  0.0,  0.0   ,
         0.0,  n,    0.0,  0.0   ,
         0.0,  0.0,  n+f,  -1.0 * (f*n),
         0.0,  0.0,  1.0,  0.0
    };
}

inline Mat4 tform_perspec_inverse(Real const n, Real const f)
{
    return {
         f,    0.0,  0.0,  0.0,
         0.0,  f,    0.0,  0.0,
         0.0,  0.0,  0.0,  f*n,
         0.0,  0.0,  -1.0, n+f
    };
}

inline Mat4 tform_per(
    Real const r, Real const l,
    Real const t, Real const b,
    Real const n, Real const f)
{
    return {
         (2*n)/(r-l), 0.0,         (l+r)/(l-r), 0.0,
         0.0,         (2*n)/(t-b), (b+t)/(b-t), 0.0,
         0.0,         0.0,         (f+n)/(n-f), (2*f*n)/(f-n),
         0.0,         0.0,         1.0,         0.0
    };
}

inline Mat4 tform_project(
    Mat4 const & orth,
    Mat4 const & per)
{
    return orth * per;
}

inline Mat4 tform_camera(
    Vec3 const & e,
    Vec3 const & w,
    Vec3 const & u,
    Vec3 const & v)
{
    return canon_to_frame(e, w, u, v);
}

inline Mat4 tform_camera(
    Vec4 const & e,
    Vec4 const & w,
    Vec4 const & u,
    Vec4 const & v)
{
    return canon_to_frame(e, w, u, v);
}

inline Mat4 tform_perspective_matrix(
    Real const nx, Real const ny,
    Real const r, Real const l,
    Real const t, Real const b,
    Real const n, Real const f,
    Vec3 const & e, Vec3 const & w, Vec3 const & u, Vec3 const & v)
{
    //return (
    //      tform_vp(nx, ny)
    //    * tform_orth(r, l, t, b, n, f)
    //    * tform_perspec(n, f)
    //    * tform_camera(e, w, u, v)
    //);

    return (
          tform_vp(nx, ny)
        * tform_per(r, l, t, b, n, f)
        * tform_camera(e, w, u, v)
    );
}

inline Mat4 tform_raster_camera(
    Mat4 const & vp,
    Mat4 const & per,
    Vec3 const & e, Vec3 const & w, Vec3 const & u, Vec3 const & v)
{
    return (
        vp * per * tform_camera(e, w, u, v)
    );
}
// viewing transforms }}}

} // namespace CxxRay

#endif
