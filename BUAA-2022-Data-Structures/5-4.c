/*
 * Read a tree of network devices from in.txt and search for a nearby printer
 * for the chosen computer; use preorder for ties and print the printer and route.
 */

#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
int k=0;
int STEP=0,step,ROUTE[20],route[20];
min(int a,int b)
{
	if(a>=b)
	{
		return b;
	}
	else 
	{
		return a;
	}
}
struct print
{
	int number;
	int id;
	int model;
	struct print *port[8];
	struct print *parent; 
}*r,*ptr,*q,*l,*printer;
struct print* a[300];
void read(char t[],int b[])
{
	int i,j,m,top=-1;
	for(i=0;i<strlen(t);i++)
	{
		if((i==0||(t[i-1]>'9'||t[i-1]<'0'))&&(t[i]>='0'&&t[i]<='9'))
		{
			m=0;
		for(j=i;t[j]>='0'&&t[j]<='9';j++)
		{
			m=m*10+t[j]-'0';
		}	
		b[++top]=m;
		}
	}
}
void perorder(struct print *p)
{
	int i;
	if(p!=NULL)
	{
		p->number=k;
		k++;
		if(p->model==0)
		{
			for(i=0;i<8;i++)
			{
				perorder(p->port[i]);
			}
		}
		else
		{
			return;
		}
	}
}
void seek(struct print *p)
{
	int i;
	if(p->model==0)
	{
		route[++step]=p->id;
		for(i=0;i<8;i++)
		{
			if(p->port[i]!=NULL&&p->port[i]->model!=1)
			{
				seek(p->port[i]);
			}
		}
		step--;
	}
	else 
	if(p->model==2)
	{
		if(STEP==0)
		{
			printer=p;
			STEP=step;
			for(i=0;i<=step;i++)
			{
				ROUTE[i]=route[i];
			}
		}
		else
		{
			if(step<STEP||(step==STEP&&p->number<printer->number))
			{
				printer=p;
				STEP=step;
				for(i=0;i<=step;i++)
				{
					ROUTE[i]=route[i];
				}
			}
		}
	}
}
int main()
{
	char s[500];
	FILE* in;
	int sum,pc,n,i=-1,j,b[4];
	scanf("%d%d",&sum,&pc);
	in=fopen("in.txt","r");
	while(fgets(s,500,in)!=NULL)
	{
		if(s[0]=='\n')
		{
			continue;
		}
		i++;
		a[i]=(struct print*)malloc(sizeof(struct print));
		for(j=0;j<8;j++)
		{
			a[i]->port[j]=NULL;
		}
		if(i==0)
		{
			a[0]->id=0;
			a[0]->model=0;
			r=a[0];
		}
		else
		{
			read(s,b);
			a[i]->id=b[0];
			a[i]->model=b[1];
			a[b[2]]->port[b[3]]=a[i];
			a[i]->parent=a[b[2]];
		}
	}
	perorder(r);
	q=a[pc];
	for(ptr=q;ptr!=r;ptr=ptr->parent)
	{
		step=-1;
		for(l=q->parent;l!=ptr->parent;l=l->parent)
		{
			route[++step]=l->id;
		}
		seek(ptr->parent);
	}
	for(i=0;i<=STEP;i++)
	{
		for(j=i+1;j<=STEP;j++)
		{
			if(ROUTE[j]==ROUTE[i])
			{
				for(k=i+1;k<=j;k++)
				{
					ROUTE[k]=-1;
				}
			}
		}
	}
	printf("%d ",printer->id);
	for(i=0;i<=STEP;i++)
	{
		if(ROUTE[i]==-1)
		continue;
		else
		{
		printf("%d ",ROUTE[i]);
	    }
	}
	return 0;
}






