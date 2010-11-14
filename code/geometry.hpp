#ifndef MONOMI_GEOMETRY_HPP
#define MONOMI_GEOMETRY_HPP

namespace monomi {
    class Vector2 {
    public:
        float x, y;

        Vector2();
        Vector2(float x, float y);

        Vector2 operator-() const;

        Vector2 &operator+=(const Vector2 &v);
        Vector2 &operator-=(const Vector2 &v);
        Vector2 &operator*=(float f);
        Vector2 &operator/=(float f);

        float length() const;
        float squaredLength() const;

        float normalize();
    };

    Vector2 operator+(const Vector2 &v1, const Vector2 &v2);
    Vector2 operator-(const Vector2 &v1, const Vector2 &v2);
    Vector2 operator*(const Vector2 &v, float f);
    Vector2 operator*(float f, const Vector2 &v);
    Vector2 operator/(const Vector2 &v, float f);

    float dot(const Vector2 &v1, const Vector2 &v2);
    float cross(const Vector2 &v1, const Vector2 &v2);
    Vector2 cross(const Vector2 &v);
    Vector2 normalize(const Vector2 &v);

    float distance(const Vector2 &p1, const Vector2 &p2);
    float squaredDistance(const Vector2 &p1, const Vector2 &p2);

    class LineSegment2 {
    public:
        Vector2 p1, p2;

        LineSegment2();
        LineSegment2(const Vector2 &p1, const Vector2 &p2);

        float length() const;
        float squaredLength() const;
    };

    class Box2 {
    public:
        Vector2 p1, p2;

        Box2();
        Box2(const Vector2 &p1, const Vector2 &p2);
    };

    class Circle {
    public:
        Vector2 center;
        float radius;

        Circle();
        Circle(const Vector2 &center, float radius);
    };
}

#endif // MONOMI_GEOMETRY_HPP
