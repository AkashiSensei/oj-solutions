/*
 * Use a stack to check brackets in example.c, attempting to ignore comments
 * and quoted strings; report an unmatched bracket and its line when found.
 */

#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
struct brackets
{
	char c;
	int line;
}a[200];
int pre(char c)
{
	if(c=='('||c=='['||c=='{')
	{
		return 1;
	}
	return 0;
}
int late(char c)
{
	if(c==')'||c==']'||c=='}')
	{
		return 1;
	}
	return 0;	
}
int match(char a,char b)
{
	if((a=='('&&b==')')||(a=='['&&b==']')||(a=='{'&&b=='}'))
	{
		return 1;
	}
	return 0;
}
int main()
{
	FILE *in;
	in=fopen("example.c","r");
	int check=0,i,l=1,top=-1,j=0,k=0,f=0,g=0;
	char s[200],b[200];
	while(fgets(s,200,in)!=NULL)
	{
		int len=strlen(s);
		for(i=0;i<len;i++)
		{
			if(s[i]=='/'&&s[i+1]=='/')
			{
				break;
			}
			else 
			if(s[i]=='/'&&s[i+1]=='*')
			{
				check=1;
			}
			else 
			if(s[i]=='*'&&s[i+1]=='/')
			{
				check=0;
			}
			else 
			if(s[i]=='"')
			{
				f++;
				if(f%2==0)
				{
					check=0;
				}
				else
				{
					check=1;
				}
			}
			else 
			if(pre(s[i])==1&&check==0)
			{
				if(s[i]!='[')
				{
					b[j++]=s[i];
				}
				a[++top].c=s[i];
				a[top].line=l;
				if(s[i]=='{'){
					for(k=0;k<top;k++)
					{
						if(a[k].c=='(')
						{
							printf("without maching '(' at line %d",a[k].line);
							return 0;
						}
					}
				}
			}
			else 
			if(late(s[i])==1&&check==0)
			{
				if(s[i]!=']')
				{
					b[j++]=s[i];
				}
				if(match(a[top].c,s[i])==0)
				{
				printf("without maching '%c' at line %d",s[i],l);
				return 0;	
				}
				top--;
			}
		}
		l++;
	} 
	if(top==0)
	{
		printf("without maching '%c' at line %d",a[0].c,a[0].line);
	}
	else
	{
		for(k=0;k<j;k++)
		{
			printf("%c",b[k]);
		}
	}
	return 0;
}






