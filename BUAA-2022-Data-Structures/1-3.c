/*
 * Convert a positive decimal number supplied as text into scientific notation
 * by locating its significant digits and adjusting the decimal exponent.
 */

#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
char a[105];
int main()
{
	int i,j=0,n=1,wz;
	gets(a);
	int length=strlen(a);
	for(i=0;i<length;i++)
	{
		if(a[i]=='.')
		{
			wz=i;
			break;
		}
	}
	if(a[0]=='0')
	{
		for(i=2;i<length;i++)
		{
			if(a[i]=='0')
			n++;
			else
			break;
	    }
	    if(n==length-2)
	    printf("%ce-%d\n",a[i],n);
	    else
	    {
	        printf("%c.",a[n+1]);
	        for(j=n+2;j<length;j++)
	        printf("%c",a[j]);
	        printf("e-%d\n",n);
	    }
    }
	else
	{
		if(wz==1)    
		{
		   for(i=0;i<length;i++)
		   printf("%c",a[i]);
		   printf("e0\n");
	    }
	    else
	    {
	    	printf("%c.",a[0]);
	    	for(i=1;i<length;i++)
	    	{
	    		if(a[i]=='.')
	    		continue;
	    		printf("%c",a[i]);
			}
			printf("e%d",wz-1);
		}
	}
	return 0;
}


