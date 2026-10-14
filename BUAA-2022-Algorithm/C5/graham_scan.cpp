/*
 * Build the convex hull of planar points with Graham scan
 * and compute the perimeter of the resulting polygon.
 */

#include<stdio.h>
#include<algorithm>
#include<math.h>

#define MAXSIZE 3005

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



Point P_LIST[MAXSIZE];
int P_CNT;
Point STACK[MAXSIZE];
int TOP = -1;
Point P0 = Point(__LONG_LONG_MAX__, __LONG_LONG_MAX__);



bool cmp(Point p1, Point p2) {
    return (p1.x - P0.x) * (p2.y - P0.y) - (p1.y - P0.y) * (p2.x - P0.x) > 0;
}

bool is_left(Point p0, Point p1, Point p2) {
    return (p1.x - p0.x) * (p2.y - p0.y) - (p1.y - p0.y) * (p2.x - p0.x) > 0;
}

double length(Point p0, Point p1) {
    return sqrt(pow(p0.x - p1.x, 2) + pow(p0.y - p1.y, 2));
}

int main() {
    int n, t;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        P_CNT = 0;
        TOP = -1;
        P0.x = __LONG_LONG_MAX__;
        P0.y = __LONG_LONG_MAX__;

        long long x, y;
        int min_ind;
        for(int i = 0; i < n; i++) {
            scanf("%lld%lld", &x, &y);
            P_LIST[P_CNT] = Point(x, y);
            if(P_LIST[P_CNT] < P0) {
                min_ind = P_CNT;
                P0 = P_LIST[P_CNT];
            }
            P_CNT++;
        }

        P_LIST[min_ind] = P_LIST[0];
        P_LIST[0] = P0;

        sort(P_LIST + 1, P_LIST + n, cmp);

        STACK[++TOP] = P_LIST[0];
        STACK[++TOP] = P_LIST[1];

        for(int i = 2; i < n; i++) {
            while(!is_left(STACK[TOP - 1], STACK[TOP], P_LIST[i])) {
                TOP--;
            }
            STACK[++TOP] = P_LIST[i];
        }

        double c = 0;
        for(int i = 0; i < TOP; i++) {
            c += length(STACK[i], STACK[i + 1]);
        }
        c += length(STACK[TOP], STACK[0]);
        printf("%.10lf\n", c);
    }
}