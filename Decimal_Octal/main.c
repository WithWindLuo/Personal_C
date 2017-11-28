#include <stdio.h>
#include <stdlib.h>
#include "head.h"
void conversion(int N)
{
    int n,e;
    stacknode *stack;
    initstack(&stack);
    while(N)
    {
        push(&stack,N%8);
        N=N/8;
    }
    while(stack)
    {
        e=pop(&stack);
        printf("%d",e);
    }
    return ;
}
int main()
{
    int N;
    scanf("%d",&N);
    conversion(N);
    return 0;
}
