#include "meshes.h"

#include "raster/draw_scene.h"

#include "loaders/tga.h"

#include "world/mesh.h"
#include "world/camera.h"
#include "world/view_volume.h"

#include "image/depth_buf_image.h"
#include "image/pixel.h"

#include "rgb/rgb.h"

#include "utils/profiler.h"
#include "utils/strings.h"

#include "global/global.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

namespace CxxRay {

static
std::string
getDefaultTex()
{
    namespace fs = std::filesystem;

    return ((fs::path{"data"} /= "tex") /= "UVCheckerMap01-512.tga").string();
}

static
std::string
getDefaultPath()
{
    namespace fs = std::filesystem;

    return ((fs::path{"data"} /= "models") /= "monkey.obj").string();
}

int drawRasterMain(int argc, char** argv)
{
    using std::cout;
    using std::endl;

    using std::string;
    using std::vector;
    using std::unordered_map;
    using std::for_each;

    using std::fixed;
    using std::setprecision;

    namespace fs = std::filesystem;

    std::cout << "Drawing Raster Scene...\n";

    Profiler timer;
    auto time = timer.stop();

    //##########################################################
    // Command Line Arguments
    //##########################################################
    string infileArg = argc > 1 ? argv[1] : "";

    string infile = infileArg != ""
        ? infileArg
        : getDefaultPath();

    if (!fs::is_regular_file(infile))
    {
        cout << "Invalid model file: " << infile << endl;
        return 1;
    }

    string texfile = argc > 2
        ? argv[2]
        : getDefaultTex();

    std::cout << "texfile: " << texfile << std::endl;

    if (texfile != "" && !fs::is_regular_file(texfile))
    {
        cout << "Invalid texture file: " << texfile << endl;
        return 1;
    }

    //##########################################################
    // Scene Setup
    //##########################################################
        ViewVolume vvol{};

        Camera cam{5.0029999, -5.29348290, 5.102934};

        PixPoint sz{1200, 900};

        vector<Light> lights{
            Light{
                Vec3{4.07625, 1.00545, 5.90386},
                RgbReal{0.8, 0.8, 0.8},
            },
        };
    //----------------------------------------------------------

    //##########################################################
    // Allocate Image
    //##########################################################
        cout << endl << "Allocating image" << endl;

        timer.start();

            DepthBufImage img{sz};

        time = timer.stop();

        cout << "Allocation time: " << time << endl;
    //----------------------------------------------------------

    //##########################################################
    // Load Meshes
    //##########################################################
        cout << endl << "Loading meshes..." << endl;

        timer.start();

            unordered_map<string,TextureImage> textures;

            Mesh mesh = loadWavefrontObjFile(infile, textures);

            if (texfile != "") {
                textures[texfile] = loadTargaFile(texfile);

                auto & faces = mesh.faces;

                for_each(faces.begin(), faces.end(),
                    [&texfile](auto & face) {
                        face.mtl.texName = texfile;
                    });
            }

            vector<Mesh> meshes = { mesh };

        time = timer.stop();

        cout << "Mesh load time: " << time << endl;
    //----------------------------------------------------------

    //##########################################################
    // Render
    //##########################################################
        cout << endl << "Drawing scene" << endl;

        timer.start();

            auto const [
                M,
                M_cam
            ] = getViewTransforms(cam, sz, vvol);

            drawColorScene(
                img,
                lights,
                meshes,
                textures,
                M,
                M_cam);

        time = timer.stop();

        cout << "Draw time: " << time << endl;
    //----------------------------------------------------------

    ////////////////////////////////////////////////////////////
    // save to file
    ////////////////////////////////////////////////////////////
        cout << endl << "Saving image file..." << endl;

        timer.start();

            saveTargaFile("raster_scene.tga", img.pixels, img.w, img.h);

        time = timer.stop();

        cout << "File write time: " << time << endl;

    return 0;
}

} // namespace CxxRay

int main(int argc, char** argv)
{
    return CxxRay::drawRasterMain(argc, argv);
}
