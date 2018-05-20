#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

//ֱ���޸�N���㲻ͬNֵ��N�ʺ�����
#define N 8
typedef int Status;
int Q[N][N];
int count = 0;
/*******************************��������****************************************/

/*******************************��������****************************************/
void ShowQueen()
{
    int ct1,ct2;
    for(ct1=0;ct1 <N;ct1++){
        for(ct2 = 0;ct2<N;ct2++)
            printf("%d ",Q[ct1][ct2]);
        printf("\n");
    }
    printf("\n");

}
void Queen(int i)
{
    int j,ct1,ct2;
    if(i== N){  //������̵ĵ�ǰ����
        ShowQueen();
        count++;
    }//if
    else
        for(j = 0;j < N;++j){
            Q[i][j] = 1;
            if(IsCorrect(i,j))
                Queen(i+1);
            Q[i][j] = 0;
            //if
        }//for
}

Status IsCorrect(int i,int j)
{
    int row,col;
    //�����ж�
    for(row = 0;row<i;row++)
        if(Q[row][j] == 1)
        return 0;
    for(row = i+1;row <N;row++)
        if(Q[row][j]==1)
            return 0;

    //�����ж�
    for(col = 0;col<j;col++)
        if(Q[i][col]==1)
            return 0;
    for(col = j+1;col<N;col++)
        if(Q[i][col]==1)
            return 0;

    //�Խ��ж�
    for(row = i-1,col = j-1;row>=0 && col>=0 ;row--,col--)
        if(Q[row][col]==1)
            return 0;
    for(row = i+1,col = j+1;row<N && col<N ;row++,col++)
        if(Q[row][col]==1)
            return 0;
    for(row = i+1,col = j-1;row<N && col>=0 ;row++,col--)
        if(Q[row][col]==1)
            return 0;
    for(row = i-1,col = j+1;row>=0 && col<N ;row--,col++)
        if(Q[row][col]==1)
            return 0;

    return 1;//���򷵻�
}

/*******************************����������**************************************/

int main()
{
    int i,j;
    for(i = 0;i<N;i++)
        for(j = 0;j<N;j++)
            Q[i][j] = 0;
    Queen(0);
    printf("N = %d ʱ��һ���� %d �ֽⷨ\n",N,count);
    return 0;
}


