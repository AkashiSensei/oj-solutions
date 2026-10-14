/*
 * Compute a longest common subsequence of two input lines with dynamic
 * programming, then reconstruct and print one such subsequence.
 */

#include<stdio.h>
#include<string.h>

char X[1005];
char Y[1005];
short C[1002][1002];
char B[1002][1002];
int LEN_X, LEN_Y;

void printLcs(short, short);

int main() {
    gets(X);
    gets(Y);
    LEN_X = strlen(X);
    LEN_Y = strlen(Y);
    
    for(int i = 0; i < LEN_X; i++) {
        for(int j = 0; j < LEN_Y; j++) {
            if(X[i] == Y[j]) {
                C[i + 1][j + 1] = C[i][j] + 1;
                B[i][j] = 1;
            }else if(C[i][j + 1] >= C[i + 1][j]) {
                C[i + 1][j + 1] = C[i][j + 1];
                B[i][j] = 2;
            }else {
                C[i + 1][j + 1] = C[i + 1][j];
                B[i][j] = 4;
            }
        }
    }
    printLcs(LEN_X - 1, LEN_Y - 1);
}

void printLcs(short xInd, short yInd) {
    if(xInd == -1 || yInd == -1) {
        return;
    }
    //printf("%hd %hd\n", xInd, yInd);
    if(B[xInd][yInd] == 1) {
        printLcs(xInd - 1, yInd - 1);
        printf("%c", X[xInd]);
    }else if(B[xInd][yInd] == 2) {
        printLcs(xInd - 1, yInd);
    }else {
        printLcs(xInd, yInd - 1);
    }
}