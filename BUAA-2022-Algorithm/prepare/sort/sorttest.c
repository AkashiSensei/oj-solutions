/*
 * Read integer groups from randomInt.txt and demonstrate insertion sort
 * or merge sort in either order, selected by compile-time constants.
 */

#include<stdio.h>

#define LENGTH 20
#define GROUP 8
#define CODE 11

int LIST[100005];
int MERGE_1[50005], MERGE_2[50005];

int compare_up(int, int);
int compare_down(int, int);

void insert_sort(int *, int, int (*)(int, int));
void merge(int *, int, int, int, int (*)(int, int));
void merge_sort(int *, int, int, int (*)(int, int));

int main() {
    FILE * fp = fopen("randomInt.txt", "r");

    for(int i = 0; i < GROUP; i++) {
        for(int j = 0; j < LENGTH; j++) {
            fscanf(fp, "%d", &LIST[j]);
        }

        switch(CODE) {
            case 0:
                insert_sort(LIST, LENGTH, compare_up);
                break;
            case 1:
                insert_sort(LIST, LENGTH, compare_down);
                break;

            case 10:
                merge_sort(LIST, 0, LENGTH - 1, compare_up);
                break;
            case 11:
                merge_sort(LIST, 0, LENGTH - 1, compare_down);
                break;
        }

        for(int j = 0; j < LENGTH; j++) {
            printf("%d ", LIST[j]);
        }
        printf("\n");
    }
}

int compare_up(int left, int right) {
    return left - right;
}
int compare_down(int left, int right) {
    return right - left;
}



void insert_sort(int *list, int length, int (*cmp)(int, int)) {

    int temp, i;
    for(int j = 1; j < length; j++) {
        temp = list[j];
        
        for(i = j - 1; i >= 0 && cmp(list[i], temp) > 0; i--) {
            list[i + 1] = list[i];
        }
        list[i + 1] = temp;
    }
}


void merge(int *list, int left, int mid, int right, int (*cmp)(int, int)) {
    int pNew, pLeft, pRight;
    for(pNew = 0, pLeft = left; pLeft <= mid; pNew++, pLeft++) {
        MERGE_1[pNew] = list[pLeft];
    }
    MERGE_1[pNew] = cmp(1073741823, 0);

    for(pNew = 0, pRight = mid + 1; pRight <= right; pNew++, pRight++) {
        MERGE_2[pNew] = list[pRight];
    }
    MERGE_2[pNew] = cmp(1073741823, 0);

    for(pNew = left, pRight = 0, pLeft = 0; pNew <= right; pNew++) {
        if(cmp(MERGE_1[pLeft], MERGE_2[pRight]) < 0) {
            list[pNew] = MERGE_1[pLeft++];
        }else {
            list[pNew] = MERGE_2[pRight++];
        }
    }
}
void merge_sort(int *list, int left, int right, int (*cmp)(int, int)) {
    if(left >= right)
    return;

    int mid = (left + right) / 2;
    merge_sort(list, left, mid, cmp);
    merge_sort(list, mid + 1, right, cmp);
    merge(list, left, mid, right, cmp);
}