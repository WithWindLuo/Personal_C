#include <stdio.h>
#include <stdlib.h>
typedef ElemType char;
typedef struct BiThTreeNode
{
    ElemType data;
    BiThTreeNode *lchild,*rchild;
    int LTag,RTag;
}BTTNode;


