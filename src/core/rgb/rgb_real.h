#ifndef CXXRAY_RGB_REAL_H
#define CXXRAY_RGB_REAL_H

#include "global/global.h"

#include <memory>
#include <string>
#include <ostream>
#include <algorithm>
#include <cmath>

namespace CxxRay {

struct RgbReal
{
    Real r = 1.0;
    Real g = 1.0;
    Real b = 1.0;

    RgbReal()
    {
    }

    RgbReal(
        Real v_)
        : r{v_}
        , g{v_}
        , b{v_}
    {
    }

    RgbReal(int v_)
        : r{static_cast<Real>(v_) / 255}
        , g{static_cast<Real>(v_) / 255}
        , b{static_cast<Real>(v_) / 255}
    {
    }

    RgbReal(char v_)
        : r{static_cast<Real>(v_) / 255}
        , g{static_cast<Real>(v_) / 255}
        , b{static_cast<Real>(v_) / 255}
    {
    }

    RgbReal(
        Real r_,
        Real g_,
        Real b_)
        : r{r_}
        , g{g_}
        , b{b_}
    {
    }

    RgbReal(
        int r_,
        int g_,
        int b_)
        : r{static_cast<Real>(r_) / 255}
        , g{static_cast<Real>(g_) / 255}
        , b{static_cast<Real>(b_) / 255}
    {
    }

    RgbReal(
        char r_,
        char g_,
        char b_)
        : r{static_cast<Real>(r_) / 255}
        , g{static_cast<Real>(g_) / 255}
        , b{static_cast<Real>(b_) / 255}
    {
    }
};

inline
RgbReal operator+(RgbReal const & c0, RgbReal const & c1)
{
    auto const r = (std::min)(c0.r + c1.r, 1.0);
    auto const g = (std::min)(c0.g + c1.g, 1.0);
    auto const b = (std::min)(c0.b + c1.b, 1.0);

    return { r, g, b };
}

inline
RgbReal operator+(RgbReal const & c0, Real const val)
{
    auto const r = (std::min)(c0.r + val, 1.0);
    auto const g = (std::min)(c0.g + val, 1.0);
    auto const b = (std::min)(c0.b + val, 1.0);

    return { r, g, b };
}

inline
RgbReal operator+(Real const val, RgbReal const & c0)
{
    auto const r = (std::min)(c0.r + val, 1.0);
    auto const g = (std::min)(c0.g + val, 1.0);
    auto const b = (std::min)(c0.b + val, 1.0);

    return { r, g, b };
}

inline
RgbReal operator+(RgbReal const & c0, int const val)
{
    auto const r = (std::min)(c0.r + val, 1.0);
    auto const g = (std::min)(c0.g + val, 1.0);
    auto const b = (std::min)(c0.b + val, 1.0);

    return { r, g, b };
}

inline
RgbReal operator+(int const val, RgbReal const & c0)
{
    auto const r = (std::min)(c0.r + val, 1.0);
    auto const g = (std::min)(c0.g + val, 1.0);
    auto const b = (std::min)(c0.b + val, 1.0);

    return { r, g, b };
}

inline
RgbReal operator-(RgbReal const & c0, Real const val)
{
    auto const r = (std::min)(c0.r - val, 1.0);
    auto const g = (std::min)(c0.g - val, 1.0);
    auto const b = (std::min)(c0.b - val, 1.0);

    return { r, g, b };
}

inline
RgbReal operator-(Real const val, RgbReal const & c0)
{
    auto const r = (std::min)(c0.r - val, 1.0);
    auto const g = (std::min)(c0.g - val, 1.0);
    auto const b = (std::min)(c0.b - val, 1.0);

    return { r, g, b };
}

inline
RgbReal operator-(RgbReal const & c0, int const val)
{
    auto const r = (std::min)(c0.r - val, 1.0);
    auto const g = (std::min)(c0.g - val, 1.0);
    auto const b = (std::min)(c0.b - val, 1.0);

    return { r, g, b };
}

inline
RgbReal operator-(int const val, RgbReal const & c0)
{
    auto const r = (std::min)(c0.r - val, 1.0);
    auto const g = (std::min)(c0.g - val, 1.0);
    auto const b = (std::min)(c0.b - val, 1.0);

    return { r, g, b };
}

inline
RgbReal operator*(RgbReal const & c0, Real const val)
{
    auto const r = (std::min)(c0.r * val, 1.0);
    auto const g = (std::min)(c0.g * val, 1.0);
    auto const b = (std::min)(c0.b * val, 1.0);

    return { r, g, b };
}

inline
RgbReal operator*(Real const val, RgbReal const & c0)
{
    auto const r = (std::min)(c0.r * val, 1.0);
    auto const g = (std::min)(c0.g * val, 1.0);
    auto const b = (std::min)(c0.b * val, 1.0);

    return { r, g, b };
}

inline
RgbReal operator*(RgbReal const & c0, RgbReal const & c1)
{
    auto const r = (std::min)(c0.r * c1.r, 1.0);
    auto const g = (std::min)(c0.g * c1.g, 1.0);
    auto const b = (std::min)(c0.b * c1.b, 1.0);

    return { r, g, b };
}

inline
std::string
toString(
    RgbReal const & obj)
{
    using std::to_string;

    return "L|"
        + to_string(obj.r) + ","
        + to_string(obj.g) + ","
        + to_string(obj.b);
}

inline
std::ostream &
operator<<(
    std::ostream & s,
    RgbReal const & obj)
{
    return s << toString(obj);
}

} // namespace CxxRay

#endif
