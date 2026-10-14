/*
 * Arithmetic experiment that repeatedly multiplies an int by 3 in an endless loop.
 * There is no input or output; the value eventually exceeds the signed-int range.
 */

#include<stdio.h>

int main() {
    int a = 3;
    while(1) {
        a *= 3;
    }
}