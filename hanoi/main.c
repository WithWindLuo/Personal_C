#include <stdio.h>
#include <stdlib.h>
int count=1;
void hanoi(int n,char A,char B,char C)  //借助B将A移到C
{
    if(n==1)
        move(n,A,C);
    else
    {
        hanoi(n-1,A,C,B);
        move(n,A,C);
        hanoi(n-1,B,A,C);
    }
    return ;
}

void move(int n,char A,char C)  //直接将A上的移到C
{
    printf("NO.%d:%c-->%c\n",count++,A,C);
    return ;
}

int main(void)
{
    int n;
    scanf("%d",&n);
    hanoi(n,'A','B','C');
    return 0;
}
