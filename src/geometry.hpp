#ifndef MONOMI_GEOMETRY_HPP
#define MONOMI_GEOMETRY_HPP

#include <complex>
#include <iostream>

namespace monomi {
    const float pi = 3.14159265358979323846264338327950288419716939937510f;

    bool finite(float x);
    float sign(float x);

    class Vector2 {
    public:
        float x, y;

        Vector2();
        explicit Vector2(float f);
        Vector2(float x, float y);

        float length() const;
        float squaredLength() const;

        Vector2 operator-() const;

        Vector2 &operator+=(const Vector2 &v);
        Vector2 &operator-=(const Vector2 &v);
        Vector2 &operator*=(float f);
        Vector2 &operator/=(float f);

        float normalize();
        void rotate(std::complex<float> const &c);
    };

    Vector2 operator+(const Vector2 &v1, const Vector2 &v2);
    Vector2 operator-(const Vector2 &v1, const Vector2 &v2);
    Vector2 operator*(const Vector2 &v, float f);
    Vector2 operator*(float f, const Vector2 &v);
    Vector2 operator/(const Vector2 &v, float f);

    std::ostream &operator<<(std::ostream &out, const Vector2 &v);

    float dot(const Vector2 &v1, const Vector2 &v2);
    float cross(const Vector2 &v1, const Vector2 &v2);
    Vector2 cross(const Vector2 &v);
    Vector2 normalize(const Vector2 &v);

    float distance(const Vector2 &p1, const Vector2 &p2);
    float squaredDistance(const Vector2 &p1, const Vector2 &p2);

    Vector2 rotate(Vector2 const &v, std::complex<float> const &c);
    Vector2 rotate(std::complex<float> const &c, Vector2 const &v);

    class Box2 {
    public:
        Vector2 p1, p2;

        Box2();
        Box2(const Vector2 &p);
        Box2(const Vector2 &p1, const Vector2 &p2);

        Vector2 center() const;
        bool empty() const;
        float dx() const;
        float dy() const;
        float perimeter() const;
        float area() const;

        void clear();
        void merge(const Vector2 &p);
        void merge(const Box2 &b);
        void intersect(const Box2 &b);

        bool contains(const Vector2 &p) const;
    };

    Box2 merge(const Box2 &b1, const Box2 &b2);
    Box2 intersect(const Box2 &b1, const Box2 &b2);

    class LineSegment2 {
    public:
        Vector2 p1, p2;

        LineSegment2();
        LineSegment2(const Vector2 &p1, const Vector2 &p2);

        float length() const;
        float squaredLength() const;
        Box2 boundingBox() const;
    };

    class Circle {
    public:
        Vector2 center;
        float radius;

        Circle();
        Circle(const Vector2 &center, float radius);

        float perimeter() const;
        float area() const;
        Box2 boundingBox() const;

        bool contains(const Vector2 &p) const;
    };

    bool intersects(const Box2 &b1, const Box2 &b2);
    bool intersects(const Circle &c1, const Circle &c2);
    bool intersects(const Box2 &b, const Circle &c);
    bool intersects(const Circle &c, const Box2 &b);

    LineSegment2 separate(const Vector2 &p, const Box2 &c);
    LineSegment2 separate(const Box2 &b, const Vector2 &p);
    LineSegment2 separate(const Vector2 &p, const Circle &c);
    LineSegment2 separate(const Circle &c, const Vector2 &p);
    LineSegment2 separate(const Box2 &b1, const Box2 &b2);
    LineSegment2 separate(const Circle &c1, const Circle &c2);
    LineSegment2 separate(const Box2 &b, const Circle &c);
    LineSegment2 separate(const Circle &c, const Box2 &b);
}

#endif // MONOMI_GEOMETRY_HPP
