#ifndef CXXRAY_RAYCAST_HIT_H
#define CXXRAY_RAYCAST_HIT_H

#include "global/global.h"

#include "linalg/linalg.h"
#include "linalg/math.h"

#include <tuple>

namespace CxxRay {

inline
std::tuple<int,Real>
rayIsHitSphere(
    Vec3 const e, // ray starting point
    Vec3 const d, // ray direction
    Vec3 const c, // sphere center
    Real const R) // sphere radius
{
    // (e-c)
    Vec3 const ec = e - c;

    // A = d · d
    Real const A = dot(d, d);

    // B = 2d · (e-c)
    Real const B = dot(2*d, ec);

    // C = (e-c) · (e-c) - R²
    Real const C = dot(ec, ec) - R*R;

    // D = B² - 4AC
    Real const D = B*B - 4*A*C;

    if (D < 0) {
        // no non-imaginary solutions
        return {0, 0.0};
    }

    int const n = D == 0 ? 1 : 2;

    // solve the quadradic equation
    // t = (-b ± √(b² - 4ac)) / 2a
    // t = (-B ± √D) / 2A
    //
    // if there is only one solution
    // then D = 0 so t1 = t2
    auto const [ t1, t2 ] = quadratic_d(A, B, D);

    // return the closest point
    return {n, t1 < t2 ? t1 : t2};
}

inline
std::tuple<int,Real>
rayIsHitTri(
    Vec3 const ray_e, // ray starting point
    Vec3 const ray_d, // ray direction
    Vec3 const tri_a, // triangle points
    Vec3 const tri_b,
    Vec3 const tri_c,
    Real const t1 = 1000000.0,
    Real const t0 = 0.0)
{
    Real const xa = tri_a.x;
    Real const ya = tri_a.y;
    Real const za = tri_a.z;

    Real const xb = tri_b.x;
    Real const yb = tri_b.y;
    Real const zb = tri_b.z;

    Real const xc = tri_c.x;
    Real const yc = tri_c.y;
    Real const zc = tri_c.z;

    Real const xd = ray_d.x;
    Real const yd = ray_d.y;
    Real const zd = ray_d.z;

    Real const xe = ray_e.x;
    Real const ye = ray_e.y;
    Real const ze = ray_e.z;

    Real const a = xa-xb;
    Real const b = ya-yb;
    Real const c = za-zb;

    Real const d = xa-xc;
    Real const e = ya-yc;
    Real const f = za-zc;

    Real const g = xd;
    Real const h = yd;
    Real const i = zd;

    Real const j = xa-xe;
    Real const k = ya-ye;
    Real const l = za-ze;

    Real const eihf = e*i - h*f;
    Real const gfdi = g*f - d*i;
    Real const dheg = d*h - e*g;

    Real const akjb = a*k - j*b;
    Real const jcal = j*c - a*l;
    Real const blck = b*l - c*k;

    Real const M = a*eihf + b*gfdi + c*dheg;

    Real const t = -1 * (f*akjb + e*jcal + d*blck) / M;
    if (t < t0 || t > t1) {
        return {0, 0.0};
    }

    Real const y = (i*akjb + h*jcal + g*blck) / M;
    if (y < 0.0 || y > 1.0) {
        return {0, 0.0};
    }

    Real const B = (j*eihf + k*gfdi + l*dheg) / M;
    if (B < 0.0 || B > (1.0 - y)) {
        return {0, 0.0};
    }

    return {1, t};
}

} // namespace CxxRay

#endif
