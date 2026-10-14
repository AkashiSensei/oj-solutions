/*
 * Scan a 19-by-19 board for four equal nonzero pieces in a row with an open end.
 * Check horizontal, vertical, and diagonal directions; report the first match.
 */

#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
int main()
{
	int a[20][20];
	int i,j;
	for(i=0;i<19;i++)
	{
		for(j=0;j<19;j++)
		{
			scanf("%d",&a[i][j]);
		}
	}
	for(i=0;i<19;i++)
	{
		for(j=0;j<19;j++)
		{
		if(a[i][j]!=0)
		{
			if((a[i][j]==a[i+1][j]&&a[i][j]==a[i+2][j]&&a[i][j]==a[i+3][j])&&(a[i+4][j]==0||a[i-1][j]==0))
			{
				printf("%d:%d,%d\n",a[i][j],i+1,j+1);
				return 0;
			}
			if((a[i][j+1]==a[i][j]&&a[i][j]==a[i][j+2]&&a[i][j]==a[i][j+3])&&(a[i][j-1]==0||a[i][j+4]==0))
			{
				printf("%d:%d,%d\n",a[i][j],i+1,j+1); 
				return 0;
			}
			if((a[i][j]==a[i+1][j+1]&&a[i][j]==a[i+2][j+2]&&a[i][j]==a[i+3][j+3])&&(a[i-1][j-1]==0||a[i+4][j+4]==0))
			{
				printf("%d:%d,%d\n",a[i][j],i+1,j+1);
				return 0;
			}
			if((a[i][j]==a[i+1][j-1]&&a[i][j]==a[i+2][j-2]&&a[i][j]==a[i+3][j-3])&&(a[i+4][j-4]==0||a[i-1][j+1]==0))
			{
				printf("%d:%d,%d\n",a[i][j],i+1,j+1);
				return 0;
			}		
		}
		}
	}
	printf("No\n");
	return 0;
}

