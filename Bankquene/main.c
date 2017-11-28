#include <stdio.h>
#include <stdlib.h>
typedef struct QNode
{
    int data;
    struct QNode *next;
}QNode;

typedef struct
{
    QNode *front;
    QNode *rear;
}Linkquene;

void initquene(Linkquene *q)    //初始化队
{
    q->front=q->rear=(QNode *)malloc(sizeof(QNode));
    q->front->next=NULL;
    return ;
}

void enterquene(Linkquene *q,int initnumber) //入队
{
    QNode *p;
    p=(QNode *)malloc(sizeof(QNode));
    p->data=initnumber;
    p->next=NULL;
    q->rear->next=p;
    q->rear=p;
    return ;
}

void deletequene(Linkquene *q,int *number)   //出队
{
    if(q->front == q->rear)
    {
        puts("Error. Empty.");
        return ;
    }
    QNode *p;
    p=q->front->next;
    *number=p->data;
    q->front->next=p->next;
    if(p == q->rear)
        q->rear=q->front;
}

void printquene(Linkquene *q)
{
    QNode *p=q->front->next;
    if(q->front == q->rear)
    {
        puts("Error. Empty.");
        return ;
    }
    while(p != q->rear)
    {
        printf("NO.%d\n",p->data);
        p=p->next;
    }
    printf("NO.%d\n",p->data);
    return ;
}

int isempty(Linkquene *q)   //判断队列是否为空 如为空返回0 不空返回1
{
    if(q->front == q->rear)
        return 0;
    else
        return 1;
}
int main(void)
{
    int choice,initnumber=1,number=-999;
    Linkquene Q;
    initquene(&Q);
    printf("1.获取叫号纸 2.请顾客到前台办理业务 3.当前正在办理业务的顾客  4.查看排队的顾客 q.退出\n");
    while(scanf("%d",&choice) == 1)
    {
        switch(choice)
        {
        case 1:
            printf("获取叫号纸成功，号码为%d\n",initnumber);
            enterquene(&Q,initnumber++);
            break;
        case 2:
            deletequene(&Q,&number);
            if(number == -999 || !isempty(&Q) )
                printf("当前没有人排队\n");
            else
                printf("请NO.%d顾客到前台办理业务\n",number);

            break;
        case 3:
            if(number == -999 || !isempty(&Q))
                printf("当前没有人在办理业务\n");
            else
                printf("当前正在办理业务的顾客号为：%d\n",number);
            break;
        case 4:
            if(isempty(&Q))
            {
                printf("正在排队办理业务的顾客号有：\n");
                printquene(&Q);
            }
            else
                printf("当前没有人排队\n");
            break;
        default:
            printf("指令有误，请重新输入\n");
            break;
        }
    }
    printf("退出成功!\n");
    return 0;
}
