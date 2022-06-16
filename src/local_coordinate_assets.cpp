#include <body.hpp>
#include <coordinate.hpp>
#include <coordinate_system.hpp>
#include <local_coordinate_assets.hpp>

LocalCoordinateSystem create_cube(double length) {
    /* 立方体を生成する.
       原点に頂点を持つ. x, y, z軸に辺を持つ. */
    return create_rectangular(length, length, length);
}

LocalCoordinateSystem create_cube(double length, Color color) {
    /* 立方体を生成する.
       原点に頂点を持つ. x, y, z軸に辺を持つ. */
    return create_rectangular(length, length, length, color);
}

LocalCoordinateSystem create_rectangular(double x_length, double y_length, double z_length) {
    /* 直方体を生成する.
       原点に頂点を持つ. x, y, z軸に辺を持つ. */
    return create_rectangular(x_length, y_length, z_length, Color());
}

LocalCoordinateSystem create_rectangular(double x_length, double y_length, double z_length, Color color) {
    /* 直方体を生成する.
       原点に頂点を持つ. x, y, z軸に辺を持つ. */
    LocalCoordinateSystem ret;
    ret.add_body(new Line(Coordinate(0.0, 0.0, 0.0),
                          Coordinate(x_length, 0.0, 0.0), color));
    ret.add_body(new Line(Coordinate(x_length, 0.0, 0.0),
                          Coordinate(x_length, y_length, 0.0), color));
    ret.add_body(new Line(Coordinate(x_length, y_length, 0.0),
                          Coordinate(0.0, y_length, 0.0), color));
    ret.add_body(new Line(Coordinate(0.0, y_length, 0.0),
                          Coordinate(0.0, 0.0, 0.0), color));

    ret.add_body(new Line(Coordinate(0.0, 0.0, 0.0),
                          Coordinate(0.0, 0.0, z_length), color));
    ret.add_body(new Line(Coordinate(x_length, 0.0, 0.0),
                          Coordinate(x_length, 0.0, z_length), color));
    ret.add_body(new Line(Coordinate(x_length, y_length, 0.0),
                          Coordinate(x_length, y_length, z_length), color));
    ret.add_body(new Line(Coordinate(0.0, y_length, 0.0),
                          Coordinate(0.0, y_length, z_length), color));

    ret.add_body(new Line(Coordinate(0.0, 0.0, z_length),
                          Coordinate(x_length, 0.0, z_length), color));
    ret.add_body(new Line(Coordinate(x_length, 0.0, z_length),
                          Coordinate(x_length, y_length, z_length), color));
    ret.add_body(new Line(Coordinate(x_length, y_length, z_length),
                          Coordinate(0.0, y_length, z_length), color));
    ret.add_body(new Line(Coordinate(0.0, y_length, z_length),
                          Coordinate(0.0, 0.0, z_length), color));
    return ret;
}
