/*
 * Count ordered positive integer solutions of x^k + y^k = z^k.
 * Handle k = 1 directly, scan Pythagorean pairs for k = 2, and return 0 for k > 2.
 */

#include<stdio.h>
#include<math.h>
#define DELTA 1e-7

int main() {
    int group, k, count, z;
    double root, z2, hz;
    scanf("%d", &group);
    for (int i = 0; i < group; i++) {
        scanf("%d %d", &z, &k);
        if(k > 2) {
            printf("0\n");
            continue;
        }
        if(k == 1) {
            printf("%d\n", z - 1);
            continue;
        }
        if(z == 1) {
            printf("0\n");
            continue;
        }


        z2 = pow(z, 2);
        double up = pow(0.5, 0.5) * z;
        count = 0;
        for(double j = 1; j < up; j += 1) {
            root = pow(z2 - j * j, 0.5);
            if(root < (int)root + DELTA || root > (int)root + 1 - DELTA) {
                count++;
                //printf("    %lf %lf\n", j, root);
            }
        }
        printf("%d\n", 2 * count);
    }
}