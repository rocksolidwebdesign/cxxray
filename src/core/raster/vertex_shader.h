#ifndef CXXRAY_VERTEX_SHADER_PROGRAM_H
#define CXXRAY_VERTEX_SHADER_PROGRAM_H

#include "lighting/lambertian.h"
#include "world/light.h"
#include "world/mesh.h"
#include "linalg/linalg.h"

namespace CxxRay {

inline
ShadedVertex
vertexShaderProgram(
    Mat4 const & M,
    Mat4 const & M_cam,
    std::vector<Light> const & lights,
    Vec3 const & vtx,
    Vec3 const & norm,
    std::tuple<Real,Real> const & uv)
{
    auto const coord = M * vtx;
    auto const zval = (M_cam * vtx).z;

    auto const lightColor = lambertianIntensity(
        vtx,
        norm,
        lights
    );

    auto const [ u, v ] = uv;

    return {
        coord,  // Vec4 coord
        zval, // Real zval
        lightColor, // RgbReal color
        coord.h,
        u,
        v
    };
}

} // namespace CxxRay

#endif
