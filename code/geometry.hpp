#ifndef MONOMI_GEOMETRY_HPP
#define MONOMI_GEOMETRY_HPP

namespace monomi {
    const float pi = 3.14159265358979323846264338327950288419716939937510f;

    class Point2;

    class Vector2 {
    public:
        float x, y;

        Vector2();
        explicit Vector2(float f);
        Vector2(float x, float y);
        explicit Vector2(const Point2 &p);

        float length() const;
        float squaredLength() const;

        Vector2 operator-() const;

        Vector2 &operator+=(const Vector2 &v);
        Vector2 &operator-=(const Vector2 &v);
        Vector2 &operator*=(float f);
        Vector2 &operator/=(float f);

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

    class Box2;

    class Point2 {
    public:
        float x, y;

        Point2();
        Point2(float x, float y);
        explicit Point2(const Vector2 &v);

        Point2 &operator+=(const Vector2 &v);
        Point2 &operator-=(const Vector2 &v);
    };

    Point2 operator+(const Point2 &p, const Vector2 &v);
    Point2 operator+(const Vector2 &v, const Point2 &p);
    Point2 operator-(const Point2 &p, const Vector2 &v);
    Vector2 operator-(const Point2 &p1, const Point2 &p2);

    float distance(const Point2 &p1, const Point2 &p2);
    float squaredDistance(const Point2 &p1, const Point2 &p2);

    class LineSegment2 {
    public:
        Point2 p1, p2;

        LineSegment2();
        LineSegment2(const Point2 &p1, const Point2 &p2);

        float length() const;
        float squaredLength() const;
    };

    class Box2 {
    public:
        Point2 p1, p2;

        Box2();
        Box2(const Point2 &p1, const Point2 &p2);

        Point2 center() const;
        bool empty() const;
        float width() const;
        float height() const;
        float perimeter() const;
        float area() const;

        void clear();
        void grow(const Point2 &p);
        void grow(const Box2 &b);
    };

    Box2 intersection(const Box2 &b1, const Box2 &b2);

    class Circle {
    public:
        Point2 center;
        float radius;

        Circle();
        Circle(const Point2 &center, float radius);

        bool contains(const Point2 &p) const;
    };

    bool intersects(const Box2 &b1, const Box2 &b2);
    bool intersects(const Circle &c1, const Circle &c2);
    bool intersects(const Box2 &b, const Circle &c);
    bool intersects(const Circle &c, const Box2 &b);

    LineSegment2 separate(const Box2 &b1, const Box2 &b2);
    LineSegment2 separate(const Circle &c1, const Circle &c2);
}

#endif // MONOMI_GEOMETRY_HPP
