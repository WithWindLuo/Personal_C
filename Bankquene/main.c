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

void initquene(Linkquene *q)    //��ʼ����
{
    q->front=q->rear=(QNode *)malloc(sizeof(QNode));
    q->front->next=NULL;
    return ;
}

void enterquene(Linkquene *q,int initnumber) //���
{
    QNode *p;
    p=(QNode *)malloc(sizeof(QNode));
    p->data=initnumber;
    p->next=NULL;
    q->rear->next=p;
    q->rear=p;
    return ;
}

void deletequene(Linkquene *q,int *number)   //����
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

int isempty(Linkquene *q)   //�ж϶����Ƿ�Ϊ�� ��Ϊ�շ���0 ���շ���1
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
    printf("1.��ȡ�к�ֽ 2.��˿͵�ǰ̨����ҵ�� 3.��ǰ���ڰ���ҵ��Ĺ˿�  4.�鿴�ŶӵĹ˿� q.�˳�\n");
    while(scanf("%d",&choice) == 1)
    {
        switch(choice)
        {
        case 1:
            printf("��ȡ�к�ֽ�ɹ�������Ϊ%d\n",initnumber);
            enterquene(&Q,initnumber++);
            break;
        case 2:
            deletequene(&Q,&number);
            if(number == -999 || !isempty(&Q) )
                printf("��ǰû�����Ŷ�\n");
            else
                printf("��NO.%d�˿͵�ǰ̨����ҵ��\n",number);

            break;
        case 3:
            if(number == -999 || !isempty(&Q))
                printf("��ǰû�����ڰ���ҵ��\n");
            else
                printf("��ǰ���ڰ���ҵ��Ĺ˿ͺ�Ϊ��%d\n",number);
            break;
        case 4:
            if(isempty(&Q))
            {
                printf("�����ŶӰ���ҵ��Ĺ˿ͺ��У�\n");
                printquene(&Q);
            }
            else
                printf("��ǰû�����Ŷ�\n");
            break;
        default:
            printf("ָ����������������\n");
            break;
        }
    }
    printf("�˳��ɹ�!\n");
    return 0;
}
