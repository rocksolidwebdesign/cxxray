#ifndef CXXRAY_CAMERA_H
#define CXXRAY_CAMERA_H

#include "linalg/basis.h"
#include "linalg/linalg.h"

#include "global/global.h"

namespace CxxRay {

inline
Basis getInitialCameraBasis(Vec3 const & e)
{
    // when given only a position e of the camera
    // in global space, orient the camera
    // to face the origin, ensuring the up
    // vector is in the positive z direction
    // such that the x/y plane represents the "ground"

    auto const w = unit(e);

    // if the camera is below the x y plane
    // then we will use a reference
    // point above the plane to find
    // the right hand direction
    if (w.z <= 0) {
        auto const T = Vec3{w.x, w.y, 1.0};
        auto const u = normal(T, w);
        auto const v = normal(w, u);

        return {e, w, u, v};
    }

    // otherwise we use a reference point
    // below the plane to find the right hand
    // direction
    auto const T = Vec3{w.x, w.y, -1.0};
    auto const u = normal(w, T);
    auto const v = normal(w, u);

    return {e, w, u, v};
}

struct Camera
{
    Basis B = {};

    Camera() {}

    Camera(Vec3 const & e)
        : B{getInitialCameraBasis(e)}
    {
    }

    Camera(Real const & x, Real const & y, Real const & z)
        : Camera{{x, y, z}}
    {
    }
};

} // namespace CxxRay

#endif
