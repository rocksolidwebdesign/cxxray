#ifndef CXXRAY_MATH_H
#define CXXRAY_MATH_H

#include "global/global.h"

#include <tuple>
#include <cmath>

namespace CxxRay {

inline
std::tuple<Real,Real> quadratic(Real const A, Real const B, Real const C)
{
    Real const D = B*B - 4*A*C;

    Real const t1 = (-1*B + std::sqrt(D)) / 2*A;
    Real const t2 = (-1*B - std::sqrt(D)) / 2*A;

    return { t1, t2 };
}

inline
std::tuple<Real,Real> quadratic_d(Real const A, Real const B, Real const D)
{
    Real const t1 = (-1*B + std::sqrt(D)) / 2*A;
    Real const t2 = (-1*B - std::sqrt(D)) / 2*A;

    return { t1, t2 };
}

} // namespace CxxRay

#endif
