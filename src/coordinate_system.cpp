#include <body.hpp>
#include <cmath>
#include <coordinate.hpp>
#include <coordinate_system.hpp>
#include <matrix.hpp>

/* CoordinateSystemクラス */
Matrix CoordinateSystem::compute_affine_transformation_matrix(
    Perspective perspective)
{
    /* アフィン変換行列を計算する. なお, 平行移動してから回転する. */
    Matrix ret = compute_zyrotation_matrix(perspective.zy_angle) *
                 compute_zxrotation_matrix(perspective.zx_angle) *
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
Matrix CoordinateSystem::compute_zyrotation_matrix(double zy_angle)
{
    /* x軸回りの回転のための行列を計算する. */
    Matrix ret(4, 4);
    ret.identity();
    ret[2][2] = cos(zy_angle);
    ret[1][2] = sin(zy_angle);
    ret[2][1] = -sin(zy_angle);
    ret[1][1] = cos(zy_angle);
    return ret;
}
Matrix CoordinateSystem::compute_zxrotation_matrix(double zx_angle)
{
    /* y軸回りの回転のための行列を計算する. */
    Matrix ret(4, 4);
    ret.identity();
    ret[2][2] = cos(zx_angle);
    ret[0][2] = sin(zx_angle);
    ret[2][0] = -sin(zx_angle);
    ret[0][0] = cos(zx_angle);
    return ret;
}
static Matrix compute_rodrigues_rotatin_matrix(Coordinate coord, double angle)
{
    /* 任意軸の回転のための行列. coordは回転軸. angleは右ねじの向き. */
    Matrix ret(4, 4);
    ret.identity();
    // 与えられた軸のベクトルを単位ベクトルに変換する.
    coord.normalize_norm();
    // coord及びangleを使いやすいように変換
    double x = coord.get_x(), y = coord.get_y(), z = coord.get_z();
    double cs = cos(angle), sn = sin(angle);
    double cs1 = 1 - cs;
    // 行列
    ret[0][0] = x * x * cs1 + cs, ret[0][1] = x * y * cs1 - z * sn,
    ret[0][2] = x * z * cs1 + y * sn;
    ret[1][0] = x * y * cs1 + z * sn, ret[1][1] = y * y * cs1 + cs,
    ret[1][2] = y * z * cs1 - x * sn;
    ret[2][0] = x * z * cs1 - y * sn, ret[2][1] = y * z * cs1 + x * sn,
    ret[2][2] = z * z * cs1 + cs;
    return ret;
}

/* LocalCoordinateSystemクラス */
LocalCoordinateSystem::LocalCoordinateSystem() {}
LocalCoordinateSystem::LocalCoordinateSystem(
    const LocalCoordinateSystem& local_coordinate_system)
{
    // 新しいBodyオブジェクトの実体を確保してコピー
    for(auto&& body : local_coordinate_system.bodys) {
        bodys.push_back(body->clone());
    }
}
LocalCoordinateSystem::~LocalCoordinateSystem()
{
    // 全てのBodyオブジェクトを解放
    for(auto&& body : bodys) {
        delete body;
    }
}
void LocalCoordinateSystem::add_body(Body* body) { bodys.push_back(body); }
void LocalCoordinateSystem::transform(Matrix matrix)
{
    /* 各Bodyオブジェクトを行列変換する. */
    for(auto&& body : bodys) {
        body->transform(matrix);
    }
}
void LocalCoordinateSystem::transform_and_div(const Matrix& matrix)
{
    /* 各Bodyオブジェクトを行列変換し, w成分で割る. */
    for(auto&& body : bodys) {
        body->transform_and_div(matrix);
    }
}
void LocalCoordinateSystem::draw(const Screen& screen)
{
    /* 全てのBodyオブジェクトを描画する */
    for(auto&& body : bodys) {
        body->draw(screen);
    }
}
bool LocalCoordinateSystem::delete_undrawable_body(double near, double far)
{
    /* z成分は描画範囲に入っていないBodyオブジェクトを解放する.
     * 返り値は描画するオブジェクトが存在するか*/
    vector<Body*> new_bodys;
    bool ret = false;
    for(auto&& body : bodys) {
        if(body->should_draw(near, far)) {
            // bodyが描画可能なz成分の場合
            ret = true;
            new_bodys.push_back(body);
        } else {
            delete body;
        }
    }
    bodys = new_bodys;
    return ret;
}
vector<Body*> LocalCoordinateSystem::get_bodys() { return bodys; }

/* WorldCoordinateSystemクラス */
WorldCoordinateSystem::WorldCoordinateSystem() {}
void WorldCoordinateSystem::add_bodys(
    LocalCoordinateSystem local_coordinate_system, Perspective perspective)
{
    /* LocalCoordinateSystemオブジェクトのBodyを移動させて配置 */
    // 与えられたオブジェクトをアフィン変換行列で移動して追加
    local_coordinate_system.transform(
        CoordinateSystem::compute_affine_transformation_matrix(perspective));
    local_coords.push_back(local_coordinate_system);
}
vector<LocalCoordinateSystem> WorldCoordinateSystem::get_local_coords()
{
    return local_coords;
}

/* CameraCoordinateSystemクラス */
CameraCoordinateSystem::CameraCoordinateSystem(
    WorldCoordinateSystem world_coordinate_system, Perspective perspective)
{
    /* WorldCoordinateSystemオブジェクトに配置されたLocalCoordinateSystemオブジェクトをすべて移動する
     */
    local_coords = vector<LocalCoordinateSystem>();
    Matrix matrix = CoordinateSystem::compute_affine_transformation_matrix(
        perspective);  //アフィン変換行列
    // 全てのLocalCoordinateSystemオブジェクトをアフィン変換して格納
    for(auto&& local_coord : world_coordinate_system.get_local_coords()) {
        local_coord.transform(matrix);
        local_coords.push_back(local_coord);
    }
}
vector<LocalCoordinateSystem> CameraCoordinateSystem::get_local_coords()
{
    return local_coords;
}

/* ProjectionCoordinateClass */
ProjectionCoordinateSystem::ProjectionCoordinateSystem(
    CameraCoordinateSystem camera_coordinate_system, int width, int height,
    double near, double far, double view_angle)
{
    // 射影変換行列で各LocalCoordinateSystemオブジェクトを変換して追加する
    local_coords = vector<LocalCoordinateSystem>();
    Matrix matrix = compute_projection_matrix(width, height, near, far,
                                              view_angle);  // 射影変換行列
    for(auto&& local_coord : camera_coordinate_system.get_local_coords()) {
        // z軸の描画範囲の条件を満たすもののみ, 変換して追加
        local_coord.delete_undrawable_body(near, far);
        local_coord.transform_and_div(matrix);
        local_coords.push_back(local_coord);
    }
}
Matrix ProjectionCoordinateSystem::compute_projection_matrix(
    int width, int height, double near, double far, double view_angle)
{
    /* 射影変換行列を計算する. */
    Matrix ret(4, 4);
    ret.zeros();
    ret[0][0] = height / width / tan(view_angle / 2.0);
    ret[1][1] = 1 / tan(view_angle / 2.0);
    ret[2][2] = far / (far - near), ret[2][3] = -far * near / (far - near);
    ret[3][2] = 1.0, ret[3][3] = 0.0;
    return ret;
}
vector<LocalCoordinateSystem> ProjectionCoordinateSystem::get_local_coords()
{
    return local_coords;
}

/* ScreenCoordinateSystemクラス */
ScreenCoordinateSystem::ScreenCoordinateSystem(
    ProjectionCoordinateSystem projection_coordinate_system, int width,
    int height)
    : width(width), height(height)
{
    Matrix matrix = compute_screen_transformation_matrix();
    // 透視投影の座標系をスクリーンの座標系に変換して格納
    for(auto&& local_coord : projection_coordinate_system.get_local_coords()) {
        local_coord.transform(matrix);
        local_coords.push_back(local_coord);
    }
}
Matrix ScreenCoordinateSystem::compute_screen_transformation_matrix()
{
    /* スクリーン変換行列を計算する */
    Matrix matrix(4, 4);
    matrix.identity();
    matrix[0][0] = width / 2.0;
    matrix[1][1] = height / 2.0;
    matrix[0][3] = width / 2.0;
    matrix[1][3] = height / 2.0;
    return matrix;
}
void ScreenCoordinateSystem::draw(const Screen& screen)
{
    /* 全てのLocalCoordinateSystemオブジェクトを描画する. */
    for(auto&& local_coord : local_coords) {
        local_coord.draw(screen);
    }
}