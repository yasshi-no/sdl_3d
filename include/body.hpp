
#pragma once
#include <coordinate.hpp>
#include <matrix.hpp>
#include <screen.hpp>

using namespace std;

class Body {
    /* CoordinateSystemで描画される物体 */
public:
    virtual ~Body();
    virtual void draw(const Screen &screen) const;
    virtual void draw(const Screen &screen, double near, double far) const;
    virtual void transform(const Matrix &matrix);
    // virtual void transform_and_div(const Matrix &matrix);
    virtual bool should_draw(double near, double far) const;
    // virtual void adjust_z(double near, double far);
    virtual void normalize();
    virtual void adjust_w(double near, double far);
    virtual Body *make_drawable_body(double near, double far) const;
    virtual Body *clone() const;
};

class Line : public Body {
    /* CoordinateSystemで描画される直線 */
private:
    // 直線の端点の座標
    Coordinate coord1;
    Coordinate coord2;
    Color color;

public:
    Line(Coordinate coord1, Coordinate coord2);
    Line(Coordinate coord1, Coordinate coord2, Color color);
    ~Line();
    void transform(const Matrix &matrix);
    // void transform_and_div(const Matrix &matrix);
    void draw(const Screen &screen) const;
    void draw(const Screen &screen, double near, double far) const;
    bool should_draw(double near, double far) const;
    // void adjust_z(double near, double far);
    void normalize();
    void adjust_w(double near, double far);
    Line *make_drawable_body(double near, double far) const;
    Line *clone() const;
};
