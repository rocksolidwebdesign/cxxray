#ifndef CXXRAY_MAT3_H
#define CXXRAY_MAT3_H

#include "global/global.h"

#include "vec3.h"

#include <string>
#include <sstream>
#include <ios>
#include <iomanip>

namespace CxxRay {

struct Mat3
{
    Real ax = 0.0; Real ay = 0.0; Real az = 0.0;
    Real bx = 0.0; Real by = 0.0; Real bz = 0.0;
    Real cx = 0.0; Real cy = 0.0; Real cz = 0.0;

    Vec3 a() const { return {ax, ay, az}; }
    Vec3 b() const { return {bx, by, bz}; }
    Vec3 c() const { return {cx, cy, cz}; }

    Vec3 x() const { return {ax, bx, cx}; }
    Vec3 y() const { return {ay, by, cy}; }
    Vec3 z() const { return {az, bz, cz}; }
};

inline
std::string toString(Mat3 const & m)
{
    auto s = std::stringstream{""};

    s << std::fixed << std::setprecision(kIoPrec)
        << "\n["
        << "[" << m.ax << ", " << m.ay << ", " << m.az << "]\n"
        << " [" << m.bx << ", " << m.by << ", " << m.bz << "]\n"
        << " [" << m.cx << ", " << m.cy << ", " << m.cz << "]"
        << "]\n"
        ;

    return s.str();
}

inline
std::ostream & operator<<(std::ostream & s, Mat3 const & m)
{
    s << toString(m);

    return s;
}

} // namespace CxxRay

#endif
