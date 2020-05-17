#ifndef CXXRAY_VEC4_H
#define CXXRAY_VEC4_H

#include "global/global.h"

#include <string>
#include <sstream>
#include <ios>
#include <iomanip>

namespace CxxRay {

struct Vec4
{
    Real x = 0.0;
    Real y = 0.0;
    Real z = 0.0;
    Real h = 0.0;
};

inline
std::string toString(Vec4 const & v)
{
    auto s = std::stringstream{""};

    s << std::fixed << std::setprecision(kIoPrec)
        << "[" << v.x << ", " << v.y << ", " << v.z << ", " << v.h << "]"
        ;

    return s.str();
}

inline
std::ostream & operator<<(std::ostream & s, Vec4 const & v)
{
    s << toString(v);

    return s;
}

} // namespace CxxRay

#endif
