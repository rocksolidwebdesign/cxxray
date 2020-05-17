#ifndef CXXRAY_TEXTURE_IMAGE_H
#define CXXRAY_TEXTURE_IMAGE_H

#include "rgb/rgb_byte.h"

#include <iostream>
#include <memory>

namespace CxxRay {

struct TextureImage
{
    long w = 10;
    long h = 10;

    std::unique_ptr<Rgb> pixelsGuard = nullptr;
    Rgb * pixels = nullptr;

    TextureImage(
        long const w_,
        long const h_)
        : w{w_}
        , h{h_}
        , pixelsGuard{(Rgb*)std::malloc(w_ * h_ * sizeof(Rgb))}
        , pixels{pixelsGuard.get()}
    {
    }

    TextureImage(
        Rgb * dat_,
        long const w_,
        long const h_)
        : w{w_}
        , h{h_}
        , pixelsGuard{dat_}
        , pixels{dat_}
    {
    }

    TextureImage()
        : TextureImage(0, 0)
    {
    }

    TextureImage(TextureImage const & img_)
        : w{img_.w}
        , h{img_.h}
        , pixelsGuard{(Rgb*)std::malloc(img_.w * img_.h * sizeof(Rgb))}
        , pixels{pixelsGuard.get()}
    {
        std::cout << "TextureImage#COPY_CONSTRUCTOR" << std::endl;

        long const len = img_.w * img_.h;

        for (long i = 0; i < len; i++)
        {
            pixels[i] = img_.pixels[i];
        }
    }

    TextureImage& operator=(TextureImage const & img_)
    {
        std::cout << "TextureImage#COPY_ASSIGNMENT" << std::endl;

        if (w != img_.w || h != img_.h) {
            pixelsGuard.reset((Rgb*)std::malloc(img_.w * img_.h * sizeof(Rgb)));
        }

        w = img_.w;
        h = img_.h;

        long const len = img_.w * img_.h;

        for (long i = 0; i < len; i++)
        {
            pixels[i] = img_.pixels[i];
        }

        return (*this);
    }

    TextureImage(TextureImage &&) = default;
    TextureImage& operator=(TextureImage &&) = default;

    ~TextureImage() = default;
};

} // namespace CxxRay

#endif
