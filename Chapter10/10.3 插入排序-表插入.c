#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

#define MAXINT -1
#define EQ(a,b) ((a) == (b))
#define LT(a,b) ((a) <  (b))
#define LQ(a,b) ((a) <= (b))

typedef int Status;
typedef int ElemType;
typedef int RcdType;
#define SIZE 100
typedef struct
{
    RcdType rc;  //��¼��
    int next;  //ָ����
}SLNode;
typedef struct
{
    SLNode r[SIZE];  //0�ŵ�ԪΪ��ͷ���
    int length;  //����ǰ����
}SLinkListType;  //��̬��������

/*******************************��������****************************************/



/*******************************��������****************************************/
Status CreateSLinkList(SLinkListType *SL)
{
    int i;
/*    printf("�����뾲̬�����ȣ�");
    scanf("%d",&SL->length);
    for(i = 1;i <= SL->length; i++){
        printf("������ֵ��");
        scanf("%d",&SL->r[i].rc);
        SL->r[i].next = i+1;
    }*/
    int arr[8] = {49,38,65,97,76,13,27,49};
    SL->r[0].rc = MAXINT;
    SL->r[0].next = 0;
    SL->length = 8;
    int j = 0;
    for(i = 1;i <= SL->length; i++){
        SL->r[i].rc = arr[j++];
        SL->r[i].next = -1;
    }
 //   SL->r[SL->length].next = 0;
    return OK;
}

Status TraverseSLL(SLinkListType SL)
{
    int i;
    printf("key  : ");
    for(i = 0;i<=SL.length;i++){
        printf("%5d",SL.r[i].rc);
    }
    printf("\n");
    printf("next : ");
    for(i = 0;i<=SL.length;i++){
        printf("%5d",SL.r[i].next);
    }

    printf("\n");
    return OK;
}

int Sort(SLinkListType *SL)
{
    int i,j,k;
    for(i = 1;i<=SL->length;i++){
        for(k=0,j=SL->r[k].next;j && LT(SL->r[j].rc,SL->r[i].rc);
            k=j,j=SL->r[k].next);
        SL->r[i].next = j;
        SL->r[k].next = i;
    }
    return OK;
}

void Arrange(SLinkListType *SL)
{
    int p,i,q;
    SLNode temp;

    p = SL->r[0].next;
    for(i = 1;i <= SL->length;i++){
        while(p < i)
            p = SL->r[p].next;

        q = SL->r[p].next;

        if( p != i){
            temp = SL->r[p];
            SL->r[p] = SL->r[i];
            SL->r[i] = temp;
            SL->r[i].next = p;
        }//if
        p = q;
    }//for
}

/*******************************����������**************************************/

int main()
{
    SLinkListType SL;
    printf("������̬����\n");
    CreateSLinkList(&SL);
    TraverseSLL(SL);

    printf("\n�޸�ָ�룺\n");
    Sort(&SL);
    TraverseSLL(SL);

    printf("\n���������\n");
    Arrange(&SL);
    TraverseSLL(SL);

    return 0;
}


