#include <stdio.h>
#include <stdlib.h>
typedef struct
{
    int *base;  //存储空间的基地址
    int length; //当前长度
}Sqlist;    //类型名

void mergelist(Sqlist LA,Sqlist LB,Sqlist *LC)
{//已知顺序有序表LA和LB的元素按值非递减排列
 //归并LA和LB得到新的顺序有序表LC，LC的元素也按值非递减排列
    LC->length=LA.length+LB.length;     //新表长度为待合并的两表长度之和
    LC->base=(int *)malloc(LC->length * sizeof(int)); //为新表分配空间
    int *pa,*pb,*pc,*pa_last,*pb_last;
    pa=LA.base;     //指针pa和pb的初值分别指向两个表的第一个元素
    pb=LB.base;
    pc=LC->base;    //指针pc指向新表的第一个元素
    pa_last=LA.base+LA.length-1;    //指针pa_last指向LA的最后一个元素
    pb_last=LB.base+LB.length-1;    //指针pb_lase指向LB的最后一个元素
    while((pa<=pa_last) && (pb<=pb_last))   //LA和LB均未达到表尾
    {//依次摘取量表中值较小的结点插入LC的最后
        if(*pa <= *pb)
            *pc++=*pa++;
        else
            *pc++=*pb++;
    }
    while(pa <= pa_last)
        *pc++=*pa++;    //LB已达到表尾，依次将LA的剩余元素插入LC的最后
    while(pb <= pb_last)
        *pc++=*pb++;    //LA已达到表位，依次将LB的剩余元素插入LC的最后
    return ;
}

int main(void)
{
    int i;
    Sqlist LA,LB,LC;
    int a[]={1,3,5,7,9};    //初始化表LA
    int b[]={2,4,6,8,10};   //初始化表LB
    LA.base=a;
    LA.length=sizeof(a)/sizeof(a[0]);   //计算LA长度
    LB.base=b;
    LB.length=sizeof(b)/sizeof(b[0]);   //计算LB长度
    mergelist(LA,LB,&LC);   //合并表LA和LB为LC
    printf("LA:");          //输出表A
    for(i=0;i<=LA.length-1;i++)
        printf("%d ",*(LA.base+i));
    putchar('\n');
    printf("LB:");          //输出表B
    for(i=0;i<=LB.length-1;i++)
        printf("%d ",*(LB.base+i));
    putchar('\n');
    printf("LC:");          //输出表C
    for(i=0;i<=LC.length-1;i++)
        printf("%d ",*(LC.base+i));
    putchar('\n');
    return 0;
}
