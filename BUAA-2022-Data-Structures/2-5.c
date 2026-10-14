/*
 * Load a book catalog from books.txt; support insertion, title-substring search,
 * and deletion, then save the remaining records to ordered.txt.
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
struct books{
	char name[50],author[20],press[30],date[10];
	 
}book[501];
void replace(int n, struct books book[501], char*temp);
void replace(int n, struct books book[501], char*temp)
{
	int i=0,j=0;
	for(i=0;i<n;i++)
	{
			for(j=i+1;j<n;j++)
			{
				if(strcmp(book[i].name ,book[j].name )>0)
				{
					strcpy(temp,book[i].name );
					strcpy(book[i].name ,book[j].name );
					strcpy(book[j].name ,temp);
					strcpy(temp,book[i].author );
					strcpy(book[i].author  ,book[j].author  );
					strcpy(book[j].author  ,temp);
					strcpy(temp,book[i].date  );
					strcpy(book[i].date  ,book[j].date  );
					strcpy(book[j].date  ,temp);
					strcpy(temp,book[i].press  );
					strcpy(book[i].press  ,book[j].press  );
					strcpy(book[j].press  ,temp);
				}
			}
		}
}

int main()
{
	int i=0,op,len=0,j=0;
	char temp[50];
	
	FILE *fp,*pp;
	fp=fopen("books.txt","r");
	pp=fopen("ordered.txt","w");
	
	while (fscanf(fp, "%s%s%s%s", book[i].name, book[i].author, book[i].press, book[i].date) != EOF)
    {
        i++;
    }
    len = i;
	
	while(scanf("%d",&op)!=0)
	{
		
		
			replace(len, book, temp);
			char a[50];
		
		if(op==1)
		{
			scanf("%s%s%s%s",book[len].name ,book[len].author ,book[len].press ,book[len].date );
			len++;
		}
		
		if(op==2)
		{
			scanf("%s",a);
			
			for(i=0;i<len;i++)
			{
				if(strstr(book[i].name ,a)!=NULL)
				{
					printf("%-50s%-20s%-30s%s\n",book[i].name ,book[i].author ,book[i].press ,book[i].date );
				}
			}
		}
		
		if(op==3)
		{
			scanf("%s",a);
			for(i=0;i<len;i++)
			{
				if(strstr(book[i].name ,a)!=NULL)
				{
					book[i].name[0]='\0';
				}
			}
		}
		
		if(op==0)
		{
			break;
		}
		
	}
	
	for(i=0;i<len;i++)
	{
		
		if(strlen(book[i].name )!=0)
		{
			
			fprintf(pp,"%-50s%-20s%-30s%s\n",book[i].name ,book[i].author ,book[i].press ,book[i].date );
			
		}
	}
	fclose(fp);
	fclose(pp);
	
	
	 
}








