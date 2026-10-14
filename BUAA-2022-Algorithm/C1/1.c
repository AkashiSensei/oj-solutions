/*
 * Classify the growth of T(n) = a*T(n/b) + n^k using the Master theorem.
 */

#include<stdio.h>
#include<math.h>

int main() {
    int n;
    double a, b, k;
    //double left;
    double right;
    scanf("%d", &n);

    for(int i = 0; i < n; i++) {
        scanf("%lf %lf %lf", &a, &b, &k);
        right = pow(b, k);
        if(fabs(a - right) < 1e-12) {
            printf("n^k\\log n\n");
        }else if(a > right) {
            printf("n^{\\log_ba}\n");
        }else{
            printf("n^k\n");
        }
    }
}