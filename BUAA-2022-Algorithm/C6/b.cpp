/*
 * Check whether all input points lie on the line through the first two points
 * by testing cross products, and print the corresponding fixed response.
 */

#include<stdio.h>
#include<stdlib.h>

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
    long long operator^(const Point &p2) const {
        return x * p2.y - y * p2.x;
    }
};

int main() {
    int t, n;
    Point p0, p1, pLine, pIn;
    bool isNoline;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        isNoline = false;
        scanf("%lld %lld", &p0.x, &p0.y);
        scanf("%lld %lld", &p1.x, &p1.y);
        pLine = p1 - p0;
        n -= 2;
        while(n--) {
            scanf("%lld %lld", &pIn.x, &pIn.y);
            if(!isNoline) {
                if(pLine ^ (pIn - p0))  {
                    isNoline = true;
                }
            }
        }
        if(isNoline)printf("how?\n");
        else printf("boo how! boo how!\n");
    }
}