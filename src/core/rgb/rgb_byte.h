#ifndef CXXRAY_RGB_BYTE_H
#define CXXRAY_RGB_BYTE_H

#include "global/global.h"

#include <memory>
#include <string>
#include <ostream>
#include <algorithm>
#include <cmath>

namespace CxxRay {

using ByteT = unsigned char;

struct Rgb
{
    ByteT r = static_cast<ByteT>(255);
    ByteT g = static_cast<ByteT>(255);
    ByteT b = static_cast<ByteT>(255);

    Rgb()
    {
    }

    Rgb(Real const v_)
        : r{static_cast<ByteT>(v_ * 255)}
        , g{static_cast<ByteT>(v_ * 255)}
        , b{static_cast<ByteT>(v_ * 255)}
    {
    }

    Rgb(short const v_)
        : r{static_cast<ByteT>(v_)}
        , g{static_cast<ByteT>(v_)}
        , b{static_cast<ByteT>(v_)}
    {
    }

    Rgb(int const v_)
        : r{static_cast<ByteT>(v_)}
        , g{static_cast<ByteT>(v_)}
        , b{static_cast<ByteT>(v_)}
    {
    }

    Rgb(long const v_)
        : r{static_cast<ByteT>(v_)}
        , g{static_cast<ByteT>(v_)}
        , b{static_cast<ByteT>(v_)}
    {
    }

    Rgb(char const v_)
        : r{static_cast<ByteT>(v_)}
        , g{static_cast<ByteT>(v_)}
        , b{static_cast<ByteT>(v_)}
    {
    }

    Rgb(Real const r_,
        Real const g_,
        Real const b_)
        : r{static_cast<ByteT>(r_ * 255)}
        , g{static_cast<ByteT>(g_ * 255)}
        , b{static_cast<ByteT>(b_ * 255)}
    {
    }

    Rgb(short const r_,
        short const g_,
        short const b_)
        : r{static_cast<ByteT>(r_)}
        , g{static_cast<ByteT>(g_)}
        , b{static_cast<ByteT>(b_)}
    {
    }

    Rgb(int const r_,
        int const g_,
        int const b_)
        : r{static_cast<ByteT>(r_)}
        , g{static_cast<ByteT>(g_)}
        , b{static_cast<ByteT>(b_)}
    {
    }

    Rgb(long const r_,
        long const g_,
        long const b_)
        : r{static_cast<ByteT>(r_)}
        , g{static_cast<ByteT>(g_)}
        , b{static_cast<ByteT>(b_)}
    {
    }

    Rgb(char const r_,
        char const g_,
        char const b_)
        : r{static_cast<ByteT>(r_)}
        , g{static_cast<ByteT>(g_)}
        , b{static_cast<ByteT>(b_)}
    {
    }
};

inline
Rgb operator+(Rgb const & c0, Rgb const & c1)
{
    int const r = (std::min)(c0.r + c1.r, 255);
    int const g = (std::min)(c0.g + c1.g, 255);
    int const b = (std::min)(c0.b + c1.b, 255);

    return { r, g, b };
}

inline
Rgb operator+(Rgb const & c0, ByteT const val)
{
    int const r = (std::min)(c0.r + val, 255);
    int const g = (std::min)(c0.g + val, 255);
    int const b = (std::min)(c0.b + val, 255);

    return { r, g, b };
}

inline
Rgb operator+(ByteT const val, Rgb const & c0)
{
    auto const r = (std::min)(c0.r + val, 255);
    auto const g = (std::min)(c0.g + val, 255);
    auto const b = (std::min)(c0.b + val, 255);

    return { r, g, b };
}

inline
Rgb operator+(Rgb const & c0, int const val)
{
    int const r = (std::min)(c0.r + val, 255);
    int const g = (std::min)(c0.g + val, 255);
    int const b = (std::min)(c0.b + val, 255);

    return { r, g, b };
}

inline
Rgb operator+(int const val, Rgb const & c0)
{
    int const r = (std::min)(c0.r + val, 255);
    int const g = (std::min)(c0.g + val, 255);
    int const b = (std::min)(c0.b + val, 255);

    return { r, g, b };
}

inline
Rgb operator-(Rgb const & c0, ByteT const val)
{
    int const r = (std::min)(c0.r - val, 255);
    int const g = (std::min)(c0.g - val, 255);
    int const b = (std::min)(c0.b - val, 255);

    return { r, g, b };
}

inline
Rgb operator-(ByteT const val, Rgb const & c0)
{
    int const r = (std::min)(c0.r - val, 255);
    int const g = (std::min)(c0.g - val, 255);
    int const b = (std::min)(c0.b - val, 255);

    return { r, g, b };
}

inline
Rgb operator-(Rgb const & c0, int const val)
{
    int const r = (std::min)(c0.r - val, 255);
    int const g = (std::min)(c0.g - val, 255);
    int const b = (std::min)(c0.b - val, 255);

    return { r, g, b };
}

inline
Rgb operator-(int const val, Rgb const & c0)
{
    int const r = (std::min)(c0.r - val, 255);
    int const g = (std::min)(c0.g - val, 255);
    int const b = (std::min)(c0.b - val, 255);

    return { r, g, b };
}

inline
Rgb operator*(Rgb const & c0, Real const val)
{
    int const r = (std::min)(static_cast<int>(std::round(c0.r * val)), 255);
    int const g = (std::min)(static_cast<int>(std::round(c0.g * val)), 255);
    int const b = (std::min)(static_cast<int>(std::round(c0.b * val)), 255);

    return { r, g, b };
}

inline
Rgb operator*(Real const val, Rgb const & c0)
{
    int const r = (std::min)(static_cast<int>(std::round(c0.r * val)), 255);
    int const g = (std::min)(static_cast<int>(std::round(c0.g * val)), 255);
    int const b = (std::min)(static_cast<int>(std::round(c0.b * val)), 255);

    return { r, g, b };
}

inline
int rgbByteToInt(char c)
{
    return static_cast<int>(static_cast<unsigned char>(c));
}

inline
std::string
toString(
    Rgb const & obj)
{
    using std::to_string;

    return "L#"
        + to_string(rgbByteToInt(obj.r)) + ","
        + to_string(rgbByteToInt(obj.g)) + ","
        + to_string(rgbByteToInt(obj.b));
}

inline
std::ostream &
operator<<(
    std::ostream & s,
    Rgb const & obj)
{
    return s << toString(obj);
}

} // namespace CxxRay

#endif
