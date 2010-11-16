#ifndef MONOMI_SHAPE_HPP
#define MONOMI_SHAPE_HPP

#include "geometry.hpp"

#include <boost/variant.hpp>

namespace monomi {
    typedef boost::variant<Point2, LineSegment2, Box2, Circle> Shape2;

    bool intersects(const Shape2 &s1, const Shape2 &s2);
    LineSegment2 separate(const Shape2 &s1, const Shape2 &s2);
}

#endif // MONOMI_SHAPE_HPP
