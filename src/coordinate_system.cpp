#include <SDL.h>

#include <coordinate_system.hpp>
#include <matrix.hpp>

Coordinate::Coordinate(double x, double y, double z) : Matrix(4, 1)
{
    // Matrixに同次座標を格納(列ベクトル)
    (*this)[0][0] = x;
    (*this)[1][0] = y;
    (*this)[2][0] = z;
    (*this)[3][0] = 1.0;
}

void Body::draw(SDL_Renderer* renderer) { SDL_Log("wrong"); }

Line::Line(Coordinate coord1, Coordinate coord2)
    : coord1(coord1), coord2(coord2)
{
}

void Line::draw(SDL_Renderer* renderer)
{
    SDL_Log("%f, %f, %f, %f\n", coord1[0][0], coord1[1][0], coord2[0][0],
            coord2[1][0]);
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