#ifndef CXXRAY_MAT4_H
#define CXXRAY_MAT4_H

#include "global/global.h"

#include "vec4.h"

#include <string>
#include <sstream>
#include <ios>
#include <iomanip>

namespace CxxRay {

struct Mat4
{
    Real ax = 0.0; Real ay = 0.0; Real az = 0.0; Real ah = 0.0;
    Real bx = 0.0; Real by = 0.0; Real bz = 0.0; Real bh = 0.0;
    Real cx = 0.0; Real cy = 0.0; Real cz = 0.0; Real ch = 0.0;
    Real dx = 0.0; Real dy = 0.0; Real dz = 0.0; Real dh = 0.0;

    Vec4 a() const { return {ax, ay, az, ah}; }
    Vec4 b() const { return {bx, by, bz, bh}; }
    Vec4 c() const { return {cx, cy, cz, ch}; }
    Vec4 d() const { return {dx, dy, dz, dh}; }

    Vec4 x() const { return {ax, bx, cx, dx}; }
    Vec4 y() const { return {ay, by, cy, dy}; }
    Vec4 z() const { return {az, bz, cz, dz}; }
    Vec4 h() const { return {ah, bh, ch, dh}; }
};

inline
std::string toString(Mat4 const & m)
{
    auto s = std::stringstream{""};

    s << std::fixed << std::setprecision(kIoPrec)
        << "\n["
        << "[" << m.ax << ", " << m.ay << ", " << m.az << ", " << m.ah << "]\n"
        << " [" << m.bx << ", " << m.by << ", " << m.bz << ", " << m.bh << "]\n"
        << " [" << m.cx << ", " << m.cy << ", " << m.cz << ", " << m.ch << "]\n"
        << " [" << m.dx << ", " << m.dy << ", " << m.dz << ", " << m.dh << "]"
        << "]\n"
        ;

    return s.str();
}

inline
std::ostream & operator<<(std::ostream & s, Mat4 const & m)
{
    s << toString(m);

    return s;
}

} // namespace CxxRay

#endif
