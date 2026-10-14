/*
 * Read two long-long integers and print their difference.
 */

#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
int main()
{   long long a,b;
    scanf("%lld\n%lld",&a,&b);
	long long c=a-b;
	printf("%lld",c);
	return 0;
}



