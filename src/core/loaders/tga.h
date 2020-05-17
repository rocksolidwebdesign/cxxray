#ifndef CXXRAY_TGA_LOADER_H
#define CXXRAY_TGA_LOADER_H

#include "image/texture_image.h"
#include "image/pixel.h"
#include "rgb/rgb.h"
#include "utils/data_array.h"

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stdexcept>

namespace CxxRay {

namespace tgaParse
{
    struct TargaHeader
    {
        char    idLen = 0;
        char    cmType = 0;
        char    dataType = 2;
        int16_t cmOrigin = 0;
        int16_t cmLen = 0;
        char    cmDepth = 0;
        int16_t xOrigin = 0;
        int16_t yOrigin = 0;
        int16_t w = 0;
        int16_t h = 0;
        char    depth = 24;
        char    id = 0;

        std::string descr = "";
        std::string colormap = "";

        TargaHeader()
           : w{0}
           , h{0}
        {
        }

        TargaHeader(long w_, long h_)
           : w{static_cast<int16_t>(w_)}
           , h{static_cast<int16_t>(h_)}
        {
        }
    };

    std::string
    toString(
        TargaHeader const & h)
    {
        std::stringstream ss{""};

        ss << std::endl;
        ss << "h.idLen: " << short(h.idLen) << std::endl;
        ss << "h.cmType: " << short(h.cmType) << std::endl;
        ss << "h.dataType: " << short(h.dataType) << std::endl;
        ss << "h.cmOrigin: " << h.cmOrigin << std::endl;
        ss << "h.cmLen: " << h.cmLen << std::endl;
        ss << "h.cmDepth: " << short(h.cmDepth) << std::endl;
        ss << "h.xOrigin: " << h.xOrigin << std::endl;
        ss << "h.yOrigin: " << h.yOrigin << std::endl;
        ss << "h.width: " << h.w << std::endl;
        ss << "h.height: " << h.h << std::endl;
        ss << "h.depth: " << short(h.depth) << std::endl;
        ss << "h.id: " << short(h.id) << std::endl;

        return ss.str();
    }

    inline
    TargaHeader
    readHeader(
        std::ifstream & fh)
    {
        TargaHeader header;

        header.idLen = static_cast<char>(fh.get());
        header.cmType = static_cast<char>(fh.get());
        header.dataType = static_cast<char>(fh.get());

        fh.read(reinterpret_cast<char*>(&header.cmOrigin), 2);
        fh.read(reinterpret_cast<char*>(&header.cmLen), 2);

        header.cmDepth = static_cast<char>(fh.get());

        fh.read(reinterpret_cast<char*>(&header.xOrigin), 2);
        fh.read(reinterpret_cast<char*>(&header.yOrigin), 2);

        fh.read(reinterpret_cast<char*>(&header.w), 2);
        fh.read(reinterpret_cast<char*>(&header.h), 2);

        header.depth = static_cast<char>(fh.get());

        header.id = static_cast<char>(fh.get());

        if (int(header.idLen) > 0) {
            std::string strBuf(header.idLen, ' ');

            fh.read(strBuf.data(), header.idLen);

            header.descr = strBuf;
        }

        auto const cmSz = header.cmType * header.cmLen;
        if (cmSz > 0) {
            std::string strBuf(cmSz, ' ');

            fh.read(strBuf.data(), cmSz);

            header.colormap = strBuf;
        }

        return header;
    }

    inline char wordLo( int16_t x) {
        return static_cast<char>(x & 0x00FF);
    }

    inline char wordHi(int16_t x) {
        return static_cast<char>((x & 0xFF00) / 256);
    }

    inline
    void
    writeHeader(
        std::ofstream & fh,
        TargaHeader const & header)
    {
        char buf[18] = {
            header.idLen, // no image descriptor
            header.cmType,
            header.dataType,
            wordLo(header.cmOrigin), // low byte first
            wordHi(header.cmOrigin), // then the high byte
            wordLo(header.cmLen), // low byte first
            wordHi(header.cmLen), // then the high byte
            header.cmDepth,
            wordLo(header.xOrigin), // low byte first
            wordHi(header.xOrigin), // then the high byte
            wordLo(header.yOrigin), // low byte first
            wordHi(header.yOrigin), // then the high byte
            wordLo(header.w), // low byte first
            wordHi(header.w), // then the high byte
            wordLo(header.h),
            wordHi(header.h),
            header.depth,
            header.id
        };

        fh.write(buf, 18);
    }
}

inline
TextureImage
loadTargaFile(
    std::string const & filePath)
{
    using namespace tgaParse;

    using std::ifstream;
    using std::runtime_error;

    ifstream fh{filePath, ::std::ios::binary};

    if (!fh.good()) {
        throw std::runtime_error{"ERROR OPENING: " + filePath};
    }

    auto header = readHeader(fh);

    if (static_cast<int>(header.dataType) != 2) {
        throw runtime_error{"TGA Loader only supports uncompressed RGB format."};
    }

    if (static_cast<int>(header.depth) != 24) {
        throw runtime_error{"TGA Loader only supports 24-bit color depth."};
    }

    auto const w = header.w;
    auto const h = header.w;

    TextureImage img{w, h};
    Rgb * pixels = img.pixels;

    for (long row = 0; row < h; row++)
    {
        for (long col = 0; col < w; col++)
        {
            if (fh.eof()) {
                return img;
            }

            Rgb p{};

            p.b = static_cast<char>(fh.get());
            p.g = static_cast<char>(fh.get());
            p.r = static_cast<char>(fh.get());

            pixels[row * w + col] = p;
        }
    }

    return img;
}

inline
void
saveTargaFile(
    std::string const & filePath,
    Rgb const * pixels,
    long const w,
    long const h)
{
    using namespace tgaParse;
    using std::ios;
    using std::ofstream;

    // initialize a header instance
    TargaHeader header{w, h};

    // open the file in binary mode
    ofstream fh{filePath, ios::binary};

    // write the header to the file
    writeHeader(fh, header);

    // write image data to the file
    for (long row = 0; row < h; row++)
    {
        for (long col = 0; col < w; col++)
        {
            auto const p = pixels[row * w + col];

            fh.put(p.b);
            fh.put(p.g);
            fh.put(p.r);
        }
    }

    fh.flush();
    fh.close();
}

} // namespace CxxRay

#endif
