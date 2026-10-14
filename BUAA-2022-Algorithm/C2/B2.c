/*
 * Maintain an array-based max heap for insertion, deletion of the maximum,
 * and maximum queries; sort and print the remaining values in descending order.
 */

#include<stdio.h>
#include<stdlib.h>

int a[1000000] = {0};

void swap(int *a, int* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void adjustHeap(int *a, int i, int n)
{
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    // 选出最大的结点
    int max = i;
    if (left < n && a[left] > a[max])
        max = left;
    if (right < n && a[right] > a[max])
        max = right;
    if (max != i)
    {
        swap(&a[i], &a[max]);
        // 1. 从下往上遍历保证了子树均为最大堆
        // 2. 若max!=i, 可能会破坏某子树的最大堆，因此要重新调整
        adjustHeap(a, max, n);
    }
}



void insert(int *a, int n)
{
    int son,fa;
   son = n-1;
   fa = (son-1)/2; //0号位置不存储数据
   while(son > 0)
   {
     if(a[son] <= a[fa])
         break;
    
     //若heap[son] < heap[fa] 则交换
     swap(&a[son],&a[fa]);
     
     //节点上移
     son = fa;
     fa = (son-1)/2;
   }
}

void Hdelete(int *a, int n)
{
    //printf("d:%d\n", a[0]);
    swap(&a[0], &a[n - 1]);
    adjustHeap(a, 0, n-1);
}

int cmp(const void *a, const void *b)
{
    int *x = (int *)a;
    int *y = (int *)b;
    return *y - *x;
}

int main()
{
    int n = 0;
    scanf("%d", &n);
    
    int cnt = 0;
    while(n--)
    {
        int x = 0;
        scanf("%d", &x);
        if(x==1)
        {
            int tmp = 0;
            scanf("%d", &tmp);
            a[cnt] = tmp;
            cnt++;
            insert(a, cnt);
        }else if(x==2)
        {
            Hdelete(a,cnt);
            cnt--;
        }else if(x==3)
        {
            int top = a[0];
            printf("%d\n", top);
        }
    }
    qsort(a, cnt, sizeof(a[0]), cmp);
    for (int i = 0; i < cnt;i++)
    {
        printf("%d ", a[i]);
    }
    return 0;
}