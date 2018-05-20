#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

#define MAXSIZE 20  //��󶥵���
typedef int Status;
typedef int ElemType;
typedef struct CSNode
{
    ElemType data;
    struct CSNode *firstchild,*nextsibling;
}CSNode,*CSTree;

typedef int Boolean;
Boolean Visited[MAXSIZE];  //���ʱ�־����

#define  INFINITY 65535   //���ֵ��
#define MAX_VERTEX_NUM 20  //��󶥵����

typedef int Status;
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
int FirstAdjVex(MGraph G,int v);
//����v�ĵ�һ���ڽӶ���
int NextAdjVex(MGraph G,int v,int w);
//����v�ģ������w�ģ���һ���ڽӶ���
VertexType Getvex(MGraph G,int v);
//v��G�е�ĳ�����㣬����v��ֵ

/*******************************��������****************************************/
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

    G->vexnum = 5;
    G->arcnum = 6;
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

    int v1_list[6] = {1,1,2,3,3,2};
    int v2_list[6] = {2,4,3,4,5,5};
    for(k = 0;k<(*G).arcnum;k++){  //�����ڽӾ���

        scanf("%d",&v2);*/
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

int LocateVex(MGraph G,VertexType v)
{
    int ct;
    for(ct = 0;ct < G.vexnum;ct++)
        if(G.vexs[ct] == v)
            return ct;
    return -1;
}

Status PrintfArcs(MGraph G)
{
    int n = G.vexnum;
    int i,j;  //i,j���ڼ���
    for(i = 0;i < n;i++){
        for(j = 0;j<n;j++){
            printf("%d ",G.arcs[i][j]);
        }
        printf("\n");
    }
    return OK;
}

VertexType Getvex(MGraph G,int v)
{
    return G.vexs[v];
}

int FirstAdjVex(MGraph G,int v)
{

    int k,j ,t;
    k = LocateVex(G,v);
    if(k)
    {
        t = 0;
        for(j = 0;j <G.vexnum;j++)
            if(G.arcs[k][j].adj != t)
                return j;
    }
    return -1;
}

int NextAdjVex(MGraph G,int v,int w)
{
    int j,t,k1,k2;
    t = 0;
    for(j = w+1;j<G.vexnum;j++)
        if(G.arcs[v][j].adj != t)
            return j;
    return -1;
}

void DFSTree(MGraph G,int v,CSTree *T)
{
    int first,w;
    CSTree p,q;
    Visited[v] = TRUE;
    first = TRUE;

    for(w = FirstAdjVex(G,G.vexs[v]);w >= 0;w = NextAdjVex(G,G.vexs[v],G.vexs[w])){
        if(!Visited[w]){
            p = (CSTree)malloc(sizeof(CSNode));  //���亢�ӽ��
            p->data = Getvex(G,w);   //���ý�㸳ֵ
            p->firstchild = NULL;
            p->nextsibling = NULL;
            if(first){      //w��v�ĵ�һ��δ�����ʵ��ڽӶ���
                (*T)->firstchild = p;  //�Ǹ������ӽ��
                first = FALSE;
            }//if
            else  //w��v������δ�����ʵ��ڽӶ���
                q->nextsibling = p;  //����һ�ڽӶ�������ֵܽ��
            q = p;
            DFSTree(G,w,&q);  //�ӵ�w���������������ȱ���ͼG��������������q
        }//if
    }//for
}

void DFSForest(MGraph G,CSTree *T)
{
    int v;
    CSTree p,q;

    *T = p = q = NULL;
    for(v = 0;v<G.vexnum;v++)
        Visited[v] = FALSE;

    for(v = 0;v<G.vexnum;v++)
    if(!Visited[v]){    //��v����Ϊ�µ��������ĸ��ĸ����
        p = (CSTree)malloc(sizeof(CSNode));  //��������
        p->data = Getvex(G,v);   //���ý�㸳ֵ
        p->firstchild = NULL;
        p->nextsibling = NULL;
        if(!(*T))
            *T = p;  //�ǵ�һ���������ĸ���T�ĸ���
        else
            q->nextsibling = p;  //�������������ĸ���ǰһ�����ĸ��ġ��ֵܡ���
        q = p;  //qָʾ��ǰ�������ĸ�
        DFSTree(G,v,&p);  //������pΪ����������
    }//if
}

Status Visit(int e)
{
    printf("%d,",e);
    return OK;
}

Status PreOrderTraverse(CSTree T,Status(*Visit)(int e))  //�ݹ�
{
    if(T){
        if(Visit(T->data))
            if(PreOrderTraverse(T->firstchild,Visit))
                if(PreOrderTraverse(T->nextsibling,Visit))
                    return OK;
        return ERROR;
    }
    else
        return OK;
}

void VisitFunc(MGraph G,int v)
{
    printf("%d ",G.vexs[v]);  //��ӡ�ö���
}

void DFS(MGraph G,int v)
{
    int w;
    Visited[v] = TRUE;
    VisitFunc(G,v);  //���ʵ�v������
    for(w = 0;w<G.vexnum;w++)
        if(G.arcs[v][w].adj == 1 && !Visited[w])
            DFS(G,w);  //��v����δ���ʵ��ڽӶ���w�ݹ����DFS
}

void DFSTraverse(MGraph G)
{
    int v;
    for(v = 0;v<G.vexnum;++v)  //���ʱ�־�����ʼ��
        Visited[v] = FALSE;
    for(v = 0;v<G.vexnum;++v)
        if(!Visited[v])
            DFS(G,v);  //����δ���ʵĶ������DFS
}

/*******************************����������**************************************/
int main()
{
    MGraph G;
    printf("\n�������������ͼ�������ʾ������\n");
    CreateUDG_auto(&G);
    PrintfArcs(G);
    printf("\n�������,DFS�������ͼ:\n");
    DFSTraverse(G);

    CSTree T;
    printf("\n\n�������������ͼ����������\n");
    DFSForest(G,&T);
    printf("\n�������,�����\n");
    PreOrderTraverse(T,Visit);
    return 0;
}




