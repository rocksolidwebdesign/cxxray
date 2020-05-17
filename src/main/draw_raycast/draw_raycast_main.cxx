#include "meshes.h"

#include "raycast/draw_scene.h"

#include "loaders/ppm.h"
#include "loaders/tga.h"

#include "world/light.h"
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
#include <unordered_map>
#include <vector>

namespace CxxRay {

int drawRaycastMain()
{
    using std::cout;
    using std::endl;

    using std::string;
    using std::vector;
    using std::unordered_map;

    using std::fixed;
    using std::setprecision;

    cout << "Drawing Raycast Scene...\n";

    Profiler timer;
    auto time = timer.stop();

    cout << fixed << setprecision(3);

    //##########################################################
    // Camera Setup
    //##########################################################
        cout << endl << "Setting up camera..." << endl;

        Camera cam{0.0, -2.0, 0.0};

        PixPoint sz{1024, 768};
    //----------------------------------------------------------

    //##########################################################
    // Lights
    //##########################################################
        cout << endl << "Setting up lights..." << endl;

        auto l1 = Light{
            Vec3{-1.0,-0.4,1.0},
            RgbReal{0.8,0.8,0.8}
        };

        vector<Light> lights = { l1 };

        cout << "Lights established..." << endl;
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
            auto meshes = loadTestMeshes(textures);

        time = timer.stop();

        cout << "Mesh load time: " << time << endl;
    //----------------------------------------------------------

    //##########################################################
    // Render
    //##########################################################
        cout << endl << "Drawing scene" << endl;

        timer.start();

            drawRaycastScene(img, cam, lights);

        time = timer.stop();

        cout << "Draw time: " << time << endl;
    //----------------------------------------------------------

    //##########################################################
    // save to file
    //##########################################################
        cout << endl << "Saving image file..." << endl;

        timer.start();

            saveTargaFile("raycast_scene.tga", img.pixels, img.w, img.h);

        time = timer.stop();

        cout << "File write time: " << time << endl;
    //----------------------------------------------------------

    return 0;
}

} // namespace CxxRay

int main()
{
    return CxxRay::drawRaycastMain();
}
