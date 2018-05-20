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

typedef int Status;
typedef int ElemType;

#define MAXSIZE 20
typedef int KeyType;
typedef char InfoType;
typedef struct
{
    KeyType key;
    InfoType otherinfo;
}RedType;
typedef struct
{
    RedType r[MAXSIZE+1];  //0�ŵ�Ԫ�ÿջ������ڱ�
    int length;
}SqList;

/*******************************��������****************************************/
void BInsertSort(SqList *L);
//��˳���L�۰��������
Status CreateSqList(SqList *L);
//����˳���
Status TraverseSqList(SqList L);
//��ӡ˳���
/*******************************��������****************************************/
void BInsertSort(SqList *L)
{
    int i,j,low,high,m;

    for(i = 2;i <= L->length;++i){
        L->r[0] = L->r[i];
        low = 1;
        high = i-1;
        while(low <= high){
            m = (low+high)/2;
            if(LT(L->r[0].key , L->r[m].key))
                high = m-1;
            else
                low = m+1;
        }//while
        for(j = i-1; j >= high+1; --j)
            L->r[j+1] = L->r[j];  //����
        L->r[high+1] = L->r[0];  //����
    }//for
}

Status CreateSqList(SqList *L)
{
 /*   int i;
    printf("�����볤�ȣ�");
    scanf("%d",&L->length);
    for(i = 1;i <= L->length;i++){
        printf("������ؼ�ֵ��");
        scanf("%d",&L->r[i].key);
    }*/
    L->r[1].key = 49;
    L->r[2].key = 38;
    L->r[3].key = 65;
    L->r[4].key = 97;
    L->r[5].key = 76;
    L->r[6].key = 13;
    L->r[7].key = 27;
    L->length = 7;

    return OK;
}

Status TraverseSqList(SqList L)
{
    int i;
    for(i = 1;i<=L.length;i++)
        printf("%d  ",L.r[i].key);

    printf("\n");
    return OK;
}

/*******************************����������**************************************/
int main()
{
    SqList L;
    printf("����һ��˳���\n");
    CreateSqList(&L);
    TraverseSqList(L);

    printf("\n�۰���������\n");
    BInsertSort(&L);
    TraverseSqList(L);
}




