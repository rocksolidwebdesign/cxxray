#ifndef CXXRAY_IMAGE_H
#define CXXRAY_IMAGE_H

#include "utils/data_array.h"
#include "image/pixel.h"
#include "rgb/rgb.h"

namespace CxxRay {

constexpr long kImageDefaultWidth = 400;
constexpr long kImageDefaultHeight = 300;
constexpr long kImageDefaultSize =
    kImageDefaultWidth *
    kImageDefaultHeight;

struct DepthBufImage
{
    using PixelArray = DataArray<Rgb>;
    using ZbufArray = DataArray<Real>;

    PixVal w = kImageDefaultWidth;
    PixVal h = kImageDefaultHeight;
    PixVal size = kImageDefaultSize;

    PixelArray pixelArray = PixelArray{kImageDefaultSize};
    ZbufArray zbufArray = ZbufArray{kImageDefaultSize};

    Rgb * pixels;
    Real * zbuf;

    DepthBufImage()
        : DepthBufImage(
            kImageDefaultWidth,
            kImageDefaultHeight)
    {
        reset();
    }

    DepthBufImage(
        PixVal const w_,
        PixVal const h_)
        : w{w_}
        , h{h_}
        , size{w * h}
        , pixelArray{w * h}
        , zbufArray{w * h}
    {
        pixels = pixelArray.data;
        zbuf = zbufArray.data;

        reset();
    }

    DepthBufImage(PixPoint const s)
        : DepthBufImage{s.x, s.y}
    {
        reset();
    }

    PixVal length() const
    {
        return w * h;
    }

    char * binary() const
    {
        return reinterpret_cast<char*>(pixels);
    }

    void reset(Rgb const & c = {255,255,255})
    {
        PixVal const len = size;

        Rgb * p = pixels;
        Real * z = zbuf;

        for (PixVal i = 0; i < len; i++) {
            // fill the z buffer with a reasonable
            // "maximum distance away" number
            // the camera faces along the negative z-axis
            // so this number should be negative
            // and as large as is reasonable within
            // the 23 bits of a 32bit-float's primary value
            z[i] = -1000000.0;
            p[i] = c;
        }
    }

    size_t pixIndex(
        PixVal const x,
        PixVal const y)
    {
        //auto const y = (h - y_) - 1;

        return w * y + x;
    }

    void set(
        PixVal const x,
        PixVal const y,
        Rgb const & c = {0,0,0})
    {
        pixels[pixIndex(x, y)] = c;
    }

    Real zval(
        PixVal const x,
        PixVal const y)
    {
        return zbuf[pixIndex(x, y)];
    }

    void zval(
        PixVal const x,
        PixVal const y,
        Real const val)
    {
        zbuf[pixIndex(x, y)] = val;
    }
};

} // namespace CxxRay

#endif
