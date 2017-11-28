#include <stdio.h>
#include <stdlib.h>
typedef struct LNode
{
    int data;
    struct LNode *next;
}LNode,*Linklist;   //Linklist为指针变量类型


Linklist addlist(LNode *L)
{
    Linklist q;
    q=(Linklist)malloc(sizeof(LNode));
    q->next=NULL;
    L->next=q;
    return q;
}

int listlength(LNode L)
{
    LNode *p=L.next;
    int n=0;
    while(p)
    {
        n++;
        p=p->next;
    }
    return n;
}

void getelem(LNode L,int i,int *e)
{
    Linklist p;
    p=L.next;
    int j=1;
    while(p&&j<i)
    {
        p=p->next;
        j++;
    }
    if(!p||j>i)
    {
        puts("Error");
        exit(0);
    }
    *e=p->data;
    return ;
}

LNode* locateelem(Linklist L,int e)
{
    LNode *p=L->next;
    int j=1;
    while(p&&p->data!=e)
    {
        p=p->next;
        j++;
    }
    return p;
}

void listinsert(LNode *L,int i,int e)
{
    LNode *p=L->next;
    int j=1;
    while(p && j<i-1)
    {
        p=p->next;
        j++;
    }
    if(!p || j>i)
    {
        puts("Error");
        exit(1);
    }
    LNode *q=(LNode *)malloc(sizeof(LNode));
    q->data=e;
    q->next=p->next;
    p->next=q;
    return ;
}

void mergelist(LNode *LA,LNode LB)
{
    int m=listlength(*LA);
    int n=listlength(LB);
    int i,e;
    for(i=1;i<=n;i++)
    {
        getelem(LB,i,&e);
        if(!locateelem(LA,e))
            listinsert(LA,++m,e);
    }
}


void printlist(LNode L)
{
    Linklist p=L.next;
    int j=1;
    while(p)
    {
        printf("NO.%d:%d    ",j,p->data);
        p=p->next;
        j++;
    }
    putchar('\n');
    return ;
}

void ordermergelist(LNode *LA,LNode *LB,LNode *LC)
{
    LNode *p=LA->next;
    LNode *q=LB->next;
    LNode *k=LC->next;
    while(p&&q)
    {
        if(p->data > q->data)
        {
            LC->next=p;
            p=p->next;
        }
        else
        {
            LC->next=q;
            q=q->next;
        }
    }
    if(!p)
    {
        LC->next=q;
    }
    if(!q)
    {
        LC->next=p;
    }
    return ;
}



int main(void)
{
    LNode list1,list2,list3;
    list1.next=NULL;
    list2.next=NULL;
    list3.next=NULL;
    Linklist p;
    int i;
    p=&list1;
    for(i=1;i<=3;i++)
    {
        p=addlist(p);
        scanf("%d",&p->data);
    }
    p=&list2;
    for(i=1;i<=3;i++)
    {
        p=addlist(p);
        scanf("%d",&p->data);
    }
    printlist(list1);
    printlist(list2);
    ordermergelist(&list1,&list2,&list3);
    printlist(list3);
    return 0;
}
