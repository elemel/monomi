#include "geometry.hpp"

#include <cmath>

namespace monomi {
    Vector2::Vector2() :
        x(0.0f),
        y(0.0f)
    { }

    Vector2::Vector2(float x, float y) :
        x(x),
        y(y)
    { }

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

    float Vector2::length() const {
        return std::sqrt(squaredLength());
    }

    float Vector2::squaredLength() const {
        return dot(*this, *this);
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

    float distance(const Vector2 &p1, const Vector2 &p2)
    {
        return (p2 - p1).length();
    }

    float squaredDistance(const Vector2 &p1, const Vector2 &p2)
    {
        return (p2 - p1).squaredLength();
    }

    LineSegment2::LineSegment2()
    { }

    LineSegment2::LineSegment2(const Vector2 &p1, const Vector2 &p2) :
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

    Box2::Box2(const Vector2 &p1, const Vector2 &p2) :
        p1(p1),
        p2(p2)
    { }

    Circle::Circle() :
        radius(0.0f)
    { }

    Circle::Circle(const Vector2 &center, float radius) :
        center(center),
        radius(radius)
    { }
}
