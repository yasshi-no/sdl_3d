#pragma once

#include <matrix.hpp>
#include <vector>

using namespace std;

class Coordinate : public Matrix
{
    /* 3次元を表現する同次座標, 右手系 */
private:
    const vector<double>& operator[](int x) const;
    vector<double>& operator[](int x);
    void set_w(double x);  // 同次座標だからwは1.0のはずだからprivate

public:
    Coordinate(double x, double y, double z);
    Coordinate& operator=(Matrix matrix);
    Coordinate operator+(const Coordinate& coord) const;
    void normalize();
    double get_x() const;
    double get_y() const;
    double get_z() const;
    double get_w() const;
    void set_x(double x);
    void set_y(double x);
    void set_z(double x);
};

class Perspective
{
    /* 視点の座標と方向 */
public:
    Coordinate coord;
    double zx_angle;
    double yz_angle;
    Perspective(Coordinate coord, double zx_angle, double yz_angle);
    Perspective operator+(const Perspective& perspective) const;
};

class Body
{
    /* CoordinateSystemで描画される物体 */
public:
    virtual void draw(SDL_Renderer* renderer);
    virtual void transform(const Matrix& matrix);
    virtual void transform_and_div(const Matrix& matrix);
    virtual bool should_draw(double near, double far);
    virtual Body* clone();
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
    void transform_and_div(const Matrix& matrix);
    void draw(SDL_Renderer* renderer);
    bool should_draw(double near, double far);
    Line* clone();
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
    static Matrix compute_zxrotation_matrix(double zx_angle);
};

class LocalCoordinateSystem
{
    /* Bodyオブジェクトを配置したもの */
private:
    vector<Body*> bodys;  // 描画する物体の配列
public:
    LocalCoordinateSystem();
    LocalCoordinateSystem(
        const LocalCoordinateSystem& loocal_coordinate_system);
    ~LocalCoordinateSystem();
    void add_body(Body* body);
    void transform(Matrix matrix);
    void draw(SDL_Renderer* renderer);
    void transform_and_div(const Matrix& matrix);
    bool delete_undrawable_body(double near, double far);
    vector<Body*> get_bodys();
};

class WorldCoordinateSystem
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

class CameraCoordinateSystem
{
    /* WorldCoordinateSystemを変換したもの */
private:
    vector<LocalCoordinateSystem> local_coords;

public:
    CameraCoordinateSystem(WorldCoordinateSystem world_Coordinate_system,
                           Perspective perspective);
    vector<LocalCoordinateSystem> get_local_coords();
};

class ProjectionCoordinateSystem
{
    /* CameraCoordinateSystemを変換したもの */
private:
    vector<LocalCoordinateSystem> local_coords;
    Matrix compute_projection_matrix(int width, int height, double near,
                                     double far, double view_angle);

public:
    ProjectionCoordinateSystem(CameraCoordinateSystem camera_Coordinate_system,
                               int width, int height, double near, double far,
                               double view_angle);
    vector<LocalCoordinateSystem> get_local_coords();
};

class ScreenCoordinateSystem
{
    /* ProjectionCoordinateSystemを変換したもの */
private:
    // スクリーンのサイズ
    int width;
    int height;
    vector<LocalCoordinateSystem> local_coords;
    Matrix compute_screen_transformation_matrix();

public:
    ScreenCoordinateSystem(
        ProjectionCoordinateSystem projection_coordinate_system, int width,
        int height);
    void draw(SDL_Renderer* renderer);
};