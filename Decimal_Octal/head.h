#ifndef HEAD_H_INCLUDED
#define HEAD_H_INCLUDED

#endif // HEAD_H_INCLUDED

typedef struct stacknode        //定义结点类型
{
    int data;                   //数据域
    struct stacknode *next;     //指针域
}stacknode,*linkstack;

void initstack(stacknode **s)    //初始化链栈
{
    *s=NULL;
    return ;
}

void push(stacknode **s,int e)       //入栈
{
    stacknode *p;
    p=(stacknode*)malloc(sizeof(stacknode));
    p->next=*s;
    p->data=e;
    *s=p;
    return;
}

int pop(stacknode **s)       //出栈
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
