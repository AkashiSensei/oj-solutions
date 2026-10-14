/*
 * Sort counted items by value and accumulate their total weighted cost.
 * The multiplier increases at the supplied cumulative-count thresholds.
 */

#include <bits/stdc++.h>

#define ZHUAN 100005

using namespace std;

struct zhuan{
    int value, cnt;
}LIST[ZHUAN];

long long TIMES[ZHUAN];

int cmp_zhuan(const void * p1, const void * p2) {
    return ((zhuan *)p1)->value - ((zhuan *)p2)->value;
}

int cmp_times(const void * p1, const void * p2) {
    return *(long long *)p1 - *(long long *)p2;    
}


int main() {
    int group, n, m, d, t, list_inx, t_inx, sub, eat;
    long long result, cnt, f, ttt;
    scanf("%d", &group);
    while(group--) {
        scanf("%d", &n);
        cnt = 0;
        for(int i = 0; i < n; i++) {
            scanf("%d %d", &LIST[i].cnt, &LIST[i].value);
            cnt += LIST[i].cnt;
        }

        scanf("%d", &t);
        t_inx = 0;
        for(int i = 0; i < t; i++ ) {
            scanf("%lld", &ttt);
            if(ttt < cnt) {
                TIMES[t_inx++] = ttt;
            }
        }

        qsort(LIST, n, sizeof(zhuan), cmp_zhuan);
        qsort(TIMES, t_inx, sizeof(long long), cmp_times);

        list_inx = 0;
        f = 1;
        result = 0;
        t = t_inx;
        t_inx = 0;
        cnt = 0;
        for(int i = 0; i < n; i++) {
            while(1) {
                sub = TIMES[t_inx] - cnt;
                if(sub > LIST[i].cnt || sub < 0) {
                    eat = LIST[i].cnt;
                }else eat = sub;

                if(TIMES[t_inx] == 0) eat = LIST[i].cnt;

                result += f * LIST[i].value * eat;
                LIST[i].cnt -= eat;
                cnt += eat;
                
                if(TIMES[t_inx] == cnt) {
                    f++;
                    t_inx++;
                }

                if(LIST[i].cnt == 0) {
                    break;
                }
            }
        }
        memset(TIMES, 0, t * sizeof(long long));
        printf("%lld\n", result);
    }
}