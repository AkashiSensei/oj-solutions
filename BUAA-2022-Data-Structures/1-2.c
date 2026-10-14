/*
 * Evaluate an integer arithmetic expression without parentheses, applying
 * multiplication and division before addition and subtraction.
 */

#include<stdio.h> 
#include<math.h> 
#include<ctype.h> 
#include<stdlib.h> 
#include<string.h> 
#include<time.h>
char a[1000],b[1000],c[1000];
int d[1000],e[1000];
int main()
{
	gets(a);
	int i,j=0,k=0,x=0,y=0;
	int m=0,n=0;
	int len1=strlen(a),len2;
	for(i=0;i<len1;i++)
	{
		if(a[i]!=' ')
		{
			b[j]=a[i];
			j++;
		}
	}
	len2=j;
	for(i=0;i<len2;i++)
	{
		if(b[i]>='0'&&b[i]<='9')
		k++;
		else
		{
			c[x]=b[i];
			x++;
			for(j=0;j<k;j++)
			{
				d[x-1]+=(b[i-j-1]-'0')*pow(10,j);
			}
			k=0;
		}
	}
	if(x==1)
	printf("%d\n", d[0]);
	else
	{
		for(i=0;i<x-1;i++)
		{
			if(c[i]=='/'||c[i]=='*')
			{
				e[i]=1;
				y++;
			}    
		}
		for(i=0;i<x-1;i++)
		{
			if(e[i]==1)
			{
				n++;
				if(c[i]=='/')
				m=d[i]/d[i+1];
			    else
				if(c[i]=='*')
				m=d[i] * d[i+1];
			    for(j=0;j<=n;j++)
				d[i+1-j]=m;
			}
			else
			n=0;
		}
		if(y<x-1)
		{
		int num=0;
		for(j=0;j<x-1;j++)
		{
		    if(c[j]=='+'||c[j]=='-')
		    {
		    	num=d[j];
		    	break;
			}
		}
		for(i=j;i<x-1;i++)
		{
			if(c[i]=='-')
			num-= d[i+1];
			else
			if(c[i]=='+')
			num+=d[i+1];
		}
		printf("%d\n",num);
	    }
	    else
		printf("%d\n",m);
    }
    return 0;
}


