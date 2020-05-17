#include "loaders/tga.h"
#include "image/texture_image.h"

#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>

namespace CxxRay {

static
std::string
getDefaultTex()
{
    namespace fs = std::filesystem;

    return ((fs::path{"data"} /= "tex") /= "UVCheckerMap09-512.tga").string();
}

static
std::string
getDefaultOutfile()
{
    namespace fs = std::filesystem;

    return (fs::path{"."} /= "tga_loader_test_output.tga").string();
}

int tgaLoaderTestMain(int argc, char** argv)
{
    std::cout << "tgaLoaderTestMain" << std::endl;

    using std::cout;
    using std::endl;
    using std::string;

    namespace fs = std::filesystem;

    // Input File Arguments
    string infileArg = argc > 1 ? argv[1] : "";

    string infile = infileArg != ""
        ? infileArg
        : getDefaultTex();

    if (!fs::is_regular_file(infile))
    {
        cout << "Invalid input file: " << infile << endl;
        return 1;
    }

    // Output File Arguments
    string outfileArg = argc > 2 ? argv[2] : "";

    string outfile = outfileArg != ""
        ? outfileArg
        : getDefaultOutfile();

    if (!fs::is_directory(fs::path(outfile).parent_path()))
    {
        cout << "Invalid output file: " << outfile << endl;
        return 1;
    }

    // Run Test
    cout << "Loading: " << infile << endl;
    TextureImage img = loadTargaFile(infile);

    cout << "Saving to: " << outfile << endl;
    saveTargaFile(outfile, img.pixels, img.w, img.h);

    return 0;
}

} // namespace CxxRay

int main(int argc, char** argv)
{
    return CxxRay::tgaLoaderTestMain(argc, argv);
}
