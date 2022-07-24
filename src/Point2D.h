#pragma once

#include <math.h>       
#include <stdlib.h>

struct Point2D
{
    Point2D() {}
    Point2D(int a, int b) { data[0] = a; data[1] = b; }
    int& operator[](const size_t id) { return data[id]; }
    const int& operator[](const size_t id) const { return data[id]; }
    Point2D operator*(const int a) const { return Point2D(data[0] * a, data[1] * a); }
    Point2D operator/(const int a) const { return Point2D(data[0] / a, data[1] / a); }
    Point2D operator-(const Point2D other) const { return Point2D(data[0] - other.data[0], data[1] - other.data[1]); }

    int data[2];
};