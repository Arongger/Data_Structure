#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//�������״̬����
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int Status;
typedef int ElemType;

typedef struct LNode
{
    ElemType data;
    struct LNode *next;
}LNode,*LinkList;

/*******************************��������****************************************/

Status GetElem_L(LinkList L,int i,ElemType *e);
//LΪ��ͷ���ĵ������ͷָ��
//����i��Ԫ�ش���ʱ����ֵ����e������OK�����򷵻�ERROR

void CreateList_L (LinkList *L,int n);
//��λ������n��Ԫ�ص�ֵ��������ͷ���ĵ������Ա�L
//���Ѹ�Ϊ�Զ����ɣ�

Status ListTraverse_L(LinkList L);
//��ӡL�е�Ԫ��

Status ListInsert_L(LinkList *L,int i,ElemType e);
//�ڴ�ͷ���ĵ������Ա�L�е�i��λ��֮ǰ����Ԫ��e

Status ListDelete_L(LinkList *L,int i,ElemType *e);
//�ڴ�Ͷ�������ĵ������Ա�L�У�ɾ����i��Ԫ�أ�����e������ֵ

void MergeList_L(LinkList *La,LinkList *Lb,LinkList *Lc);
//��֪�������Ա�La��Lb��Ԫ�ذ�ֵ�ǵݼ�����
//�鲢La��Lb�õ��µĵ������Ա�Lc��LcҲ��ֵ�ǵݼ�����

/*******************************��������****************************************/

Status GetElem_L(LinkList L,int i,ElemType *e)
{
    LinkList p;
    p = L->next;  //��ʼ����pָ���һ�����
    int count = 1;
    while(p && count < i){  //˳ָ�������ң�ֱ��pָ���i��Ԫ�ػ�pΪ��
        p = p->next;
        ++count;
    }
    if(!p || count>i)
        return ERROR;  //��i��Ԫ�ز�����
    *e = p->data;
    return OK;
}

void CreateList_L (LinkList *L,int n)
{
    *L = (LinkList)malloc(sizeof(LNode));
    (*L)->next = NULL;  //����һ����ͷ���ĵ�����
    int count;
    for(count = n;count>0;count--){
        LinkList p;
        p = (LinkList)malloc(sizeof(LNode)); //�����½��
        p->data = count;
        p->next = (*L)->next;
        (*L)->next = p; //���뵽��ͷ
    } //for
}

Status ListTraverse_L(LinkList L)
{
    LinkList p;
    p = L->next;
    printf("\nL�е�Ԫ���У�");
    while(p){
        printf(" %d ",p->data);
        p = p->next;
    }
    printf("\n");
    return OK;
}

Status ListInsert_L(LinkList *L,int i,ElemType e)
{
    LinkList p;
    p = *L;
    int count = 0;
    while(p && count<i-1){
        p = p->next;
        ++count;  //Ѱ�ҵ�i-1�����
    }
    if(!p || count>i-1)
        return ERROR;
    LinkList s;
    s = (LinkList)malloc(sizeof(LNode));
    s->data = e;
    s->next = p->next;
    p->next = s;  //����L��
    return OK;
}

Status ListDelete_L(LinkList *L,int i,ElemType *e)
{
    LinkList p;
    p = *L;
    int count = 0;
    while(p->next && count<i-1){
        p = p->next;
        ++count;  //Ѱ�ҵ�i�����
    }
    if(!p->next || count>i-1)
        return ERROR;
    LinkList s;
    s = p->next;
    p->next = s->next;
    *e = s->data;
    free(s);   //ɾ�����ͷŽ��
    return OK;
}

void MergeList_L(LinkList *La,LinkList *Lb,LinkList *Lc)
{
    LinkList pa,pb,pc;
    pa = (*La)->next;
    pb = (*Lb)->next;
    *Lc = pc = *La;  //��La��ͷ�����ΪLc��ͷ���
    while(pa && pb){
        if(pa->data <= pb->data){
            pc->next = pa;
            pc = pa;
            pa = pa->next;
        }
        else{
            pc->next = pb;
            pc = pb;
            pb = pb->next;
        }
    }//while
    pc->next = pa?pa:pb;  //����ʣ���
    free(*Lb);
}

/*******************************����������**************************************/

int main()
{
    LinkList L;
    CreateList_L(&L,5);
    ListTraverse_L(L);

    ElemType e;
    GetElem_L(L,2,&e);
    printf("\nL�еĵ� 2 ��Ԫ��Ϊ %d\n",e);

    printf("\n\n������L�ĵ�4��Ԫ��ǰ���롮6��\n");
    ListInsert_L(&L,4,6);
    ListTraverse_L(L);

    ElemType e1;
    printf("\n\n���潫ɾ��L�еĵ�5��Ԫ�� \n");
    ListDelete_L(&L,5,&e1);
    ListTraverse_L(L);
    printf("��ɾ����Ԫ��Ϊ %d\n",e1);

    printf("\n\n���潫La=123 ,Lb=1234567 �ϲ���Lc��\n");
    LinkList La,Lb,Lc;
    CreateList_L(&La,3);
    CreateList_L(&Lb,7);
    MergeList_L(&La,&Lb,&Lc);
    printf("���潫��ӡLc�е�Ԫ��\n");
    ListTraverse_L(Lc);

    return 0;
}
