#ifndef CXXRAY_VEC3_H
#define CXXRAY_VEC3_H

#include "global/global.h"

#include <string>
#include <sstream>
#include <ios>
#include <iomanip>

namespace CxxRay {

struct Vec3
{
    Real x = 0.0;
    Real y = 0.0;
    Real z = 0.0;
};

inline
std::string toString(Vec3 const & v)
{
    auto s = std::stringstream{""};

    s << std::fixed << std::setprecision(kIoPrec)
        << "[" << v.x << ", " << v.y << ", " << v.z << "]"
        ;

    return s.str();
}

inline
std::ostream & operator<<(std::ostream & s, Vec3 const & v)
{
    s << toString(v);

    return s;
}

} // namespace CxxRay

#endif
