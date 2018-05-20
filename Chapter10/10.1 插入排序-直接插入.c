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
void InsertSort(SqList *L);
//��˳���L��ֱ�Ӳ�������
Status CreateSqList(SqList *L);
//����˳���
Status TraverseSqList(SqList L);
//��ӡ˳���
/*******************************��������****************************************/
void InsertSort(SqList *L)
{
    int i,j;

    for(i = 2;i <= L->length;++i){
        if(LT(L->r[i].key , L->r[i-1].key)){
            L->r[0] = L->r[i];  //����Ϊ�ڱ�
            L->r[i] = L->r[i-1];
            for(j = i-2; LT(L->r[0].key , L->r[j].key); --j)
                L->r[j+1] = L->r[j];  //����
            L->r[j+1] = L->r[0];  //����
        }//if
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
    L->r[8].key = 49;

    L->length = 8;

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

    printf("\nֱ�Ӳ��������\n");
    InsertSort(&L);
    TraverseSqList(L);
}



