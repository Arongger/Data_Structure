#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAX_VERTEX_NUM 20  //��󶥵����
#define  INFINITY 65535   //���ֵ��

typedef int Status;
typedef enum {DG,DN,UDG,UDN} GraphKind;   //{����ͼ��������������ͼ��������}

typedef struct
{
    int vexs[MAX_VERTEX_NUM];  //��������
    int arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];  //�ڽӾ���
    int vexnum,arcnum;  //ͼ�ĵ�ǰ�������ͻ���
    GraphKind kind;  //ͼ�������־
}MGraph;

typedef int PathMatrix;
typedef int ShortPathTable;

/*******************************��������****************************************/
Status CreateDN(MGraph *G);
//����������
int LocateVex(MGraph G,int v);
//ȷ��v��G�е�λ��
Status ShortestPath_DIJ(MGraph G,int v0,PathMatrix *p,ShortPathTable *D);
//��Dijkstra�㷨��������G��v0���㵽���ඥ��v�����·��P[v]�����Ȩ����D[v]

/*******************************��������****************************************/
Status CreateDN(MGraph *G)
{
    printf("\n����������\n");
    int i,j,k; //i,j,k���ڼ���
    int w;  //Ȩ��
    int v1,v2;  //��ͷ����β

 /*   printf("�����붥�������");
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
        for(j = 0;j<(*G).vexnum;j++)
            (*G).arcs[i][j] = INFINITY;  //������

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
            (*G).arcs[i][j] = w;  //��<v1,v2>�ĶԳƻ�<v2,v1>
    */
    (*G).vexnum = 6;
    (*G).arcnum = 8;
    for(i = 0;i<(*G).vexnum;i++)
        (*G).vexs[i] = i;
    for(i = 0;i<(*G).vexnum;i++)
        for(j = 0;j<(*G).vexnum;j++)
            (*G).arcs[i][j] = INFINITY;

    (*G).arcs[0][2] = 10;
    (*G).arcs[1][2] = 5;
    (*G).arcs[2][3] = 50;
    (*G).arcs[4][3] = 20;
    (*G).arcs[0][4] = 30;
    (*G).arcs[0][5] = 100;
    (*G).arcs[3][5] = 10;
    (*G).arcs[4][5] = 60;

    return OK;
}

int LocateVex(MGraph G,int v)
{
    int ct;
    for(ct = 0;ct < G.vexnum;ct++)
        if(G.vexs[ct] == v)
            return ct;
    return -1;
}

Status ShortestPath_DIJ(MGraph G,int v0,PathMatrix *p,ShortPathTable *D)
{
    int v,w,i,min,j;
    int final[MAX_VERTEX_NUM];
    for(v = 0;v<G.vexnum;v++){
        final[v] = 0;
        D[v] = G.arcs[v0][v];
        p[v] = -1;
    }//for
    D[v0] = 0;
    final[v0] = 1;  //��ʼ����v0��������S��
    //��ʼ��ѭ����ÿ�����v0��ĳ��v��������·��������v��S��
    for(i = 0;i<G.vexnum;++i){   //����G.vexnum-1������
        min =INFINITY;     //��ǰ��֪��v0������������
        for(w = 0;w < G.vexnum;++w)
            if(!final[w])
                if(D[w]<min){   //w������V-S��
                    v = w;
                    min = D[w];   //w������v0�������
                }//if
        final[v] = 1;  //��v0���������v����S��
        for(w = 0;w<G.vexnum;w++)   //���µ�ǰ���·��������
            if(!final[w] && (min+G.arcs[v][w]<D[w])){  //�޸�D[w]��P[w],w����V-S
                D[w] = min+G.arcs[v][w];
                for(j = 1;j<G.vexnum;j++)
                    p[w] = v;
            }//if
    }//for
}
/*******************************����������**************************************/

int main()
{
    MGraph G;
    ShortPathTable D[MAX_VERTEX_NUM];
    PathMatrix P[MAX_VERTEX_NUM];
    int v0 = 0,i,j;
    CreateDN(&G);
    ShortestPath_DIJ(G,v0,P,D);
    printf("\n���·���������£�\n");
    for(i = 0;i<G.vexnum;i++){
        printf("v%d - v%d : ",v0,i);
        j = i;
        printf("v%d",i);
        while(P[j] != -1){
            printf("<-");
            printf("v%d",P[j]);
            j = P[j];
        }
        printf("<-v0");
        printf("\n");
    }
    printf("\nԴ�㵽����������·������Ϊ��\n");
    for(i = 0;i<G.vexnum;i++){
        if(D[i] != INFINITY)
            printf("v%d-v%d : %d \n",G.vexs[0],G.vexs[i],D[i]);
        else
            printf("v%d-v%d : �� \n",G.vexs[0],G.vexs[i]);
    }
    return 0;
}
