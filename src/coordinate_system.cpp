#include <SDL.h>

#include <coordinate_system.hpp>
#include <matrix.hpp>

/* Coordinateクラス */
Coordinate::Coordinate(double x, double y, double z) : Matrix(4, 1)
{
    // Matrixに同次座標を格納(列ベクトル)
    (*this)[0][0] = x;
    (*this)[1][0] = y;
    (*this)[2][0] = z;
    (*this)[3][0] = 1.0;
}
Coordinate& Coordinate::operator=(Matrix matrix)
{
    *this = Coordinate(matrix[0][0], matrix[1][0], matrix[2][0]);
    return *this;
}

/* Bodyクラス */
void Body::draw(SDL_Renderer* renderer)
{
    /* 物体を描画する. */
    return;
}
void Body::transform(Matrix matrix)
{
    /* 座標を行列変換する. */
    return;
}

/* Lineクラス */
Line::Line(Coordinate coord1, Coordinate coord2)
    : coord1(coord1), coord2(coord2)
{
}
void Line::transform(Matrix matrix)
{ /* 座標を行列変換する. */
    coord1 = matrix * coord1;
    coord2 = matrix * coord2;
    return;
}

/* Lineクラス */
void Line::draw(SDL_Renderer* renderer)
{
    /* 直線を描画する. */
    SDL_RenderDrawLine(renderer, coord1[0][0], coord1[1][0], coord2[0][0],
                       coord2[1][0]);
    return;
}

/* CoordinateSystemクラス */
#ifndef NDEBUG
void CoordinateSystem::draw_debug(SDL_Renderer* renderer)
{
    for(Body* body : bodys) {
        body->draw(renderer);
    }
}
#endif

/* ScreenCoordinateSystemクラス */
#ifndef NDEBUG
ScreenCoordinateSystem::ScreenCoordinateSystem(int width, int height)
    : width(width), height(height)
{
}
void ScreenCoordinateSystem::add_body(Body* body) { bodys.push_back(body); }
#endif