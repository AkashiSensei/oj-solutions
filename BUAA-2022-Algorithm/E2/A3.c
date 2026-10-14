/*
 * Maintain an array-based min heap with insertion, remove-minimum, minimum queries,
 * and deletion by value; print remaining elements in ascending order.
 */

#include <stdio.h>
#define maxn 1000005
#define inf 0x3f3f3f3f
#define ls(x) (x << 1)
#define rs(x) (x << 1 | 1)

int n, sz, a[maxn];

void swap(int *a, int *b)
{
    int t = *a;
    *a = *b, *b = t;
}

void minHeapify(int x)
{
    int l = ls(x), r = rs(x), min;
    if (l <= sz && a[l] < a[x])
        min = l;
    else
        min = x;
    if (r <= sz && a[r] < a[min])
        min = r;
    if (min != x)
        swap(&a[x], &a[min]), minHeapify(min);
}

void increaseKey(int i, int key)
{
    a[i] = key;
    while (i > 1 && a[i / 2] > a[i])
    {
        swap(&a[i / 2], &a[i]);
        i = i / 2;
    }
}

void insert(int x)
{
    sz += 1;
    a[sz] = inf;
    increaseKey(sz, x);
}

int top()
{
    return a[1];
}

void pop()
{
    a[1] = a[sz];
    sz -= 1;
    minHeapify(1);
}

void erase(int x)
{
    int i = 0;
    for (i = 1; i <= sz; i++)
    {
        if(a[i]==x)
            break;
    }
    a[i] = a[sz--];
    if(a[i]>x)
    {
        minHeapify(i);
    }else
    {
        increaseKey(i, a[i]);
    }
}

int main()
{
    scanf("%d", &n);
    int i;
    for (i = 1; i <= n; i++)
    {
        int op, x;
        scanf("%d", &op);
        if (op == 1)
        {
            scanf("%d", &x);
            insert(x);
        }
        if (op == 2)
            pop();
        if (op == 3)
            printf("%d\n", top());
        if (op == 4)
        {
            scanf("%d", &x);
            erase(x);
        }
    }
    while (sz)
    {
        printf("%d ", top()), pop();
    }
}