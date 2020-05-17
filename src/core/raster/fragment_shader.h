#ifndef CXXRAY_FRAGMENT_SHADER_PROGRAM_H
#define CXXRAY_FRAGMENT_SHADER_PROGRAM_H

#include "linalg/linalg.h"

#include "world/mesh.h"
#include "image/depth_buf_image.h"
#include "image/pixel.h"
#include "rgb/rgb.h"

#include "global/global.h"

#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <algorithm>
#include <functional>
#include <cmath>

namespace CxxRay {

constexpr Real gammaCorrect = 1.0/kMonitorGamma;
constexpr bool dbgOn = true;

inline
PixVal
xfloor(
    PixPoint const & pa,
    PixPoint const & pb,
    PixPoint const & pc)
{
    auto x = pa.x;
    if (pb.x < x) { x = pb.x; }
    if (pc.x < x) { x = pc.x; }
    return x;
}

inline
PixVal
yfloor(
    PixPoint const & pa,
    PixPoint const & pb,
    PixPoint const & pc)
{
    auto y = pa.y;
    if (pb.y < y) { y = pb.y; }
    if (pc.y < y) { y = pc.y; }
    return y;
}

inline
PixVal xceil(
    PixPoint const & pa,
    PixPoint const & pb,
    PixPoint const & pc)
{
    auto x = pa.x;
    if (pb.x > x) { x = pb.x; }
    if (pc.x > x) { x = pc.x; }
    return x;
}

inline
PixVal
yceil(
    PixPoint const & pa,
    PixPoint const & pb,
    PixPoint const & pc)
{
    auto y = pa.y;
    if (pb.y > y) { y = pb.y; }
    if (pc.y > y) { y = pc.y; }
    return y;
}

inline
PixVal
clamp(
    PixVal const val,
    PixVal const lbound,
    PixVal const ubound)
{
    if (val < lbound) {
        return lbound;
    }

    if (val > ubound) {
        return ubound;
    }

    return val;
}

inline
void
fragementShaderProgram(
    DepthBufImage & img,
    ShadedFace const & face,
    std::unordered_map<std::string,TextureImage> & textures)
{
    auto const & mtl = face.mtl;

    auto const & texName = mtl.texName;

    bool const hasTex = texName != "" && textures.count(texName) != 0;
    auto const & tex = textures[mtl.texName];

    auto const & tri = face.triangle;

    auto const & aVp = tri[0].coord; // vertex coordinates of
    auto const & bVp = tri[1].coord; // each triangle point
    auto const & cVp = tri[2].coord;

    auto const & aTexU = tri[0].u; // texture coordinates
    auto const & aTexV = tri[0].v; // of each triangle point

    auto const & bTexU = tri[1].u;
    auto const & bTexV = tri[1].v;

    auto const & cTexU = tri[2].u;
    auto const & cTexV = tri[2].v;

    auto const & az = tri[0].zval; // z coords of
    auto const & bz = tri[1].zval; // each triangle point
    auto const & cz = tri[2].zval;

    auto const aHom = tri[0].h; // homogenous coordinates
    auto const bHom = tri[1].h; // of each triangle point
    auto const cHom = tri[2].h;

    RgbReal const la = tri[0].light; // light intensity at vertex A
    RgbReal const lb = tri[1].light; // light intensity at vertex B
    RgbReal const lc = tri[2].light; // light intensity at vertex C

    // translate the x and y world coordinates of the
    // vertices within the view volume to pixel coordinates
    // on the screen's viewport, this requires dividing
    // by the homogenous coordinate to find the "real"
    // x and y values because of the perspective transformation
    //
    // we want the truncation aspect of casting doubles
    // to ints because the viewing system assumes pixel
    // centers at offsets of 0.5
    PixPoint const p0 = { aVp.x / aVp.h, aVp.y / aVp.h };
    PixPoint const p1 = { bVp.x / bVp.h, bVp.y / bVp.h };
    PixPoint const p2 = { cVp.x / cVp.h, cVp.y / cVp.h };

    PixVal const xmin = clamp(xfloor(p0, p1, p2), 0, img.w);
    PixVal const xmax = clamp(xceil (p0, p1, p2), 0, img.w);
    PixVal const ymin = clamp(yfloor(p0, p1, p2), 0, img.h);
    PixVal const ymax = clamp(yceil (p0, p1, p2), 0, img.h);

    PixVal const A01 = p0.y - p1.y;
    PixVal const B01 = p1.x - p0.x;
    PixVal const C01 = p0.x*p1.y - p1.x*p0.y;

    PixVal const A12 = p1.y - p2.y;
    PixVal const B12 = p2.x - p1.x;
    PixVal const C12 = p1.x*p2.y - p2.x*p1.y;

    PixVal const A20 = p2.y - p0.y;
    PixVal const B20 = p0.x - p2.x;
    PixVal const C20 = p2.x*p0.y - p0.x*p2.y;

    Real const fp0 = static_cast<Real>(A12*p0.x + B12*p0.y + C12);
    Real const fp1 = static_cast<Real>(A20*p1.x + B20*p1.y + C20);
    Real const fp2 = static_cast<Real>(A01*p2.x + B01*p2.y + C01);

    // any arbitrary offscreen point to
    // determine edge winning contests
    auto const offx = -1;
    auto const offy = -1;

    Real const edge12 = fp0 * static_cast<Real>(A12*offx + B12*offy + C12);
    Real const edge20 = fp1 * static_cast<Real>(A20*offx + B20*offy + C20);
    Real const edge01 = fp2 * static_cast<Real>(A01*offx + B01*offy + C01);

    for (PixVal y = ymin; y < ymax; y++)
    {
        for (PixVal x = xmin; x < xmax; x++)
        {
            // calculate the barycentric coefficients
            Real const alpha = static_cast<Real>(A12*x + B12*y + C12) / fp0;
            Real const beta  = static_cast<Real>(A20*x + B20*y + C20) / fp1;
            Real const gamma = static_cast<Real>(A01*x + B01*y + C01) / fp2;

            if (alpha >= 0 && beta >= 0 && gamma >= 0)
            {
                if (
                    // we're either on an edge or vertex
                    (
                        // when on a face edge, a single component will be 0.0
                        // and the others will have some value, but we still
                        // need to draw the edge
                        //
                        // when on a vertex, a single component will be 1.0
                        // and the others will be 0.0 but we still need to draw the edge
                        //
                        // α + β + γ = 1
                        //
                        // but the greater than zero test accompanying the edge check
                        // is all or nothing, so we need to provide one more way
                        // to confirm we should draw this pixel
                        alpha == 0.0 ||
                         beta == 0.0 ||
                        gamma == 0.0 ||

                        alpha == 1.0 ||
                         beta == 1.0 ||
                        gamma == 1.0
                    )
                    ||
                    // or we're inside the triangle somewhere
                    (
                        (alpha > 0 || edge12 > 0) &&
                        ( beta > 0 || edge20 > 0) &&
                        (gamma > 0 || edge01 > 0)
                    )
                ) {
                    // interpolate the z value, same as the color
                    // try subtracting z values instead?
                    auto const zdist = alpha*az + beta*bz + gamma*cz;

                    auto const curz = img.zval(x, y);

                    if (zdist <= curz) {
                        continue;
                    }

                    img.zval(x, y, zdist);

                    // if there is no UV texture map
                    // we'll just use the diffuse color
                    // (or surface color) from the MTL
                    // file
                    RgbReal kd = mtl.diffuse;

                    if (hasTex)
                    {
                        ////////////////////////////////////////////////
                        // Texturing
                        ////////////////////////////////////////////////
                        //
                        // In its simplest form the relative position of
                        // the appropriate color from the texture is
                        // given by finding barycentric versions of
                        // the uv coordinates and interpolating
                        // across the vertices as would be done with
                        // color
                        //
                        // u(β,γ) = u_a + β(u_a - u_c) + γ(u_b - u_a)
                        // v(β,γ) = v_a + β(v_a - v_c) + γ(v_b - v_a)
                        //
                        // However this will not work properly with
                        // respect to the perspective transform, so
                        // we want to find the barycentric coordinates
                        // relative to the world before the perspective
                        // transform

                        auto const bary_d = bHom*cHom + cHom*beta*(aHom - bHom) + bHom*gamma*(aHom - cHom);
                        auto const beta_w = (aHom*cHom*beta)/bary_d;
                        auto const gamma_w = (aHom*bHom*gamma)/bary_d;
                        auto const alpha_w = 1 - beta_w - gamma_w;
                        auto const u0 = alpha_w*aTexU + beta_w*bTexU + gamma_w*cTexU;
                        auto const v0 = alpha_w*aTexV + beta_w*bTexV + gamma_w*cTexV;

                        Real const u = std::clamp(u0, 0.0, 1.0);
                        Real const v = std::clamp(v0, 0.0, 1.0);

                        // we multiply u by the texture width
                        // and v by the texture height to arrive at
                        // the pixel color from the texture which
                        // corresponds to this pixel of the triangle
                        auto const xTex = static_cast<long>(u * static_cast<Real>(tex.w));
                        auto const yTex = static_cast<long>(v * static_cast<Real>(tex.h));

                        auto const idxTex = (yTex * tex.w) + xTex;

                        kd = toRgbReal(tex.pixels[idxTex]);
                    }

                    // for nice looking (non-washed out) results, the
                    // ambient color should probably be the surface color
                    // times the ambient intensity, but could be different
                    //
                    // blender seems to draw ambient differently
                    // so we reduce the total abmient by a constant to get
                    // closer to blender's render output
                    auto const ka = mtl.ambient * kd * 0.23;

                    // interpolate the light intensity
                    // barycentric coordinates
                    //
                    // colAtPix = αc0 + βc1 + γc2
                    auto const l = alpha*la + beta*lb + gamma*lc;
                    auto L = ka + l * kd;

                    L.r = std::clamp(std::pow(L.r, gammaCorrect), 0.0, 1.0);
                    L.g = std::clamp(std::pow(L.g, gammaCorrect), 0.0, 1.0);
                    L.b = std::clamp(std::pow(L.b, gammaCorrect), 0.0, 1.0);

                    img.set(x, y, toRgb(L));
                }
            }
        }
    }
}

} // namespace CxxRay

#endif
