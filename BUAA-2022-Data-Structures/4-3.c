/*
 * Evaluate an integer expression ending in = using operand and operator stacks,
 * with parentheses and the operators +, -, *, /, and %.
 */

#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define MAX 202

struct opstack
{
    int data[101];
    char character[101];
    int top;
};

int i, j, n, result;
char c;
typedef struct opstack stack;
stack op, num;

void initstack(stack *s) { s->top=-1; }

void push_stack(stack *s, char c, int line)
{
    s->character[++s->top]=c;
    s->data[s->top]=line;
}

int pop_stack(stack *s, stack *num)
{
    int tamp=0;
    switch (s->character[s->top])
    {
    case '+':
        tamp=num->data[num->top-1]+num->data[num->top];
        break;
    case '-':
        tamp=num->data[num->top-1]-num->data[num->top];
        break;
    case '*':
        tamp=num->data[num->top-1]*num->data[num->top];
        break;
    case '/':
        tamp=num->data[num->top-1]/num->data[num->top];
        break;
    case '%':
        tamp=num->data[num->top-1]%num->data[num->top];
        break;
    }
    s->character[s->top]='\0';
    s->data[s->top]='\0';
    s->top--;
    num->top-=2;
    return tamp;
}

int main(void)
{
    initstack(&op);
    initstack(&num);
    op.character[++op.top] = 32;
    op.data[op.top] = -1;
    while ((c = getchar())!='=')
    {
        if (c>='0'&&c<='9')
        {
            for (i=0;c>='0'&&c<='9';c=getchar())
                n=c-'0'+n*10;
            ungetc(c, stdin);
            push_stack(&num, 32, n);
            n=0;
        }
        else 
		if (c!=' ')
        {
            int pnum=0,option=0;
            switch (c)
            {
            case'+':
                option=1;
                break;
            case'-':
                option=1;
                break;
            case'*':
                option=2;
                break;
            case'/':
                option=2;
                break;
            case'%':
                option=2;
                break;
            case'(':
                option=5;
                break;
            case')':
                option=6;
                break;
            }
            if (option<=op.data[op.top]&&op.data[op.top]!= 5)
            {
                pnum=pop_stack(&op, &num);
                push_stack(&num, 32, pnum);
            }
            if (option<=op.data[op.top]&&op.data[op.top]==5)
            {
                push_stack(&op,c,option);
            }
            if (option == 6)
            {
                while (op.data[op.top]!= 5)
                {
                    pnum=pop_stack(&op, &num);
                    push_stack(&num, 32, pnum);
                }
                op.top--;
                continue;
            }
            if (option>op.data[op.top])
                push_stack(&op,c,option);
        }
    }
    for (i=0,j=op.top;i<strlen(op.character);i++,j--)
    {
        int pnum=0;
        if (op.data[j]!=-1)
        {
            pnum=pop_stack(&op, &num);
            push_stack(&num, 32, pnum);
        }
    }
    printf("%d",num.data[0]);
}




