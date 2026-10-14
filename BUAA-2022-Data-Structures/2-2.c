/*
 * Read a search string and replacement, then perform case-insensitive substring
 * replacement in filein.txt and write the modified text to fileout.txt.
 */

#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
char m[100],n[100],s[100],t[100];
int main()
{
	FILE *in,*out;
	int i,j,k;
	char *p=s,*q=n;
	gets(m);
	gets(n);
	in=fopen("filein.txt","r");
	out=fopen("fileout.txt","w");
	while((fgets(s,100,in))!=NULL)
	{
		for(i=0;i<strlen(s);i++)
		{
			if(s[i]==m[0]||s[i]==m[0]-32||s[i]==m[0]+32)
			{
				int check=0;
				int len=strlen(m);
				for(j=0;j<len;j++)
				{
					if(s[i+j]!=m[j]&&s[i+j]!=m[j]-32&&s[i+j]!=m[j]+32)
					{
						check=1;
					}
				}
				if(check==0)
				{
					for(k=0;k<i;k++)
					{
						t[k]=s[k];
					}
					t[k]='\0';
					strcat(t,q);
					strcat(t,p+i+len);
					strcpy(s,t);	
				}
			}
		}
		fputs(s,out);
	}
	fclose(in);
	fclose(out);
	return 0;
}


