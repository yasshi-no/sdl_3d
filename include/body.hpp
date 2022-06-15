
#pragma once
#include <coordinate.hpp>
#include <matrix.hpp>
#include <screen.hpp>

using namespace std;

class Body
{
    /* CoordinateSystemで描画される物体 */
public:
    virtual ~Body();
    virtual void draw(const Screen& screen) const;
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
    ~Line();
    void transform(const Matrix& matrix);
    void transform_and_div(const Matrix& matrix);
    void draw(const Screen& screen) const;
    bool should_draw(double near, double far);
    Line* clone();
};
