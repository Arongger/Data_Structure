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

typedef struct LNode{
	ElemType data;
	struct LNode *next;
}LNode,*LinkList;

void CreatList_L(LinkList *L, int n);
void CreatList2_L(LinkList *L, int n);
Status GetElem_L(LinkList L, int i, ElemType *e);
Status ListInsert_L(LinkList *L,int i,ElemType e);
Status ListDelete_L(LinkList *L, int i, ElemType *e);
void MergeList_L(LinkList *La, LinkList *Lb, LinkList *Lc);

void CreatList_L(LinkList *L, int n){
	//��λ������n��Ԫ�ص�ֵ����������ͷ���ĵ������Ա�L��
	LNode *p;
	int i;
	*L = (LinkList)malloc(sizeof(LNode));
	(*L)->next = NULL;//�Ƚ���һ����ͷ���ĵ�����
	printf("����������ĸ���Ԫ��ֵ��") ;
	for(i = n; i > 0; --i){
		p = (LinkList)malloc(sizeof(LNode));//�����½��
		scanf("%d",&(p->data));//����Ԫ��ֵ
		p->next = (*L)->next; (*L)->next = p; //���뵽��ͷ
	}

}//CreateList_L

void CreatList2_L(LinkList *L, int n){
	LNode *p,*q;
	int i;
	*L = (LinkList)malloc(sizeof(LNode));
	(*L)->next = NULL;
	q= *L;
	printf("����������ĸ���Ԫ��ֵ��");
	for(i = 0; i < n; i++){
		p = (LinkList)malloc(sizeof(LNode));
		scanf("%d",&(p->data));
		q->next = p;
		q = q->next;
	}
}//CreateList2_L

Status GetElem_L(LinkList L, int i, ElemType *e){
	//LΪ��ͷ���ĵ������ͷָ��
	//����i��Ԫ�ش���ʱ����ֵ����e������OK,���򷵻�ERROR
	LNode *p;
	int j;
	p = L->next; j = 1;//��ʼ����pָ���һ����㣬jΪ������
	while(p && j < i){//˳ָ�������ң�ֱ��pָ���i��Ԫ�ػ�pΪ��
		p = p->next;++j;
	}
	if(!p || j > i)return ERROR;//��i��Ԫ�ز�����
	*e = p->data;//ȡ��i��Ԫ��
	return OK;
}//GetElem_L

Status ListInsert_L(LinkList *L,int i,ElemType e){
	//�ڴ�ͷ���ĵ������Ա�L�е�i��λ��֮ǰ����Ԫ��e
	 LNode *p,*s;
	int j;
	p = *L; j = 0;
	while(p && j < i-1){
		p = p->next; ++j;
	}//Ѱ�ҵ�i-1�����
	if(!p || j > i)return ERROR;
	s = (LinkList)malloc(sizeof(LNode));
	s->data = e;s->next = p->next;
	p->next = s;
	return OK;
}

Status ListDelete_L(LinkList *L, int i, ElemType *e){
	//�ڴ�ͷ���ĵ������Ա�l�У�ɾ����i��Ԫ�أ�����e������ֵ
	LNode *p,*q;
	int j;
	p = *L; j = 0;
	while(p->next && j < i-1){
		//Ѱ�ҵ�i����㣬����pָ����ǰ��
		p = p->next; ++j;
	}
	if(!(p->next) || j > i-1)return ERROR;//ɾ��λ�ò�����
	q = p->next; p->next = q->next;
	*e = q->data; free(q);
	return OK;
}//ListDelete_L



void MergeList_L(LinkList *La, LinkList *Lb, LinkList *Lc){
	//��֪�������Ա�La��Lb��Ԫ�ذ�ֵ�ǵݼ�����
	//�鲢La��Lb�õ��µĵ������Ա�Lc,Lc��Ԫ��Ҳ��ֵ�ǵݼ�����
	LNode *pa,*pb,*pc;
	pa = (*La)->next; pb = (*Lb)->next;
	(*Lc) = pc =pa;
	while(pa && pb){
		if(pa->data <= pb->data){
			pc->next = pa; pc = pa; pa = pa->next;
		}
		else{
			pc->next = pb; pc = pb; pb = pb->next;
		}
	}
	pc->next = pa ? pa : pb;
	free((*Lb));
}//MergeList_L

main()
{
	LinkList La,Lb,p,q;
	int n=5,i;

	CreatList_L(&La, n);
	printf("��λ��������������Ϊ��");
	p = La->next;
	while(p){
        printf("%d->",p->data);
        p = p->next;
	}

}
















