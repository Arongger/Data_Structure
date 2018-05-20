#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define MAXKEYLEN 16
typedef int Status;
typedef int ElemType;
typedef enum{LEAF,BRANCH} NodeKind;
typedef char Record;
typedef struct
{
    char ch[MAXKEYLEN];
    int num;
}KeysType;

typedef struct TrieNode
{
    NodeKind kind;
    union
    {
        struct { KeysType K; Record *infoptr;} lf;
        struct { struct TrieNode *ptr[27];int num;} bh;
    };
}TrieNode , *TrieTree;
/*******************************��������****************************************/
int ord(char ch);
Status cmp(KeysType A,KeysType B);
Record *SearchTrie(TrieTree T,KeysType k);
/*******************************��������****************************************/
int ord(char ch)
 {
     if(isalpha(ch))
        return ch-'A'+1;
     else
        return 0;
}

Status cmp(KeysType A,KeysType B)
{
    int i;
    if(A.num != B.num)
        return ERROR;
    for(i = 0;i<A.num;i++)
        if(A.ch[i] != B.ch[i])
            return ERROR;
    return OK;
}

Record *SearchTrie(TrieTree T,KeysType k)
{
    TrieTree p;
    int i;

    for(p = T , i = 0 ;   //��k��ÿ���ַ��������
        p && p->kind == BRANCH && i<k.num;  //*pΪ��֧���
        p = p->bh.ptr[ ord(k.ch[i]) ], ++i);  //ord���ַ�����ĸ���е����

    if(p && p->kind == LEAF && cmp(p->lf.K,k))
        return p->lf.infoptr;
    else
        return NULL;
}

/*******************************����������**************************************/

int main()
{
    TrieTree T;
    T = NULL;
    KeysType k;
    k.ch[0] = 'C';
    k.ch[1] = 'A';
    k.ch[2] = 'I';
    k.num = 3;
    printf("%s \n",SearchTrie(T,k));
    return 0;
}


