/*
 * Generate and print every permutation of the integers 1 through n
 * using recursive backtracking.
 */

#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
int a[15];
 void qpl(int n,int a[],int num)
 {
	int i,j;
	if(num==n)
	{
		for(i=0;i<n;i++)
		{
			printf("%d ",a[i]);
		}
		printf("\n");
	}
	else
	{
		for(i=0;i<n;i++)
		{
			int check=0;
			for(j=0;j<num;j++)
			{
				if(a[j]==i+1)
				{
					check=1;
				}
			}
			if(check==0)
			{
				a[num]=i+1;
				qpl(n,a,num+1);
			}
		}
	}
}
int main()
{
	int n;
	scanf("%d",&n);
	qpl(n,a,0);
	return 0;
}



