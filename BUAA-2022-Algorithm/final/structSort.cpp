/*
 * Demonstrate sorting Point structures with an overloaded comparison operator,
 * ordering first by x and then by y, and print the sorted x coordinates.
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

struct Point{
    LL x, y;

    bool operator<(const Point &n) const {
        return (x == n.x)? y < n.y : x < n.x;
    }
}a[100];

int main() {
    for(int i = 0; i < 100; i++) {
        a[i].x = 200 - i;
    }
    sort(a, a+100);
    for(int i = 0; i < 100; i++) {
        cout << a[i].x << endl;
    }
}