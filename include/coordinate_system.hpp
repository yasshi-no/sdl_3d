#pragma once

#include <matrix.hpp>
#include <vector>

using namespace std;

class Coordinate : public Matrix
{
    /* 3次元を表現する同次座標 */
public:
    Coordinate(double x, double y, double z);
};

class Perspective
{
    /* 視点の座標と方向 */
private:
    Coordinate coord;
    double xy_angle;
    double yz_angle;

public:
    Perspective(Coordinate coord, double xy_angle, double yz_angle);
};

class Body
{
    /* CoordinateSystemで描画される物体 */
public:
    virtual void draw(SDL_Renderer* renderer);
};

class Line : public Body
{
    /* CoordinateSystemで描画される直線 */
private:
    // 直線の端点の座標
    Coordinate coord1;
    Coordinate coord2;

public:
    Line(Coordinate coord1, Coordinate coord2);
    void draw(SDL_Renderer* renderer);
};

class CoordinateSystem
{
    /* 物体が配置される座標系, 描画までの各変換で得られる座標系の親クラス */
protected:
    // TODO:これだとオーバーライドした関数を呼び出せない?
    vector<Body*> bodys;  // 描画する物体の配列
    Matrix compute_affine_transformation_matrix(Perspective perspective);

public:
#ifndef NDEBUG
    void draw_debug(SDL_Renderer* renderer);
#endif
};

class LocalCoordinateSystem : public CoordinateSystem
{
    /* Bodyオブジェクトを配置したもの */
private:
public:
    void add_body(Body* body);
};

class WorldCoordinateSystem : public CoordinateSystem
{
    /* LocalCoordinateSystemを配置したもの */
private:
public:
    WorldCoordinateSystem();
    void add_bodys(LocalCoordinateSystem local_coordinate_system,
                   Perspective perspective);
};

class CameraCoordinateSystem : public CoordinateSystem
{
    /* WorldCoordinateSystemを変換したもの */
private:
public:
    CameraCoordinateSystem(WorldCoordinateSystem world_Coordinate_system,
                           Perspective perspective);
};

class ProjectionCoordinateSystem : public CoordinateSystem
{
    /* CameraCoordinateSystemを変換したもの */
private:
    Matrix compute_projection_matrix();

public:
    ProjectionCoordinateSystem(CameraCoordinateSystem camera_Coordinate_system);
};

class ScreenCoordinateSystem : public CoordinateSystem
{
    /* ProjectionCoordinateSystemを変換したもの */
private:
    // スクリーンのサイズ
    int width;
    int height;
    void draw(SDL_Renderer* renderer);

public:
    ScreenCoordinateSystem(
        ProjectionCoordinateSystem projection_coordinate_system, int width,
        int height);
#ifndef NDEBUG
    ScreenCoordinateSystem(int width, int height);
    void add_body(Body* body);
#endif
};