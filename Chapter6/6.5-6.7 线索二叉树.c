#include<stdio.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int Status;
typedef char TElemType;

typedef enum {Link, Thread} PointerTag;   //Link == 0: ָ�� ��Thread == 1:����

typedef struct BiThrNode
{
    TElemType data;
    struct BiThrNode *lchild, *rchild;  //���Һ���ָ��
    PointerTag   LTag,RTag;    //���ұ�־
}BiThrNode, *BiThrTree;

/*******************************��������****************************************/

Status Visit(TElemType e);
Status CreateBiTree(BiThrTree *T);
//���ȴ�������������н���ֵ��һ���ַ������ո��ַ���ʾ������
//������������ʾ�Ķ�����T
void InThreading(BiThrTree p);
//���������������ĸ�������
Status InOrderThreading(BiThrTree *Thrt,BiThrTree T);
//�������������T��������������������Thrtָ��ͷ���
Status InOrderTraverse_Thr(BiThrTree T,Status(*Visit)(TElemType e));
//Tָ��ͷ��㣬ͷ��������lchildָ������
//�����������������T�ķǵݹ��㷨����ÿ������Ԫ�ص���Visit����

/*******************************��������****************************************/

Status Visit(TElemType e)
{
    printf("%c\t",e);
    return OK;
}

Status CreateBiTree(BiThrTree *T)
{
    TElemType ch;
  //  scanf("%c",&ch);
    ch = getchar();
    if(ch == ' ')
        *T = NULL;
    else{
        *T = (BiThrTree)malloc(sizeof(BiThrNode));
        if(!(*T))
            exit(OVERFLOW);
        (*T)->data = ch;  //���ɸ����
        CreateBiTree(&(*T)->lchild);  //����������
        if((*T)->lchild)  //������
            (*T)->LTag = Link;
        CreateBiTree(&(*T)->rchild);  //����������
        if((*T)->rchild)  //���Һ���
            (*T)->RTag = Link;
    }
    return OK;
}

BiThrTree pre;  //ȫ�ֱ�����ʼ��ָ��ոշ��ʹ��Ľ��
void InThreading(BiThrTree p)
{
    if(p){
        InThreading(p->lchild);  //������������
        if(!p->lchild){  //ǰ������
            p->LTag = Thread;
            p->lchild = pre;
        }
        if(!pre->rchild){  //�������
            pre->RTag = Thread;
            pre->rchild = p;
        }
        pre = p;
        InThreading(p->rchild);  //������������
    }
}

Status InOrderThreading(BiThrTree *Thrt,BiThrTree T)
{
    (*Thrt)= (BiThrTree)malloc(sizeof(BiThrNode));
    if(!(*Thrt))
        exit(OVERFLOW);
    (*Thrt)->LTag = Link;
    (*Thrt)->RTag = Thread;  //����ͷ���
    (*Thrt)->rchild = *Thrt;  //��ָ���ָ
    if(!T)
        (*Thrt)->lchild = *Thrt;  //���������գ�����ָ���ָ
    else{
        (*Thrt)->lchild = T;
        pre = *Thrt;
        InThreading(T);  //���������������������
        pre->rchild = *Thrt;
        pre->RTag = Thread;   //���һ�����������
        (*Thrt)->rchild = pre;
    }//else
    return OK;
}

Status InOrderTraverse_Thr(BiThrTree T,Status(*Visit)(TElemType e))
{
    BiThrTree p;
    p = T->lchild;   //pָ������
    while(p != T){
        //�������������ʱ��p == T
        while(p->LTag == Link)
            p = p->lchild;
        if(!Visit(p->data))  //������������Ϊ�յĽ��
            return ERROR;
        while(p->RTag == Thread && p->rchild != T){
            p = p->rchild;
            Visit(p->data);  //���ʺ�̽��
        }//while
        p = p->rchild;
    }//while
    return OK;
}

/*******************************����������**************************************/

int main()
{
    BiThrTree H,T;

    //���Ʒֺ�ǰ���ַ�:ABC  DE G  F   ��
    printf("\n����������(����ABC^^DE^G^^F^^^)��\n");
    CreateBiTree(&T);
    InOrderThreading(&H,T);
    printf("\n������� �������������\n");
    InOrderTraverse_Thr(H,Visit);
    printf("\n");

    return 0;
}


