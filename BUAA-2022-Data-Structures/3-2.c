/*
 * Simulate Josephus-style elimination in a circular linked list with n participants,
 * counting interval m and starting position q; print the last survivor.
 */

#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
typedef struct node     
{    int number;       
    int mydata;       
    struct node *next; 
} linklist;


linklist *CreateCircle( int n,int m )
{
    linklist *head=NULL;
    linklist *tail=NULL;
    linklist *a;
    int i; 
    for(i=0;i<n;i++)
	{
        
        a=(linklist*)malloc(sizeof(linklist));
        a->number=i+1;
        a->mydata=m;
        if(i==0){head=a;head->next=NULL;tail=head;}
        else{tail->next=a;tail=a;}
    }
    tail->next=head;
    return tail;
}
int KingOfMonkey(int n,linklist *head,int q)
{
    linklist *a;
    int b=head->mydata-1+q-1;
    int k;
    while(head->number!=head->next->number)
	{
        for(k=0;k<b;k++)
		{
            head=head->next;
            
        }
        b=(head->next->mydata)-1;
        a=head->next;
        head->next=a->next;
        free(a);
    }
    int z=head->number;
return z;
}

int main()
{
    linklist *head;
    int n,m,q;
    scanf("%d",&n);
	scanf("%d",&m);
	scanf("%d",&q); 
    head = CreateCircle(n,m); 
    printf("%d", KingOfMonkey(n,head,q));
    return 0;
}

