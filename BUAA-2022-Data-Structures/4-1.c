/*
 * Process stack push and pop operations using an array.
 * Print popped values or an error for an empty stack; stop on operation -1.
 */

#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
int stack[105], top = -1;
int Empty()
{
	return top==-1;
}
void push(int item)
{
	stack[++top]=item;
}
int pop()
{
	int m;
	m=stack[top];
	stack[top]=0;
	top--;
	return m;
}
int main()
{
    int i,j=0,k=0,a,b;
    while(scanf("%d",&a)!=EOF&&a!= -1)
    {
    	if(a)
    	{
    		scanf("%d",&b);
    		push(b);
		}
		else
		{
			if(Empty()) 
			printf("error ");
			else
			{
				b=pop();
				printf("%d ",b);
			}
		}
	}
    return 0;
}

