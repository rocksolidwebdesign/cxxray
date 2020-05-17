#ifndef CXXRAY_BASIS_H
#define CXXRAY_BASIS_H

#include "linalg/vec3.h"

namespace CxxRay {

struct Basis
{
    Vec3 e = {0.0, -2.0, 0.0};
    Vec3 w = {0.0, -1.0, 0.0};
    Vec3 u = {1.0, 0.0, 0.0};
    Vec3 v = {0.0, 0.0, 1.0};
};

} // namespace CxxRay

#endif
