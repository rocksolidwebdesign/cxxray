#ifndef CXXRAY_RAYCAST_ORIGINS_H
#define CXXRAY_RAYCAST_ORIGINS_H

#include "linalg/linalg.h"
#include "linalg/vec3.h"
#include "linalg/math.h"
#include "image/pixel.h"

#include <vector>

namespace CxxRay {

inline
std::vector<Vec3>
rayGenerateOrtho(
    Basis const & B,
    Real const r = 4.0,
    Real const t = 3.0,
    PixVal const nx = 40,
    PixVal const ny = 30)
{
    using std::vector;

    // left and bottom
    Real const l = -1 * r;
    Real const b = -1 * t;

    // camera plane pixel width and height in global space
    Real const pxw = (r - l) / static_cast<Real>(nx);
    Real const pxh = (t - b) / static_cast<Real>(ny);

    // camera right (U) and up (V) vectors
    Vec3 const & E = B.e;
    Vec3 const & U = B.u;
    Vec3 const & V = B.v;

    // ray origins for each pixel
    vector<Vec3> origins = {};

    // there are the same number of origins
    // as pixels in the image
    origins.reserve(nx * ny);

    // find the raster plane pixel positions (ray origins)
    // in global coordinate space
    //
    // bottom to top, left to right
    for (int j = 0; j < ny; j++)
    {
        for (int i = 0; i < nx; i++)
        {
            // add half a pixel width
            // to center the pixel grid
            Real const u = l + ((i + 0.5) * pxw);
            Real const v = b + ((j + 0.5) * pxh);

            Vec3 p = E + u*U + v*V;

            origins.push_back(p);
        }
    }

    return origins;
}

} // namespace CxxRay

#endif
