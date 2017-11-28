#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100
typedef char elemtype;
typedef struct BiTreeNode
{
    elemtype data;
    struct BiTreeNode *lchild,*rchild;
}BiTreeNode,*BiTree;

typedef struct stacknode        //定义结点类型
{
    BiTreeNode data;                   //数据域
    struct stacknode *next;     //指针域
}stacknode,*linkstack;

void initstack(stacknode **s)    //初始化链栈
{
    *s=NULL;
    return ;
}

void push(stacknode **s,BiTreeNode e)       //入栈
{
    stacknode *p;
    p=(stacknode*)malloc(sizeof(stacknode));
    p->next=*s;
    p->data=e;
    *s=p;                   //更改栈顶指针
    return;
}



void pop(stacknode *s,BiTreeNode *T)       //出栈
{
    stacknode *p;
    if(s==NULL)
    {
        puts("Error! Empty!");
    }
    *T=(s)->data;
    p=s;
    s=(s)->next;
    free(p);
}

int StackEmpty(stacknode *S)
{
    if(S)
        return 1;
    else
        return 0;
}


void PreOrderTraverse(BiTreeNode *T)
{
    if(T)
    {
        printf("%c",T->data);
        PreOrderTraverse(T->lchild);
        PreOrderTraverse(T->rchild);
    }
}


void InOrderTraverse(BiTreeNode *T)
{
    if(T)
    {
        InOrderTraverse(T->lchild);
        printf("%c",T->data);
        InOrderTraverse(T->rchild);
    }
}

void PostOrderTraverse(BiTreeNode *T)
{
    if(T)
    {
        PostOrderTraverse(T->lchild);
        PostOrderTraverse(T->rchild);
        printf("%c",T->data);
    }
}



void InOrderTraverse1(BiTreeNode *T)
{
    stacknode *S;
    initstack(&S);
    BiTreeNode *p = T;
    BiTreeNode q;
    while(p || StackEmpty(S))
    {
        if(p)
        {
            push(&S,*T);
            p=p->lchild;
        }
        else
        {
            pop(S,&q);
            printf("%c",q.data);
            p=q.rchild;
        }
    }
}


void PreCreatBiTree(BiTreeNode **T)
{
    char ch;
    ch=getchar();
    if(ch == '*')
        *T=NULL;
    else
    {
        (*T)=(BiTreeNode*)malloc(sizeof(BiTreeNode));
        (*T)->data=ch;
        PreCreatBiTree(&((*T)->lchild));
        PreCreatBiTree(&((*T)->rchild));
    }
}

void CopyBiTree(BiTreeNode *T,BiTreeNode **NewT)
{
    if(T==NULL)
    {
        *NewT=NULL;
        return;
    }
    else
    {
        *NewT=(BiTreeNode *)malloc(sizeof(BiTreeNode));
        (*NewT)->data=T->data;
        CopyBiTree(T->lchild,&((*NewT)->lchild));
        CopyBiTree(T->rchild,&((*NewT)->rchild));
    }
}

int BTDepth(BiTreeNode *T)
{

    int l,r;
    if(T == NULL)
        return 0;
    else
    {
        l=BTDepth(T->lchild);
        r=BTDepth(T->rchild);
        if(l>r)
            return(l+1);
        else
            return(r+1);
    }
}

int BTNodeCount(BiTreeNode *T)
{
    int l,r;

    if(T==NULL)
        return 0;
    else
    {
        l=BTNodeCount(T->lchild);
        r=BTNodeCount(T->rchild);
        return l+r+1;
    }
}
int main(void)
{
    int depth;
    a:
    printf("Preorder_creat:");
    BiTreeNode *t;
    BiTreeNode *T;
    PreCreatBiTree(&t);
    CopyBiTree(t,&T);
    printf("Preorder:");
    PreOrderTraverse(T);
    putchar('\n');
    printf("Inorder:");
    InOrderTraverse(T);
    putchar('\n');
    printf("Postorder:");
    PostOrderTraverse(T);
    putchar('\n');
    printf("Depth=%d\n",BTDepth(T));
    goto a;
    return 0;
}
