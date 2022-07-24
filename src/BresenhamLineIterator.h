#pragma once

#include <stdlib.h>
#include "Point2D.h"


// Actual implementation
class BresenhamLineIterator
{
public:
    BresenhamLineIterator(const Point2D& p, const Point2D& q) :
    firstPoint(p),
    lastPoint(q),
    point(p),
    delta(Point2D(q[0] - p[0], q[1] - p[1]))
    {
        id = std::abs(delta[0]) >= std::abs(delta[1]) ? 0 : 1;
        increment[id] = delta[id] >= 0 ? 1 : -1;
        increment[1 - id] = delta[1 - id] >= 0 ? 1 : -1;
        delta = Point2D(delta[0] * increment[0], delta[1] * increment[1]);
        error = 2 * delta[1 - id] - delta[id];
    }

    BresenhamLineIterator operator++()
    {
        point[id] += increment[id];
        if (error > 0)
        {
            point[1 - id] += increment[1 - id];
            error -= 2 * delta[id];
        }
        error += 2 * delta[1 - id];
        return *this;
    }

    // Extra structure to allow iteration over range-based loops
    Point2D& operator*() { return point; }
    bool operator!=(const BresenhamLineIterator& bl) const { return point[id] != bl.point[id]; }
    BresenhamLineIterator begin() { return BresenhamLineIterator(firstPoint, lastPoint); };
    BresenhamLineIterator end() { return BresenhamLineIterator(lastPoint, lastPoint); };
    //BresenhamLineIterator end() { return BresenhamLineIterator(lastPoint + increment, lastPoint); }; use this if last point is included

private:
	Point2D firstPoint;   // first point
    Point2D lastPoint;    // last point
    Point2D point;        // storage for actual point on line
    Point2D delta;        // delta between end and start point
    Point2D increment;    // increment between two points on line
    size_t id;            // main direction of the line (0 for x, 1 for y)
	int error;            // error term
};
