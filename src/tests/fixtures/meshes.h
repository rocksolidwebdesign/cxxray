#ifndef CXXRAY_TESTS_FIXTURES_MESHES_H
#define CXXRAY_TESTS_FIXTURES_MESHES_H

#include "world/mesh.h"
#include "loaders/wavefront_obj.h"

#include <filesystem>

namespace CxxRay {

inline
Mesh
loadTestMesh(
    std::string const & fileName,
    std::unordered_map<std::string,TextureImage> & textures)
{
    namespace fs = std::filesystem;

    auto filePath =
        fs::path{"data"} /= "models";

    filePath /= fileName;

    return loadWavefrontObjFile(filePath.string(), textures);
}

inline
std::vector<Mesh>
loadTestMeshes(
    std::unordered_map<std::string,TextureImage> & textures)
{
    auto meshes = std::vector<Mesh>{};

    auto mesh = loadTestMesh("icosphere.obj", textures);

    meshes.push_back(mesh);

    return meshes;
}

} // namespace CxxRay

#endif
