#include <stdio.h>
#include <stdlib.h>
#include "header.h"

int matching()
{
    int e;
    char ch;
    int flag=1;
    stacknode *stack;
    initstack(&stack);
    ch=getchar();
    while(ch!='#' && flag)
    {
        switch(ch)
        {
        case '[':
        case '(':
            push(&stack,ch);
            break;
        case ')':
            if(stack && gettop(&stack)=='(')
                pop(&stack);
            else
                flag=0;
            break;
        case ']':
            if(stack && gettop(&stack)=='[')
                pop(&stack);
            else
                flag=0;
            break;
        }
        ch=getchar();
    }
    if(!stack && flag )
        return 1;
    else
        return -1;
}
int main(void)
{
    int e;
    e=matching();
    printf("%d\n",e);
    return 0;
}
