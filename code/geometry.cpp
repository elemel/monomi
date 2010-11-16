#include "geometry.hpp"

#include <algorithm>
#include <cmath>
#include <limits>

namespace monomi {
    Vector2::Vector2() :
        x(0.0f),
        y(0.0f)
    { }

    Vector2::Vector2(float f) :
        x(f),
        y(f)
    { }

    Vector2::Vector2(float x, float y) :
        x(x),
        y(y)
    { }

    Vector2::Vector2(const Point2 &p) :
        x(p.x),
        y(p.y)
    { }

    float Vector2::length() const {
        return std::sqrt(squaredLength());
    }

    float Vector2::squaredLength() const {
        return dot(*this, *this);
    }

    Vector2 Vector2::operator-() const
    {
        return Vector2(-x, -y);
    }

    Vector2 &Vector2::operator+=(const Vector2 &v)
    {
        x += v.x;
        y += v.y;
        return *this;
    }

    Vector2 &Vector2::operator-=(const Vector2 &v)
    {
        x -= v.x;
        y -= v.y;
        return *this;
    }

    Vector2 &Vector2::operator*=(float f)
    {
        x *= f;
        y *= f;
        return *this;
    }

    Vector2 &Vector2::operator/=(float f)
    {
        x /= f;
        y /= f;
        return *this;
    }

    float Vector2::normalize() {
        float f = length();
        if (f != 0.0f) {
            *this /= f;
        }
        return f;
    }

    Vector2 operator+(const Vector2 &v1, const Vector2 &v2)
    {
        return Vector2(v1) += v2;
    }

    Vector2 operator-(const Vector2 &v1, const Vector2 &v2)
    {
        return Vector2(v1) -= v2;
    }

    Vector2 operator*(const Vector2 &v, float f)
    {
        return Vector2(v) *= f;
    }

    Vector2 operator*(float f, const Vector2 &v)
    {
        return Vector2(v) *= f;
    }

    Vector2 operator/(const Vector2 &v, float f)
    {
        return Vector2(v) /= f;
    }

    float dot(const Vector2 &v1, const Vector2 &v2)
    {
        return v1.x * v2.x + v1.y * v1.y;
    }

    float cross(const Vector2 &v1, const Vector2 &v2)
    {
        return v1.x * v2.y - v2.x * v1.y;
    }

    Vector2 cross(const Vector2 &v)
    {
        return Vector2(-v.y, v.x);
    }

    Vector2 normalize(const Vector2 &v)
    {
        Vector2 v2(v);
        v2.normalize();
        return v2;
    }

    Point2::Point2() :
        x(0.0f),
        y(0.0f)
    { }

    Point2::Point2(float x, float y) :
        x(x),
        y(y)
    { }

    Point2::Point2(const Vector2 &v) :
        x(v.x),
        y(v.y)
    { }

    Point2 &Point2::operator+=(const Vector2 &v)
    {
        x += v.x;
        y += v.y;
        return *this;
    }

    Point2 &Point2::operator-=(const Vector2 &v)
    {
        x -= v.x;
        y -= v.y;
        return *this;
    }

    Point2 operator+(const Point2 &p, const Vector2 &v)
    {
        return Point2(p) += v;
    }

    Point2 operator+(const Vector2 &v, const Point2 &p)
    {
        return Point2(p) += v;
    }

    Point2 operator-(const Point2 &p, const Vector2 &v)
    {
        return Point2(p) -= v;
    }

    Vector2 operator-(const Point2 &p1, const Point2 &p2)
    {
        return Vector2(p1.x - p2.x, p1.y - p2.y);
    }

    float distance(const Point2 &p1, const Point2 &p2)
    {
        return (p2 - p1).length();
    }

    float squaredDistance(const Point2 &p1, const Point2 &p2)
    {
        return (p2 - p1).squaredLength();
    }

    LineSegment2::LineSegment2()
    { }

    LineSegment2::LineSegment2(const Point2 &p1, const Point2 &p2) :
        p1(p1),
        p2(p2)
    { }

    float LineSegment2::length() const
    {
        return distance(p1, p2);
    }

    float LineSegment2::squaredLength() const
    {
        return squaredDistance(p1, p2);
    }

    Box2::Box2()
    { }

    Box2::Box2(const Point2 &p1, const Point2 &p2) :
        p1(p1),
        p2(p2)
    { }

    Point2 Box2::center() const
    {
        return Point2(0.5f * (p1.x + p2.x), 0.5f * (p1.y + p2.y));
    }

    bool Box2::empty() const
    {
        return dx() <= 0.0f || dy() <= 0.0f;
    }

    float Box2::dx() const
    {
        return p2.x - p1.x;
    }

    float Box2::dy() const
    {
        return p2.y - p1.y;
    }

    float Box2::perimeter() const
    {
        return 2.0f * (dx() + dy());
    }

    float Box2::area() const
    {
        return dx() * dy();
    }

    void Box2::clear()
    {
        p1.x = std::numeric_limits<float>::infinity();
        p1.y = std::numeric_limits<float>::infinity();
        p2.x = -std::numeric_limits<float>::infinity();
        p2.y = -std::numeric_limits<float>::infinity();
    }

    void Box2::grow(const Point2 &p)
    {
        p1.x = std::min(p1.x, p.x);
        p1.y = std::min(p1.y, p.y);
        p2.x = std::max(p2.x, p.x);
        p2.y = std::max(p2.y, p.y);
    }

    void Box2::grow(const Box2 &b)
    {
        p1.x = std::min(p1.x, b.p1.x);
        p1.y = std::min(p1.y, b.p1.y);
        p2.x = std::max(p2.x, b.p2.x);
        p2.y = std::max(p2.y, b.p2.y);
    }

    Box2 intersection(const Box2 &b1, const Box2 &b2)
    {
        float x1 = std::max(b1.p1.x, b2.p1.x);
        float y1 = std::max(b1.p1.y, b2.p1.y);
        float x2 = std::min(b1.p2.x, b2.p2.x);
        float y2 = std::min(b1.p2.y, b2.p2.y);
        return Box2(Point2(x1, y1), Point2(x2, y2));
    }

    Circle::Circle() :
        radius(0.0f)
    { }

    Circle::Circle(const Point2 &center, float radius) :
        center(center),
        radius(radius)
    { }

    bool Circle::contains(const Point2 &p) const
    {
        return squaredDistance(center, p) <= radius * radius;
    }

    Box2 boundingBox(const LineSegment2 &s)
    {
        float x1 = std::min(s.p1.x, s.p2.x);
        float y1 = std::min(s.p1.y, s.p2.y);
        float x2 = std::max(s.p1.x, s.p2.x);
        float y2 = std::max(s.p1.y, s.p2.y);
        return Box2(Point2(x1, y1), Point2(x2, y2));
    }

    Box2 boundingBox(const Box2 &b)
    {
        return b;
    }

    Box2 boundingBox(const Circle &c)
    {
        return Box2(c.center - Vector2(c.radius),
                    c.center + Vector2(c.radius));
    }

    Box2 boundingBox(const Box2 &b1, const Box2 &b2)
    {
        float x1 = std::min(b1.p1.x, b2.p1.x);
        float y1 = std::min(b1.p1.y, b2.p1.y);
        float x2 = std::max(b1.p2.x, b2.p2.x);
        float y2 = std::max(b1.p2.y, b2.p2.y);
        return Box2(Point2(x1, y1), Point2(x2, y2));
    }

    bool intersects(const Box2 &b1, const Box2 &b2)
    {
        return b1.p1.x <= b2.p2.x && b2.p1.x <= b1.p2.x &&
               b1.p1.y <= b2.p2.y && b2.p1.y <= b1.p2.y;
    }

    bool intersects(const Circle &c1, const Circle &c2)
    {
        return squaredDistance(c1.center, c2.center) <=
               (c1.radius + c2.radius) * (c1.radius + c2.radius);
    }

    bool intersects(const Box2 &b, const Circle &c)
    {
        if (b.p1.x <= c.center.x && c.center.x <= b.p2.x) {
            return b.p1.y <= c.center.y + c.radius &&
                   c.center.y - c.radius <= b.p2.y;
        } else if (b.p1.y <= c.center.y && c.center.y <= b.p2.y) {
            return b.p1.x <= c.center.x + c.radius &&
                   c.center.x - c.radius <= b.p2.x;
        } else {
            return c.contains(b.p1) || c.contains(Point2(b.p2.x, b.p1.y)) ||
                   c.contains(b.p2) || c.contains(Point2(b.p1.x, b.p2.y));
        }
    }

    bool intersects(const Circle &c, const Box2 &b)
    {
        return intersects(b, c);
    }

    LineSegment2 separate(const Box2 &b1, const Box2 &b2)
    {
        Box2 i = intersection(b1, b2);
        if (i.dx() <= i.dy()) {
            float y = i.center().y;
            if (b2.p2.x - b1.p1.x <= b1.p2.x - b2.p1.x) {
                return LineSegment2(Point2(b1.p1.x, y), Point2(b2.p2.x, y));
            } else {
                return LineSegment2(Point2(b1.p2.x, y), Point2(b2.p1.x, y));
            }
        } else {
            float x = i.center().x;
            if (b2.p2.y - b1.p1.y <= b1.p2.x - b2.p1.x) {
                return LineSegment2(Point2(x, b1.p1.y), Point2(x, b2.p2.y));
            } else {
                return LineSegment2(Point2(x, b1.p2.y), Point2(x, b2.p1.y));
            }
        }
    }

    LineSegment2 separate(const Circle &c1, const Circle &c2)
    {
        Vector2 normal = c2.center - c1.center;
        if (normal.x == 0.0f && normal.y == 0.0f) {
            normal.x = 1.0f;
        } else {
            normal.normalize();
        }
        return LineSegment2(c1.center + c1.radius * normal,
                            c2.center - c2.radius * normal);
    }
}
