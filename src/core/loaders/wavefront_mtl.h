#ifndef CXXRAY_LOAD_WAVEFRONT_MTL_H
#define CXXRAY_LOAD_WAVEFRONT_MTL_H

#include "world/mesh.h"
#include "utils/strings.h"
#include "loaders/tga.h"

#include <string>
#include <unordered_map>

#include <regex>
#include <sstream>
#include <fstream>
#include <iostream>
#include <utility>

namespace CxxRay {

inline
void loadWavefrontMtlFile(
    Mesh & mesh,
    std::string const & filePathArg,
    std::unordered_map<std::string,TextureImage> & textures)
{
    using std::cout;
    using std::endl;

    using std::string;
    using std::stringstream;
    using std::ifstream;
    using std::getline;

    using std::regex;
    using std::regex_match;
    using std::smatch;

    using std::stod;

    // TODO: support multi-object files
    MeshMtl mtl;

    regex pat_newmtl{"newmtl (.*)"};

    regex pat_map_Kd{"map_Kd (.*)"};

    // diffuse reflectivity (surface color)
    regex pat_Kd{"Kd (-?\\d+\\.\\d+) (-?\\d+\\.\\d+) (-?\\d+\\.\\d+)"};

    // ambient reflectivity
    regex pat_Ka{"Ka (-?\\d+\\.\\d+) (-?\\d+\\.\\d+) (-?\\d+\\.\\d+)"};

    // specular reflectivity
    regex pat_Ks{"Ks (-?\\d+\\.\\d+) (-?\\d+\\.\\d+) (-?\\d+\\.\\d+)"};

    // specular exponent
    regex pat_Ns{"Ns (-?\\d+\\.\\d+)"};

    // dissolve amount (opacity)
    //regex pat_d{"d (-?\\d+\\.\\d+)"};

    // optical density
    //regex pat_Ni{"d (-?\\d+\\.\\d+)"};

    // illumination model
    //regex pat_illum{"illum (\\d+)"};

    string line{""};
    string tok{""};

    auto fh = ifstream{filePathArg};

    if (!fh.is_open()) {
        cout << "loadWavefrontMtlFile(): File not found " << filePathArg << endl;
        return;
    }

    string mtlName = "no_mtl";
    mesh.mtls[mtlName] = MeshMtl{};

    while (!fh.eof()) {
        getline(fh, line);

        trim(line);
        strip_comments(line);

        if (line.size() == 0) {
            continue;
        }

        stringstream ss{line};
        ss >> tok;

        smatch m;
        if (tok == "newmtl")
        {
            if (!regex_match(line, m, pat_newmtl))
            {
                cout << "INVALID MATERIAL NAME" << endl;
                continue;
            }

            mtlName = m[1];
            mesh.mtls[mtlName] = MeshMtl{};
        }
        else if (tok == "map_Kd")
        {
            if (!regex_match(line, m, pat_map_Kd))
            {
                cout << "INVALID TEXTURE FILENAME" << endl;
                continue;
            }

            string const texPath = m[1];

            if (textures.count(texPath) == 0)
            {
                cout << "Loading texture: " << texPath << endl;

                textures[texPath] = loadTargaFile(texPath);
            }

            mesh.mtls[mtlName].texName = texPath;
        }
        else if (tok == "Kd")
        {
            if (!regex_match(line, m, pat_Kd))
            {
                cout << "INVALID DIFFUSE COLOR" << endl;
                continue;
            }

            auto const r = stod(m[1]);
            auto const g = stod(m[2]);
            auto const b = stod(m[3]);

            auto const c = RgbReal{ r, g, b };

            cout << "Diffuse Color: " << c << endl;

            mesh.mtls[mtlName].diffuse = c;
        }
        else if (tok == "Ka")
        {
            if (!regex_match(line, m, pat_Ka))
            {
                cout << "INVALID AMBIENT COLOR" << endl;
                continue;
            }

            mesh.mtls[mtlName].ambient = RgbReal{
                stod(m[1]),
                stod(m[2]),
                stod(m[3])
            };
        }
        else if (tok == "Ks")
        {
            if (!regex_match(line, m, pat_Ks))
            {
                cout << "INVALID SPECULAR COLOR" << endl;
                continue;
            }

            mesh.mtls[mtlName].specular = RgbReal{
                stod(m[1]),
                stod(m[2]),
                stod(m[3])
            };
        }
        else if (tok == "Ns")
        {
            if (!regex_match(line, m, pat_Ns))
            {
                cout << "INVALID SPECULAR EXPONENT" << endl;
                continue;
            }

            mesh.mtls[mtlName].specExp = stod(m[1]);
        }
    }
}

} // namespace CxxRay

#endif
