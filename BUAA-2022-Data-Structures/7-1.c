/*
 * Print DFS and BFS traversals from vertex 0 in an undirected graph,
 * remove a specified vertex's incident edges, and repeat both traversals.
 */

#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
int v,e;
struct route{
	int id;
	int visited;
	struct route *next[100];
}r[100];
void bfs(struct route r[])
{
	int ord[100],front=0,rear=-1,i;
	ord[++rear]=0;
	r[0].visited=1;
	while(rear>=front)
	{
		for(i=0;i<v;i++)
		{
			if(r[ord[front]].next[i]!=NULL&&r[ord[front]].next[i]->visited==0)
			{
				ord[++rear]=r[ord[front]].next[i]->id;
				r[ord[front]].next[i]->visited=1;
			}
		}
		printf("%d ",r[ord[front]].id);
		front++;
	}
}
void dfs(struct route *r)
{
	int i;
	if(r!=NULL&&r->visited==0)
	{
		r->visited=1;
		printf("%d ",r->id);
		for(i=0;i<v;i++)
		{
			if(r->next[i]!=NULL)
			{
				dfs(r->next[i]);
			}
		}
	}
}
void delete(struct route r[],int d)
{
	int i,j;
	for(i=0;i<v;i++)
	{
		if(r[i].id==d)
		{
			for(j=0;j<v;j++)
			{
				r[i].next[j]=NULL;
			}
		}
		else
		{
			r[i].next[d]=NULL;
		}
	}
}
int main()
{
	int i,j,v1,v2;
	scanf("%d%d",&v,&e);
	for(i=0;i<v;i++)
	{
		r[i].id=i;
		r[i].visited=0;
	}
	for(i=0;i<e;i++)
	{
		scanf("%d %d",&v1,&v2);
		r[v1].next[v2]=&r[v2];
		r[v2].next[v1]=&r[v1];
	}
	dfs(&r[0]);
	printf("\n");
	for(i=0;i<v;i++)
	{
		r[i].visited=0;
	}
	bfs(r);
	printf("\n");
	for(i=0;i<v;i++)
	{
		r[i].visited=0;
	}
	scanf("%d",&j);
	delete(r,j);
	dfs(&r[0]);
	printf("\n");
	for(i=0;i<v;i++)
	{
		r[i].visited=0;
	}
	bfs(r);
	printf("\n");
	return 0;
}







