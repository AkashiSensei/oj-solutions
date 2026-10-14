/*
 * Use KMP to search for the first occurrence of a pattern in a text.
 * This version returns 0 for failure as well as for a match at position 0.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
typedef struct node{
    char ch[255];
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
int KMP(Node S,Node T){
    int i=0,j=0;
    int next[T.length];//在局部变量里，数组长度可以用变量来定义
    get_next(T,next);
    while(i<S.length && j<T.length){
        if(-1 == j || S.ch[i] == T.ch[j]){
            i++;
            j++;
        } else {
            j = next[j];
        }   
    }
    if(j==T.length)
        return i-T.length;
    else 
        return 0;
}
int main()
{
    Node S,T;
    scanf("%s",S.ch);
    scanf("%s",T.ch);
    S.length = strlen(S.ch);
    T.length = strlen(T.ch);
    int loc = KMP(S,T);
    printf("%d",loc);
    return 0;
}
