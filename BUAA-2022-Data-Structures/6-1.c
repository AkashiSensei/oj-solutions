/*
 * Search dictionary3000.txt using sequential search, binary search, initial-letter
 * indexing, or chained hashing; print whether the word was found and comparisons.
 */

#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define NHASH  3001
#define MULT  37
char word[3500][50];
int N;
int a[50];
struct Hash{
	char t[50];
	struct Harh *link;
	int flag;
};
struct Hash b[3001];
void hash(char *str)
{
	unsigned int h=0;
    char *p;
    struct Hash *q;
    for(p=str;*p!='\0';p++)
	{
    	h=MULT*h+*p;
	}
    h=h%NHASH;
    if(b[h].flag==0)
	{
    	strcpy(b[h].t,str);
    	b[h].flag=1;
	}
	else
	{
		for(q=&b[h];q->link!=NULL;q=q->link);
		q->link=(struct Hash*)malloc(sizeof(struct Hash));
		q=q->link;
		strcpy(q->t,str);
		q->link=NULL;
	}
}
void form(FILE *in)
{
	int i=0;
	while(fscanf(in,"%s",word[i])!=EOF)
	{
		if(i==0||word[i][0]!=word[i-1][0])
		{
			a[word[i][0]-'a']=i;
		}
		i++;
	}
	N=i;
	a[26]=N;
	for(i=0;i<26;i++)
	{
		if(a[i]==0&&i!=0)
		{
			a[i]=a[i+1];
		}
	}
}
void binsearch1(char s[])
{
	int i;
	for(i=0;i<N;i++)
	{
		if(strcmp(s,word[i])==0)
		{
			printf("1 %d\n",i+1);
			break;
		}
		else 
		if(strcmp(s,word[i])<0)
		{
			printf("0 %d\n",i+1);
			break;
		}
	}
}
void binsearch2(char s[])
{
	int mid,low=0,high=N-1,step=0;
	while(low<=high)
	{
		step++;
		mid=(low+high)/2;
		if(strcmp(s,word[mid])==0)
		{
			printf("1 %d\n",step);
			return;
		}
		else 
		if(strcmp(s,word[mid])<0)
		{
			high=mid-1;
		}
		else 
		if(strcmp(s,word[mid])>0)
		{
			low=mid+1;
		}
	}
	printf("0 %d\n",step);
}
void binsearch3(char s[])
{
	int mid,low=a[s[0]-'a'],high=a[s[0]-'a'+1]-1,step=0;
	while(low<=high)
	{
		step++;
		mid=(low+high)/2;
		if(strcmp(s,word[mid])==0)
		{
			printf("1 %d\n",step);
			return;
		}
		else 
		if(strcmp(s,word[mid])<0)
		{
			high=mid-1;
		}
		else 
		if(strcmp(s,word[mid])>0)
		{
			low=mid+1;
		}
	}
	printf("0 %d\n",step);
}
void rehash(char *s)
{
	unsigned int h=0,step=0;
    char *p;
    struct Hash *q;
    for(p=s;*p!='\0';p++)
	{
    	h=MULT*h+*p;
	}
    h=h%NHASH;
    if(b[h].flag==0)
	{
    	printf("0 1\n");
	}
	else
	{
		for(q=&b[h];q!=NULL;q=q->link)
		{
			step++;
			if(strcmp(s,q->t)==0)
			{
				printf("1 %d\n",step);
				return;
			}
			else 
			if(strcmp(s,q->t)<0)
			{
				printf("0 %d\n",step);
				return;
			}
		}
		printf("0 %d\n",step);
	}
}

int main()
{
	int i,order;
	char s[50];
	FILE *in;
	in=fopen("dictionary3000.txt","r"); 
	form(in);
	for(i=0;i<=3000;i++)
	{
		b[i].flag=0;
		b[i].link=NULL;
	}
	for(i=0;i<N;i++)
	{
		hash(word[i]);
	}
	while(scanf("%s %d",s,&order)!=EOF)
	{
		if(order==1)
		{
			binsearch1(s);
		}
		else 
		if(order==2)
		{
			binsearch2(s);
		}
		else 
		if(order==3)
		{
			binsearch3(s);
		}
		else 
		if(order==4)
		{
			rehash(s);
		}
	}
	return 0;
}





