#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLEN 20
typedef struct
{
    char ch[MAXLEN+1];
    int length;
}SString;

int index_BF(SString *S,SString *T,int pos)
{
    int i=pos,j=1;
    while(i<=S->length && j<=T->length)
    {
        if(S->ch[i]==T->ch[j])
        {
            i++;
            j++;
        }
        else
        {
            i=i-j+2;
            j=1;
        }
    }
    if(j > T->length)
    {
        return i-j+1;
    }
    else
        return -1;
}


int main(void)
{
    int n;
    SString S,T;
    gets(S.ch+1);
    S.length=strlen(S.ch+1);
    gets(T.ch+1);
    T.length=strlen(T.ch+1);
    printf("%d\n",index_BF(&S,&T,1));
    return 0;
}
