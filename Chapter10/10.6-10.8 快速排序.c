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
/*******************************��������************************************/
Status CreateSqList(SqList *L);
//����˳���
Status TraverseSqList(SqList L);
//��ӡ˳���
int Partition_1(SqList *L,int low,int high);
//����˳���L���ӱ�L.r[low,high]�ļ�¼��ʹ�����¼��λ����������λ�ã�
//��ʱ��֮ǰ(��)�ļ�¼������С������
int Partition_2(SqList *L,int low,int high);
//����˳���L���ӱ�L.r[low,high]�ļ�¼��ʹ�����¼��λ����������λ�ã�
//��ʱ��֮ǰ(��)�ļ�¼������С������
void QSort_1(SqList *L,int low,int high);
//��˳���L�е�������L.r[low...high]����������
void QSort_2(SqList *L,int low,int high);
//��˳���L�е�������L.r[low...high]����������
/*******************************��������************************************/
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

int Partition_1(SqList *L,int low,int high)
{
    RedType temp;
    int pivotkey = L->r[low].key;
    while(low < high){
        while(low < high && L->r[high].key >= pivotkey)
            --high;
        temp = L->r[low];
        L->r[low] = L->r[high];
        L->r[high] = temp;
        while(low < high && L->r[low].key <= pivotkey)
            ++low;
        temp = L->r[low];
        L->r[low] = L->r[high];
        L->r[high] = temp;
    }
    return low;
}

int Partition_2(SqList *L,int low,int high)
{
    int pivotkey;
    L->r[0] = L->r[low];
    pivotkey = L->r[low].key;
    while(low < high){
        while(low < high && L->r[high].key >= pivotkey)
            --high;
        L->r[low] = L->r[high];
        while(low < high && L->r[low].key <= pivotkey)
            ++low;
        L->r[high] = L->r[low];
    }
    L->r[low] = L->r[0];
    return low;

}

void QSort_1(SqList *L,int low,int high)
{
    int pivoloc;
    if(low < high){
        pivoloc = Partition_1(L,low,high);
        QSort_1(L,low,pivoloc-1);
        QSort_1(L,pivoloc+1,high);
    }
}

void QSort_2(SqList *L,int low,int high)
{
    int pivoloc;
    int ct;
    if(low < high){
        pivoloc = Partition_1(L,low,high);
        for(ct = 1;ct <=L->length;++ct)
            printf("%d ",L->r[ct]);
        printf("\n\n");
        QSort_2(L,low,pivoloc-1);
        QSort_2(L,pivoloc+1,high);
        /*Output*/
    }

}

void QuickSort(SqList *L)
{
    QSort_1(L,1,L->length);
}

/*******************************����������**********************************/
int main()
{
    SqList L1,L2;

    printf("����һ��˳���\n");
    CreateSqList(&L1);
    TraverseSqList(L1);

    printf("\nʹ���㷨10.6(a)��������\n");
    QSort_1(&L1,1,L1.length);
    TraverseSqList(L1);

    CreateSqList(&L2);
    printf("\nʹ���㷨10.6(b)��������\n");
    QSort_2(&L2,1,L2.length);
    printf("���ս����\n");
    TraverseSqList(L2);
    return 0;
}



