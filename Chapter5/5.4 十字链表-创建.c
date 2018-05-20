#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdarg.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int Status;
typedef int ElemType;

typedef struct OLNode
{
    int i,j;   //�÷���Ԫ���к����±�
    ElemType e;
    struct OLNode *right,*down;  //�÷���Ԫ�����б���б�ĺ������
}OLNode, *OLink;
typedef struct
{
    OLink *rhead,*chead;  //�к�������ͷָ��������ַ��CreateSMatrix����
    int mu,nu,tu;   //ϡ�����������������ͷ���Ԫ����
}CrossList;  //ʮ������


/*******************************��������****************************************/
Status CreateSMatrix_OL(CrossList *M);
//����ʮ������
Status PrintSMatrix_OL(CrossList M);
//���ʮ������
/*******************************��������****************************************/
Status CreateSMatrix_OL(CrossList *M)
{
    int m,n,t,k,i,j,e;
    if(M)
        free(M);
    printf("����������������");
    scanf("%d",& m);
    printf("����������������");
    scanf("%d",& n);
    printf("���������ķ���Ԫ������");
    scanf("%d",& t);
    M->mu = m;
    M->nu = n;
    M->tu = t;

    if(!(M->rhead = (OLink *)malloc((m+1)*sizeof(OLink))))
        exit(OVERFLOW);
    if(!(M->chead = (OLink *)malloc((n+1)*sizeof(OLink))))
        exit(OVERFLOW);

    for(k = 0;k<= M->mu;k++)  //��ʼ������ͷָ������������������Ϊ������
        M->rhead[k] = NULL;
    for(k = 0;k<= M->nu;k++)
        M->chead[k] = NULL;
    for(k = 1;k<= M->tu;k++){
        printf("������� %d ������Ԫ����Ϣ\n",k);
        printf("�������кţ�\n");
        scanf("%d",&i);
        printf("�������к�\n");
        scanf("%d",&j);
        printf("������ֵ��\n");
        scanf("%d",&e);

        OLNode *p,*q;
        p = (OLNode *)malloc(sizeof(OLNode));  //���ɽ��
        p->i = i;
        p->j = j;
        p->e = e;

        if(M->rhead[i] == NULL || M->rhead[i]->j > j){
            p->right = M->rhead[i];
            M->rhead[i] = p;
        }//if
        else{  //Ѱ�����б��еĲ���λ��
            for(q = M->rhead[i];(q->right) && q->right->j < j;q = q->right);
            p->right = q->right;
            q->right = p;  //����в���
        }//else

        if(M->chead[j] == NULL || M->chead[j]->i > i){
            p->down = M->chead[j];
            M->chead[j] = p;
        }//if
        else{  //Ѱ�����б��еĲ���λ��
            for(q = M->chead[j];(q->down) && q->down->i < i;q = q->down);
            p->down = q->down;
            q->down = p;  //����в���
        }//else
    }//for
    return OK;
}

Status CreateSMatrix_OL_auto(CrossList *M)
{
    int m,n,t,k,i,j,e;
    int i_list[4] = {1,1,2,3};
    int j_list[4] = {1,4,2,1};
    int e_list[4] = {3,5,-1,2};

    if(M)
        free(M);
    m = 3;
    n = 4;
    t = 4;
    M->mu = m;
    M->nu = n;
    M->tu = t;

    if(!(M->rhead = (OLink *)malloc((m+1)*sizeof(OLink))))
        exit(OVERFLOW);
    if(!(M->chead = (OLink *)malloc((n+1)*sizeof(OLink))))
        exit(OVERFLOW);
    for(k = 0;k<= M->mu;k++)  //��ʼ������ͷָ������������������Ϊ������
        M->rhead[k] = NULL;
    for(k = 0;k<= M->nu;k++)
        M->chead[k] = NULL;
    for(k = 1;k<= M->tu;k++){
        i = i_list[k-1];
        j = j_list[k-1];
        e = e_list[k-1];
        OLNode *p,*q;
        p = (OLNode *)malloc(sizeof(OLNode));  //���ɽ��
        p->i = i;
        p->j = j;
        p->e = e;

        if(M->rhead[i] == NULL || M->rhead[i]->j > j){
            p->right = M->rhead[i];
            M->rhead[i] = p;
        }//if
        else{  //Ѱ�����б��еĲ���λ��
            for(q = M->rhead[i];(q->right) && q->right->j < j;q = q->right);
            p->right = q->right;
            q->right = p;  //����в���
        }//else

        if(M->chead[j] == NULL || M->chead[j]->i > i){
            p->down = M->chead[j];
            M->chead[j] = p;
        }//if
        else{  //Ѱ�����б��еĲ���λ��
            for(q = M->chead[j];(q->down) && q->down->i < i;q = q->down);
            p->down = q->down;
            q->down = p;  //����в���
        }//else
    }//for
    return OK;
}

Status PrintSMatrix_OL(CrossList M)
{
    int i,j;
    OLNode *p;
    for(i = 1;i<= M.mu;i++){
        p = M.rhead[i];
        for(j = 1;j<=M.nu;j++){
            if(p && p->j == j){
                printf("%2d",p->e);
                p = p->right;
            }
            else
                printf(" 0 ");
        }
        printf("\n");
    }
}
/*******************************����������**************************************/
int main()
{
    CrossList M;

    printf("����ʮ������\n");
    CreateSMatrix_OL_auto(&M);
    PrintSMatrix_OL(M);
    return 0;
}
