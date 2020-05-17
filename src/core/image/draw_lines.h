#ifndef CXXRAY_CANVAS_DRAW_LINES_H
#define CXXRAY_CANVAS_DRAW_LINES_H

#include "linalg/vec4.h"

#include "image/depth_buf_image.h"
#include "image/pixel.h"
#include "rgb/rgb.h"

#include "global/global.h"

#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <algorithm>
#include <functional>
#include <cmath>

namespace CxxRay {

inline
bool
checkInBounds(
    PixVal const x, PixVal const y,
    PixVal const nx, PixVal const ny)
{
    return (
        x > 0 && x < nx &&
        y > 0 && y < ny
    );
}

inline
std::tuple<PixVal,PixVal,PixVal,PixVal>
lpSortX(
    PixVal const x0, PixVal const y0,
    PixVal const x1, PixVal const y1)
{
    // swap the points such that x0,y0
    // is always to the left
    if (x0 > x1) {
        return {x1,y1,x0,y0};
    }

    return {x0,y0,x1,y1};
}

inline
std::tuple<PixVal,PixVal,PixVal,PixVal>
lpSortY(
    PixVal const x0, PixVal const y0,
    PixVal const x1, PixVal const y1)
{
    // swap the points such that x0,y0
    // is always to bottom
    if (y0 > y1) {
        return {x1,y1,x0,y0};
    }

    return {x0,y0,x1,y1};
}

inline
std::tuple<Real,Real,Real>
lpGetCoef(
    PixVal const x0, PixVal const y0,
    PixVal const x1, PixVal const y1)
{
    // implicit equation of a line
    // f(x, y) = Ax + By + C
    //
    // through two points
    // f(x, y) = (y0 - y1)x + (x1 - x0)y + x0y1 - x1y0

    return {
        y0 - y1, // A
        x1 - x0, // B
        x0*y1 - x1*y0 // C
    };
}

inline
std::function<Real(PixVal,PixVal)>
lpGetFormula(
    Real const A,
    Real const B,
    Real const C)
{
    return [A, B, C](PixVal const x, PixVal const y) {
        return A*static_cast<Real>(x) + B*static_cast<Real>(y) + C;
    };
}

inline
void
drawVerticalLine(
    DepthBufImage & img,
    Rgb const & color,
    PixVal const nx, PixVal const ny,
    PixVal const x0, PixVal const y0,
    PixVal const y1)
{
    auto const is_in_bounds = (
        x0 > 0 &&
        x0 < nx
    );

    if (!is_in_bounds) {
        return;
    }

    auto maxY = y0 > y1 ? y0 : y1;
    auto minY = y0 < y1 ? y0 : y1;

    auto curY = minY;

    while (curY <= maxY)
    {
        auto const is_in_bounds = (
            curY >= 0 &&
            curY < ny
        );

        if (is_in_bounds) {
            img.set(x0, curY, color);
        }

        curY += 1;
    }
}

inline
void
drawHorizontalLine(
    DepthBufImage & img,
    Rgb const & color,
    PixVal const nx, PixVal const ny,
    PixVal const y0, PixVal const x0,
    PixVal const x1)
{
    auto const is_in_bounds = (
        y0 >= 0 &&
        y0 < ny
    );

    if (!is_in_bounds) {
        return;
    }

    auto maxX = x0 > x1 ? x0 : x1;
    auto minX = x0 < x1 ? x0 : x1;

    auto curX = minX;

    while (curX <= maxX)
    {
        auto const is_in_bounds = (
            curX >= 0 &&
            curX < nx
        );

        if (is_in_bounds) {
            img.set(curX, y0, color);
        }

        curX += 1;
    }
}

inline
void
drawLineShallow(
    DepthBufImage & img,
    Rgb const & color,
    PixVal const nx,  PixVal const ny,
    PixVal const x0_, PixVal const y0_,
    PixVal const x1_, PixVal const y1_)
{
    // make sure we always draw left to right
    auto const [ x0, y0, x1, y1 ] = lpSortX(x0_, y0_, x1_, y1_);

    // get formula for an implicit line
    auto const [ A, B, C ] = lpGetCoef(x0, y0, x1, y1);

    // always fill in the last pixel
    if (checkInBounds(x1, y1, nx, ny)) {
        img.set(x1, y1, color);
    }

    // find whether the slope is positive or negative
    Real const slope =
        static_cast<Real>(y1 - y0) /
        static_cast<Real>(x1 - x0);

    bool const is_up = slope > 0.0;

    // shallow slope, more run than rise
    // so draw from left to right
    //
    // the y increment will be positive for an
    // up slope and negative for a downslope
    PixVal const y_inc = is_up ? 1 : -1;

    // the midpoint check moves downwards on a downslope
    Real const mp = is_up ? 0.5 : -0.5;

    PixVal curX = x0;
    PixVal curY = y0;

    while (curX < x1)
    {
        if (checkInBounds(curX, curY, nx, ny)) {
            img.set(curX, curY, color);
        }

        // evaluate the function at the midpoint
        // between the next pixel directly to the right and
        // the next pixel diagonally right-up or right-down
        auto const val_at_midp =
            A * (static_cast<Real>(curX) + 1.0) +
            B * (static_cast<Real>(curY) + mp) +
            C;

        // if the point is on the line, the val
        // will be zero, otherwise the point
        // is either above or below the line
        // depending on sign
        auto const should_inc = is_up
            // if the line slope is up, we
            // will mostly be below the line
            // as we go to the right, and we
            // only want to check whether we should move
            // the line upwards by one pixel,
            // i.e. whether the evaluated point is below the line
            ? (val_at_midp < 0.0)

            // if the line slope is down, we
            // will mostly be above the line
            // as we go to the right, and we
            // only want to check whether we should move
            // the line downwards by one pixel,
            // i.e. whether the evaluated point is above the line
            : (val_at_midp > 0.0);

        if (should_inc) {
            curY += y_inc;
        }

        curX += 1;
    }
}

inline
void
drawLineSteep(
    DepthBufImage & img,
    Rgb const & color,
    PixVal const nx, PixVal const ny,
    PixVal const x0_, PixVal const y0_,
    PixVal const x1_, PixVal const y1_)
{
    // make sure we always draw bottom to top
    auto const [ x0, y0, x1, y1 ] = lpSortY(x0_, y0_, x1_, y1_);

    // get formula for an implicit line
    auto const [ A, B, C ] = lpGetCoef(x0, y0, x1, y1);

    // always fill in the last pixel
    if (checkInBounds(x1, y1, nx, ny)) {
        img.set(x1, y1, color);
    }

    // find whether the slope is positive or negative
    Real const slope =
        static_cast<Real>(y1 - y0) /
        static_cast<Real>(x1 - x0);
    bool const is_up = slope > 0.0;

    // steep slope, more rise than run
    // so draw from bottom to top
    //
    // the x increment will be positive for an
    // up slope and negative for a downslope
    PixVal const x_inc = is_up ? 1 : -1;

    // the midpoint check moves leftwards on a downslope
    Real const mp = is_up ? 0.5 : -0.5;

    PixVal curX = x0;
    PixVal curY = y0;

    while (curY < y1)
    {
        if (checkInBounds(curX, curY, nx, ny)) {
            img.set(curX, curY, color);
        }

        // evaluate the function at the midpoint
        // between the next the next pixel directly up and
        // pixel diagonally up-right (or up-left)
        auto const val_at_midp =
            A * (static_cast<Real>(curX) + mp) +
            B * (static_cast<Real>(curY) + 1.0) +
            C;

        // if the point is on the line, the val
        // will be zero, otherwise the point
        // is either above or below the line
        // depending on sign
        auto const should_inc = is_up
            // if the line slope is up, we
            // will mostly be left of the line
            // as we go from bottom to top, and
            // only want to check whether we should move
            // the line rightwards by one pixel,
            // i.e. whether the line is to the right of the
            // evaluated midpoint which is to say the
            // point is left of the line
            ? (val_at_midp > 0)

            // if the line slope is down, we
            // will mostly be right of the line
            // as we go from bottom to top, and
            // only want to check whether we should move
            // the line leftwards by one pixel,
            // i.e. whether the line is to the left of the
            // evaluated midpoint which is to say the
            // point is right of the line
            : (val_at_midp < 0);

        if (should_inc) {
            curX += x_inc;
        }

        curY += 1;
    }
}

inline
void
drawLine(
    DepthBufImage & img,
    Rgb const & color,
    PixPoint const & a,
    PixPoint const & b)
{
    auto x0 = a.x;
    auto y0 = a.y;

    auto x1 = b.x;
    auto y1 = b.y;

    auto nx = img.w;
    auto ny = img.h;

    // check the pieces of the fraction
    // representing the slope for
    // special cases such as infinite
    // or zero slope
    auto const numerator = y1 - y0;
    auto const divisor = x1 - x0;

    if (numerator == 0 && divisor == 0)
    {
        // the points are the same so just
        // draw a pixel at that point
        if (checkInBounds(x0, y0, nx, ny)) {
            img.set(x0, y0, color);
        }

        return;
    }
    else if (divisor == 0)
    {
        drawVerticalLine(img, color, nx, ny, x0, y0, y1);
        return;
    }
    else if (numerator == 0)
    {
        drawHorizontalLine(img, color, nx, ny, y0, x0, x1);
        return;
    }

    Real const slope =
        static_cast<Real>(numerator) /
        static_cast<Real>(divisor);

    if (slope >= -1.0 && slope <= 1.0)
    {
        drawLineShallow(img, color, nx, ny, x0, y0, x1, y1);
        return;
    }

    drawLineSteep(img, color, nx, ny, x0, y0, x1, y1);
}

inline
void
drawLine(
    DepthBufImage & img,
    Rgb const & color,
    Vec4 const & a,
    Vec4 const & b)
{
    using std::round;

    auto ax = round(a.x / a.h);
    auto ay = round(a.y / a.h);
    auto bx = round(b.x / b.h);
    auto by = round(b.y / b.h);

    auto x0 = static_cast<long>(ax);
    auto y0 = static_cast<long>(ay);

    auto x1 = static_cast<long>(bx);
    auto y1 = static_cast<long>(by);

    drawLine(img, color,
        PixPoint{x0, y0},
        PixPoint{x1, y1});
}

} // namespace CxxRay

#endif
