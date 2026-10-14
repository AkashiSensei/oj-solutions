/*
 * Count case-insensitive word occurrences in article.txt using an array of records,
 * then print words and their frequencies in alphabetical order.
 */

#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
struct word{
	char w[20];
	int times;
}s[100]={"",0};
int main()
{
	int i,j,k,n=0,check;
	FILE *in;
	in=fopen("article.txt","r");
	char a[200],b[200],c[20];
	while(fgets(a,200,in)!=NULL)
	{
		change(a,b);
	    small(b);
	    j=0;
	    for(i=0;b[i]!='\0';i++)
		{
	    	if(b[i]!=' ')
			{
	    		c[j++]=b[i];
			}
			else
			if(b[i]==' ')
			{
				c[j]='\0';
				j=0;
				check=0;
				for(k=0;k<n;k++)
				{
					if(strcmp(c,s[k].w)==0)
					{
						s[k].times++;
						check=1;
						break;
					}
				}
				if(check==0&&strlen(c)!=0)
				{
					strcpy(s[n].w,c);
					s[n].times++;
					n++;
				}
			}
	    }
    }
    sort(s,n);
    for(i=0;i<n;i++)
	{
    	printf("%s %d\n",s[i].w,s[i].times);
	}
	return 0;
}
void change(char s[],char t[])
{
	int i,j;
	for(i=0,j=0;s[i]!='\0';i++){
		if((s[i]>='a'&&s[i]<='z')||(s[i]>='A'&&s[i]<='Z')||s[i]==' ')
		{
			t[j++]=s[i];
		}
		else
		{
			t[j++]=' ';
		}
	}
	t[j++]=' ';
	t[j]='\0';
}
void small(char t[])
{
	int i;
	for(i=0;i<strlen(t);i++)
	{
		if(t[i]>='A'&&t[i]<='Z')
		{
			t[i]=t[i]+32;
		}
	}
}
void sort(struct word a[],int n)
{
	int i,j;
	struct word tmp;
	for(i=0;i<n;i++)
	{
		for(j=i+1;j<n;j++)
		{
			if(strcmp(a[i].w,a[j].w)>0)
			{
				tmp=a[i];
				a[i]=a[j];
				a[j]=tmp;
			}
		}
	}
}




