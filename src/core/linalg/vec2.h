#ifndef CXXRAY_VEC2_H
#define CXXRAY_VEC2_H

#include "global/global.h"

#include <string>
#include <sstream>
#include <ios>
#include <iomanip>

namespace CxxRay {

struct Vec2
{
    Real x = 0.0;
    Real y = 0.0;
};

inline
std::string toString(Vec2 const & v)
{
    auto s = std::stringstream{""};

    s << std::fixed << std::setprecision(kIoPrec)
        << "[" << v.x << ", " << v.y << "]"
        ;

    return s.str();
}

inline
std::ostream & operator<<(std::ostream & s, Vec2 const & v)
{
    s << toString(v);

    return s;
}

} // namespace CxxRay

#endif
