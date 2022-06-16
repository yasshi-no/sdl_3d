#pragma once
#include <body.hpp>
#include <coordinate.hpp>
#include <matrix.hpp>
#include <screen.hpp>
#include <vector>

class CoordinateSystem
{
    /* 物体が配置される座標系, 描画までの各変換で得られる座標系の親クラス */
protected:
public:
    static Matrix compute_affine_transformation_matrix(Perspective perspective);
    static Matrix compute_translation_matrix(Coordinate coord);
    static Matrix compute_xyrotation_matrix(double xy_angle);
    static Matrix compute_yzrotation_matrix(double yz_angle);
    static Matrix compute_zyrotation_matrix(double zy_angle);
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
    void draw(const Screen& renderer);
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
    void draw(const Screen& screen);
};