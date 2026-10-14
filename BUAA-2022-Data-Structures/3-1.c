/*
 * Follow chains of segments whose end coordinates match the next segment's start.
 * Report the largest chain count found and its starting coordinates.
 */

#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
struct place
{
	int m1[2];
    int m2[2];
}a[100];
int main()
{
	struct place most;
	int n,i,num=1,*q,max=0;
	q=&num;
	scanf("%d",&n); 
	for(i=0;i<n;i++)
	{
		scanf("%d%d%d%d",&a[i].m1[0],&a[i].m1[1],&a[i].m2[0],&a[i].m2[1]);
	}
	sort(a,n);
	for(i=0;i<n;i++)
	{
		num=1;
		find(a,n,i,q);
		if(num>max)
		{
			max=num;
			most=a[i];
		}
	}
	printf("%d %d %d",max,most.m1[0],most.m1[1]);
return 0;
}
void sort(struct place a[],int n)
{
	struct place tmp;
	int i,j;
	for(i=0;i<n;i++)
	{
		int check=0;
		for(j=i;j<n;j++)
		{
			if(a[i].m1[0]>a[j].m1[0])
			{
				tmp=a[i];
				a[i]=a[j];
				a[j]=tmp;
				check=1;
			}
		}
		if(check==0)
		{
			break;
		}
	}
}
void find(struct place a[],int n,int s,int *q)
{
	int i=0;
	for(i=0;i<n;i++)
	{
		if(a[s].m2[0]==a[i].m1[0]&&a[s].m2[1]==a[i].m1[1])
		{
			(*q)++;
			find(a,n,i,q);
		}
		if(a[s].m2[0]<a[i].m1[0])
		{
			return 0;
		}
	}
}





