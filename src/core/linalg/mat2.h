#ifndef CXXRAY_MAT2_H
#define CXXRAY_MAT2_H

#include "global/global.h"

#include "vec2.h"

#include <string>
#include <sstream>
#include <ios>
#include <iomanip>

namespace CxxRay {

struct Mat2
{
    Real ax = 0.0; Real ay = 0.0;
    Real bx = 0.0; Real by = 0.0;

    Vec2 a() const { return {ax, ay}; }
    Vec2 b() const { return {bx, by}; }

    Vec2 x() const { return {ax, bx}; }
    Vec2 y() const { return {ay, by}; }
};

inline
std::string toString(Mat2 const & m)
{
    auto s = std::stringstream{""};

    s << std::fixed << std::setprecision(kIoPrec)
        << "\n["
        << "[" << m.ax << ", " << m.ay << "]\n"
        << " [" << m.bx << ", " << m.by << "]"
        << "]\n"
        ;

    return s.str();
}

inline
std::ostream & operator<<(std::ostream & s, Mat2 const & m)
{
    s << toString(m);

    return s;
}

} // namespace CxxRay

#endif
