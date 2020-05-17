#ifndef CXXRAY_LIGHT_H
#define CXXRAY_LIGHT_H

#include "rgb/rgb.h"
#include "linalg/vec3.h"
#include "global/global.h"

#include <array>
#include <vector>

namespace CxxRay {

struct Light
{
    RgbReal col = {1.0,1.0,1.0};
    Vec3 pos = {1.0,1.0,1.0};

    Light()
    {
    }

    Light(RgbReal const & col_)
        : col{col_}
    {
    }

    Light(Vec3 const & pos_)
        : pos{pos_}
    {
    }

    Light(
        Vec3 const & pos_,
        Real const col_)
        : col{col_}
        , pos{pos_}
    {
    }

    Light(
        Real const col_,
        Vec3 const & pos_)
        : col{col_}
        , pos{pos_}
    {
    }

    Light(
        RgbReal const & col_,
        Vec3 const pos_)
        : col{col_}
        , pos{pos_}
    {
    }

    Light(
        Vec3 const & pos_,
        RgbReal const & col_)
        : col{col_}
        , pos{pos_}
    {
    }
};

} // namespace CxxRay

#endif
