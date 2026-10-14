/*
 * Convert an arithmetic expression to postfix notation, build an expression tree,
 * print its root and immediate children, and evaluate the expression with a stack.
 */

#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
int ca(int x,int y,char c)
{
	if(c=='+')
	{
		return x+y;
	}
	if(c=='-')
	{
		return x-y;
	}
	if(c=='*')
	{
		return x*y;
	}
	if(c=='/')
	{
		return x/y;
	}
	if(c=='%')
	{
		return x%y;
	}
}
struct cal
{
	char calculate[10];
	struct cal *left;
	struct cal *right;
}t1,t2,*r,a[100];
int p(char c)
{
	if(c=='+'||c=='-')
	{
		return 0;
	}
	if(c=='*'||c=='/'||c=='%')
	{
		return 1;
	}
	if(c=='(')
	{
		return 2;
	}
}
void RPN(char s[],char t[])
{
	int top=-1,i,j=0;
	char stack[100];
	int len=strlen(s);
	for(i=0;i<len;i++)
	{
		if(s[i]>='0'&&s[i]<='9')
		{
			t[j++]=s[i];
			if(s[i+1]<'0'||s[i+1]>'9')
			{
				t[j++]=' ';
			}
		}
		else 
		if(s[i]==')')
		{
			while(stack[top]!='(')
			{
				t[j++]=stack[top];
				top--;
			}
			top--;
		}
		else 
		if(s[i]=='+'||s[i]=='-'||s[i]=='*'||s[i]=='/'||s[i]=='%')
		{
			while(p(stack[top])>=p(s[i])&&top!=-1&&stack[top]!='(')
			{
				t[j++]=stack[top];
				top--;
			}
			stack[++top]=s[i];
		}
		else 
		if(s[i]=='(')
		{
			stack[++top]=s[i];
		}
	}
	while(top!=-1)
	{
		t[j++]=stack[top];
		top--;
	}
	t[j]='\0';
}
int main()
{
	int i,j,k,top=-1,sum,b[100],x,y;
	char s[100],t[100],n[10];
	gets(s);
	RPN(s,t);
	for(i=0;i<strlen(t);i++)
	{
		if((i==0||t[i-1]<'0'||t[i-1]>'9')&&t[i]>='0'&&t[i]<='9')
		{
			k=0;
			for(j=i;t[j]>='0'&&t[j]<='9';j++)
			{
				n[k++]=t[j];
			}
			n[k]='\0';
			strcpy(a[++top].calculate,n);
		}
		else 
		if(t[i]=='+'||t[i]=='-'||t[i]=='*'||t[i]=='/')
		{
			free(r);
			r=(struct cal*)malloc(sizeof(struct cal));
			r->right=(struct cal*)malloc(sizeof(struct cal));
			r->left=(struct cal*)malloc(sizeof(struct cal));
			n[0]=t[i];
			n[1]='\0';
			strcpy(r->calculate,n);
			*(r->right)=a[top--];
			*(r->left)=a[top--];
			a[++top]=*r;
		}
	}
	printf("%s %s %s\n",r->calculate,r->left->calculate,r->right->calculate);
	top=-1;
	int len1=strlen(t);
	for(i=0;i<len1;i++)
	{
		if((i==0||(t[i-1]>'9'||t[i-1]<'0'))&&(t[i]>='0'&&t[i]<='9'))
		{
			sum=0;
		for(j=i;t[j]>='0'&&t[j]<='9';j++)
		{
			sum=sum*10+t[j]-'0';
		}	
		b[++top]=sum;
		}
		else 
		if(t[i]=='+'||t[i]=='-'||t[i]=='*'||t[i]=='/'||t[i]=='%') 
		{
			y=b[top--];
			x=b[top--];
			sum=ca(x,y,t[i]);
			b[++top]=sum;
		}
	}
	printf("%d\n",b[0]);
	return 0;
}




