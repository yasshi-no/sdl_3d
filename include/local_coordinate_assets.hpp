#pragma once
#include <body.hpp>
#include <coordinate_system.hpp>

LocalCoordinateSystem create_cube(double length);
LocalCoordinateSystem create_cube(double length, Color color);
LocalCoordinateSystem create_rectangular(double x_length, double y_length, double z_length);
LocalCoordinateSystem create_rectangular(double x_length, double y_length, double z_length, Color color);