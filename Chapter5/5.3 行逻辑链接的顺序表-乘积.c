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

#define MAXSIZE 125  //�������Ԫ���������ֵΪ125  //ԭ��Ϊ12500
#define MAXRC 20

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
    int rpos[MAXRC + 1];   //rpos[row]��ʾ����ĵ�row���е�һ������Ԫ��N.data�е����
    int mu,nu,tu;   //����������������ͷ���Ԫ����
}RLSMatrix;   //ϡ������һ��ѹ���洢��ʽ

/*******************************��������****************************************/
Status CreateTSMatrix (RLSMatrix *M);
//������Ԫ��˳���洢�ṹ��ϡ�����M
Status CreateTSMatrix_AUTO(RLSMatrix *M);
//������Ԫ��˳���洢�ṹ��ϡ�����M
Status PrintTSMatrix(RLSMatrix M);
//��ӡϡ�����M
Status MultSMatrix(RLSMatrix M,RLSMatrix N,RLSMatrix *Q);
//�����˻�Q = M*N���������߼����Ӵ洢��ʾ
/*******************************��������****************************************/
Status CreateTSMatrix (RLSMatrix *M)
{
 /*   printf("����������������");
    scanf("%d",& M->mu);
    printf("����������������");
    scanf("%d",& M->nu);
    printf("���������ķ���Ԫ������");
    scanf("%d",& M->tu);

    int i,j,k,row_num,ct = 0;
    for(k = 1;k<= M->tu;k++){
        printf("������� %d ������Ԫ����Ϣ\n",k);
        printf("�������кţ�\n");
        scanf("%d",&M->data[k].i);
        printf("�������к�\n");
        scanf("%d",&M->data[k].j);
        printf("������ֵ��\n");
        scanf("%d",&M->data[k].e);
        if(k == 1){
            row_num = M->data[k].i;
            M->rpos[ct] = k;
            ct++;
        }

        if(row_num != M->data[k].i){  //�����i�е��׸�����Ԫ
            row_num = M->data[k].i;
            M->rpos[ct] = k;
            ct++;
        }
    } */

    M->mu = 3;
    M->nu = 4;
    M->tu = 4;
    M->data[1].i = 1;
    M->data[1].j = 1;
    M->data[1].e = 3;

    M->data[2].i = 1;
    M->data[2].j = 4;
    M->data[2].e = 5;

    M->data[3].i = 2;
    M->data[3].j = 2;
    M->data[3].e = -1;

    M->data[4].i = 3;
    M->data[4].j = 1;
    M->data[4].e = 2;

    M->rpos[1] = 1;
    M->rpos[2] = 3;
    M->rpos[3] = 4;
}

Status CreateTSMatrix_AUTO(RLSMatrix *M)
{
    M->mu = 4;
    M->nu = 2;
    M->tu = 4;
    M->data[1].i = 1;
    M->data[1].j = 2;
    M->data[1].e = 2;

    M->data[2].i = 2;
    M->data[2].j = 1;
    M->data[2].e = 1;

    M->data[3].i = 3;
    M->data[3].j = 1;
    M->data[3].e = -2;

    M->data[4].i = 3;
    M->data[4].j = 2;
    M->data[4].e = 4;

    M->rpos[1] = 1;
    M->rpos[2] = 2;
    M->rpos[3] = 3;
    M->rpos[4] = 5;
}

Status PrintTSMatrix(RLSMatrix M)
{
    int k;

    printf(" i  j  v\n");
    for(k = 1;k<= M.tu;k++)
        printf("%2d %2d %2d\n",M.data[k].i,M.data[k].j,M.data[k].e);
}

Status MultSMatrix(RLSMatrix M,RLSMatrix N,RLSMatrix *Q)
{
    int arow,brow,ccol,i,tp,p,q,tq,ctemp[N.nu+1];
    if(M.nu != N.mu)
        return ERROR;
    (*Q).mu = M.mu;
    (*Q).nu = N.nu;
    Q->tu = 0;
    if(M.tu * N.tu){  //Q�Ƿ������
        for(arow = 1;arow <= M.mu;++arow){ //����M��ÿһ��

            for(ccol = 0;ccol<=N.nu;++ccol)
                ctemp[ccol] = 0;//��ǰ�и�Ԫ���ۼ�������

            (*Q).rpos[arow] = (*Q).tu + 1;

            if(arow < M.mu)
               tp = M.rpos[arow + 1];
            else
               tp = M.tu + 1;

            for(p = M.rpos[arow]; p<tp;++p){  //�Ե�ǰ����ÿһ������Ԫ
                brow = M.data[p].j;  //�ҵ���ӦԪ��N�е��к�

                if(brow < N.mu)
                    tq = N.rpos[brow + 1];
                else
                    tq = N.tu + 1;

                for(q = N.rpos[brow];q < tq;++q){
                    ccol = N.data[q].j;
                    ctemp[ccol] += M.data[p].e * N.data[q].e;
                }//for q
            }//���Q�е�crow��=arow���еķ���Ԫ

            if(ctemp[ccol]){
                ++Q->tu;
                (*Q).data[(*Q).tu].i = arow;
                (*Q).data[(*Q).tu].j = ccol;
                (*Q).data[(*Q).tu].e = ctemp[ccol];
            }//if
        }//for arow
    }//if
    return OK;
}
/*******************************����������**************************************/
int main()
{
    RLSMatrix M,N,Q;
    CreateTSMatrix(&M);
    printf("M�������Ԫ���ʾΪ��\n");
    PrintTSMatrix(M);

    printf("\nN�������Ԫ���ʾΪ��\n");
    CreateTSMatrix_AUTO(&N);
    PrintTSMatrix(N);

    printf("\nQ = M * N ����Ԫ��Ϊ��\n");
    MultSMatrix(M,N,&Q);
    PrintTSMatrix(Q);
    return 0;
}



