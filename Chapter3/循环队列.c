#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int Status;
typedef int QElemType;

#define MAXQSIZE 100  //max queue length
typedef struct
{
    QElemType *base;  //��ʼ���Ķ�̬����洢�ռ�
    int front;  //head pointer,�����в��գ�ָ�����ͷԪ��
    int rear;  //tail pointer,�����в��գ�ָ�����βԪ�ص���һ��λ��
}SqQueue;

/*******************************��������****************************************/
Status InitQueue(SqQueue *Q);
//����һ���ն���Q
int QueueLength(SqQueue Q);
//����Q��Ԫ�ظ����������еĳ���
Status EnQueue(SqQueue *Q,QElemType e);
//����Ԫ��eΪQ���µĶ�βԪ��
Status DeQueue(SqQueue *Q,QElemType *e);
//�����в��գ���ɾ��Q�Ķ�ͷԪ�أ���e������ֵ
Status TraverseQueue(SqQueue Q);
//�������Q�е�����Ԫ��
/*******************************��������****************************************/
Status InitQueue(SqQueue *Q)
{
    Q->base = (QElemType *)malloc(MAXQSIZE * sizeof(QElemType));
    if(!Q->base)
        exit(OVERFLOW);
    Q->front = Q->rear = 0;
    return OK;
}

int QueueLength(SqQueue Q)
{
    return (Q.rear-Q.front+MAXQSIZE)%MAXQSIZE;
}

Status EnQueue(SqQueue *Q,QElemType e)
{
    if((Q->rear+1)%MAXQSIZE==Q->front)
        return ERROR;
    Q->base[Q->rear] = e;
    Q->rear = (Q->rear+1)%MAXQSIZE;
    return OK;
}

Status DeQueue(SqQueue *Q,QElemType *e)
{
    if(Q->front == Q->rear)
        return ERROR;
    *e = Q->base[Q->front];
    Q->front = (Q->front+1)%MAXQSIZE;
    return OK;
}

Status TraverseQueue(SqQueue Q)
{
    if(Q.front == Q.rear){
        printf("����Ϊ��\n");
        return ERROR;
    }
    int i = Q.front;
    while(i%MAXQSIZE != Q.rear)
        printf("%d ",Q.base[i++]);
    printf("\n");
    return OK;
}
/*******************************����������**************************************/

int main()
{
    SqQueue Q;
    QElemType e;

    printf("��ʼ��һ���ն��У�\n");
    InitQueue(&Q);
    TraverseQueue(Q);

    printf("\n������� 1...10 ��\n");
    int i;
    for(i = 1;i<=10;++i)
        EnQueue(&Q,i);
    TraverseQueue(Q);

    printf("\n�ڶ���β����Ԫ�� 13 ��\n");
    EnQueue(&Q,13);
    TraverseQueue(Q);

    printf("\nɾ����ͷԪ�أ���e���ظ�ɾ��ֵ��\n");
    DeQueue(&Q,&e);
    TraverseQueue(Q);
    printf("��ɾ����Ԫ�� e = %d\n",e);

    printf("\n������˳�...\n");
    _getch();
    return 0;
}


