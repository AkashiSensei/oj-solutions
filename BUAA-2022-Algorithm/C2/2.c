/*
 * Process insert, remove-maximum, and query-maximum operations with an array heap.
 * Print the remaining values in descending order.
 */

#include<stdio.h>
#define MAXSIZE 100005

int HEAP_LIST[MAXSIZE];

int popTop(int *, int);
int queryTop(int *, int);
int insert(int *, int, int);
void changeDown(int *, int, int);
void changeUp(int *, int);

int main() {
    int count = 0;
    int n, code, input;
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        scanf("%d", &code);
        switch (code)
        {
        case 1:
            scanf("%d", &input);
            insert(HEAP_LIST, count, input);
            count++;
            break;
        case 2:
            popTop(HEAP_LIST, count);
            count--;
            break;
        case 3:
            printf("%d\n", queryTop(HEAP_LIST, count));
            break;
        default:
            return 1;
        }
    }
    while(count) {
        printf("%d ", popTop(HEAP_LIST, count));
        count--;
    }
}


int popTop(int * heap, int cou) {
    int value = heap[0];
    if(cou == 1) {
        return value;
    }
    heap[0] = heap[--cou];
    changeDown(heap, cou, 0);
    return value;
}
void changeDown(int * heap, int cou, int index) {
    int temp = heap[index];
    int leftChi = index * 2 + 1, maxChiVal, bigInd;
    if(leftChi >= cou) {
        return;
    }
    if(leftChi + 1 < cou && heap[leftChi] < heap[leftChi + 1]){
        maxChiVal = heap[leftChi + 1];
        bigInd = leftChi + 1;
    }else {
        maxChiVal = heap[leftChi];
        bigInd = leftChi;
    }

    if(temp >= maxChiVal) {
        return;
    }else {
        heap[index] = maxChiVal;
        heap[bigInd] = temp;
        changeDown(heap, cou, bigInd);
    }
}

int queryTop(int * heap, int cou){
    if(cou == 0) {
        printf("???\n");
        return 0;
    }
    else {
        return heap[0];
    }
}

int insert(int * heap, int cou, int value) {
    heap[cou++] = value;
    changeUp(heap, cou - 1);
}
void changeUp(int * heap, int index) {
    if(index == 0){
        return;
    }
    int faInd = (index - 1) / 2;
    if(heap[index] <= heap[faInd]) {
        return;
    }
    int temp = heap[index];
    heap[index] = heap[faInd];
    heap[faInd] = temp;
    changeUp(heap, faInd);
}