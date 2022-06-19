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
// void Body::transform_and_div(const Matrix &matrix) {
//     /* 座標を行列変換し, w成分で全成分を割る. */
//     return;
// }
bool Body::should_draw(double near, double far) {
    /* z成分は描画範囲に入っているか. */
    return false;
}
// void Body::adjust_z(double near, double far) {
//     /* 適切なz成分になるように加工する. CameraCoordinateSystemからPerspectiveCoordinateSystemに変換する際,
//        nearやfarの境界を跨ぐような物体を描画できるようにするため. */
// }
void Body::normalize() {
    /* w成分で割る. 描画直前に行う. */
}
void Body::adjust_w(double near, double far) {
    /* 描画直前のz成分がw成分に収まっているとき, w成分がnear~farに収まるよう調整する. */
}
Body *Body::make_drawable_body(double near, double far) const {
    Body *ret = new Body(*this);
    ret->adjust_w(near, far);
    ret->normalize();
    return ret;
}
void Body::draw(const Screen &screen, double near, double far) const {
    Body *body = make_drawable_body(near, far);
    body->draw(screen);
    delete body;
    return;
}
Body *Body::clone() {
    /* 複製した実体のポインタを返す. */
    return 0;
}

/* Lineクラス */
Line::Line(Coordinate coord1, Coordinate coord2) : coord1(coord1), coord2(coord2), color(Color(255, 255, 255, 255)) {}
Line::Line(Coordinate coord1, Coordinate coord2, Color color) : coord1(coord1), coord2(coord2), color(color) {}
Line::~Line() {}
void Line::transform(const Matrix &matrix) {
    /* 座標を行列変換する. */
    coord1 = matrix * coord1;
    coord2 = matrix * coord2;
    return;
}
// void Line::transform_and_div(const Matrix &matrix) {
//     /* 座標を行列変換し, w成分で全成分を割る. */
//     transform(matrix);
//     coord1.normalize();
//     coord2.normalize();
//     return;
// }
void Line::draw(const Screen &screen) const {
    /* 直線を描画する. */
    // 色の変更
    screen.set_draw_color(color);
    // 直線の描画
    screen.draw_line(coord1.get_x(), coord1.get_y(), coord2.get_x(), coord2.get_y());
    return;
}
void Line::draw(const Screen &screen, double near, double far) const {
    Line *body = make_drawable_body(near, far);
    body->draw(screen);
    delete body;
    return;
}
bool Line::should_draw(double near, double far) {
    /* z成分は描画範囲に入っているか. */
    double z1 = coord1.get_z();
    double z2 = coord2.get_z();
    bool ret = near <= z1 && z1 <= far || near <= z2 && z2 <= far;
    return ret;
}
// void Line::adjust_z(double near, double far) {
//     /* 適切なz成分になるように加工する. CameraCoordinateSystemからPerspectiveCoordinateSystemに変換する際,
//        nearやfarの境界を跨ぐような物体を描画できるようにするため. */
//     if(coord1.get_z() > coord2.get_z()) {
//         // swap(x1, x2), swap(y1, y2), swap(z1, z2);
//         swap(coord1, coord2);
//     }
//     double x1 = coord1.get_x(), y1 = coord1.get_y(), z1 = coord1.get_z();
//     double x2 = coord2.get_x(), y2 = coord2.get_y(), z2 = coord2.get_z();

//     // zが範囲外にある場合, 範囲に収まるような内分点をとる
//     // near = 100;
//     if(z1 < near) {
//         double dist = z2 - z1;
//         double t = (near - z1) / dist; // どれだけxx2に寄せればいいか
//         x1 = x1 + (x2 - x1) * t;
//         y1 = y1 + (y2 - y1) * t;
//         z1 = z1 + (z2 - z1) * t;
//     }
//     if(z2 > far) {
//         double dist = z1 - z2;
//         double t = (far - z2) / dist; // どれだけxx1に寄せればいいか
//         x2 = x2 + (x1 - x2) * t;
//         y2 = y2 + (y1 - y2) * t;
//         z2 = far;
//     }
//     coord1.set_x(x1), coord1.set_y(y1), coord1.set_z(z1);
//     coord2.set_x(x2), coord2.set_y(y2), coord2.set_z(z2);
// }
void Line::normalize() {
    /* w成分で割る. 描画直前に行う. */
    double w = coord1.get_w();
    // coord1の変換
    coord1.set_x(coord1.get_x() / w);
    coord1.set_y(coord1.get_y() / w);
    coord1.set_z(coord1.get_z() / w);
    coord1.set_w(1.0);
    // coord2の変換
    w = coord2.get_w();
    coord2.set_x(coord2.get_x() / w);
    coord2.set_y(coord2.get_y() / w);
    coord2.set_z(coord2.get_z() / w);
    coord2.set_w(1.0);
    return;
}
void Line::adjust_w(double near, double far) {
    /* 描画直前のz成分がw成分に収まっているとき, w成分がnear~farに収まるよう調整する. */
    if(coord1.get_w() > coord2.get_w()) {
        // swap(x1, x2), swap(y1, y2), swap(z1, z2);
        swap(coord1, coord2);
    }
    double x1 = coord1.get_x(), y1 = coord1.get_y(), z1 = coord1.get_z(), w1 = coord1.get_w();
    double x2 = coord2.get_x(), y2 = coord2.get_y(), z2 = coord2.get_z(), w2 = coord2.get_w();

    // zが範囲外にある場合, 範囲に収まるような内分点をとる
    if(w1 < near) {
        double dist = w2 - w1;
        double t = (near - w1) / dist; // どれだけxx2に寄せればいいか
        x1 = x1 + (x2 - x1) * t;
        y1 = y1 + (y2 - y1) * t;
        z1 = z1 + (z2 - z1) * t;
        w1 = w1 + (w2 - w1) * t;
    }
    if(w2 > far) {
        double dist = w1 - w2;
        double t = (far - w2) / dist; // どれだけxx1に寄せればいいか
        x2 = x2 + (x1 - x2) * t;
        y2 = y2 + (y1 - y2) * t;
        w2 = w2 + (w1 - w2) * t;
    }
    coord1.set_x(x1), coord1.set_y(y1), coord1.set_z(z1), coord1.set_w(w1);
    coord2.set_x(x2), coord2.set_y(y2), coord2.set_z(z2), coord2.set_w(w2);
}
Line *Line::make_drawable_body(double near, double far) const {
    Line *ret = new Line(*this);
    ret->adjust_w(near, far);
    ret->normalize();
    return ret;
}
Line *Line::clone() { return new Line(*this); }
