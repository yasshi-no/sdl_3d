#pragma once

#include <matrix.hpp>
#include <vector>

using namespace std;

class Coordinate : public Matrix
{
    /* 3次元を表現する同次座標 */
private:
    const vector<double>& operator[](int x) const;
    vector<double>& operator[](int x);
    void set_w(double x);  // 同次座標だからwは1.0のはずだからprivate

public:
    Coordinate(double x, double y, double z);
    Coordinate& operator=(Matrix matrix);
    double get_x() const;
    double get_y() const;
    double get_z() const;
    void set_x(double x);
    void set_y(double x);
    void set_z(double x);
};

class Perspective
{
    /* 視点の座標と方向 */
public:
    Perspective(Coordinate coord, double xy_angle, double yz_angle);
    Coordinate coord;
    double xy_angle;
    double yz_angle;
};

class Body
{
    /* CoordinateSystemで描画される物体 */
public:
    virtual void draw(SDL_Renderer* renderer);
    virtual void transform(const Matrix& matrix);
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
    void transform(const Matrix& matrix);
    void draw(SDL_Renderer* renderer);
};

class CoordinateSystem
{
    /* 物体が配置される座標系, 描画までの各変換で得られる座標系の親クラス */
protected:
public:
    static Matrix compute_affine_transformation_matrix(Perspective perspective);
    static Matrix compute_translation_matrix(Coordinate coord);
    static Matrix compute_xyrotation_matrix(double xy_angle);
    static Matrix compute_yzrotation_matrix(double yz_angle);
};

class LocalCoordinateSystem : public CoordinateSystem
{
    /* Bodyオブジェクトを配置したもの */
private:
    vector<Body*> bodys;  // 描画する物体の配列
public:
    void add_body(Body* body);
    void transform(Matrix matrix);
    void draw(SDL_Renderer* renderer);
    vector<Body*> get_bodys();
};

class WorldCoordinateSystem : public CoordinateSystem
{
    /* LocalCoordinateSystemを配置したもの */
private:
    vector<LocalCoordinateSystem>
        local_coords;  // 変換したLocalCoordinateSystem

public:
    WorldCoordinateSystem();
    void add_bodys(LocalCoordinateSystem local_coordinate_system,
                   Perspective perspective);
    vector<LocalCoordinateSystem> get_local_coords();
};

class CameraCoordinateSystem : public CoordinateSystem
{
    /* WorldCoordinateSystemを変換したもの */
private:
    vector<LocalCoordinateSystem> local_coords;

public:
    CameraCoordinateSystem(WorldCoordinateSystem world_Coordinate_system,
                           Perspective perspective);
    void draw_debug(SDL_Renderer* renderer);
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
    // void add_body(Body* body);
#endif
};