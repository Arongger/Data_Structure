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
typedef int InfoType;
typedef int VertexType;

#define MAX_VERTEX_NUM 20
typedef struct ArcNode
{
    int adjvex;  //�û���ָ��Ķ����λ��
    struct ArcNode *nextarc;  //ָ����һ������ָ��
    int info;  //�û������Ϣ��ָ�� //Ȩ��
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

int ve[MAX_VERTEX_NUM];
int vl[MAX_VERTEX_NUM];
/*******************************��������****************************************/
Status InitStack(SqStack *S);
//����һ����ջS
Status Push(SqStack *S,SElemType e);
//����Ԫ��eΪ�µ�ջ��Ԫ��
Status Pop(SqStack *S,SElemType *e);
//��ջ���գ���ɾ��S��ջ��Ԫ�أ���e������ֵ
Status StackEmpty(SqStack S);
//��ջSΪ�գ��򷵻�TRUE������FALSE
int LocateVex(ALGraph G,VertexType v);
//ȷ��v��G�е�λ��
Status CreateALGraph(ALGraph *G);
//����������
Status FindInDegree(ALGraph G,int indegree[]);
//�Ը����������indegree[0...vernum-1]
Status TopologicalSort(ALGraph G,SqStack *T);
//������G�����ڽӱ�洢�ṹ����������¼������緢��ʱ��ve(ȫ�ֱ���)
//TΪ�������ж���ջ��SΪ����ȶ���ջ
//��G�޻�·������ջT����G��һ���������У��Һ���ֵΪOK������ΪERROR
Status CriticalPath(ALGraph G);
//GΪ�����������G�ĸ���ؼ��
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

Status CreateALGraph(ALGraph *G)
{
    printf("��ʼ����������\n");
    int i,j,k,w;
    VertexType v1,v2;

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
    } //for

    for(k = 0;k<(*G).arcnum;k++){
        printf("�����뻡ͷ(��ʼ��)��");  //����һ������ʼ����յ�
        scanf("%d",&v1);
        printf("�����뻡β(�ն˵�)��");
        scanf("%d",&v2);
        printf("������Ȩ�أ�");
        scanf("%d",&w);
        i = LocateVex(*G,v1);
        j = LocateVex(*G,v2);

        if(i<0 || j<0)
            return ERROR;

        ArcNode *p;
        p = (ArcNode *)malloc(sizeof(ArcNode));
        p->adjvex = j;
        p->nextarc = (*G).vertices[i].firstarc;
        (*G).vertices[i].firstarc = p;

        p->info = w;
    }
    return OK;
}

Status CreateALGraph_auto(ALGraph *G)
{
    printf("��ʼ����������\n");
    int i,j,k,w;
    VertexType v1,v2;
    int v1_list[11] = {1,1,1,2,3,4,5,5,6,7,8};
    int v2_list[11] = {2,3,4,5,5,6,7,8,8,9,9};
    int w_list[11] = {6,4,5,1,1,2,9,7,4,2,4};
    (*G).vexnum = 9;
    (*G).arcnum = 11;

    //�ٶ���ͼ����������Ϣ
    int IncInfo = 0;

    for(i = 0;i<(*G).vexnum;i++){  //���춥������
        (*G).vertices[i].data = i+1;
        (*G).vertices[i].firstarc = NULL;
    } //for

    for(k = 0;k<(*G).arcnum;k++){
        v1 = v1_list[k];
        v2 = v2_list[k];
        w = w_list[k];
        i = LocateVex(*G,v1);
        j = LocateVex(*G,v2);

        if(i<0 || j<0)
            return ERROR;

        ArcNode *p;
        p = (ArcNode *)malloc(sizeof(ArcNode));
        p->adjvex = j;
        p->nextarc = (*G).vertices[i].firstarc;
        (*G).vertices[i].firstarc = p;

        p->info = w;
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

Status TopologicalSort(ALGraph G,SqStack *T)
{
    int i,j,count,k;
    int indegree[MAX_VERTEX_NUM];
    ArcNode *p;
    SqStack S;

    FindInDegree(G,indegree);  //�Ը����������
    InitStack(&S);
    for(j = 0;j < G.vexnum;j++)
        if(!indegree[j])
        Push(&S,j);

    count = 0;  //������������

    for(i = 0;i<G.vexnum;++i)
        ve[i] = 0;  //��ʼ��

    while(!StackEmpty(S)){
        Pop(&S,&j);
        Push(&(*T),j);
        ++count;
        for(p = G.vertices[j].firstarc; p ;p = p->nextarc){
            k = p->adjvex;   //��i�Ŷ����ÿ���ڽӵ�����-1
            if(!(--indegree[k]))
                Push(&S,k);  //�����Ϊ0������ջ
            if(ve[j] + p->info > ve[k])
                ve[k] = ve[j]+ p->info;
        }//for
    }//while
    if(count < G.vexnum)
    {
        printf("���������л�·\n");
        return ERROR;  //������ͼ�л�·
    }
    else
        return OK;
}

Status CriticalPath(ALGraph G)
{
    SqStack T;
    int i,j,k,dut,ee,el;
    char tag;
    ArcNode *p;

    InitStack(&T);
    if(!TopologicalSort(G,&T))
        return ERROR;

    j = ve[0];
    for(i = 1;i<G.vexnum;i++)
        if(ve[i] > j)
        j = ve[i];

    for(i = 0;i<G.vexnum;i++)
        vl[i] = j;

    while(!StackEmpty(T))

        for(Pop(&T,&j),p = G.vertices[j].firstarc; p ; p = p ->nextarc){
            k = p->adjvex;
            dut = p->info;
            if(vl[k]-dut  < vl[j])
                vl[j] = vl[k]-dut;
        }//for
    printf("j   k   dut   ee   el   tag\n");

    for(j = 0;j<G.vexnum;j++)
    for(p = G.vertices[j].firstarc; p ;p = p->nextarc){
        k = p->adjvex;
        dut = p->info;
        ee = ve[j];
        el = vl[k]-dut;
        tag = (ee == el) ? '*':' ' ;
        printf("%2d  a%d =%2d  < %2d , %2d>  %2c\n",j,k,dut,ee,el,tag);
    }//for
    printf("����ؼ�·����\n");
    for(j = 0;j < G.vexnum; j++){
        for(p = G.vertices[j].firstarc; p ; p = p->nextarc){
            k = p->adjvex;
            dut = p->info;
            if(ve[j] == vl[k]-dut)
                printf("%d->%d\n",G.vertices[j].data,G.vertices[k].data);
        }//for
    }//for
    return OK;
}

/*******************************����������**************************************/
int main()
{
    ALGraph G;
    printf("P168 ͼ7.29\n");
    CreateALGraph_auto(&G);
    CriticalPath(G);
    return 0;
}
