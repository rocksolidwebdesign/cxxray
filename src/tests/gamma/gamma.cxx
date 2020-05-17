#include "loaders/tga.h"
#include "image/depth_buf_image.h"
#include "image/pixel.h"
#include "rgb/rgb.h"
#include "global/global.h"

#include <string>
#include <array>
#include <cmath>
#include <iostream>

namespace CxxRay {

int gammaTestMain(int argc, char** argv)
{
    using std::cout;
    using std::endl;

    using std::string;
    using std::stof;

    using std::pow;

    cout << "Running gamma_test..." << endl;

    string gammaArg = argc > 1 ? argv[1] : "";

    string gammaStr = gammaArg != ""
        ? gammaArg
        : string{"2.2"};

    Real const gamma = stof(gammaStr);

    // when adjusted  with gamma, the half  way value should
    // result  in  a color  with  the  same intensity  as  a
    // black-and-white checkerboard  pixel pattern  i.e. the
    // grey exactly in between black and white
    Real const a = 0.5;

    RgbReal const kMinIntens{0.0};
    RgbReal const kMaxIntens{1.0};

    PixPoint const sz{1000,500};

    DepthBufImage img{sz};

    auto const w = img.w;
    auto const h = img.h;
    auto const w2 = w / 2;

    // Left Half (gamma adjusted)
    //------------------------------------------------------------
    cout << "Generating left half (gamma adjusted)..." << endl;

    auto const intens = pow(a, 1.0/gamma);

    for (PixVal y = 0; y < h; y++) {
        for (PixVal x = 0; x < w2; x++) {
            img.set(x, y, toRgb(intens));
        }
    }

    // Right Half (mix)
    //------------------------------------------------------------
    cout << "Generating right half (mix)..." << endl;

    for (PixVal y = 0; y < h; y++)
    {
        using Palette = std::array<RgbReal,2>;

        // if it's an even row then start white
        // if it's an odd row then start black
        Palette const palette = y % 2 == 0
            ? Palette{kMaxIntens, kMinIntens}
            : Palette{kMinIntens, kMaxIntens};

        for (PixVal x = w2; x < w; x++)
        {
            // alternate color every pixel
            auto const intens = palette[x % 2];

            img.set(x, y, toRgb(intens));
        }
    }

    saveTargaFile("gamma_test.tga", img.pixels, img.w, img.h);

    return 0;
}

} // namespace CxxRay

int main(int argc, char** argv)
{
    return CxxRay::gammaTestMain(argc, argv);
}
