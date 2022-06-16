#include <body.hpp>
#include <coordinate.hpp>
#include <matrix.hpp>
#include <screen.hpp>

/* Bodyクラス */
Body::~Body() {}
void Body::draw(const Screen &screen) const {
    /* 物体を描画する. */
    return;
}
void Body::transform(const Matrix &matrix) {
    /* 座標を行列変換する. */
    return;
}
void Body::transform_and_div(const Matrix &matrix) {
    /* 座標を行列変換し, w成分で全成分を割る. */
    return;
}
bool Body::should_draw(double near, double far) {
    /* z成分は描画範囲に入っているか. */
    return false;
}
Body *Body::clone() {
    /* 複製した実体のポインタを返す. */
    return 0;
}

/* Lineクラス */
Line::Line(Coordinate coord1, Coordinate coord2) : coord1(coord1), coord2(coord2) {}
Line::~Line() {}
void Line::transform(const Matrix &matrix) {
    /* 座標を行列変換する. */
    coord1 = matrix * coord1;
    coord2 = matrix * coord2;
    return;
}
void Line::transform_and_div(const Matrix &matrix) {
    /* 座標を行列変換し, w成分で全成分を割る. */
    transform(matrix);
    coord1.normalize();
    coord2.normalize();
    return;
}
void Line::draw(const Screen &screen) const {
    /* 直線を描画する. */
    screen.draw_line(coord1.get_x(), coord1.get_y(), coord2.get_x(), coord2.get_y());
    return;
}
bool Line::should_draw(double near, double far) {
    /* z成分は描画範囲に入っているか. */
    double z1 = coord1.get_z();
    double z2 = coord2.get_z();
    bool ret = near <= z1 && z1 <= far && near <= z2 && z2 <= far;
    return ret;
}
Line *Line::clone() { return new Line(*this); }
