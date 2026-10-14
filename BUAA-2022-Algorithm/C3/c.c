/*
 * Find a minimum-cost route through stations on two assembly lines,
 * including line-transfer costs, and reconstruct the chosen line at each station.
 */

#include<stdio.h>
long long COST[2][105];
long long MIN[2][105];
long long CHANGE[3][3];
int ROAD[3][105];

void output(int n, int station) {
    if(n == 1) {
        return;
    }
    else{
        output(n - 1, ROAD[station][n]);
        printf("Station%d, Line%d\n", n - 1, ROAD[station][n]);
    }
}

int main() {
    long long min, m, from1, from2;
    scanf("%lld", &m);
    for(int i = 1; i <= m; i++) {
        scanf("%lld", &COST[1][i]);
    }
    for(int i = 1; i <= m; i++) {
        scanf("%lld", &COST[2][i]);
    }


    for(int i = 1; i <= 2; i++) {
        scanf("%lld", &CHANGE[1][i]);
    }
    for(int i = 1; i <= 2; i++) {
        scanf("%lld", &CHANGE[2][i]);
    }

    MIN[1][1] = COST[1][1];
    MIN[2][1] = COST[2][1];

    for(int sta = 2; sta <= m; sta++) {
        from1 = MIN[1][sta - 1] + CHANGE[1][1] + COST[1][sta];
        from2 = MIN[2][sta - 1] + CHANGE[2][1] + COST[1][sta];
        if(from1 < from2) {
            ROAD[1][sta] = 1;
            MIN[1][sta] = from1;
        } else {
            ROAD[1][sta] = 2;
            MIN[1][sta] = from2;
        }

        from1 = MIN[1][sta - 1] + CHANGE[1][2] + COST[2][sta];
        from2 = MIN[2][sta - 1] + CHANGE[2][2] + COST[2][sta];
        if(from1 < from2) {
            ROAD[2][sta] = 1;
            MIN[2][sta] = from1;
        } else {
            ROAD[2][sta] = 2;
            MIN[2][sta] = from2;
        }
    }

    if(MIN[1][m] < MIN[2][m]) {
        printf("%lld\n", MIN[1][m]);
        output(m, 1);
        printf("Station%d, Line1\n", m);
    }else {
        printf("%lld\n", MIN[2][m]);
        output(m, 2);
        printf("Station%d, Line2\n", m);
    }
}