#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

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
Status CreateGraph (MGraph *G);
//�������飨�ڽӾ��󣩱�ʾ��������ͼG
Status CreateDG(MGraph *G);
 //��������ͼ
Status CreateDN(MGraph *G);
//����������
Status CreateUDG(MGraph *G);
//��������ͼ
Status CreateUDN(MGraph *G);
//����������
int LocateVex(MGraph G,VertexType v);
//ȷ��v��G�е�λ��
Status PrintfArcs(MGraph G);
//���ͼG���ڽӾ���
/*******************************��������****************************************/
Status CreateGraph (MGraph *G)
{
    printf("������ͼ�����ͣ�\n");
    printf("0:����ͼ  1:������  2:����ͼ  3:������\n");
    scanf("%d",&(*G).kind);
    switch((*G).kind)
    {
        case DG: return CreateDG(G);  //��������ͼ
        case DN: return CreateDN(G);  //����������
        case UDG: return CreateUDG(G);  //��������ͼ
        case UDN: return CreateUDN(G);  //����������
        default : return ERROR;
    }
}
Status CreateDG(MGraph *G)
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
            (*G).arcs[i][j].adj = 1;
    }
    return OK;
}
Status CreateDN(MGraph *G)
{
    printf("\n����������\n");
    int i,j,k; //i,j,k���ڼ���
    int w;  //Ȩ��
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
            (*G).arcs[i][j].adj = INFINITY;  //������
            (*G).arcs[i][j].info = NULL;
        }

    for(k = 0;k<(*G).arcnum;k++){  //�����ڽӾ���
        printf("�����뻡ͷ(��ʼ��)��");  //����һ������ʼ����յ�
        scanf("%d",&v1);
        printf("�����뻡β(�ն˵�)��");
        scanf("%d",&v2);
        printf("������Ȩ�أ�");
        scanf("%d",&w);

        i = LocateVex(*G,v1);
        j = LocateVex(*G,v2);

        if(i>=0 && j>=0)
            (*G).arcs[i][j].adj = w;  //��<v1,v2>�ĶԳƻ�<v2,v1>

        //��������û����е������Ϣ
    }
    return OK;
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
Status CreateUDN(MGraph *G)
{
    printf("\n3����������\n");
    int i,j,k; //i,j,k���ڼ���
    int w;  //Ȩ��
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
            (*G).arcs[i][j].adj = INFINITY;  //������
            (*G).arcs[i][j].info = NULL;
        }

    for(k = 0;k<(*G).arcnum;k++){  //�����ڽӾ���
        printf("�����뻡ͷ(��ʼ��)��");  //����һ������ʼ����յ�
        scanf("%d",&v1);
        printf("�����뻡β(�ն˵�)��");
        scanf("%d",&v2);
        printf("������Ȩ�أ�");
        scanf("%d",&w);

        i = LocateVex(*G,v1);
        j = LocateVex(*G,v2);

        if(i>=0 && j>=0)
            (*G).arcs[i][j].adj = (*G).arcs[j][i].adj = w;  //��<v1,v2>�ĶԳƻ�<v2,v1>

        //��������û����е������Ϣ
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
    CreateGraph(&G);
    PrintfArcs(G);
    return 0;
}

typedef struct ArcNode
{
    int adjvex;  //�û���ָ��Ķ����λ��
    struct ArcNode *nextarc;  //ָ����һ������ָ��
    InfoType *info;  //�û������Ϣ��ָ��
}ArcNode;  //����
typedef struct VNode
{
    VertexType data;   //������Ϣ
    ArcNode *firstarc;  //ָ���һ�������ö���Ļ���ָ��
}VNode, AdjList[MAX_VERTEX_NUM];  //ͷ���
typedef struct
{
    AdjList vertices;
    int vexnum,arcnum;  //ͼ�ĵ�ǰ�������ͻ���
    int kind;
}ALGraph;
