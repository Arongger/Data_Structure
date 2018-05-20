#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAX 20

#define  INFINITY 65535   //���ֵ��
#define MAX_VERTEX_NUM 20  //��󶥵����

typedef int Status;
typedef int ElemType;
typedef int Boolean;

Boolean Visited[MAX];  //���ʱ�־����

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
Status CreateUDG(MGraph *G);
//��������ͼ  //����������ȱ���
int LocateVex(MGraph G,VertexType v);
//ȷ��v��G�е�λ��
void VisitFunc(MGraph G,int v);
//��ӡ�����v���������Ϣ
void DFS(MGraph G,int v);
//�ӵ�v����������ݹ��shenduyouxianͼG
void DFSTraverse(MGraph G);
//��ͼG��������ȱ���
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
    return OK;
}

Status CreateUDG_auto(MGraph *G)
{
    printf("\n��������ͼ\n");
    int i,j,k; //i,j,k���ڼ���
    VertexType v1,v2;  //��ͷ����β
    int v1_list[6] = {1,1,2,3,3,2};
    int v2_list[6] = {2,4,3,4,5,5};

    (*G).vexnum = 5;
    (*G).arcnum = 6;
    //�ٶ���ͼ����������Ϣ
    int IncInfo = 0;

    for(i = 0;i<(*G).vexnum;i++){  //���춥������
        (*G).vexs[i] = i+1;
    } //for

    for(i = 0;i<(*G).vexnum;i++)  //��ʼ���ڽӾ���
        for(j = 0;j<(*G).vexnum;j++){
            (*G).arcs[i][j].adj = 0;  //����ͼ
            (*G).arcs[i][j].info = NULL;
        }

    for(k = 0;k<(*G).arcnum;k++){  //�����ڽӾ���
        v1 = v1_list[k];
        v2 = v2_list[k];
        i = LocateVex(*G,v1);
        j = LocateVex(*G,v2);

        if(i>=0 && j>=0)
            (*G).arcs[i][j].adj = (*G).arcs[j][i].adj = 1;
            //��<v1,v2>�ĶԳƻ�<v2,v1>
    }
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



void DFS(MGraph G,int v)
{
    int w;
    Visited[v] = TRUE;
    printf("%d ",G.vexs[v]);  //��ӡ�ö���
    for(w = 0;w<G.vexnum;w++)
        if(G.arcs[v][w].adj == 1 && !Visited[w])
            DFS(G,w);  //��v����δ���ʵ��ڽӶ���w�ݹ����DFS
}

void DFSTraverse(MGraph G)
{
    printf("\nDFS������ͼ.\n");
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
    printf("�Զ���������ͼ(P157,G2)��\n");
    CreateUDG_auto(&G);
    DFSTraverse(G);
    return 0;
}
