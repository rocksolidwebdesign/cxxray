#ifndef CXXRAY_PPM_H
#define CXXRAY_PPM_H

#include "image/texture_image.h"
#include "image/pixel.h"
#include "rgb/rgb.h"
#include "utils/data_array.h"

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace CxxRay {

namespace pnmParse {

    inline
    bool isWhite(char const c)
    {
        return c == ' ' || c == '\t' || c == '\n' || c == '\r';
    }

    inline
    bool isComment(char const c)
    {
        return c == '#';
    }

    inline
    void skipWhite(std::ifstream & fh)
    {
        char c = '@';

        while (!fh.eof())
        {
            fh.get(c);

            if (!isWhite(c)) {
                fh.unget();

                break;
            }
        }
    }

    inline
    std::string skipLine(std::ifstream & fh)
    {
        std::string comment = "";

        char c = '@';

        // skip initial whitespace so
        // we don't have dangling white
        // space at the beginning of
        // comments
        skipWhite(fh);

        while (!fh.eof())
        {
            fh.get(c);

            if (c == '\n') {
                break;
            }

            comment += c;
        }

        return comment;
    }

    inline
    std::string getToken(std::ifstream & fh)
    {
        std::string tok = "";

        char c = 127;

        while (!fh.eof())
        {
            fh.get(c);

            if (isWhite(c)) {
                skipWhite(fh);
                break;
            }

            if (isComment(c) || isWhite(c)) {
                skipLine(fh);
                break;
            }

            tok += c;
        }

        return tok;
    }

    inline
    void
    nextToken(
        std::ifstream & fh)
    {
        skipWhite(fh);

        if (fh.peek() == '#') {
            skipLine(fh);
        }
    }

    inline
    std::tuple<long,long>
    readHeader(
        std::ifstream & fh)
    {
        using std::stoi;
        using std::runtime_error;

        auto const magicStr = getToken(fh); nextToken(fh);

        if (magicStr != "P6") {
            throw runtime_error{"Loader only supports PPM P6 format."};
        }

        auto const widthStr = getToken(fh); nextToken(fh);
        auto const heightStr = getToken(fh); nextToken(fh);
        auto const depthStr = getToken(fh);

        if (depthStr != "255") {
            throw runtime_error{"Loader only supports 24-bit color depth."};
        }

        return {
            stoi(widthStr),
            stoi(heightStr),
        };
    }
}

inline
TextureImage
loadPnmFile(
    std::string const & pnmPath)
{
    using namespace pnmParse;

    using std::ios;
    using std::ifstream;

    // Open file
    ifstream fh{pnmPath, ios::binary};

    // Read header
    auto const [ w, h ] = readHeader(fh);

    // Allocate memory
    TextureImage img{w, h};
    Rgb * dat = img.pixels;

    // Read data
    //------------------------------------------------------
    auto r = static_cast<unsigned char>(255);
    auto g = static_cast<unsigned char>(255);
    auto b = static_cast<unsigned char>(255);

    for (long j = h - 1; j >= 0; j--)
    {
        long const offset = j * w;

        for (long i = 0; i < w; i++)
        {
            // Read RGB Value
            r = static_cast<unsigned char>(fh.get());
            g = static_cast<unsigned char>(fh.get());
            b = static_cast<unsigned char>(fh.get());

            // Set Pixel Color
            dat[offset + i] = Rgb{r, g, b};
        }
    }

    return img;
}

inline
void
savePnmFile(
    std::string const & pnmPath,
    Rgb const * pixels,
    int const w,
    int const h,
    int const max_val = 255,
    std::string const format = "P6")
{
    using std::ofstream;
    using std::ios;
    using std::stringstream;

    // Build Header
    auto ss = stringstream{""};

    ss
        << format << "\n"
        << w << " " << h << "\n"
        << max_val << "\n";

    auto const header = ss.str();

    // Open File
    ofstream fh{pnmPath, ios::binary};

    // Write Header
    fh.write(header.c_str(), header.size());

    // Write Data
    //----------------------------------------------------------
    for (long j = h - 1; j >= 0; j--)
    {
        for (long i = 0; i < w; i++)
        {
            auto const p = pixels[j * w + i];

            char const c[3] = {
                static_cast<char>(p.r),
                static_cast<char>(p.g),
                static_cast<char>(p.b)
            };

            fh.write(c, 3);
        }
    }

    fh.flush();
    fh.close();
}

} // namespace CxxRay

#endif
