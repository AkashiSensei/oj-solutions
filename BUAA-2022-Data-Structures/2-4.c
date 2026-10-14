/*
 * Remove duplicate name/phone entries, add suffixes to distinguish repeated names
 * with different numbers, and print the directory sorted by name.
 */

#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
struct phone
{
	char name[100];
	char number[100];
}
*p,a[100];
int main()
{
	int n,i;
	scanf("%d",&n);
	for(p=a;p<a+n;p++)
	{
		scanf("%s %s",p->name,p->number);
	}
	cut(a,n);
	under(a,n);
	sort(a,n);
	for(i=0;i<n;i++)
	{
		if(strcmp(a[i].name,"0")!=0||strcmp(a[i].number,"0")!=0)
		{
			printf("%s %s\n",a[i].name,a[i].number);
		}
	}
	return 0;
}
void under(struct phone a[],int n)
{
	int i,j;
	char s[2]="_0";
	for(i=0;i<n;i++)
	{
		if(strcmp(a[i].name,"0")==0&&strcmp(a[i].number,"0")==0)
		    {
				continue;
			}	
		strcpy(s,"_0");
		for(j=i+1;j<n;j++)
		{
			if(strcmp(a[i].name,a[j].name)==0&&strcmp(a[i].number,a[j].number)!=0)
			{
				s[1]++;
				strcat(a[j].name,s);
			}
		}
	}
}
void cut(struct phone a[],int n)
{
	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=i+1;j<n;j++)
		{
			if(strcmp(a[i].name,a[j].name)==0&&strcmp(a[i].number,a[j].number)==0)
			{
				strcpy(a[j].name,"0");
				strcpy(a[j].number,"0");
			}
		}
	}
}
void sort(struct phone a[],int n)
{
	struct phone tmp;
	int i,j;
	for(i=0;i<n;i++)
	{
		int check=0;
		for(j=i;j<n;j++)
		{
			if(strcmp(a[i].name,a[j].name)>0)
			{
				tmp=a[i];
				a[i]=a[j];
				a[j]=tmp;
				check=1;
			}
		}
		if(check==0)
		{
			break;
		}
	}
}

