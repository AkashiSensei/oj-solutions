/*
 * Classify the relationship between two lines or line segments using
 * cross products, distinguishing parallel, coincident, and intersection cases.
 */

#include<stdio.h>
#include<algorithm>
#include<math.h>
#include<iostream>
#define DATA_TYPE long long

using namespace std;

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
    int type;
    Point p1, p2;
    Vector dir;
    Segment(int type, Point p1, Point p2) : type(type), p1(p1), p2(p2), dir(Vector(p1, p2)) {}
    Segment(Point p1, Vector dir) : p1(p1), dir(dir), p2(Point(p1.x + dir.dx, p1.y + dir.dy)) {}
    Segment() {}
};


bool is_on(Point p, Segment s) {
    return min(s.p1.x, s.p2.x) <= p.x && p.x <= max(s.p1.x, s.p2.x) && min(s.p1.y, s.p2.y) <= p.y && p.y <= max(s.p1.y, s.p2.y);
}


int main() {
    int t;
    scanf("%d", &t);
    int type;
    long long x1, y1, x2, y2;
    Segment s1, s2;
    long long d11, d12, d21, d22;
    while (t--) {
        scanf("%d%lld%lld%lld%lld", &type, &x1, &y1, &x2, &y2);
        s1 = Segment(type, Point(x1, y1), Point(x2, y2));
        scanf("%d%lld%lld%lld%lld", &type, &x1, &y1, &x2, &y2);
        s2 = Segment(type, Point(x1, y1), Point(x2, y2));


        if(s1.type == 1 && s2.type == 1) {
            if((s1.dir ^ s2.dir) == 0) {
                if((s1.dir ^ Vector(s1.p1, s2.p1)) == 0) {
                    printf("Coincide\n");
                    continue;
                }else {
                    printf("Parallel\n");
                    continue;
                }
            }
            else {
                printf("Intersect\n");
                continue;
            }
        }else if(s1.type + s2.type == 3) {
            if(s1.type == 1) {
                d11 = s1.dir ^ Vector(s1.p1, s2.p1);
                d12 = s1.dir ^ Vector(s1.p1, s2.p2);

                if(d11 == 0 || d12 == 0) {
                    printf("Not strict\n");
                    continue;
                }else if(d11 < 0 && d12 > 0 || d11 > 0 && d12 < 0) {
                    printf("Strict\n");
                    continue;
                }else {
                    printf("Don't intersect\n");
                    continue;
                }
            }else {
                d21 = s2.dir ^ Vector(s2.p1, s1.p1);
                d22 = s2.dir ^ Vector(s2.p1, s1.p2);

                if(d21 == 0 || d22 == 0) {
                    printf("Not strict\n");
                    continue;
                }else if(d21 < 0 && d22 > 0 || d21 > 0 && d22 < 0) {
                    printf("Strict\n");
                    continue;
                }else {
                    printf("Don't intersect\n");
                    continue;
                }
            }
        }else {
            d11 = s1.dir ^ Vector(s1.p1, s2.p1);
            d12 = s1.dir ^ Vector(s1.p1, s2.p2);
            d21 = s2.dir ^ Vector(s2.p1, s1.p1);
            d22 = s2.dir ^ Vector(s2.p1, s1.p2);

            if((d11 == 0 && is_on(s2.p1, s1)) || (d12 == 0 && is_on(s2.p2, s1))
            || (d21 == 0 && is_on(s1.p1, s2)) || (d22 == 0 && is_on(s1.p2, s2))) {
                printf("Not strict\n");
                continue;
            }else if((d11 < 0 && d12 > 0 || d11 > 0 && d12 < 0) && (d21 < 0 && d22 > 0 || d21 > 0 && d22 < 0)) {
                printf("Strict\n");
                continue;
            }else {
                printf("Don't intersect\n");
                continue;
            }
        }
    }    
}