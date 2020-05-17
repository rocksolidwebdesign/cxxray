#ifndef CXXRAY_PIXEL_H
#define CXXRAY_PIXEL_H

#include "global/global.h"

#include <iostream>
#include <iomanip>
#include <sstream>
#include <cmath>

namespace CxxRay {

using PixVal = long;

struct PixPoint
{
    using string = std::string;

    PixVal x = 0l;
    PixVal y = 0l;

    PixPoint()
    {
    }

    PixPoint(Real const x_, Real const y_)
        : x{static_cast<PixVal>(std::round(x_))}
        , y{static_cast<PixVal>(std::round(y_))}
    {
    }

    PixPoint(int const x_, int const y_)
        : x{x_}
        , y{y_}
    {
    }

    PixPoint(PixVal const x_, PixVal const y_)
        : x{x_}
        , y{y_}
    {
    }

    string toString() const
    {
        using std::to_string;

        return to_string(x) + "," + to_string(y);
    }
};

struct PixLine
{
    using string = std::string;

    PixPoint a = {};
    PixPoint b = {};

    string toString() const
    {
        return a.toString() + "->" + b.toString();
    }
};

inline
std::ostream &
operator<<(
    std::ostream & s,
    PixPoint const & obj)
{
    s << obj.toString(); return s;
}

inline
std::ostream &
operator<<(
    std::ostream & s,
    PixLine const & obj)
{
    s << obj.toString(); return s;
}

} // namespace CxxRay

#endif
