#ifndef MONOMI_GEOMETRY_HPP
#define MONOMI_GEOMETRY_HPP

#include <cmath>
#include <iostream>
#include <vector>

namespace monomi {
    const float pi = 3.14159265358979323846264338327950288419716939937510f;

    inline bool finite(float f)
    {
        return std::abs(f) <= std::numeric_limits<float>::max();
    }

    inline float sign(float f)
    {
        return f < 0.0f ? -1.0f : 1.0f;
    }

    inline float square(float f)
    {
        return f * f;
    }

    class Vector2 {
    public:
        float x, y;

        Vector2();
        explicit Vector2(float f);
        Vector2(float x, float y);

        float length() const;
        float squaredLength() const;

        Vector2 operator-() const;

        Vector2 &operator+=(Vector2 const &v);
        Vector2 &operator-=(Vector2 const &v);
        Vector2 &operator*=(float f);
        Vector2 &operator/=(float f);

        float normalize();
    };

    inline Vector2::Vector2() :
        x(0.0f), y(0.0f)
    { }

    inline Vector2::Vector2(float f) :
        x(f), y(f)
    { }

    inline Vector2::Vector2(float x, float y) :
        x(x), y(y)
    { }

    inline float Vector2::length() const
    {
        return std::sqrt(squaredLength());
    }

    inline float Vector2::squaredLength() const
    {
        return square(x) + square(y);
    }

    inline Vector2 Vector2::operator-() const
    {
        return Vector2(-x, -y);
    }

    inline Vector2 &Vector2::operator+=(Vector2 const &v)
    {
        x += v.x;
        y += v.y;
        return *this;
    }

    inline Vector2 &Vector2::operator-=(Vector2 const &v)
    {
        x -= v.x;
        y -= v.y;
        return *this;
    }

    inline Vector2 &Vector2::operator*=(float f)
    {
        x *= f;
        y *= f;
        return *this;
    }

    inline Vector2 &Vector2::operator/=(float f)
    {
        x /= f;
        y /= f;
        return *this;
    }

    inline float Vector2::normalize()
    {
        float f = squaredLength();
        if (f != 0.0f && f != 1.0f) {
            *this /= std::sqrt(f);
        }
        return f;
    }

    inline Vector2 operator+(Vector2 const &v1, Vector2 const &v2)
    {
        return Vector2(v1) += v2;
    }

    inline Vector2 operator-(Vector2 const &v1, Vector2 const &v2)
    {
        return Vector2(v1) -= v2;
    }

    inline Vector2 operator*(Vector2 const &v, float f)
    {
        return Vector2(v) *= f;
    }

    inline Vector2 operator*(float f, Vector2 const &v)
    {
        return Vector2(v) *= f;
    }

    inline Vector2 operator/(Vector2 const &v, float f)
    {
        return Vector2(v) /= f;
    }

    inline float dot(Vector2 const &v1, Vector2 const &v2)
    {
        return v1.x * v2.x + v1.y * v2.y;
    }

    inline float cross(Vector2 const &v1, Vector2 const &v2)
    {
        return v1.x * v2.y - v2.x * v1.y;
    }

    inline Vector2 cross(Vector2 const &v)
    {
        return Vector2(-v.y, v.x);
    }

    inline Vector2 normalize(Vector2 const &v)
    {
        Vector2 v2(v);
        v2.normalize();
        return v2;
    }

    inline float distance(Vector2 const &p1, Vector2 const &p2)
    {
        return (p2 - p1).length();
    }

    inline float squaredDistance(Vector2 const &p1, Vector2 const &p2)
    {
        return (p2 - p1).squaredLength();
    }

    std::ostream &operator<<(std::ostream &out, Vector2 const &v);

    class Matrix3 {
    public:
        float a, b, c;
        float d, e, f;
        float g, h, i;

        Matrix3();
        explicit Matrix3(float x);
        Matrix3(float a, float b, float c,
                float d, float e, float f);
        Matrix3(float a, float b, float c,
                float d, float e, float f,
                float g, float h, float i);

        float scale() const;

        Matrix3 &operator+=(Matrix3 const &m);
        Matrix3 &operator-=(Matrix3 const &m);
        Matrix3 &operator*=(Matrix3 const &m);
        Matrix3 &operator*=(float x);
        Matrix3 &operator/=(float x);

        void transpose();
    };

    inline Matrix3::Matrix3() :
        a(1.0f), b(0.0f), c(0.0f),
        d(0.0f), e(1.0f), f(0.0f),
        g(0.0f), h(0.0f), i(1.0f)
    { }

    inline Matrix3::Matrix3(float x) :
        a(x), b(x), c(x),
        d(x), e(x), f(x),
        g(x), h(x), i(x)
    { }

    inline Matrix3::Matrix3(float a, float b, float c,
                            float d, float e, float f) :
        a(a), b(b), c(c),
        d(d), e(e), f(f),
        g(0.0f), h(0.0f), i(1.0f)
    { }

    inline Matrix3::Matrix3(float a, float b, float c,
                            float d, float e, float f,
                            float g, float h, float i) :
        a(a), b(b), c(c),
        d(d), e(e), f(f),
        g(g), h(h), i(i)
    { }

    inline Matrix3 &Matrix3::operator+=(Matrix3 const &m)
    {
        a += m.a;
        b += m.b;
        c += m.c;

        d += m.d;
        e += m.e;
        f += m.f;

        g += m.g;
        h += m.h;
        i += m.i;

        return *this;
    }

    inline Matrix3 &Matrix3::operator-=(Matrix3 const &m)
    {
        a -= m.a;
        b -= m.b;
        c -= m.c;

        d -= m.d;
        e -= m.e;
        f -= m.f;

        g -= m.g;
        h -= m.h;
        i -= m.i;

        return *this;
    }

    inline Matrix3 &Matrix3::operator*=(float x)
    {
        a *= x;
        b *= x;
        c *= x;

        d *= x;
        e *= x;
        f *= x;

        g *= x;
        h *= x;
        i *= x;

        return *this;
    }

    inline Matrix3 &Matrix3::operator/=(float x)
    {
        a /= x;
        b /= x;
        c /= x;

        d /= x;
        e /= x;
        f /= x;

        g /= x;
        h /= x;
        i /= x;

        return *this;
    }

    inline void Matrix3::transpose()
    {
        std::swap(d, b);
        std::swap(g, c);
        std::swap(h, f);
    }

    inline Matrix3 operator*(Matrix3 const &m1, Matrix3 const &m2)
    {
        return Matrix3(m1.a * m2.a + m1.b * m2.d + m1.c * m2.g,
                       m1.a * m2.b + m1.b * m2.e + m1.c * m2.h,
                       m1.a * m2.c + m1.b * m2.f + m1.c * m2.i,
          
                       m1.d * m2.a + m1.e * m2.d + m1.f * m2.g,
                       m1.d * m2.b + m1.e * m2.e + m1.f * m2.h,
                       m1.d * m2.c + m1.e * m2.f + m1.f * m2.i,
          
                       m1.g * m2.a + m1.h * m2.d + m1.i * m2.g,
                       m1.g * m2.b + m1.h * m2.e + m1.i * m2.h,
                       m1.g * m2.c + m1.h * m2.f + m1.i * m2.i);
    }

    inline Matrix3 &Matrix3::operator*=(Matrix3 const &m)
    {
        return *this = *this * m;
    }

    inline Vector2 operator*(Matrix3 const &m, Vector2 const &p)
    {
        return Vector2(m.a * p.x + m.b * p.y + m.c,
                       m.d * p.x + m.e * p.y + m.f);
    }

    class Box2 {
    public:
        Vector2 p1, p2;

        Box2();
        Box2(Vector2 const &p1, Vector2 const &p2);

        Vector2 center() const;
        bool empty() const;
        float dx() const;
        float dy() const;
        float perimeter() const;
        float area() const;

        void clear();
        void merge(Vector2 const &p);
        void merge(Box2 const &b);
    };

    inline Box2::Box2()
    { }

    inline Box2::Box2(Vector2 const &p1, Vector2 const &p2) :
        p1(p1),
        p2(p2)
    { }

    inline Vector2 Box2::center() const
    {
        return Vector2(0.5f * (p1.x + p2.x), 0.5f * (p1.y + p2.y));
    }

    inline bool Box2::empty() const
    {
        return dx() <= 0.0f || dy() <= 0.0f;
    }

    inline float Box2::dx() const
    {
        return p2.x - p1.x;
    }

    inline float Box2::dy() const
    {
        return p2.y - p1.y;
    }

    inline float Box2::perimeter() const
    {
        return 2.0f * (dx() + dy());
    }

    inline float Box2::area() const
    {
        return dx() * dy();
    }

    inline void Box2::clear()
    {
        p1.x = std::numeric_limits<float>::max();
        p1.y = std::numeric_limits<float>::max();
        p2.x = std::numeric_limits<float>::min();
        p2.y = std::numeric_limits<float>::min();
    }

    inline void Box2::merge(Vector2 const &p)
    {
        p1.x = std::min(p1.x, p.x);
        p1.y = std::min(p1.y, p.y);
        p2.x = std::max(p2.x, p.x);
        p2.y = std::max(p2.y, p.y);
    }

    inline void Box2::merge(const Box2 &b)
    {
        p1.x = std::min(p1.x, b.p1.x);
        p1.y = std::min(p1.y, b.p1.y);
        p2.x = std::max(p2.x, b.p2.x);
        p2.y = std::max(p2.y, b.p2.y);
    }

    inline Box2 intersect(const Box2 &b1, const Box2 &b2)
    {
        float x1 = std::max(b1.p1.x, b2.p1.x);
        float y1 = std::max(b1.p1.y, b2.p1.y);
        float x2 = std::min(b1.p2.x, b2.p2.x);
        float y2 = std::min(b1.p2.y, b2.p2.y);
        return Box2(Vector2(x1, y1), Vector2(x2, y2));
    }

    class LineSegment2 {
    public:
        Vector2 p1, p2;

        LineSegment2();
        LineSegment2(Vector2 const &p1, Vector2 const &p2);

        float length() const;
        float squaredLength() const;
        Box2 boundingBox() const;
    };

    inline LineSegment2::LineSegment2()
    { }

    inline LineSegment2::LineSegment2(Vector2 const &p1, Vector2 const &p2) :
        p1(p1),
        p2(p2)
    { }

    inline float LineSegment2::length() const
    {
        return distance(p1, p2);
    }

    inline float LineSegment2::squaredLength() const
    {
        return squaredDistance(p1, p2);
    }

    inline Box2 LineSegment2::boundingBox() const
    {
        return Box2(Vector2(std::min(p1.x, p2.x), std::min(p1.y, p2.y)),
                    Vector2(std::max(p1.x, p2.x), std::max(p1.y, p2.y)));
    }

    class Circle2 {
    public:
        Vector2 center;
        float radius;

        Circle2();
        Circle2(Vector2 const &center, float radius);

        float perimeter() const;
        float area() const;
        Box2 boundingBox() const;

        void transform(Matrix3 const &m);
    };

    inline Circle2::Circle2() :
        radius(0.0f)
    { }

    inline Circle2::Circle2(Vector2 const &center, float radius) :
        center(center),
        radius(radius)
    { }

    inline float Circle2::perimeter() const
    {
        return 2.0f * pi * radius;
    }

    inline float Circle2::area() const
    {
        return pi * square(radius);
    }

    inline Box2 Circle2::boundingBox() const
    {
        return Box2(center - Vector2(radius), center + Vector2(radius));
    }

    inline Circle2 transform(Circle2 const &c, Matrix3 const &m)
    {
        Circle2 result(c);
        result.transform(m);
        return result;
    }

    class Polygon2 {
    public:
        std::vector<Vector2> vertices;

        Polygon2();
        explicit Polygon2(Box2 const &b);

        void transform(Matrix3 const &m);
    };

    inline Polygon2::Polygon2()
    { }

    inline Polygon2 transform(Polygon2 const &p, Matrix3 const &m)
    {
        Polygon2 result(p);
        result.transform(m);
        return result;
    }

    inline bool intersects(Vector2 const &p1, Vector2 const &p2)
    {
        return false;
    }

    inline bool intersects(Box2 const &b1, Box2 const &b2)
    {
        return (b1.p1.x <= b2.p2.x && b2.p1.x <= b1.p2.x &&
                b1.p1.y <= b2.p2.y && b2.p1.y <= b1.p2.y);
    }

    inline bool intersects(Box2 const &b, Vector2 const &p)
    {
        return (b.p1.x <= p.x && p.x <= b.p2.x &&
                b.p1.y <= p.y && p.y <= b.p2.y);
    }

    bool intersects(Box2 const &b, Circle2 const &c);

    inline bool intersects(Circle2 const &c1, Circle2 const &c2)
    {
        return (squaredDistance(c1.center, c2.center) <=
                square(c1.radius + c2.radius));
    }

    inline bool intersects(Circle2 const &c, Vector2 const &p)
    {
        return squaredDistance(c.center, p) <= square(c.radius);
    }

    inline bool intersects(Vector2 const &p, Box2 const &b)
    {
        return intersects(b, p);
    }

    inline bool intersects(Vector2 const &p, Circle2 const &c)
    {
        return intersects(c, p);
    }

    inline bool intersects(Circle2 const &c, Box2 const &b)
    {
        return intersects(b, c);
    }
}

#endif // MONOMI_GEOMETRY_HPP
