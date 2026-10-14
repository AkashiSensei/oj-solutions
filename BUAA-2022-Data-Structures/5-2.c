/*
 * Count case-insensitive words from article.txt in a binary search tree.
 * Print up to three nodes on the right spine, followed by alphabetical frequencies.
 */

#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
struct word{
	char w[30];
	int sum;
	struct bst *left;
	struct bst *right;
}*r,*ptr;
void small(char s[])
{
	int i;
	for(i=0;i<strlen(s);i++)
	{
		if(s[i]>='A'&&s[i]<='Z')
		{
			s[i]='a'+s[i]-'A';
		}
		if((s[i]<'A'||(s[i]>'Z'&&s[i]<'a')||s[i]>'z')&&(s[i]!='\n'&&s[i]!='\0'))
		{
			s[i]=' ';
		}
	}
}
void sort(struct word *p,char t[])
{
	if(strcmp(t,p->w)<0)
	{
		if(p->left==NULL)
		{
			p->left=(struct word*)malloc(sizeof(struct word));
			p=p->left;
			p->left=p->right=NULL;
			strcpy(p->w,t);
			p->sum=1;
		}
		else
		{
			sort(p->left,t);
		}
	}
	else 
	if(strcmp(t,p->w)>0)
	{
		if(p->right==NULL)
		{
			p->right=(struct word*)malloc(sizeof(struct word));
			p=p->right;
			p->left=p->right=NULL;
			strcpy(p->w,t);
			p->sum=1;
		}
		else
		{
			sort(p->right,t);
		}
	}
	else 
	if(strcmp(t,p->w)==0)
	{
		(p->sum)++;
	}
}
void  postorder(struct word *p)
{
	if(p!=NULL)
	{
	postorder(p->left);
	printf("%s %d\n",p->w,p->sum);
	postorder(p->right);
    }
}
int main()
{
	FILE *in;
	in=fopen("article.txt","r");
	char s[200],t[30];
	int i,j,k,m=0;
	r=(struct word*)malloc(sizeof(struct word));
	r->left=r->right=NULL;
	while(fgets(s,200,in)!=NULL)
	{
		small(s);
		int len=strlen(s);
		for(i=0;i<len;i++)
		{
			if((i==0||s[i-1]==' ')&&s[i]!=' '&&s[i]!='\n'&&s[i]!='\0')
			{
				k=0;
			    for(j=i;s[j]!=' '&&s[j]!='\n'&&s[j]!='\0';j++)
				{
			    	t[k++]=s[j];
				}
				t[k]='\0';
				m++;	
				if(m!=1)
				{
					sort(r,t);
				}
				else
				{
					strcpy(r->w,t);
					r->sum=1;
				}
			}
		}
	}
	ptr=r;
	for(i=0;i<3;i++)
	{
		printf("%s ",ptr->w);
		ptr=ptr->right;
		if(ptr==NULL)
		{
			break;
		}
	}
	printf("\n");
	postorder(r);
	return 0;
}






