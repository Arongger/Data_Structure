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
typedef char InfoType;
typedef int VertexType;

#define MAX_VERTEX_NUM 20
typedef struct ArcNode
{
    int adjvex;  //�û���ָ��Ķ����λ��
    struct ArcNode *nextarc;  //ָ����һ������ָ��
    InfoType *info;  //�û������Ϣ��ָ��
}ArcNode;
typedef struct VNode
{
    VertexType data;   //������Ϣ
    ArcNode *firstarc;   //ָ���һ�������ö���Ļ���ָ��
}VNode,AdjList[MAX_VERTEX_NUM];
typedef struct
{
    AdjList vertices;
    int vexnum,arcnum;  //ͼ�ĵ�ǰ�������ͻ���
    int kind;  //ͼ�������־
}ALGraph;  //Adjacency List Graph   �ڽӱ�

int count;  //ȫ�ֱ���count�Է��ʼ�����
int Visited[MAX_VERTEX_NUM];
int low[MAX_VERTEX_NUM];
/*******************************��������****************************************/
Status CreateALGraph(ALGraph *G);
//�����ڽӱ�ʽ�洢������ͼ
int LocateVex(ALGraph G,VertexType v);
//ȷ��v��G�е�λ��
void DFSArticul(ALGraph G,int v0);
//�ӵ�v0���������������ȱ���ͼG�����Ҳ�����ؽڵ�
void FindArticul(ALGraph G);
//��ͨͼG���ڽӱ����洢�ṹ�����Ҳ����G��ȫ���ؽڵ�
/*******************************��������****************************************/
Status CreateALGraph(ALGraph *G)
{
    printf("��ʼ��������ͼ\n");
    int i,j,k;
    VertexType v1,v2;
    ArcNode *r[MAX_VERTEX_NUM+1];

    printf("\n�����붥�������");
    scanf("%d",&(*G).vexnum);
    printf("�����뻡������");
    scanf("%d",&(*G).arcnum);
    //�ٶ���ͼ����������Ϣ
    int IncInfo = 0;

    for(i = 0;i<(*G).vexnum;i++){  //���춥������
        printf("������G..vertices[%d].data = ",i);
        scanf("%d",&(*G).vertices[i].data);
        (*G).vertices[i].firstarc = NULL;
        r[i] = NULL;
    } //for

    for(k = 0;k<(*G).arcnum;k++){
        printf("�����뻡ͷ(��ʼ��)��");  //����һ������ʼ����յ�
        scanf("%d",&v1);
        printf("�����뻡β(�ն˵�)��");
        scanf("%d",&v2);
        i = LocateVex(*G,v1);
        j = LocateVex(*G,v2);

        if(i<0 || j<0)
            return ERROR;
        ArcNode *p,*q;
        p = (ArcNode *)malloc(sizeof(ArcNode));
        p->adjvex = j;
        p->nextarc = NULL;

        if(r[i] == NULL)    //�ڽӱ��е�һ�����
            (*G).vertices[i].firstarc = p;   //���뵽�ڽӱ�
        else
            r[i]->nextarc = p;
        r[i] = p;

        q = (ArcNode *)malloc(sizeof(ArcNode));
        q->adjvex = i;
        q->nextarc = NULL;

        if(r[j] == NULL)    //�ڽӱ��е�һ�����
            (*G).vertices[j].firstarc = q;   //���뵽�ڽӱ�
        else
            r[j]->nextarc = q;
        r[j] = q;
    }
    return OK;
}

Status CreateALGraph_auto(ALGraph *G)
{
    printf("��ʼ��������ͼ\n");
    int i,j,k;
    VertexType v1,v2;
    ArcNode *r[MAX_VERTEX_NUM+1];
    int v1_list[17] = {1,1,1,1,12,10,10,2,2,2,2,2,8,7,11,7,4};
    int v2_list[17] = {12,2,3,6,13,12,13,13,8,7,4,3,11,8,7,9,5};

    (*G).vexnum = 13;
    (*G).arcnum = 17;
    //�ٶ���ͼ����������Ϣ
    int IncInfo = 0;

    for(i = 0;i<(*G).vexnum;i++){  //���춥������
        (*G).vertices[i].data = i+1;
        (*G).vertices[i].firstarc = NULL;
        r[i] = NULL;
    } //for

    for(k = 0;k<(*G).arcnum;k++){
        v1 = v1_list[k];
        v2 = v2_list[k];
        i = LocateVex(*G,v1);
        j = LocateVex(*G,v2);

        if(i<0 || j<0)
            return ERROR;
        ArcNode *p,*q;
        p = (ArcNode *)malloc(sizeof(ArcNode));
        p->adjvex = j;
        p->nextarc = NULL;

        if(r[i] == NULL)    //�ڽӱ��е�һ�����
            (*G).vertices[i].firstarc = p;   //���뵽�ڽӱ�
        else
            r[i]->nextarc = p;
        r[i] = p;

        q = (ArcNode *)malloc(sizeof(ArcNode));
        q->adjvex = i;
        q->nextarc = NULL;

        if(r[j] == NULL)    //�ڽӱ��е�һ�����
            (*G).vertices[j].firstarc = q;   //���뵽�ڽӱ�
        else
            r[j]->nextarc = q;
        r[j] = q;
    }
    return OK;
}


int LocateVex(ALGraph G,VertexType v)
{
    int ct;
    for(ct = 0;ct < G.vexnum;ct++)
        if(G.vertices[ct].data == v)
            return ct;
    return -1;
}

void DFSArticul(ALGraph G,int v0)
{
    int min,w;
    ArcNode *p;

    Visited[v0] = min = ++count;  //v0�ǵ�count�����ʵĶ���
    for(p = G.vertices[v0].firstarc; p ;p = p->nextarc){  //��v0��ÿ���ڽӶ�����
        w = p->adjvex;  //wΪv0���ڽӶ���
        if(Visited[w] == 0){  //wδ�����ʣ���v0�ĺ���
            DFSArticul(G,w);  //����ǰ���low[w]
            if(low[w] < min)
                min = low[w];
            if(low[w] >= Visited[v0])
                printf("%d,%d\n",v0,G.vertices[v0].data);  //�ؽڵ�
        }//if
        else if(Visited[w] < min)
            min = Visited[w];  //w�ѷ��ʣ�w��v0���������ϵ�����
    }//for
    low[v0] = min;
}

void FindArticul(ALGraph G)
{
    int i,v;
    ArcNode *p;

    count = 1;
    low[0] = Visited[0] = 1;  //�趨�ڽӱ���0�Ŷ���Ϊ�������ĸ�

    for(i = 1;i<G.vexnum;++i)
        Visited[i] = 0;  //���ඥ����δ����

    p = G.vertices[0].firstarc;
    v = p->adjvex;

    DFSArticul(G,v);  //�ӵ�v�������������Ȳ��ҹؽڵ�

    if(count < G.vexnum){
        printf("%d,%d\n",0,G.vertices[0].data);
        while(p->nextarc){
            p = p->nextarc;
            v = p->adjvex;
            if(Visited[v] == 0)
                DFSArticul(G,v);
        }//while
    }//if
}

/*******************************����������**************************************/

int main()
{
    int i;
    ALGraph G;

    printf("P177,ͼ7.19 G5\n");
    CreateALGraph_auto(&G);

    printf("\n�ؽڵ㼰�ؽڵ㱣��ĵ�ֵΪ��\n");
    FindArticul(G);
    return 0;
}


