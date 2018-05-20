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
typedef int ElemType;
typedef int QElemType;

#define MAXQSIZE 100  //max queue length
typedef struct
{
    QElemType *base;  //��ʼ���Ķ�̬����洢�ռ�
    int front;  //head pointer,�����в��գ�ָ�����ͷԪ��
    int rear;  //tail pointer,�����в��գ�ָ�����βԪ�ص���һ��λ��
}SqQueue;

#define INFINITY 65535   //���ֵ��
#define MAX_VERTEX_NUM 20  //��󶥵����
#define MAX 20
typedef int Status;
typedef int ElemType;
typedef int Boolean;

Boolean visited[MAX];  //���ʱ�־����

typedef int VRType;
typedef char InfoType;
typedef int VertexType;
typedef enum {DG,DN,UDG,UDN}GraphKind;   //{����ͼ��������������ͼ��������}

typedef struct ArcCell
{
    VRType adj;  //VRType �Ƕ����ϵ���͡�����Ȩͼ����0��1��ʾ���ڷ񣻶Դ�Ȩͼ����ΪȨֵ����
    InfoType *info; //�û������Ϣ��ָ��
}ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef struct
{
    VertexType vexs[MAX_VERTEX_NUM];  //��������
    AdjMatrix arcs;  //�ڽӾ���
    int vexnum,arcnum;  //ͼ�ĵ�ǰ�������ͻ���
    GraphKind kind;  //ͼ�������־
}MGraph;

/*******************************��������****************************************/



/*******************************��������****************************************/
Status InitQueue(SqQueue *Q)
{
    Q->base = (QElemType *)malloc(MAXQSIZE * sizeof(QElemType));
    if(!Q->base)
        exit(OVERFLOW);
    Q->front = Q->rear = 0;
    return OK;
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

Status QueueEmpty(SqQueue Q)
{
    return (Q.front == Q.rear);
}

int FirstAdjVex(MGraph G,int v)
{
    int k,j;
    v = LocateVex(G,v);
    if(v > 0){
    for(j = 0;j <G.vexnum;j++)
        if(G.arcs[v][j].adj != 0){
            return j;
        }
    }
    return -1;
}

int NextAdjVex(MGraph G,int v,int w)
{
    int j;
    v = LocateVex(G,v);
    if(v>0){
    for(j = w+1;j<G.vexnum;j++)
        if(G.arcs[v][j].adj != 0){
            return j;
        }
    }
    return -1;
}

int LocateVex(MGraph G,VertexType v)
{
    int ct;
    for(ct = 0;ct < G.vexnum;ct++)
        if(G.vexs[ct] == v)
            return ct;
    return -1;
}

Status CreateUDG(MGraph *G)
{
    printf("\n��������ͼ\n");
    int i,j,k; //i,j,k���ڼ���
    VertexType v1,v2;  //��ͷ����β

    printf("�����붥�������");
    scanf("%d",&(*G).vexnum);
    printf("�����뻡������");
    scanf("%d",&(*G).arcnum);
    //�ٶ���ͼ����������Ϣ
    int IncInfo = 0;
    for(i = 0;i<(*G).vexnum;i++){  //��ʼ����������
       (*G).vexs[i]=0;
    } //for

    for(i = 0;i<(*G).vexnum;i++){  //���춥������
        printf("������G.vexs[%d] = ",i);
        scanf("%d",&(*G).vexs[i]);
    } //for

    for(i = 0;i<(*G).vexnum;i++)  //��ʼ���ڽӾ���
        for(j = 0;j<(*G).vexnum;j++){
            (*G).arcs[i][j].adj = 0;  //����ͼ
            (*G).arcs[i][j].info = NULL;
        }

    for(k = 0;k<(*G).arcnum;k++){  //�����ڽӾ���
        printf("�����뻡ͷ(��ʼ��)��");  //����һ������ʼ����յ�
        scanf("%d",&v1);
        printf("�����뻡β(�ն˵�)��");
        scanf("%d",&v2);

        i = LocateVex(*G,v1);
        j = LocateVex(*G,v2);

        if(i>=0 && j>=0)
            (*G).arcs[i][j].adj = (*G).arcs[j][i].adj = 1;
            //��<v1,v2>�ĶԳƻ�<v2,v1>
    }
    G->kind = UDG;
    return OK;
}

Status CreateUDG_auto(MGraph *G)
{
    printf("\n��������ͼ\n");
    int i,j,k; //i,j,k���ڼ���
    VertexType v1,v2;  //��ͷ����β

    G->vexnum = 8;
    G->arcnum = 9;
    //�ٶ���ͼ����������Ϣ
    int IncInfo = 0;

    for(i = 0;i<(*G).vexnum;i++){  //���춥������
        G->vexs[i] = i+1;
    } //for

    for(i = 0;i<(*G).vexnum;i++)  //��ʼ���ڽӾ���
        for(j = 0;j<(*G).vexnum;j++){
            (*G).arcs[i][j].adj = 0;  //����ͼ
            (*G).arcs[i][j].info = NULL;
        }

    int v1_list[9] = {1,1,2,2,3,3,4,5,6};
    int v2_list[9] = {2,3,4,5,6,7,8,8,7};
    for(k = 0;k<(*G).arcnum;k++){  //�����ڽӾ���
        v1 = v1_list[k];
        v2 = v2_list[k];

        i = LocateVex(*G,v1);
        j = LocateVex(*G,v2);

        if(i>=0 && j>=0)
            (*G).arcs[i][j].adj = (*G).arcs[j][i].adj = 1;
            //��<v1,v2>�ĶԳƻ�<v2,v1>
    }
    G->kind = UDG;
    return OK;
}

void BFSTraverse(MGraph G)
{
    SqQueue Q;
    int v,u,w , visited[G.vexnum],ct;
    for(v = 0;v<G.vexnum;++v)
        visited[v] = FALSE;
    InitQueue(&Q);

    for(v = 0;v<G.vexnum;++v)
    if(!visited[v]){
        visited[v] = TRUE;
        printf("%d ",G.vexs[v]);
        EnQueue(&Q,v);
        while(!QueueEmpty(Q)){
            DeQueue(&Q,&u);
            for(w = FirstAdjVex(G,u);w>=0;w = NextAdjVex(G,u,w))
            if(w>0&&!visited[w]){
                visited[w] = TRUE;
                printf("%d ",G.vexs[w]);
                EnQueue(&Q,w);
            }//if
        }//while
    }//if
}
Status PrintfArcs(MGraph G)
{
    int n = G.vexnum;
    int i,j;  //i,j���ڼ���
    for(i = 0;i < n;i++){
        for(j = 0;j<n;j++){
            if(G.arcs[i][j].adj == INFINITY)
                printf("�� ");
            else
                printf("%d ",G.arcs[i][j].adj);
        }
        printf("\n");
    }
    return OK;
}
/*******************************����������**************************************/
int main()
{
    MGraph G;
    CreateUDG_auto(&G);

    printf("\nBFS���������\n");

    BFSTraverse(G);
    return 0;
}



