#ifndef CXXRAY_RASTER_DRAW_SCENE_H
#define CXXRAY_RASTER_DRAW_SCENE_H

#include "raster/vertex_shader.h"
#include "raster/fragment_shader.h"
#include "image/draw_lines.h"
#include "world/mesh.h"
#include "world/light.h"
#include "world/camera.h"
#include "world/view_volume.h"
#include "image/depth_buf_image.h"
#include "utils/profiler.h"
#include "linalg/linalg.h"

#include <iostream>
#include <ios>
#include <iomanip>
#include <string>
#include <array>
#include <vector>
#include <algorithm>
#include <cmath>

namespace CxxRay {

using ViewTransforms = std::tuple<Mat4,Mat4>;

inline
ViewTransforms
getViewTransforms(
    Camera const & cam,
    PixPoint const & sz,
    ViewVolume const & v)
{
    auto const M_vp = tform_vp(
        static_cast<Real>(sz.x),
        static_cast<Real>(sz.y)
    );

    auto const M_per = tform_per(v.right, v.left, v.top, v.bot, v.near, v.far);
    auto const M_cam = tform_camera(cam.B.e, cam.B.w, cam.B.u, cam.B.v);

    auto const M = M_vp * M_per * M_cam;

    // send the composite transform
    // and the camera transform separately
    // so we can get z-coords in camera
    // space to avoid z-fighting
    return {
        M,
        M_cam,
    };
}

inline
int
drawColorScene(
    DepthBufImage & img,
    std::vector<Light> const & lights,
    std::vector<Mesh> const & meshes,
    std::unordered_map<std::string,TextureImage> & textures,
    Mat4 const & M,
    Mat4 const & M_cam)
{
    using std::cout;
    using std::endl;
    using std::vector;

    cout << "drawColorScene()" << endl;

    Profiler timer;
    auto time = timer.stop();

    ////////////////////////////////////////////////////////////
    // Drawing
    ////////////////////////////////////////////////////////////
    cout << "shading vertexes..." << endl;

    vector<ShadedFace> shadedFaces;

    timer.start();
    for (auto const & mesh : meshes)
    {
        auto const & verts = mesh.verts;
        auto const & norms = mesh.norms;
        auto const & uvs = mesh.uvs;

        // there may be many materials, but for now
        // we'll only ever use the first one.
        //
        // the textures are stored in a hash which
        // gives a pair where the second item in
        // the pair is the actual material object
        for (auto const & face : mesh.faces)
        {
            auto const & I = face.vertexIndexes;

            shadedFaces.push_back({
                face.mtl,
                ShadedTriangle{
                    vertexShaderProgram(M, M_cam, lights, verts[I[0].id - 1], norms[I[0].normId - 1], uvs[I[0].uvId - 1]),
                    vertexShaderProgram(M, M_cam, lights, verts[I[1].id - 1], norms[I[1].normId - 1], uvs[I[1].uvId - 1]),
                    vertexShaderProgram(M, M_cam, lights, verts[I[2].id - 1], norms[I[2].normId - 1], uvs[I[2].uvId - 1])
                },
            });
        }
    }

    time = timer.stop();

    cout << "vertex shader time: " << time << endl;

    cout << "shading fragments..." << endl;

    timer.start();

    for (auto const & face : shadedFaces)
    {
        fragementShaderProgram(img, face, textures);
    }

    time = timer.stop();

    cout << "fragment shader time: " << time << endl;

    // the fragment shader needs
    // vertex material info (color, texture)
    // vertex position info
    // vertex light intensity info

    // draw each 3D object, probably loaded
    // from a file on disk
    //for (auto const & mesh : meshes) {
    //    auto const & verts = mesh.verts;
    //    auto const & norms = mesh.norms;

    //    // draw each triangle of the 3D object
    //    for (auto const & face : mesh.faces) {
    //        // get the 3 vertices of the triangle face

    //        auto const & avtx = verts[face.a.id - 1];
    //        auto const & bvtx = verts[face.b.id - 1];
    //        auto const & cvtx = verts[face.c.id - 1];

    //        // get the normal vector
    //        auto const & an = norms[face.a.normId - 1];
    //        auto const & bn = norms[face.b.normId - 1];
    //        auto const & cn = norms[face.c.normId - 1];

    //        // light intensity =
    //        //   cos of angle (dot product) between
    //        //   - surf-point to light-point vector and
    //        //   - surf-normal vector
    //        auto const & lpos = light.pos;

    //        Vec3 const lveca = unit(lpos - avtx);
    //        Vec3 const lvecb = unit(lpos - bvtx);
    //        Vec3 const lvecc = unit(lpos - cvtx);

    //        Real const anga = dot(lveca, an);
    //        Real const angb = dot(lvecb, bn);
    //        Real const angc = dot(lvecc, cn);

    //        Real const la = anga > 0.0 ? anga : 0.0;
    //        Real const lb = angb > 0.0 ? angb : 0.0;
    //        Real const lc = angc > 0.0 ? angc : 0.0;

    //        auto const & mtl = face.mtl;

    //        shadeFragments(
    //            img, mtl,
    //            la, lb, lc,
    //            avtx, bvtx, cvtx,
    //            M, M_cam
    //        );
    //    }
    //}

    return 0;
}

inline
int
drawRasterAxes(
    DepthBufImage & img,
    Mat4 M)
{
    ////////////////////////////////////////////////////////////
    // Scene Objects
    ////////////////////////////////////////////////////////////
    auto const o = Vec4{0.0, 0.0, 0.0, 1.0};
    auto const x = Vec4{0.3, 0.0, 0.0, 1.0};
    auto const y = Vec4{0.0, 0.3, 0.0, 1.0};
    auto const z = Vec4{0.0, 0.0, 0.3, 1.0};

    auto const cx = Rgb{200, 0, 0}; // red
    auto const cy = Rgb{0, 200, 0}; // green
    auto const cz = Rgb{0, 0, 200}; // blue

    ////////////////////////////////////////////////////////////
    // Transformations
    ////////////////////////////////////////////////////////////
    auto const O = M * o;
    auto const X = M * x;
    auto const Y = M * y;
    auto const Z = M * z;

    ////////////////////////////////////////////////////////////
    // Drawing
    ////////////////////////////////////////////////////////////
    drawLine(img, cx, O, X);
    drawLine(img, cy, O, Y);
    drawLine(img, cz, O, Z);

    return 0;
}

} // namespace CxxRay

#endif
