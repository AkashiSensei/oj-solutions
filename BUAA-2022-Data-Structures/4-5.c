/*
 * Simulate arrivals and waiting times in a service queue, adjusting the number
 * of service windows between three and five according to the queue length.
 */

#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
struct line{
	int number;
	int time;
}a[300]; 
void in(struct line a[])
{
	int i;
	for(i=0;i<300;i++)
	{
		a[i].number=i;
		a[i].time=0;
	}
}

int front=1,rear=0,count=0,num=3;
int main()
{
	in(a);
	int n,i,t;
	int add[n+1];
	scanf("%d",&n);
	for(i=1;i<=n;i++)
	{
		scanf("%d",&add[i]);
	}
	for(t=1;;t++)
	{
		for(i=front;i<=rear;i++)
		{
			a[i].time++;
		}
		if(t<=n)
		{
		   for(i=0;i<add[t];i++)
		   {
		   	rear++;
		   	count++;
		   	if(count/num>=7&&num<5)
			   {
		   		num++;
			   }
		   }	
		}
		for(i=0;i<num&&count!=0;i++)
		{
			printf("%d : %d\n",a[front].number,a[front].time);
			front++;
			count--;		
		}
		if(count/num<7&&num>3)
		{
				num--;	
		}	
		if(t>n&&count==0)
		{
			break;
		}
	}
	return 0;
}





