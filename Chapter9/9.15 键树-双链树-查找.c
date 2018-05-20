#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int Status;
typedef int ElemType;

#define MAXKEYLEN 16    //max length of keyword
typedef struct
{
    char ch[MAXKEYLEN];  //keyword
    int num;   //keyword length
}KeysType;    //keyword type

typedef enum{LEAF,BRANCH}NodeKind;  //node tyoe:{leaf,branch}
typedef char Record;
typedef struct DLTNode
{
    char symbol;
    struct DLTNode *next;  //pointer point to brother node
    NodeKind kind;  //��֧���ĺ�����ָ��
    union{
        Record *infoptr;  //Ҷ�ӽ��ļ�¼ָ��
        struct DLTNode *first;  //��֧���ĺ�����ָ��
    };
}DLTNode,*DLTree;
/*******************************��������****************************************/
Record *SearchDLTree(DLTree T,KeysType K);
//�ڷǿ�˫����T�в��ҹؼ��ֵ���K�ļ�¼�������ڣ��򷵻�ָ��ü�¼��ָ�룬����NULL
Status InitDLTree(DLTree *T);
//��ʼ��˫����
void PrintKeys(DLTree T);
//��ӡ˫����
/*******************************��������****************************************/
Record *SearchDLTree(DLTree T,KeysType K)
{
    DLTree p;
    int i;

    p = T->first;
    i = 0;
    while(p && i < K.num){
        while(p && p->symbol != K.ch[i])
            p = p->next;
        if(p && i < K.num-1)
            p = p->next;
        ++i;
    }
    if(!p)
        return NULL;
    else
        return p->infoptr;
}

Status InitDLTree(DLTree *T)
{
    *T = (DLTree)malloc(sizeof(DLTNode));
    (*T)->symbol = '\0';
    (*T)->next = NULL;
    (*T)->first = NULL;
}

void PrintKeys(DLTree T)
{
    if(T){
        if(T->symbol == '\0')
            PrintKeys(T->first);
        else if(T->symbol == '$')
            printf("%s ",T->infoptr);
        else
            PrintKeys(T->first);
        PrintKeys(T->next);
    }
}

/*******************************����������**************************************/
int main()
{
    DLTree T;
    KeysType k = {"CAI",3};

    InitDLTree(&T);
 //   PrintKeys(T);
    printf("%s ",SearchDLTree(T,k));
}



