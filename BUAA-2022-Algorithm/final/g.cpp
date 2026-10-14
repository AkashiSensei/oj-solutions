/*
 * Test whether one input string is a cyclic rotation of the other
 * by searching for it with KMP inside a doubled copy of the first string.
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 1e2+5;

char S[2 * maxn];
char T[maxn];
int ne[maxn];



void GetNext(char p[],int nex[],int n)
{
	nex[0] = -1;
	int k = -1;
	int j = 0;
	while (j < n - 1)
	{
		if (k == -1 || p[j] == p[k]) 
		{
			++k;
			++j;
			nex[j] = k;
		}
		else 
		{
			k = nex[k];
		}
	}
}

bool KmpSearch(int m,int n)
{
	GetNext(T,ne,n);
	
	int pLen = n;
	int sLen = m;
	int i = 0;
	int j = 0;
	
	while(i<sLen){
		if(j==n-1&&S[i]==T[j]){
			//printf("found the number  %d\n",i-j);
            return true;
		}
		if(S[i]==T[j]){
			i++;
			j++;
		}
		else{
			j = ne[j];
			if(j==-1){
				i++;
				j++;
			}
		}
	}
	return false;
}


int main() {
    int g, len;
    scanf("%d", &g);
    fgets(T, maxn, stdin);
    while(g--) {
        
        fgets(S, 2 * maxn, stdin);
        fgets(T, maxn, stdin);
        len = strlen(T);
        if(S[len - 1] == '\r' || S[len - 1] == '\n') {
            S[len - 1] = '\0';
            T[len - 1] = '\0';
            len--;
        }
        if(S[len - 1] == '\r' || S[len - 1] == '\n') {
            S[len - 1] = '\0';
            T[len - 1] = '\0';
            len--;
        }
        
        for(int i = 0; i < len; i++) {
            S[len + i] = S[i];
        }
        S[2 * len] = '\0';
        if(KmpSearch(2 * len, len)) {
            printf("Yes\n");
        }else {
            printf("No\n");
        }
    }
}