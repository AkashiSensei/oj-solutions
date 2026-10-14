/*
 * Read a and b, compute gcd(a, 360*b), and print a divided by that gcd.
 * The original application is not identifiable from this fragment alone.
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    long long a, b;
    cin >> a >> b;
    long long gcd = __gcd(a, b * 360);
    printf("%lld", a / gcd);

}