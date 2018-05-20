#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

#define MAXSIZE 125  //�������Ԫ���������ֵΪ125  //ԭ��Ϊ12500

typedef int Status;
typedef int ElemType;

typedef struct
{
    int i,j;  //�÷���Ԫ�����±�����±�
    ElemType e;
}Triple;
typedef struct
{
    Triple data[MAXSIZE + 1];  //����Ԫ��Ԫ���data[0]δ��
    int mu,nu,tu;   //����������������ͷ���Ԫ����
}TSMatrix;   //ϡ������һ��ѹ���洢��ʽ


/*******************************��������****************************************/
Status CreateTSMatrix (TSMatrix *M);
//������Ԫ��˳���洢�ṹ��ϡ�����M
Status PrintTSMatrix(TSMatrix M);
//��ӡϡ�����M
Status TransposeSMatrix(TSMatrix M,TSMatrix *T);
//������Ԫ��˳���洢��ʾ����ϡ�����M��ת�þ���T
Status FastTransposeSMatrix(TSMatrix M,TSMatrix *T);
//������Ԫ��˳���洢��ʾ����ϡ�����M��ת�þ���T
/*******************************��������****************************************/
Status CreateTSMatrix (TSMatrix *M)
{
   /* printf("����������������");
    scanf("%d",& M->mu);
    printf("����������������");
    scanf("%d",& M->nu);
    printf("���������ķ���Ԫ������");
    scanf("%d",& M->tu);

    int i,j,k;
    for(k = 1;k<= M->tu;k++){
        printf("������� %d ������Ԫ����Ϣ\n",k);
        printf("�������кţ�\n");
        scanf("%d",&M->data[k].i);
        printf("�������к�\n");
        scanf("%d",&M->data[k].j);
        printf("������ֵ��\n");
        scanf("%d",&M->data[k].e);
    }*/
    M->mu = 6;
    M->nu = 7;
    M->tu = 8;
    M->data[1].i = 1;
    M->data[1].j = 2;
    M->data[1].e = 12;

    M->data[2].i = 1;
    M->data[2].j = 3;
    M->data[2].e = 9;

    M->data[3].i = 3;
    M->data[3].j = 1;
    M->data[3].e = -3;

    M->data[4].i = 3;
    M->data[4].j = 6;
    M->data[4].e = 14;

    M->data[5].i = 4;
    M->data[5].j = 3;
    M->data[5].e = 24;

    M->data[6].i = 5;
    M->data[6].j = 2;
    M->data[6].e = 18;

    M->data[7].i = 6;
    M->data[7].j = 1;
    M->data[7].e = 15;

    M->data[8].i = 6;
    M->data[8].j = 4;
    M->data[8].e = -7;

}

Status PrintTSMatrix(TSMatrix M)
{
    int k;

    printf("i j v\n");
    for(k = 1;k<= M.tu;k++)
        printf("%d %d %d\n",M.data[k].i,M.data[k].j,M.data[k].e);
}

Status TransposeSMatrix(TSMatrix M,TSMatrix *T)
{
    int p,q,col;
    T->mu = M.nu;
    T->nu = M.mu;
    T->tu = M.tu;
    if(T->tu){
        q = 1;
        for(col = 1;col<=M.nu;col++)
            for(p = 1;p<=M.tu;p++){
                if(M.data[p].j == col){
                    T->data[q].i = M.data[p].j;
                    T->data[q].j = M.data[p].i;
                    T->data[q].e = M.data[p].e;
                    q++;
                }//if
            }//for
    }//if
    return OK;
}

Status FastTransposeSMatrix(TSMatrix M,TSMatrix *T)
{
    int col,t,p,q,num[M.nu],cpot[M.nu];
    T->mu = M.nu;
    T->nu = M.mu;
    T->tu = M.tu;
    if(T->tu){
        for(col = 1;col <= M.nu;col++)
            num[col] = 0;
        for(t = 1;t<=M.tu;t++)
            ++num[M.data[t].j];  //��M��ÿһ�к�����Ԫ����
        cpot[1] = 1;
        //���col���е�һ������Ԫ��b.data�е����
        for(col = 2;col<=M.nu;col++)
            cpot[col] = cpot[col-1]+num[col-1];
        for(p = 1;p<=M.tu;p++){
            col = M.data[p].j;
            q = cpot[col];
            T->data[q].i = M.data[p].j;
            T->data[q].j = M.data[p].i;
            T->data[q].e = M.data[p].e;
            ++cpot[col];
        }//for
    }//if
    return OK;
}
/*******************************����������**************************************/
int main()
{
    TSMatrix M,T,Q;
    CreateTSMatrix(&M);
    printf("M�������Ԫ���ʾΪ��\n");
    PrintTSMatrix(M);
    TransposeSMatrix(M,&T);
    printf("\nT�������Ԫ���ʾΪ��\n");
    PrintTSMatrix(T);
    FastTransposeSMatrix(M,&Q);
    printf("\nQ������ת�ú�\n");
    PrintTSMatrix(Q);
    return 0;
}



