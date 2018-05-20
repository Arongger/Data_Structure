#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

#define EQ(a,b) ((a) == (b))
#define LT(a,b) ((a) <  (b))
#define LQ(a,b) ((a) <= (b))
#define LH +1  //���
#define EH 0  //�Ǹ�
#define RH -1  //�Ҹ�

typedef int Status;
typedef int KeyType;
typedef struct
{
    KeyType key;
    int weight;
}ElemType;
typedef struct BSTNode
{
    ElemType data;
    int bf;    //����ƽ������
    struct BSTNode *lchild,*rchild;  //�����Һ���ָ��
}BSTNode,*BSTree;
typedef struct
{
    ElemType *elem; //unit elem[0] keep NULL
    int length;   //length of table
}SSTable;
/*******************************��������****************************************/
void R_Rotate(BSTree *p);
//����*pΪ���Ķ�����������������������֮��dpָ���µ������ڵ㣬
//����ת֮ǰ���������ĸ����
void L_Rotate(BSTree *p);
//����*pΪ���Ķ�����������������������֮��dpָ���µ������ڵ㣬
//����ת֮ǰ���������ĸ����
void LeftBalance(BSTree *T);
//����ָ��T��ָ���Ϊ���Ķ�������ƽ����ת�������㷨����ʱ��Tָ���µĸ����
Status InsertAVL(BSTree *T,ElemType e,int *taller);
//����ƽ��Ķ���������T�в����ں�e����ͬ�ؼ��ֵĽ�㣬�����һ������Ԫ��Ϊe
//���½�㣬������1�����򷵻�0.������ʹ�ö���������ʧȥƽ�⣬����ƽ����ת����
//taller��Ӧ���������
Status CreateTalbe(SSTable *L);
Status InitTable(SSTable *L);
Status Visit(ElemType e);
Status PreOrderTraverse(BSTree T,Status(*Visit)(ElemType e));
/*******************************��������****************************************/
void R_Rotate(BSTree *p)
{
    BSTree lc;
    lc = (*p)->lchild;  //lcָ��*p�������������
    (*p)->lchild = lc->rchild;  //lc���������ҽ�Ϊ*p��������
    lc->rchild = *p;  //pָ���µĸ����
    *p = lc;
}

void L_Rotate(BSTree *p)
{
    BSTree rc;
    rc = (*p)->rchild;  //lcָ��*p�������������
    (*p)->rchild = rc->lchild;  //lc���������ҽ�Ϊ*p��������
    rc->lchild = *p;  //pָ���µĸ����
    *p = rc;
}

void LeftBalance(BSTree *T)
{
    BSTree lc,rd;
    lc = (*T)->lchild;  //lcָ��*T�������������
    switch(lc->bf)   //���*T��������ƽ��ȣ�������Ӧƽ�⴦��
    {
    case LH:  //�½�������*T�����ӵ��������ϣ�Ҫ������������
        (*T)->bf = lc->bf = EH;
        R_Rotate(T);
        break;
    case RH:  //�½�������*T�����ӵ��������ϣ�Ҫ��˫������
        rd = lc->rchild;   //rdָ��*T�����ӵ���������
        switch(rd->bf)  //�޸�*T�������ӵ�ƽ������
        {
        case LH:
            (*T)->bf = RH;
            lc->bf = EH;
            break;
        case EH:
            (*T)->bf = lc->bf = EH;
            break;
        case RH:
            (*T)->bf = EH;
            lc->bf = LH;
            break;
        }//switch(lc->bf)
        rd->bf = EH;
        L_Rotate(&(*T)->lchild);  //��*T������������ƽ����ת����
        R_Rotate(T);  //��*T������ƽ�⴦��
        break;
    }//switch(lc->bf)
}

void RightBalance(BSTree *T)
{
    BSTree rc,ld;
    rc = (*T)->rchild;
    switch(rc->bf)
    {
    case RH:
        (*T)->bf = rc->bf = EH;
        L_Rotate(T);
        break;

    case LH:
        ld = rc->lchild;
        switch(ld->bf)
        {
        case LH:
            (*T)->bf = EH;
            rc->bf = RH;
            break;
        case EH:
            (*T)->bf = rc->bf = EH;
            break;
        case RH:
            (*T)->bf = LH;
            rc->bf = EH;
            break;
        }
        ld->bf = EH;
        R_Rotate(&(*T)->rchild);
        L_Rotate(T);
        break;
    }
}

Status InsertAVL(BSTree *T,ElemType e,int *taller)
{
    if(!(*T)){          //insert new node,the tree turns taller,set taller = 1
        *T = (BSTree)malloc(sizeof(BSTNode));
        (*T)->data = e;
        (*T)->lchild = (*T)->rchild = NULL;
        (*T)->bf = EH;
        *taller = 1;
    }
    else{
        if(EQ(e.key,(*T)->data.key)){  //the tree already has a node == e
            *taller = 0;  //no need to insert
            return 0;
        }
        if(LT(e.key,(*T)->data.key)){  //continue search in lchild
            if(!InsertAVL(&(*T)->lchild,e,taller))
                return 0;  //uninsert
            if(*taller)   //had inserted in lchild,and lchild turns taller
                switch((*T)->bf)   //check if balance
                {
                case LH:    //before,lchild taller than rchild,need leftbalance
                    LeftBalance(T);
                    *taller = 0;
                    break;
                case EH:   //before,lchild the same tall as rchild,now the whole tree turns taller
                    (*T)->bf = LH;
                    *taller = 1;
                    break;
                case RH:  //before,rchild taller than lchild,now the same tall
                    (*T)->bf = EH;
                    *taller = 0;
                    break;
                }//switch t->bf
        }//if
        else{
            if(!InsertAVL(&(*T)->rchild,e,taller))  //continue search in rchild
                return 0;  //uninsert
            if(*taller)   //had inserted in rchild,and rchild turns taller
                switch((*T)->bf)   //check if balance
                {
                case LH:  //before,rchild taller than lchild,now the same tall
                    (*T)->bf = EH;
                    *taller = 0;
                    break;
                case EH:   //before,lchild the same tall as rchild,now the whole tree turns taller
                    (*T)->bf = RH;
                    *taller = 1;
                    break;
                case RH:
                    RightBalance(T);    //before,rchild taller than lchild,need rightbalance
                    *taller = 0;
                    break;
                }//switch T->fb
        }//else
    }//else
    return 1;
}

Status CreateTalbe(SSTable *L)
{
  /*  int i;
    printf("������˳���ĳ���:");
    scanf("%d",&L->length);
    for(i = 1;i<=L->length;i++){
        printf("������� %d ��Ԫ�ص�ֵ��",i);
        scanf("%d",&L->elem[i].key);
    }*/
    L->length = 5;
    L->elem[1].key = 13;
    L->elem[2].key = 24;
    L->elem[3].key = 37;
    L->elem[4].key = 90;
    L->elem[5].key = 53;

    return OK;
}

Status InitTable(SSTable *L)
{
    (*L).elem = (ElemType *)malloc(100 * sizeof(ElemType));
    if(!(*L).elem)
        exit(OVERFLOW);
    (*L).length = 0;
    return OK;
}

Status Visit(ElemType e)
{
    printf("%d\t",e.key);
    return OK;
}

Status PreOrderTraverse(BSTree T,Status(*Visit)(ElemType e))  //�ݹ�
{
    if(T){
        if(Visit(T->data))
            if(PreOrderTraverse(T->lchild,Visit))
                if(PreOrderTraverse(T->rchild,Visit))
                    return OK;
        return ERROR;
    }
    else
        return OK;
}
/*******************************����������**************************************/
int main()
{
    BSTree T;
    SSTable L;
    int i,taller;

    InitTable(&L);
    CreateTalbe(&L);

    taller = 0;
    T = NULL;
    printf("��ƽ���������������Ԫ�أ�\n");
    for(i = 1;i<=L.length;i++){
        printf("%d ",L.elem[i].key);
        InsertAVL(&T,L.elem[i],&taller);
    }

    printf("\n\n�������������ɵ�ƽ�������Ϊ��\n");
    PreOrderTraverse(T,Visit);
    return 0;
}



