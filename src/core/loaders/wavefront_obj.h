#ifndef CXXRAY_WAVEFRONT_OBJ_H
#define CXXRAY_WAVEFRONT_OBJ_H

#include "wavefront_mtl.h"

#include "world/mesh.h"
#include "utils/strings.h"

#include <string>
#include <regex>
#include <sstream>
#include <fstream>
#include <iostream>
#include <filesystem>

namespace CxxRay {

inline
Mesh
loadWavefrontObjFile(
    std::string const & filePath,
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
    using std::stoll;

    namespace fs = std::filesystem;

    Mesh mesh;

    regex pat_usemtl{"usemtl (.*)"};
    regex pat_mtllib{"mtllib (.*)"};
    regex pat_o{"o (.*)"};
    regex pat_v{"v (-?\\d+\\.\\d+) (-?\\d+\\.\\d+) (-?\\d+\\.\\d+) ?(-?\\d+\\.\\d+)?"};
    regex pat_vn{"vn (-?\\d+\\.\\d+) (-?\\d+\\.\\d+) (-?\\d+\\.\\d+) ?(-?\\d+\\.\\d+)?"};
    regex pat_vt{"vt (-?\\d+\\.\\d+) (-?\\d+\\.\\d+)"};
    regex pat_f{"f (\\d+)/?(\\d+)?/?(\\d+)? (\\d+)/?(\\d+)?/?(\\d+)? (\\d+)/?(\\d+)?/?(\\d+)?"};

    string line = "";
    string tok = "";

    auto fileName = fs::path{filePath}.filename().string();
    auto fileDir = fs::path{filePath}.parent_path().string();

    auto fh = ifstream{filePath};

    if (!fh.is_open()) {
        cout << "loadMeshOBJ(): File not found " << filePath << endl;
        return mesh;
    }

    string mtlName = "no_mtl";

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
        if (tok == "mtllib")
        {
            if (!regex_match(line, m, pat_mtllib))
            {
                cout << "INVALID MTL LIB" << endl;
                continue;
            }

            string mtlLibName = m[1];
            string mtlLibPath = (fs::path{fileDir} /= mtlLibName).string();

            loadWavefrontMtlFile(mesh, mtlLibPath, textures);
        }
        else if (tok == "v")
        {
            if (!regex_match(line, m, pat_v))
            {
                cout << "INVALID VERTEX" << endl;
                continue;
            }

            mesh.verts.push_back(Vec3{
                stod(m[1]),
                stod(m[2]),
                stod(m[3])
            });
        }
        else if (tok == "vn")
        {
            if (!regex_match(line, m, pat_vn))
            {
                cout << "INVALID NORMAL" << endl;
                continue;
            }

            mesh.norms.push_back(Vec3{
                stod(m[1]),
                stod(m[2]),
                stod(m[3])
            });
        }
        else if (tok == "vt")
        {
            if (!regex_match(line, m, pat_vt))
            {
                cout << "INVALID UV COORD" << endl;
                continue;
            }

            mesh.uvs.push_back({
                stod(m[1]),
                stod(m[2])
            });
        }
        else if (tok == "usemtl")
        {
            if (!regex_match(line, m, pat_usemtl))
            {
                cout << "INVALID MTL NAME" << endl;
                continue;
            }

            mtlName = m[1];
        }
        else if (tok == "f")
        {
            if (!regex_match(line, m, pat_f))
            {
                cout << "INVALID FACE" << endl;
                continue;
            }

            // The first reference number is the geometric vertex.
            // * The second reference number is the texture vertex. It follows the first slash.
            // * The third reference number is the vertex normal. It follows the second slash.

            MeshFace face{
                mesh.mtls[mtlName],
                {
                    MeshIndex{
                        stoll(m[1]),
                        m[2] != "" ? stoll(m[2]) : 0,
                        m[3] != "" ? stoll(m[3]) : 0
                    },
                    MeshIndex{
                        stoll(m[4]),
                        m[5] != "" ? stoll(m[5]) : 0,
                        m[6] != "" ? stoll(m[6]) : 0
                    },
                    MeshIndex{
                        stoll(m[7]),
                        m[8] != "" ? stoll(m[8]) : 0,
                        m[9] != "" ? stoll(m[9]) : 0
                    }
                }
            };

            mesh.faces.push_back(face);
        }
    }

    return mesh;
}

} // namespace CxxRay

#endif
