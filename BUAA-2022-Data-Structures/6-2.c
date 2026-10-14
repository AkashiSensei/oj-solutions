/*
 * Read ID/name/number records from in.txt, fill numbering gaps and resolve duplicates.
 * Print intermediate states and write the adjusted records to out.txt in ID order.
 */

#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
int m=0,q,flag[200]={0};
struct position{
	int id;
	char name[20];
	int number;
}Z[100];
void sort(struct position Z[],int n)
{
	int i,j;
	struct position tmp;
	for(i=0;i<n;i++)
	{
		for(j=i+1;j<n;j++)
		{
			if(Z[i].number>Z[j].number||(Z[i].number==Z[j].number&&Z[i].id>Z[j].id))
			{
				tmp=Z[i];
				Z[i]=Z[j];
				Z[j]=tmp;
			}
		}
	}
}
void leak(struct position Z[],int n)
{
	int i,j=1,q=n;
	for(i=1;i<=q;i++)
	{
		if(flag[i]==0)
		{
			Z[n-j].number=i;
			m=Z[n-j-1].number;
			flag[i]=1;
			j++;
		}
		if(m>=n)
		{
		q=n;
	    }
		else
		{
		q=m;
	    }
	}
}
void repeat(struct position Z[],int n)
{
	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=i+1;j<n;j++)
		{
			if(Z[j].number==Z[i].number)
			{
				Z[j].number=++m;
			}
		}
	}
}
void Sort(struct position T[],int n)
{
	int i,j;
	struct position tmp;
	for(i=0;i<n;i++){
		for(j=i+1;j<n;j++)
		{
			if(Z[i].id>Z[j].id)
			{
				tmp=Z[i];
				Z[i]=Z[j];
				Z[j]=tmp;
			}
		}
	}
}
int main()
{
	int k,i,j;
	char s[100];
	FILE *in,*out;
	in=fopen("in.txt","r");
	out=fopen("out.txt","w");
	i=0;
	scanf("%d",&k);
	for(i=0;i<k;i++)
	{
		fscanf(in,"%d%s%d",&Z[i].id,Z[i].name,&Z[i].number);
		flag[Z[i].number]=1;
		if(Z[i].number>=m)
		{
			m=Z[i].number;
		}
	}
	sort(Z,k);
	for(i=0;i<k;i++)
	{
		printf("%d %s %d\n",Z[i].id,Z[i].name,Z[i].number);
	}
	printf("\n");
	leak(Z,k);
	for(i=0;i<k;i++)
	{
		printf("%d %s %d\n",Z[i].id,Z[i].name,Z[i].number);
	}
	printf("\n");
	repeat(Z,k);
	for(i=0;i<k;i++)
	{
		printf("%d %s %d\n",Z[i].id,Z[i].name,Z[i].number);
	}
	printf("\n");
	Sort(Z,k);
	for(i=0;i<k;i++)
	{
		fprintf(out,"%d %s %d\n",Z[i].id,Z[i].name,Z[i].number);
	}
	return 0;
}





