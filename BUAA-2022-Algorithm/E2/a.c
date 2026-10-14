/*
 * Implement a min-priority queue with an array heap, including deletion by value.
 * Process operation codes and print the remaining elements in ascending order.
 */

#include<stdio.h>
#define MAXSIZE 100005

int HEAP_LIST[MAXSIZE];

int popTop(int *, int);
int queryTop(int *, int);
int insert(int *, int, int);
void changeDown(int *, int, int);
void changeUp(int *, int);
void delete(int *, int, int);
int search(int *, int, int, int);

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
        case 4:
            scanf("%d", &input);
            delete(HEAP_LIST, input, count--);
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
    int leftChi = index * 2 + 1, minChildValue, minChildIndex;
    if(leftChi >= cou) {
        return;
    }
    if(leftChi + 1 < cou && heap[leftChi] > heap[leftChi + 1]){
        minChildValue = heap[leftChi + 1];
        minChildIndex = leftChi + 1;
    }else {
        minChildValue = heap[leftChi];
        minChildIndex = leftChi;
    }

    if(temp <= minChildValue) {
        return;
    }else {
        heap[index] = minChildValue;
        heap[minChildIndex] = temp;
        changeDown(heap, cou, minChildIndex);
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
    if(heap[index] >= heap[faInd]) {
        return;
    }
    int temp = heap[index];
    heap[index] = heap[faInd];
    heap[faInd] = temp;
    changeUp(heap, faInd);
}

void delete(int * heap, int x, int cou) {
    int index = search(heap, x, 0, cou);
    //printf("%d", heap[index]);
    if(heap[cou - 1] > heap[index]) {
        heap[index] = heap[--cou];
        changeDown(heap, cou, index);
    } else if(heap[cou - 1] < heap[index]) {
        heap[index] = heap[--cou];
        changeUp(heap, index);
    }
    
    changeDown(heap, cou, index);
}

int search(int *heap, int key, int index, int cou) {
    /*
    if(index >= cou) {
        return -1;
    }

    if(heap[index] == key) {
        return index;
    }

    if(heap[index] > key) {
        return -1;
    }

    int leftResult = search(heap, key, index * 2 + 1, cou);
    if(~leftResult) {
        return leftResult;
    }

    return search(heap, key, index * 2 + 2, cou);
    */
   

    for(int i = 0; i < cou; i++) {
        if(heap[i] == key) {
            return i;
        }
    }
}