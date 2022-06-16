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
    Coordinate(const Matrix& matrix);
    Coordinate& operator=(Matrix matrix);
    Coordinate operator+(const Coordinate& coord) const;
    Coordinate operator-() const;
    void normalize();
    void normalize_norm();
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
    double zy_angle;
    Perspective(Coordinate coord, double zx_angle, double zy_angle);
    Perspective operator+(const Perspective& perspective) const;
    Perspective operator-() const;
};
