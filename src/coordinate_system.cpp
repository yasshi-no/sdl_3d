#include <SDL.h>

#include <cmath>
#include <coordinate_system.hpp>
#include <matrix.hpp>

/* Coordinateクラス */
Coordinate::Coordinate(double x, double y, double z) : Matrix(4, 1)
{
    // Matrixに同次座標を格納(列ベクトル)
    set_x(x);
    set_y(y);
    set_z(z);
    set_w(1.0);
}
Coordinate& Coordinate::operator=(Matrix matrix)
{
    *this = Coordinate(matrix[0][0], matrix[1][0], matrix[2][0]);
    return *this;
}
double Coordinate::get_x() const { return v[0][0]; }
double Coordinate::get_y() const { return v[1][0]; }
double Coordinate::get_z() const { return v[2][0]; }
void Coordinate::set_x(double val) { v[0][0] = val; }
void Coordinate::set_y(double val) { v[1][0] = val; }
void Coordinate::set_z(double val) { v[2][0] = val; }
void Coordinate::set_w(double val) { v[3][0] = val; }
/* Perspectiveクラス */
Perspective::Perspective(Coordinate coord, double xy_angle, double yz_angle)
    : coord(coord), xy_angle(xy_angle), yz_angle(yz_angle)
{
}

/* Bodyクラス */
void Body::draw(SDL_Renderer* renderer)
{
    /* 物体を描画する. */
    return;
}
void Body::transform(const Matrix& matrix)
{
    /* 座標を行列変換する. */
    return;
}

/* Lineクラス */
Line::Line(Coordinate coord1, Coordinate coord2)
    : coord1(coord1), coord2(coord2)
{
}
void Line::transform(const Matrix& matrix)
{ /* 座標を行列変換する. */
    coord1 = matrix * coord1;
    coord2 = matrix * coord2;
    SDL_Log("%f %f %f\n", coord1.get_x(), coord1.get_y(), coord1.get_z());
    SDL_Log("%f %f %f\n", coord2.get_x(), coord2.get_y(), coord2.get_z());
    return;
}
void Line::draw(SDL_Renderer* renderer)
{
    /* 直線を描画する. */
    SDL_RenderDrawLine(renderer, coord1.get_x(), coord1.get_y(), coord2.get_x(),
                       coord2.get_y());
    return;
}

/* CoordinateSystemクラス */
Matrix CoordinateSystem::compute_affine_transformation_matrix(
    Perspective perspective)
{
    /* アフィン変換行列を計算する. */
    Matrix ret = compute_yzrotation_matrix(perspective.yz_angle) *
                 compute_xyrotation_matrix(perspective.xy_angle) *
                 compute_translation_matrix(perspective.coord);
    return ret;
}
Matrix CoordinateSystem::compute_translation_matrix(Coordinate coord)
{
    /* 平行移動するための行列を計算する. */
    Matrix ret(4, 4);
    ret.identity();
    ret[0][3] = coord.get_x();
    ret[1][3] = coord.get_y();
    ret[2][3] = coord.get_z();
    return ret;
}
Matrix CoordinateSystem::compute_xyrotation_matrix(double xy_angle)
{
    /* z軸回りの回転のための行列を計算する. */
    Matrix ret(4, 4);
    ret.identity();
    ret[0][0] = cos(xy_angle);
    ret[1][0] = sin(xy_angle);
    ret[0][1] = -sin(xy_angle);
    ret[1][1] = cos(xy_angle);
    return ret;
}
Matrix CoordinateSystem::compute_yzrotation_matrix(double yz_angle)
{
    /* x軸回りの回転のための行列を計算する. */
    Matrix ret(4, 4);
    ret.identity();
    ret[1][1] = cos(yz_angle);
    ret[2][1] = sin(yz_angle);
    ret[1][2] = -sin(yz_angle);
    ret[2][2] = cos(yz_angle);
    return ret;
}
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