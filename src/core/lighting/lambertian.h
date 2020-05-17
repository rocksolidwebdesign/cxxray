#ifndef CXXRAY_LIGHTING_LAMBERTIAN_H
#define CXXRAY_LIGHTING_LAMBERTIAN_H

#include "world/light.h"
#include "rgb/rgb.h"
#include "linalg/linalg.h"

#include <iostream>
#include <algorithm>

namespace CxxRay {

inline
RgbReal lambertianIntensity(
    Vec3 const & surfacePoint,
    Vec3 const & surfaceNormal,
    Light const & pointLight)
{
    // light must be a unit vector
    // from the surface point to the light
    Vec3 const l = unit(pointLight.pos - surfacePoint);

    // the intensity or "value" of the light
    // is roughly the cosine of the angle between
    // the suface-point to light vector and
    // the surface normal
    auto const angCos = dot(surfaceNormal, l);

    // if the angle is greater than 90 degrees
    // then the cosine will be negative
    // because the light does not hit the front
    // of the surface so we set the value to black
    return angCos > 0
        ? pointLight.col * angCos
        : RgbReal{0.0, 0.0, 0.0};
}

inline
RgbReal lambertianIntensity(
    Vec3 const & surfacePoint,
    Vec3 const & surfaceNormal,
    std::vector<Light> const & lights,
    RgbReal const & ambient = {0.0, 0.0, 0.0})
{
    RgbReal L{0.0, 0.0, 0.0};

    for (auto const & light : lights) {
        L = L + lambertianIntensity(
            surfacePoint,
            surfaceNormal,
            light
        );
    }

    return L + ambient;
}

} // namespace CxxRay

#endif
