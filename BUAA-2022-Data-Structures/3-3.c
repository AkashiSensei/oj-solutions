/*
 * Multiply two polynomials given as coefficient/exponent pairs, combine equal
 * exponents, and print nonzero terms in decreasing exponent order.
 */

#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
struct fx{
	int x;
	int y;
};
int main() 
{
	struct fx f1[100],f2[100],f[100];
	int i=0,j=0,num1,num2;
	while(1)
	{
		scanf("%d%d",&f1[i].x,&f1[i].y);
		i++;
		if(getchar()=='\n')
		break;
	}
	num1=i;
	i=0;
	while(1)
	{
		scanf("%d%d",&f2[i].x,&f2[i].y);
		i++;
		if(getchar()=='\n')
		break;
	}
	num2=i;
	i=0;
	int k=0;
	for(i=0;i<num1;i++)
	{
		for(j=0;j<num2;j++)
		{
			f[k].x=f1[i].x*f2[j].x;
			f[k].y=f1[i].y+f2[j].y;
			k++;
		}
	}
	int change;
    for(i=0;i<k;i++)
	{
		for(j=i+1;j<k;j++)
		{
			if(f[i].y<f[j].y)
			{   change=f[i].x;
				f[i].x=f[j].x;
				f[j].x=change; 
				change=f[i].y;
				f[i].y=f[j].y;
				f[j].y=change;
			}
		}
	}
	for(i=0;i<k;i++)
	{
		for(j=i+1;j<k;j++)
		{
			if(f[i].y==f[j].y)
			{
				f[i].x+=f[j].x;
				f[j].x=0;
			}
		}
	}
	for(i=0;i<k;i++)
	{
		if(f[i].x==0)
		continue;
		else
		printf("%d %d ",f[i].x,f[i].y);
	}
	return 0;
}

