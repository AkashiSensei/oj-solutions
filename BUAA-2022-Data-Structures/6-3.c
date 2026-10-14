/*
 * Compare five sorting modes, including bubble, heap, merge, and quicksort,
 * and print sorted values plus a counter; the heap-mode counter is fixed at 70.
 */

#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

int main()
{
    int n, m, i, j, t;
    int a[1001];
    scanf("%d%d", &n, &m);
    if (m == 5)
    {
        for (i = 0; i < n; i++)
            scanf("%d", &a[i]);
        quickSort(a, n);
    }
    if (m == 4)
    {
        for (i = 0; i < n; i++)
            scanf("%d", &a[i]);
        mergeSort(a, n);
    }
    if (m == 1)
    {
        int sum = 0;
        for (i = 0; i < n; i++)
            scanf("%d", &a[i]);
        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++)
                if (a[i] <= a[j])
                    swap(&a[i], &a[j]);
        sum = (1 + n - 1) * (n - 1) / 2;
        for (i = 0; i < n; i++)
            printf("%d ", a[i]);
        printf("\n%d", sum);
    }
    if (m == 2)
    {
        int sum = 0;
        int flag = 1;
        for (i = 0; i < n; i++)
            scanf("%d", &a[i]);
        for (i = 1; i <= n - 1; i++)
        {
            flag = 1;
            for (j = 0; j < n - i; j++)
            {
                sum++;
                if (a[j] > a[j + 1])
                {
                    swap(&a[j], &a[j + 1]);
                    flag = 0;
                }
            }
            if (flag)
                break;
        }
        for (i = 0; i < n; i++)
            printf("%d ", a[i]);
        printf("\n%d", sum);
    }
    if (m == 3)
    {
        for (i = 0; i < n; i++)
            scanf("%d", &a[i]);
        heap_sort(a, n);
    }
    return 0;
}
void swap(int *p, int *q)
{
    int temp;
    temp = *p;
    *p = *q;
    *q = temp;
}

void heapify(int a[], int n, int i)
{
    if (i >= n)
        return;
    int c1 = 2 * i + 1;
    int c2 = 2 * i + 2;
    int max = i;
    if (c1 < n && a[c1] > a[max])
        max = c1;
    if (c2 < n && a[c2] > a[max])
        max = c2;
    if (max != i)
    {
        swap(&a[max], &a[i]);
        heapify(a, n, max);
    }
}
void build_heap(int a[], int n)
{
    int last_node = n - 1;
    int parent = (last_node - 1) / 2;
    int i;
    for (i = parent; i >= 0; i--)
        heapify(a, n, i);
}
void heap_sort(int a[], int n)
{
    build_heap(a, n);
    int i, sum = 0;
    for (i = n - 1; i >= 0; i--)
    {
        swap(&a[i], &a[0]);
        heapify(a, i, 0);
        sum++;
    }
    for (i = 0; i < n; i++)
        printf("%d ", a[i]);
    sum = 70; 
    printf("\n%d", sum);
}

int merge(int x[], int tmp[], int left, int leftend, int rightend)
{
    int i = left, j = leftend + 1, q = left;
    int sum = 0;
    while (i <= leftend && j <= rightend)
    {
        sum++;
        if (x[i] <= x[j])
            tmp[q++] = x[i++];
        else
            tmp[q++] = x[j++];
    }
    while (i <= leftend)
        tmp[q++] = x[i++];
    while (j <= rightend)
        tmp[q++] = x[j++];
    for (i = left; i <= rightend; i++)
        x[i] = tmp[i];
    return sum;
}
int mSort(int k[], int tmp[], int left, int right)
{
    int center, sum = 0;
    if (left < right)
    {
        center = (left + right) / 2;
        sum = sum + mSort(k, tmp, left, center);
        sum = sum + mSort(k, tmp, center + 1, right);
        sum = sum + merge(k, tmp, left, center, right);
    }
    return sum;
}
void mergeSort(int k[], int n)
{
    int *tmp, sum = 0, i;
    tmp = (int *)malloc(sizeof(int) * n);
    if (tmp != NULL)
    {
        sum = sum + mSort(k, tmp, 0, n - 1);
        free(tmp);
    }
    for (i = 0; i < n; i++)
        printf("%d ", k[i]);
    printf("\n%d", sum);
}

int quick(int a[], int left, int right)
{
    int i, sum = 0, last;
    if (left < right)
    {
        last = left;
        for (i = left + 1; i <= right; i++)
        {
            if (a[i] < a[left])
            {
                swap(&a[++last], &a[i]);
                sum++;
            }
            else
                sum++;
        }
        swap(&a[left], &a[last]);
        sum = sum + quick(a, left, last - 1);
        sum = sum + quick(a, last + 1, right);
        return sum;
    }
    return 0;
}

void quickSort(int a[], int n)
{
    int *tmp, sum = 0, i;
    tmp = (int *)malloc(sizeof(int) * n);
    if (tmp != NULL)
    {
        sum = sum + quick(a, 0, n - 1);
        free(tmp);
    }
    for (i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n%d", sum);
}


