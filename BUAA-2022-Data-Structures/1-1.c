/*
 * Expand ascending character ranges such as a-d or 1-4 in an input string,
 * while leaving unrecognized hyphens unchanged.
 */

#include<stdio.h> 
#include<math.h> 
#include<ctype.h> 
#include<stdlib.h> 
#include<string.h> 
#include<time.h>
char a[1000];
int main()
{
    gets(a);
    int i,j,k;
    int length=strlen(a);
    for(i=0;i<length;i++)
    {
    	if(a[i]=='-')
		{
    		k=i;
    		if(a[k-1] >='0'&& a[k+1]<='9'&&a[k-1]<a[k+1])
    		{
    			for(j=0;j<a[k+1]-a[k-1];j++)
				printf("%c",a[k-1]+j+1); 
			}
			else
    		if(a[k-1]>='a'&&a[k+1]<='z'&&a[k-1]<a[k+1])
    		{
    			for(j=0;j<a[k+1]-a[k-1];j++)
				printf("%c",a[k-1]+j+1); 
			}
		    else
			if(a[k-1]>='A'&&a[k+1]<='Z'&&a[k-1]<a[k+1])
    		{
    			for(j=0;j<a[k+1]-a[k-1];j++)
				printf("%c",a[k-1]+j+1); 
			}
			else
			{
				printf("%c",a[k]);
				printf("%c",a[k+1]);
			}    
		    i++;
		}
		else
		printf("%c",a[i]);    
	}
    return 0;
}


