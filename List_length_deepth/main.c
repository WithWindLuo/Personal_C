#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef char DataType;
typedef struct GlistNode
{
    int tag;
    union
    {
        DataType atom; //原子元素域
        struct
        {
            struct GListNode *head; //头链
            struct GListNode *tail; //尾链
        }subList;
    }val;
}GLNode;


void DecomposeStr(char str[], char hstr[])
{
    int i,j,tag,n=strlen(str);
    char ch;
    ch=str[0];
    tag=0;
    for(i=0;i<=n-1;i++)
    {
        if(str[i]==',' && tag == 1 )
            break;
        ch=str[i];
        if(ch=='(')
            tag++;
        if(ch==')')
            tag--;
    }
    if(i<=n-1 && str[i] == ',')
    {
        for(j=0;j<i-1;j++)
            hstr[j]=str[j+1];
	    hstr[j] = '\0';
	    if(str[i] == ',')
            i++;
	    str[0] = '(';
	    for(j = 1; i <= n-2; i++, j++)
            str[j] = str[i];
	    str[j] = ')';
        str[++j] = '\0';
    }
    else
    {
        str++;
	    strncpy(hstr,str, n-2);
	    hstr[n-2] = '\0';
	    str--;
	    strcpy(str, "()");
    }
}

GLNode* CreatGList(char str[])
{
    GLNode *h;
    char hstr[200];
    int len = strlen(str);
    if(strcmp(str, "()") == 0)
        h = NULL;
    else  if(len == 1)
    {
        h = (GLNode *)malloc(sizeof(GLNode));
        h->tag = 0;
        h->val.atom = str[0];
    }
    else
    {
        h = (GLNode *)malloc(sizeof(GLNode));
	    h->tag = 1;
	    DecomposeStr(str, hstr);
        h->val.subList.head = CreatGList(hstr);
        if(strcmp(str, "()") != 0)
            h->val.subList.tail = CreatGList(str);
        else
            h->val.subList.tail = NULL;
   }
   return h;
}

int GListDepth(GLNode *h)
{
    int max, dep;
    GLNode *pre;
    if(h == NULL)
        return 1;
    if(h->tag == 0)
        return 0;
    pre = h;
    for(max = 0; pre != NULL; pre = pre->val.subList.tail)
    {
        dep = GListDepth(pre->val.subList.head);
        if(dep > max)
            max = dep;
    }
    return max + 1;
}

int GListLength(GLNode *h)
{
    int number = 0;
    GLNode *p;
    for(p = h;p!=NULL;p=p->val.subList.tail)
        number++;
    return number;
}


