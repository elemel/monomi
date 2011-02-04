#include "geometry.hpp"

#include <algorithm>
#include <cmath>
#include <limits>

namespace monomi {
    std::ostream &operator<<(std::ostream &out, Vector2 const &v)
    {
        return out << "Vector2(" << v.x << ", " << v.y << ")";
    }

    float Matrix3::scale() const
    {
        return distance(*this * Vector2(0.0f, 0.0f),
                        *this * Vector2(0.0f, 1.0f));
    }

    void Circle2::transform(Matrix3 const &m)
    {
        center = m * center;
        radius *= m.scale();
    }

    Polygon2::Polygon2(Box2 const &b)
    {
        vertices.push_back(b.p1);
        vertices.push_back(Vector2(b.p2.x, b.p1.y)); 
        vertices.push_back(b.p2);
        vertices.push_back(Vector2(b.p1.x, b.p2.y)); 
    }

    void Polygon2::transform(Matrix3 const &m)
    {
        for (std::vector<Vector2>::iterator i = vertices.begin();
             i != vertices.end(); ++i)
        {
            *i = m * *i;
        }
    }

    bool intersects(Box2 const &b, Circle2 const &c)
    {
        if (b.p1.x <= c.center.x && c.center.x <= b.p2.x) {
            return (b.p1.y <= c.center.y + c.radius &&
                    c.center.y - c.radius <= b.p2.y);
        } else if (b.p1.y <= c.center.y && c.center.y <= b.p2.y) {
            return (b.p1.x <= c.center.x + c.radius &&
                    c.center.x - c.radius <= b.p2.x);
        } else {
            return (intersects(c, b.p1) ||
                    intersects(c, Vector2(b.p2.x, b.p1.y)) ||
                    intersects(c, b.p2) ||
                    intersects(c, Vector2(b.p1.x, b.p2.y)));
        }
    }
}
