#ifndef CXXRAY_MESH_H
#define CXXRAY_MESH_H

#include "linalg/vec3.h"
#include "linalg/vec4.h"
#include "image/pixel.h"
#include "image/texture_image.h"
#include "rgb/rgb.h"

#include <array>
#include <vector>
#include <unordered_map>

namespace CxxRay {

// material
struct MeshMtl
{
    RgbReal ambient = {0.1, 0.1, 0.1};
    RgbReal diffuse = {1.0, 0.0, 1.0};
    RgbReal specular = {0.0, 0.0, 0.0};
    Real specExp = 0.0;
    std::string texName = "";
};

struct ShadedVertex
{
    Vec4 coord = {1.0, 1.0, 1.0, 1.0};
    Real zval = -1000000000.0;
    RgbReal light = {1.0, 1.0, 1.0};
    Real h = 1.000;
    Real u = 0.001;
    Real v = 0.001;
};

using ShadedTriangle = std::array<ShadedVertex,3>;

struct ShadedFace
{
    MeshMtl const & mtl;
    ShadedTriangle triangle;
};

// vertex lookup record
struct MeshIndex
{
    long long id     = 0;
    long long uvId   = 0;
    long long normId = 0;
};

using MeshFaceIndex = std::array<MeshIndex,3>;

// mesh face information lookup
struct MeshFace
{
    MeshMtl mtl;
    MeshFaceIndex vertexIndexes;
};

struct Mesh
{
    std::unordered_map<std::string,MeshMtl> mtls;
    std::vector<MeshFace> faces = {};
    std::vector<Vec3> verts = {};
    std::vector<Vec3> norms = {};
    std::vector<std::tuple<Real,Real>> uvs = {};
};

} // namespace CxxRay

#endif
