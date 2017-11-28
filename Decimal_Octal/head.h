#ifndef HEAD_H_INCLUDED
#define HEAD_H_INCLUDED

#endif // HEAD_H_INCLUDED

typedef struct stacknode        //����������
{
    int data;                   //������
    struct stacknode *next;     //ָ����
}stacknode,*linkstack;

void initstack(stacknode **s)    //��ʼ����ջ
{
    *s=NULL;
    return ;
}

void push(stacknode **s,int e)       //��ջ
{
    stacknode *p;
    p=(stacknode*)malloc(sizeof(stacknode));
    p->next=*s;
    p->data=e;
    *s=p;
    return;
}

int pop(stacknode **s)       //��ջ
{
    int e;
    stacknode *p;
    if(*s==NULL)
    {
        puts("Error! Empty!");
        return -999;

    }
    e=(*s)->data;
    p=*s;
    *s=(*s)->next;
    free(p);
    return e;
}

int gettop(stacknode *s)
{
    if(s==NULL)
    {
        puts("Error! Empty!");
        return -999;
    }
    return (s->data);
}

void printstack(stacknode *s)
{
    int i=1;
    if(s==NULL)
    {
        puts("Error! Empty!");
        return ;
    }
    while(s)
    {
        printf("NO.%d:%d\n",i,s->data);
        s=s->next;
    }
    return ;
}
