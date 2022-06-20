#include <cmath>
#include <coordinate.hpp>
#include <matrix.hpp>
#include <vector>

using namespace std;

/* Coordinateクラス */
Coordinate::Coordinate(double x, double y, double z) : Matrix(4, 1) {
    // Matrixに同次座標を格納(列ベクトル)
    set_x(x);
    set_y(y);
    set_z(z);
    set_w(1.0);
}
Coordinate::Coordinate(const Matrix &matrix) : Matrix(4, 1) {
    // Matrixに同次座標を格納(列ベクトル)
    set_x(matrix[0][0]);
    set_y(matrix[1][0]);
    set_z(matrix[2][0]);
    set_w(matrix[3][0]);
}
Coordinate &Coordinate::operator=(const Matrix &matrix) {
    // matrixの1列目の成分を格納
    set_x(matrix[0][0]);
    set_y(matrix[1][0]);
    set_z(matrix[2][0]);
    set_w(matrix[3][0]);
    return *this;
}
Coordinate Coordinate::operator+(const Coordinate &coord) const {
    /* x,y,z成分を加算する. */
    Coordinate ret(get_x() + coord.get_x(), get_y() + coord.get_y(), get_z() + coord.get_z());
    return ret;
}
Coordinate Coordinate::operator-() const {
    /* 全ての成分の符号を反転させる. */
    Coordinate ret(-get_x(), -get_y(), -get_z());
    return ret;
}
void Coordinate::normalize() {
    /* 全成分をw成分で割る. */
    double w = get_w();
    set_x(get_x() / w);
    set_y(get_y() / w);
    set_z(get_z() / w);
    set_w(1.0);
}
void Coordinate::normalize_norm() {
    /* 単位ベクトルに変換する. */
    double x = get_x(), y = get_y(), z = get_z();
    double dist = sqrt(x * x + y * y + z * z);
    set_x(x / dist);
    set_y(y / dist);
    set_z(z / dist);
}
double Coordinate::get_x() const { return v[0][0]; }
double Coordinate::get_y() const { return v[1][0]; }
double Coordinate::get_z() const { return v[2][0]; }
double Coordinate::get_w() const { return v[3][0]; }
void Coordinate::set_x(double val) { v[0][0] = val; }
void Coordinate::set_y(double val) { v[1][0] = val; }
void Coordinate::set_z(double val) { v[2][0] = val; }
void Coordinate::set_w(double val) { v[3][0] = val; }

/* Perspectiveクラス */
Perspective::Perspective(const Coordinate &coord, double zx_angle, double zy_angle)
    : coord(coord), zx_angle(zx_angle), zy_angle(zy_angle) {
    /* coordにより視点の位置を決定する. その後に視点の方向をfoo_angleで決定する.
        決定の順番に注意.
     */
}
Perspective Perspective::operator+(const Perspective &perspective) const {
    Perspective ret(coord + perspective.coord,
                    zx_angle + perspective.zx_angle,
                    zy_angle + perspective.zy_angle);
    return ret;
}
Perspective Perspective::operator-() const {
    /* 全ての成分を反転させる. */
    Perspective ret(-coord, -zx_angle, -zy_angle);
    return ret;
}