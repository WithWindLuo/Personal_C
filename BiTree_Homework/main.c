#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100
typedef char elemtype;
typedef struct BiTreeNode       //二叉树结点
{
    elemtype data;
    struct BiTreeNode *lchild,*rchild;
}BiTreeNode,*BiTree;

void PreCreatBiTree(BiTreeNode **T)     //先序创建二叉树
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


void PreOrderTraverse(BiTreeNode *T)    //先序遍历
{
    if(T)
    {
        printf("%c",T->data);
        PreOrderTraverse(T->lchild);
        PreOrderTraverse(T->rchild);
    }
}


void InOrderTraverse(BiTreeNode *T)     //中序遍历
{
    if(T)
    {
        InOrderTraverse(T->lchild);
        printf("%c",T->data);
        InOrderTraverse(T->rchild);
    }
}

void PostOrderTraverse(BiTreeNode *T)    //后序遍历
{
    if(T)
    {
        PostOrderTraverse(T->lchild);
        PostOrderTraverse(T->rchild);
        printf("%c",T->data);
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


int main(void)
{
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
    return 0;
}
