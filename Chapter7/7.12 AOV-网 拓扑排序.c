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

typedef int SElemType;
#define STACK_INIT_SIZE 100  //�洢�ռ��ʼ������
#define STACKINCREMENT 10  //�洢�ռ��������

typedef struct
{
    SElemType *base;  //��ջ����֮ǰ������֮��base��ֵΪNULL
    SElemType *top;  //ջ��ָ��
    int stacksize;  //��ǰ�ѷ���Ĵ洢�ռ䣬��Ԫ��Ϊ��λ
}SqStack;



/*******************************��������****************************************/
Status InitStack(SqStack *S);
//����һ����ջS
Status Push(SqStack *S,SElemType e);
//����Ԫ��eΪ�µ�ջ��Ԫ��
Status Pop(SqStack *S,SElemType *e);
//��ջ���գ���ɾ��S��ջ��Ԫ�أ���e������ֵ
Status StackEmpty(SqStack S);
//��ջSΪ�գ��򷵻�TRUE������FALSE
Status CreateALGraph(ALGraph *G);
//�����ڽӱ�ʽ�洢������ͼ
int LocateVex(ALGraph G,VertexType v);
//ȷ��v��G�е�λ��
Status TopologicalSort(ALGraph G);
//��G�޻�·�����G�Ķ����һ���������в�����OK������ERROR
Status FindInDegree(ALGraph G,int indegree[]);
//�Ը����������indegree[0...vernum-1]
/*******************************��������****************************************/
Status InitStack(SqStack *S)
{
    (*S).base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));
    if(!(*S).base)
        exit(OVERFLOW);
    (*S).top = (*S).base;
    (*S).stacksize = STACK_INIT_SIZE;
    return OK;
}

Status Push(SqStack *S,SElemType e)
{
    if((*S).top - (*S).base >= (*S).stacksize){  //ջ����׷�ӿռ�
        (*S).base = (SElemType *)realloc((*S).base,((*S).stacksize + STACKINCREMENT)* sizeof(SElemType));
    if( !(*S).base)
        exit(OVERFLOW);
    (*S).top = (*S).base + (*S).stacksize;
    (*S).stacksize += STACKINCREMENT;
    }
    *(*S).top++ = e;
    return OK;
}

Status Pop(SqStack *S,SElemType *e)
{
    if((*S).top == (*S).base)
        return ERROR;
    *e = *--(*S).top;
    return OK;
}

Status StackEmpty(SqStack S)
{
    return S.base == S.top ? TRUE : FALSE;
}

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
        ArcNode *p;
        p = (ArcNode *)malloc(sizeof(ArcNode));
        p->adjvex = j;
        p->nextarc = NULL;

        if(r[i] == NULL)    //�ڽӱ��е�һ�����
            (*G).vertices[i].firstarc = p;   //���뵽�ڽӱ�
        else
            r[i]->nextarc = p;
        r[i] = p;
    }
    return OK;
}

Status CreateALGraph_auto(ALGraph *G)
{
    printf("��ʼ��������ͼ\n");
    int i,j,k;
    VertexType v1,v2;
    ArcNode *r[MAX_VERTEX_NUM+1];
    int v1_list[8] = {1,1,1,3,3,4,6,6};
    int v2_list[8] = {2,4,3,2,5,5,4,5};

    (*G).vexnum = 6;
    (*G).arcnum = 8;
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
        ArcNode *p;
        p = (ArcNode *)malloc(sizeof(ArcNode));
        p->adjvex = j;
        p->nextarc = NULL;

        if(r[i] == NULL)    //�ڽӱ��е�һ�����
            (*G).vertices[i].firstarc = p;   //���뵽�ڽӱ�
        else
            r[i]->nextarc = p;
        r[i] = p;
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

Status TopologicalSort(ALGraph G)
{
    SqStack S;
    int i,count,k;
    int indegree[MAX_VERTEX_NUM];
    ArcNode *p;

    FindInDegree(G,indegree);  //�Ը����������
    InitStack(&S);

    for(i = 0;i<G.vexnum;++i)  //��0���ջ��S
        if(!indegree[i])   //���Ϊ0�߽�ջ
            Push(&S,i);
    count = 0;  //������������
    while(!StackEmpty(S)){
        Pop(&S,&i);
        printf("%d,%d\n",i,G.vertices[i].data);
        ++count;  //���i�Ŷ��㲢����
        for(p = G.vertices[i].firstarc; p ;p = p->nextarc){
            k = p->adjvex;   //��i�Ŷ����ÿ���ڽӵ�����-1
            if(!(--indegree[k]))
                Push(&S,k);  //�����Ϊ0������ջ
        }//for
    }//while
    if(count < G.vexnum)
    {
        printf("������ͼ�л�·\n");
        return ERROR;  //������ͼ�л�·
    }
    else
        return OK;
}

Status FindInDegree(ALGraph G,int indegree[])
{
    int i,n = G.vexnum,j;
    ArcNode *p;
    for(i = 0;i<n;i++)
        indegree[i] = 0;
    for(i = 0;i<n;i++){
        p = G.vertices[i].firstarc;
        while(p){
            indegree[p->adjvex]++;
            p = p->nextarc;
        }//while
    }//for
    return OK;
}

/*******************************����������**************************************/
int main()
{
    ALGraph G;
    printf("P182,ͼ7.28 (a)\n");
    CreateALGraph_auto(&G);
    printf("��������������м��õ㱣���ֵΪ��\n");
    TopologicalSort(G);
    return 0;
}
