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

typedef int Status;
typedef int VertexType;
typedef char InfoType;

typedef struct ArcBox
{
    int tailvex,headvex;  //�û���β��ͷ�����λ��
    struct ArcBox *hlink,*tlink;   //�ֱ�Ϊ��ͷ��ͬ�ͻ�β��ͬ�Ļ�������
    InfoType *info;  //�û������Ϣ��ָ��
}ArcBox;  //�����
typedef struct VexNode
{
    VertexType data;
    ArcBox *firstin,*firstout;  //�ֱ�ָ��ö����һ���뻡�ͳ���
}VexNode;  //������
typedef struct
{
    VexNode xlist[MAX_VERTEX_NUM];  //��ͷ���� //˳��洢��ͷ���
    int vexnum,arcnum;  //����ͼ�ĵ�ǰ�������ͻ���
}OLGraph;  //Othogoal List ʮ������



/*******************************��������****************************************/
Status CreateDG(OLGraph *G);
//����ʮ������洢��ʾ����������ͼG


/*******************************��������****************************************/
Status CreateDG(OLGraph *G)
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

    for(i = 0;i<(*G).vexnum;i++){  //�����ͷ����
        printf("������G.xlist[%d].data = ",i);
        scanf("%d",&(*G).xlist[i].data);  //���붥��ֵ
        (*G).xlist[i].firstin = NULL;
        (*G).xlist[i].firstout = NULL;  //��ʼ��ָ��
    }

    for(k = 0;k<(*G).arcnum;k++){  //�������������ʮ������
        printf("�����뻡ͷ(��ʼ��)��");  //����һ������ʼ����յ�
        scanf("%d",&v1);
        printf("�����뻡β(�ն˵�)��");
        scanf("%d",&v2);

        i = LocateVex(*G,v1);  //ȷ��v1��v2��G�е�λ��
        j = LocateVex(*G,v2);

        ArcBox *p;
        p = (ArcBox *)malloc(sizeof(ArcBox));  //�������㹻�ռ�
        p->tailvex = i;  //�Ի���㸳ֵ
        p->headvex = j;
        p->hlink = (*G).xlist[j].firstin;
        p->tlink = (*G).xlist[i].firstout;
        p->info = NULL;

        //������뻡�ͳ�����ͷ�Ĳ���
        (*G).xlist[j].firstin = (*G).xlist[i].firstout = p;
    }
}

int LocateVex(OLGraph G,VertexType v)
{
    int ct;
    for(ct = 0;ct < G.vexnum;ct++)
        if(G.xlist[ct].data == v)
            return ct;
    return -1;
}


/*******************************����������**************************************/

int main()
{
    printf("����P465 ͼ7.11 ������ͼ��\n");
    OLGraph G;
    CreateDG(&G);
}

typedef enum {unvisited, visited} VisitIf;
typedef struct EBox
{
    VisitIf mark;  //���ʱ��
    int ivex,jvex;  //�ñ����������������λ��
    struct EBox *ilink, *jlink;  //�ֱ�ָ�������������������һ����
    InfoType *info;
}EBox;
typedef struct VexBox
{
    VertexType data;
    EBox *firstedge;  //ָ���һ�������ö���ı�
}VexBox;
typedef struct
{
    VexBox adjmulist[MAX_VERTEX_NUM];
    int vexnum,edgenum;  //����ͼ�ĵ�ǰ�Ķ������ͱ���
}AMLGraph;

