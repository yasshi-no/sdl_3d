#include <matrix.hpp>
#include <vector>

using namespace std;

class Coordinate : public Matrix
{
    /* 3次元を表現する同次座標 */
private:
    Matrix coord;

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
    /* CoodinateSystemで描画される物体 */
public:
    virtual void draw();
};

class Line : public Body
{
    /* CoodinateSystemで描画される直線 */
private:
    // 直線の端点の座標
    Coordinate coord1;
    Coordinate coord2;

public:
    Line(Coordinate coord1, Coordinate coord2);
    void draw();
};

class CoodinateSystem
{
    /* 物体が配置される座標系, 描画までの各変換で得られる座標系の親クラス */
private:
    // TODO:これだとオーバーライドした関数を呼び出せない?
    vector<Body> bodys;  // 描画する物体の配列
    Matrix compute_affine_transformation_matrix(Perspective perspective);

public:
#ifndef NDEBUG
    void draw_debug();
#endif
};

class LocalCoodinateSystem : public CoodinateSystem
{
    /* Bodyオブジェクトを配置したもの */
private:
public:
    void add_body(Body body);
};

class WorldCoodinateSystem : public CoodinateSystem
{
    /* LocalCoodinateSystemを配置したもの */
private:
public:
    WorldCoodinateSystem();
    void add_bodys(LocalCoodinateSystem local_coordinate_system,
                   Perspective perspective);
};

class CameraCoodinateSystem : public CoodinateSystem
{
    /* WorldCoodinateSystemを変換したもの */
private:
public:
    CameraCoodinateSystem(WorldCoodinateSystem world_coodinate_system,
                          Perspective perspective);
};

class ProjectionCoodinateSystem : public CoodinateSystem
{
    /* CameraCoodinateSystemを変換したもの */
private:
    Matrix compute_projection_matrix();

public:
    ProjectionCoodinateSystem(CameraCoodinateSystem camera_coodinate_system);
};

class ScreenCoordinateSystem : public CoodinateSystem
{
    /* ProjectionCoordinateSystemを変換したもの */
private:
    void draw();

public:
    ScreenCoordinateSystem(
        ProjectionCoodinateSystem projection_coordinate_system, double width,
        double height);
};