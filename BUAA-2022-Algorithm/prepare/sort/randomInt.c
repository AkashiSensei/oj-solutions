/*
 * Generate random integer test data and ascending/descending sorted variants.
 * Write the generated data to both standard output and randomInt.txt.
 */

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define DATA_TYPE int

int LIST[1000005];

int cmp(const void *p1, const void *p2) {
    return *(int *)p1 - *(int *)p2;
}

int main() {
    DATA_TYPE div, max, length, group;
    printf("div, max, length, group\n");
    scanf("%d %d %d %d", &div, &max, &length, &group);

    FILE *fp = fopen("randomInt.txt", "w");
    srand(time(0));

    DATA_TYPE temp;
    for(int i = 0; i < group; i++) {
        for(int j = 0; j < length; j++) {
            temp = (rand() + rand() +rand()) % max + div;
            printf("%d ", temp);
            fprintf(fp, "%d ", temp);
        }
        printf("\n");
        fprintf(fp, "\n");
    }

    for(int j = 0; j < length; j++) {
        LIST[j] = (rand() + rand() +rand()) % max + div;
    }
    printf("\n");
    fprintf(fp, "\n");

    for(int j = 0; j < length; j++) {
        printf("%d ", LIST[j]);
        fprintf(fp, "%d ", LIST[j]);
    }
    printf("\n");
    fprintf(fp, "\n");

    qsort(LIST, length, sizeof(int), cmp);
    
    for(int j = 0; j < length; j++) {
        printf("%d ", LIST[j]);
        fprintf(fp, "%d ", LIST[j]);
    }
    printf("\n");
    fprintf(fp, "\n");

    for(int j = length - 1; j >= 0; j--) {
        printf("%d ", LIST[j]);
        fprintf(fp, "%d ", LIST[j]);
    }
    
    fclose(fp);
}
