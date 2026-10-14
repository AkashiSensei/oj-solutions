/*
 * Build a keyword-based circular list of printable ASCII characters and derive
 * a substitution mapping by elimination; encrypt in.txt into in_crpyt.txt.
 */

#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
char password[127];
struct code{
	char word;
	struct code *next;
}*start,*ptr;
int main()
{
	FILE *in,*out;
	in=fopen("in.txt","r");
	out=fopen("in_crpyt.txt","w");
	char keyword[50],first;
	gets(keyword);
	first=keyword[0];
	int flag[127]={0},i,l=strlen(keyword);
	ptr=start=(struct code*)malloc(sizeof(struct code));
	start->word=keyword[0];
	flag[keyword[0]]=1;
	for(i=1;i<l;i++){
		if(flag[keyword[i]]==0)
		{
			ptr->next=(struct code*)malloc(sizeof(struct code));
			ptr=ptr->next;
			ptr->word=keyword[i];
			flag[keyword[i]]=1;
		}
	}
	for(i=32;i<=126;i++)
	{
		if(flag[i]==0)
		{
		ptr->next=(struct code*)malloc(sizeof(struct code));
		ptr=ptr->next;	
		ptr->word=i;
		}
	}
	ptr->next=(struct code*)malloc(sizeof(struct code));
	ptr->next=start;
	printf("\n");
	encode(ptr,start->word,first);
	char s[500];
	while(fgets(s,500,in)!=NULL)
	{
		for(i=0;i<strlen(s);i++)
		{
			if(s[i]>=32&&s[i]<=126)
			{
				s[i]=password[s[i]];
			}
		} 
		fputs(s,out);
	}
	fclose(in);
	fclose(out);
	return 0;
}
void encode(struct code *ptr,int n,char first)
{
	if(ptr->next==ptr)
	{
		password[ptr->word]=first;
		return;
	}
	else
	{ 
	    int i;
	    struct code *tmp;
		tmp=(struct code*)malloc(sizeof(struct code));
		tmp=ptr->next;
		ptr->next=tmp->next;
		free(tmp);
		for(i=1;i<n;i++)
		{
			ptr=ptr->next;
		}
		password[n]=ptr->next->word;
		encode(ptr,ptr->next->word,first);
	}
}






