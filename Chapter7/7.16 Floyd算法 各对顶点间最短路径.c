#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAX 20  //��󶥵����
#define  INFINITY 65535   //���ֵ��

typedef int Status;
typedef enum {DG,DN,UDG,UDN} GraphKind;   //{����ͼ��������������ͼ��������}

typedef struct
{
    int vexs[MAX];  //��������
    int arcs[MAX][MAX];  //�ڽӾ���
    int vexnum,arcnum;  //ͼ�ĵ�ǰ�������ͻ���
    GraphKind kind;  //ͼ�������־
}MGraph;

typedef int PathMatrix[MAX][MAX][MAX];
typedef int DistanceMatrix[MAX][MAX];

/*******************************��������****************************************/
Status CreateDN(MGraph *G);
//����������
int LocateVex(MGraph G,int v);
//ȷ��v��G�е�λ��
void ShortestPath_FLOYD(MGraph G,PathMatrix *P,DistanceMatrix *D);
//��Floyd�㷨��������G�и��Զ���v��w֮������·��P[v][w]����
//��Ȩ����D[v][w].��P[v][w]ΪTRUE����u�Ǵ�v��w��ǰ������·���ϵĶ���
/*******************************��������****************************************/
Status CreateDN(MGraph *G)
{
    printf("\n����������\n");
    int i,j,k; //i,j,k���ڼ���
    int w;  //Ȩ��
    int v1,v2;  //��ͷ����β

  /*  printf("�����붥�������");
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
            (*G).arcs[i][j] = w;
        }*/

    (*G).vexnum = 3;
    (*G).arcnum = 5;

    for(i = 0;i<(*G).vexnum;i++)
        (*G).vexs[i] = i;

    for(i = 0;i<(*G).vexnum;i++)
        for(j = 0;j<(*G).vexnum;j++)
            (*G).arcs[i][j] = INFINITY;

    (*G).arcs[0][1] = 4;
    (*G).arcs[0][2] = 11;
    (*G).arcs[1][0] = 6;
    (*G).arcs[1][2] = 2;
    (*G).arcs[2][0] = 3;

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

void ShortestPath_FLOYD(MGraph G,PathMatrix *P,DistanceMatrix *D)
{
    int v,w,u,i;

    for(v = 0;v<G.vexnum;v++)    //������֮���ʼ��֪·��������

        for(w = 0;w<G.vexnum;w++){

            (*D)[v][w] = G.arcs[v][w];

            for(u = 0;u<G.vexnum;u++)
                (*P)[v][w][u] = 0;

            if((*D)[v][w] < INFINITY){   //��v��w��ֱ��·��
                (*P)[v][w][v] = 1;
                (*P)[v][w][w] = 1;
            }//if
        }//for
    for(u = 0;u<G.vexnum;u++)
        for(v = 0;v<G.vexnum;v++)
            for(w = 0;w<G.vexnum;w++)
                if((*D)[v][u] + (*D)[u][w] < (*D)[v][w]){   //��v����u��w��һ��·������
                    (*D)[v][w] = (*D)[v][u] + (*D)[u][w];

                    for(i = 0;i<G.vexnum;i++)
                        (*P)[v][w][i] = (*P)[v][u][i] || (*P)[u][w][i];
                }//if

}

/*******************************����������**************************************/
int main()
{
    int v,w,k;
    MGraph G;
    PathMatrix P;
    DistanceMatrix D;

    CreateDN(&G);
    ShortestPath_FLOYD(G,&P,&D);

    printf("\n����������·�����£�\n");
    for(v = 0;v<G.vexnum;v++)
        for(w = 0;w<G.vexnum;w++){
            if(v!=w){
                printf("\nv%d-v%d : Ȩ��: %2d , ",G.vexs[v],G.vexs[w],D[v][w]);
                printf("·����v%d",v);
                for(k = 0;k<G.vexnum;k++)
                //    if(k!=w )
                        printf("->v%d",P[v][w][k]);
            }
            printf("->v%d",w);
        }
}
