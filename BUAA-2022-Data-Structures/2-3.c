/*
 * Construct a substitution alphabet from a keyword followed by unused letters
 * in reverse order; attempt to encrypt encrypt.txt into output.txt.
 */

#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
int main()
{
	FILE *in,*out;
	in=fopen("encrypt.txt","r");
	out=fopen("output.txt","w");
	char c[50],t[26],a[50];
	int s[26]={0};
	int i,j=0;
	gets(c);
	int len1=strlen(c);
	int len2=strlen(a);
	for(i=0;i<len1;i++)
	{
		if(s[c[i]-'a']==0)
		{
			t[j]=c[i];
			j++;
		}
		s[c[i]-'a']++;
	}
	for(i=0;i<26;i++)
	{
		if(s[25-i]==0)
		{
			t[j]='a'+25-i;
			j++; 
		}
	}
	while(fgets(a,100,in)!=NULL)
	{
	for(i=0;i<len2;i++)
	{
		if(a[i]>='a'&&a[i]<='z')
		{
			a[i]=t[a[i]-'a'];
		}
	}
	fputs(a,out);
}
    fclose(in);
    fclose(out);
	return 0;
}





