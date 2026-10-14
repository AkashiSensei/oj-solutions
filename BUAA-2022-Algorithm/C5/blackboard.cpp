/*
 * Geometry practice: define points, vectors, and segments with overloaded
 * operators, then demonstrate vector addition and a cross product.
 */

#include<stdio.h>
#include<algorithm>
#define DATA_TYPE long long

struct Point {
    long long x, y;
    Point(long long x, long long y) : x(x), y(y) {}
    Point() {}


    Point operator+(const Point &p2) const {
        return Point(x + p2.x, y + p2.y);
    }
    Point operator-(const Point &p2) const {
        return Point(x - p2.x, y - p2.y);
    }
    bool operator<(const Point &p2) const {
        if(y < p2.y) {
            return true;
        }
        if(y == p2.y) {
            return x < p2.x;
        }
        return false;
    }
    long long operator^(const Point &p2) const {
        return x * p2.y - y * p2.x;
    }
};

struct Vector {
    long long dx, dy;
    Vector(long long dx, long long dy) : dx(dx), dy(dy) {}
    Vector(Point p1, Point p2) : dx(p2.x - p1.x), dy(p2.y - p1.y) {}
    Vector() {}

    Vector operator+(const Vector &v2) const {
        return Vector(dx + v2.dx, dy + v2.dy);
    }
    Vector operator-(const Vector &v2) const {
        return Vector(dx - v2.dx, dy - v2.dy);
    }
    long long operator*(const Vector &v2) const {
        return dx * v2.dx + dy * v2.dy;
    }
    long long operator^(const Vector &v2) const {
        return dx * v2.dy - dy * v2.dx;
    }
    bool operator<(const Vector &v2) const {
        return this->operator^(v2) > 0;
    }
};

struct Segment {
    Point p1, p2;
    Vector dir;
    Segment(Point p1, Point p2) : p1(p1), p2(p2), dir(Vector(p1, p2)) {}
    Segment(Point p1, Vector dir) : p1(p1), dir(dir), p2(Point(p1.x + dir.dx, p1.y + dir.dy)) {}
    Segment() {}
};

int main() {
    Point p1 = Point(1, 3);
    Point p2 = Point(2, 4);
    Point p3 = Point(0, 5);

    Segment s1 = Segment(p1, p2);
    Segment s2 = Segment(p1, p3);

    Vector v1 = Vector(0, 1);
    Vector v2 = Vector(1, 0);

    Vector vp = s2.dir + s1.dir;
    printf("%lld %lld\n", vp.dx, vp.dy);

    long long cross = v1 ^ v2;
    printf("%lld\n", cross);
}