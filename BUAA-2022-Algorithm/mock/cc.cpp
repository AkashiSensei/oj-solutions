/*
 * Maintain the median of a growing sequence using two heaps and a central value.
 * Print the median after each odd-length prefix.
 */

#include <bits/stdc++.h>

using namespace std;
int main() {
    int t;
    cin >> t;
    while (t--) {
        priority_queue<int> leftNum;
        priority_queue<int, vector<int>, greater<int> > rightNum;
        int n, centre, a ,b;
        scanf("%d %d", &n, &centre);
        n--;
        printf("%d ", centre);
        while(n) {
            scanf("%d %d", &a, &b);
            if(a > centre) {
                rightNum.push(a);
            }else {
                leftNum.push(a);
            }

            if(b > centre) {
                rightNum.push(b);
            }else {
                leftNum.push(b);
            }

            if((a > centre) + (b > centre) == 1) {
                printf("%d ", centre);
            }else if((a > centre) + (b > centre) == 2) {
                leftNum.push(centre);
                centre = rightNum.top();
                printf("%d ", centre);
                rightNum.pop();
            }else {
                rightNum.push(centre);
                centre = leftNum.top();
                printf("%d ", centre);
                leftNum.pop();
            }

            n -= 2;
        }
        printf("\n");
    }
}