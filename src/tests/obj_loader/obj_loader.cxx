#include "loaders/wavefront_obj.h"
#include "image/texture_image.h"

#include <iostream>
#include <filesystem>
#include <string>

namespace CxxRay {

static
std::string
getDefaultPath()
{
    namespace fs = std::filesystem;

    return ((fs::path{"data"} /= "models") /= "icosphere.obj").string();
}

int objLoaderTestMain(int argc, char** argv)
{
    using std::cout;
    using std::endl;
    using std::string;
    using std::unordered_map;

    namespace fs = std::filesystem;

    cout << "Test OBJ Loader" << endl;

    // Input File Arguments
    string infileArg = argc > 1 ? argv[1] : "";

    string infile = fs::absolute((infileArg != ""
        ? infileArg
        : getDefaultPath())).make_preferred().string();

    if (!fs::is_regular_file(infile))
    {
        cout << "Invalid input file: " << infile << endl;
        return 1;
    }

    // Run Test
    cout << "Loading: " << infile << endl;

    unordered_map<string,TextureImage> textures;

    auto obj = loadWavefrontObjFile(infile, textures);

    return 0;
}

} // namespace CxxRay

int main(int argc, char** argv)
{
    return CxxRay::objLoaderTestMain(argc, argv);
}
