/*
 * Find all occurrences of a pattern in a text with KMP
 * and print their zero-based starting positions, including overlapping matches.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <vector>
#include <bits/stdc++.h>
using namespace std;
typedef struct node{
    char ch[1000005];
    int length;
} Node;
void get_next(Node T,int next[]){//数组传入时，由于自己表示的就是地址，所以既是形参也是实参
    int i = 0,j = -1;
    next[0] = -1;
    while(i<T.length){
        if(-1 == j || T.ch[i] == T.ch[j]){
            i++;
            j++;
            next[i] = j;
        } else {
            j = next[j];
        }
    }
    for(j = 1;j<T.length;j++){
        if(T.ch[next[j]] == T.ch[j]){
            next[j] = next[next[j]];
        }
    }
}


vector<int> KMP(const string& S, const string& T)
{
    vector<int> Next;
    Next.push_back(-1);

    for (int i = 0, j = -1; i < T.size();) {
        if (j == -1 || T[i] == T[j]) {
            i++, j++;
            if (i != T.size() && T[j] == T[i]) Next.push_back(Next[j]);
            else Next.push_back(j);
        }
        else j = Next[j];
    }

    vector<int> res;
    for (int i = 0, j = 0; i < S.size() && j < (int)T.size();) {
        if (j == -1 || S[i] == T[j]) {
            i++, j++;
            if (j == T.size()) {
                res.push_back(i - j);
                j = Next[j];
            }
        }
        else j = Next[j];
    }

    return res;
}
int main()
{
    Node S,T;
    scanf("%s",S.ch);
    scanf("%s",T.ch);
    S.length = strlen(S.ch);
    T.length = strlen(T.ch);
    vector<int> v =  KMP(S.ch,T.ch);
    for(int i = 0; i < v.size(); i++){
        printf("%d ",v[i]);
    }
    return 0;
}