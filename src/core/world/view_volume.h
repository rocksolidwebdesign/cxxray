#ifndef CXXRAY_VIEW_VOLUME_H
#define CXXRAY_VIEW_VOLUME_H

#include "global/global.h"

namespace CxxRay {

struct ViewVolume
{
    Real far = -6.0;
    Real near = -4.0;

    Real right = 1.0;
    Real left = -1.0;

    Real top = 0.75;
    Real bot = -0.75;
};

} // namespace CxxRay

#endif
