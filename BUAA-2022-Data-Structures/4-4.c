/*
 * Apply insertion, deletion, and undo commands to a text line.
 * Keep edit records on a stack so the latest operation can be reversed.
 */

#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
struct edit{
	int op;
	int pos;
	char str[512];
	int l;
}a[100]; 
void unable(struct edit a,char s[])
{
	char t[512];
	int i;
	if(a.op==2){
	for(i=0;i<a.pos;i++)
	{
		t[i]=s[i];
	}
	t[i]='\0';
	strcat(t,a.str);
	strcat(t,s+a.pos);	
	strcpy(s,t);
	}
	else
	if(a.op==1)
	{
	for(i=0;i<a.pos;i++)
	{
		t[i]=s[i];
	}	
	t[i]='\0';
	int len=strlen(s);
	if(a.pos+a.l<len)
	{
	strcat(t,s+a.pos+a.l);	
	}
	strcpy(s,t);
	} 
}
int main()
{
	char s[512],b[512];
	int n,i,top=-1,order,j=0;
	gets(s);
	scanf("%d",&n);
	for(i=0;i<n;i++){
		top++;
		scanf("%d%d%s",&a[top].op,&a[top].pos,a[top].str);
		a[top].l=strlen(a[top].str);
	}
	while(scanf("%d",&order)!=EOF)
	{
		if(order==1)
		{
			top++;
			a[top].op=1;
			scanf("%d%s",&a[top].pos,a[top].str);
			a[top].l=strlen(a[top].str);
			for(i=0;i<a[top].pos;i++)
			{
				b[i]=s[i];
			}
			b[i]='\0';
			strcat(b,a[top].str);
			strcat(b,s+a[top].pos);
			strcpy(s,b);
		}
		else 
		if(order==2)
		{
			j=0;
			top++;
			a[top].op=2;
			scanf("%d%d",&a[top].pos,&a[top].l);
			for(i=a[top].pos;i<a[top].pos+a[top].l;i++)
			{
				a[top].str[j]=s[i];
				j++;
			}
			a[top].str[j]='\0';	
			for(i=0;i<a[top].pos;i++)
			{
				b[i]=s[i];
			}
			b[i]='\0';
			if(a[top].pos+a[top].l<strlen(s))
			{
				strcat(b,s+a[top].pos+a[top].l);
			}
			strcpy(s,b);
		}
		else 
		if(order==3&&top!=-1)
		{
			unable(a[top],s);
			top--;
		}
		else 
		if(order==-1)
		{
			puts(s);
			break;
		}
	}
	return 0;
}





