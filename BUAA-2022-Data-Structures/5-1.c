/*
 * Insert integers into a binary search tree and print each leaf's value and depth,
 * counting the root as depth 1 and placing equal values in the right subtree.
 */

#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
struct node{
	int data;
	int deep;
	struct node *left,*right;
}*t;

void sort(struct node *p,int m,int l)
{
 if(m<p->data)
 {
  if(p->left==NULL)
  {
   p->left=(struct node*)malloc(sizeof(struct node));
   p=p->left;
   p->left=p->right=NULL;
   p->data=m;
   p->deep=l+1;
  }
  else
  {
   sort(p->left,m,l+1);
  }
 }
 else 
 if(m>=p->data)
 {
  if(p->right==NULL)
  {
   p->right=(struct node*)malloc(sizeof(struct node));
   p=p->right;
   p->left=p->right=NULL;
   p->data=m;
   p->deep=l+1;
  }
  else
  {
   sort(p->right,m,l+1);
  }
 }
}
void pre(struct node *t)
{
	if(t!=NULL)
	{
		pre(t->left);
		pre(t->right);
	    if(t->left==NULL&&t->right==NULL)
	    {
		    printf("%d %d\n",t->data,t->deep);
	    }
	}
}
int main()
{
	t=(struct node*)malloc(sizeof(struct node));
	t->left=t->right=NULL;
	int n,i,a;
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		scanf("%d",&a);
		if(i!=0)
		{
			sort(t,a,1);
		}
		else
		{
			t->data=a;
			t->deep=1;
		}
	}
	pre(t);
	return 0;
}

