#ifndef CXXRAY_RGB_CONVERSIONS_H
#define CXXRAY_RGB_CONVERSIONS_H

#include "rgb_byte.h"
#include "rgb_real.h"

namespace CxxRay {

inline Rgb toRgb(RgbReal const & c) {
    return { c.r, c.g, c.b };
}

inline RgbReal toRgbReal(Rgb const & c) {
    return { c.r, c.g, c.b };
}

} // namespace CxxRay

#endif
