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

// 6.15 �� 6.14 ���󾫺���㷨��ֻ���6.15
int A[4] = {0,1,2,3};  //ǰ���0�����㣬ֻ���2-4��Ԫ�ص��ݼ�
int B[20];
int k = 0;
/*******************************��������****************************************/

void Output(int *B);
//�����ǰBֵ
void GetPowerSet(int i,int n);
//���ݼ�

/*******************************��������****************************************/
void Output(int *B)
{
    int ct;
    printf("{");
    for(ct = 0;ct <k;ct++){
        printf(" %d ",B[ct]);
        if(ct != k-1)
            printf(",");
    }
    printf("},");

}

void GetPowerSet(int i,int n)
{
    int ct,B_len;
    if(i > n)
        Output(B);

    else{
        B[k] = A[i];
        k++;
        GetPowerSet(i+1,n);

        k--;
        GetPowerSet(i+1,n);
    }
}

/*******************************����������**************************************/
int main()
{
    GetPowerSet(1,3);
    printf("\n");
    return 0;
}

