#ifndef CXXRAY_RAYCAST_DRAW_SCENE_H
#define CXXRAY_RAYCAST_DRAW_SCENE_H

#include "raycast/ray_origins.h"
#include "raycast/hit.h"

#include "loaders/ppm.h"

#include "lighting/lambertian.h"
#include "image/depth_buf_image.h"

#include "world/camera.h"
#include "world/light.h"

#include "rgb/rgb.h"

#include "utils/profiler.h"

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

namespace CxxRay {

inline
void
drawRaycastScene(
    DepthBufImage & img,
    Camera const & cam,
    std::vector<Light> const & lights)
{
    using std::cout;
    using std::endl;
    using std::vector;

    std::cout << "drawRaycastScene" << std::endl;

    Vec3 const d = -1.0 * cam.B.w; // camera direction vector

    PixVal const nx = img.w;
    PixVal const ny = img.h;

    Real const aspect =
        static_cast<Real>(nx) /
        static_cast<Real>(ny);

    Real const top = 2.0;
    Real const right = top * aspect;

    auto const c = Vec3{0.0,0.0,0.0}; // sphere center
    auto const R = 1.0; // sphere radius

    //auto const tri_a = Vec3{0.0,1.0,0.0}; // triangle point 1
    //auto const tri_b = Vec3{1.0,1.0,0.0}; // triangle point 2
    //auto const tri_c = Vec3{0.0,1.0,1.0}; // triangle point 3

    // ray origins, i.e. pixels
    vector<Vec3> rayOrigins =
        rayGenerateOrtho(cam.B, right, top, nx, ny);

    for (int j = 0; j < ny; j++)
    {
        for (int i = 0; i < nx; i++)
        {
            // number of rows * width, then add column offset
            auto const idx = j * nx + i;
            auto const e = rayOrigins[idx];

            auto [ isHit, tVal ] = rayIsHitSphere(e, d, c, R);
            //auto [ isHit, tVal ] = rayIsHitTri(e, d, tri_a, tri_b, tri_c);

            auto pixelColor = Rgb{255, 255, 255};

            if (isHit > 0) {
                Vec3 const surfacePoint = e + tVal * d;
                Vec3 const norm = sphere_normal(surfacePoint, c, R);
                //Vec3 const norm = triangle_normal(tri_a, tri_b, tri_c);

                auto const surfaceRgb = RgbReal{1.0,0.0,0.0};

                // ambient should probably use the surface color as the rgb
                // value but this is left up to the caller
                //
                // ambient color = surface rgb value * ambient rgb intensity
                auto const ambient = surfaceRgb * 0.25;

                auto const l = lambertianIntensity(
                    surfacePoint,
                    norm,
                    lights,
                    ambient);

                auto const L = l * surfaceRgb;

                pixelColor = toRgb(L);
            }

            img.set(i, j, pixelColor);
        }
    }
}

} // namespace CxxRay

#endif
