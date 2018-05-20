#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

#define MAX_TREE_SIZE 100
typedef int Status;
typedef char TElemType;

typedef struct PTNode  //���ṹ
{
    TElemType data;
    int parent;   //˫��λ����
}PTNode;
typedef struct  //���ṹ
{
    PTNode nodes[MAX_TREE_SIZE];
    int r,n;  //����λ�úͽ����
}PTree;

typedef PTree MFSet;

/*******************************��������****************************************/
Status find_mfset(MFSet S,int i);
//�Ҽ���S��i�����Ӽ��ĸ�
Status merge_mfset(MFSet *S, int i,int j);
//S.nodes[i]��S.nodes[j]�ֱ�ΪS�Ļ����ཻ�������Ӽ�Si��Sj�ĸ����
//���󽻼�Si �� Sj
Status mix_mfset(MFSet *S,int i,int j);
//S.nodes[i]��S.nodes[j]�ֱ�ΪS�Ļ����ཻ�������Ӽ�Si��Sj�ĸ����
//���󽻼�Si �� Sj
int fix_mfset(MFSet *S,int i);
//ȷ��j�����Ӽ���������i����·�������н�㶼��̸��ĺ��ӽ��
Status CreateMFSet(MFSet *S);
//������������P135 ͼ6.13 ������
/*******************************��������****************************************/

Status find_mfset(MFSet S,int i)
{
    if(i<1 || i>S.n)
        return -1;  //i������S����һ�Ӽ�
    int ct;
    for(ct = i;S.nodes[ct].parent > 0;ct = S.nodes[ct].parent);
    return ct;
}

Status merge_mfset(MFSet *S, int i,int j)
{
    if(i<1 || i>(*S).n || j<1 || j>(*S).n)
        return ERROR;
    (*S).nodes[i].parent = j;
    return OK;
}

Status mix_mfset(MFSet *S,int i,int j)
{
    if(i<1 || i>(*S).n || j<1 || j>(*S).n)
        return ERROR;
    if((*S).nodes[i].parent > (*S).nodes[j].parent){
        (*S).nodes[j].parent += (*S).nodes[i].parent;
        (*S).nodes[i].parent = j;
    }
    else{
        (*S).nodes[i].parent += (*S).nodes[j].parent;
        (*S).nodes[j].parent += i;
    }
    return OK;
}

int fix_mfset(MFSet *S,int i)
{
    int j,k,t;
    if(i<1 || i>(*S).n)
        return -1;
    for(j = i;(*S).nodes[j].parent>0;j = (*S).nodes[j].parent);

    for(k = i;k != j;k = t){
        t = (*S).nodes[k].parent;
        (*S).nodes[k].parent = j;
    }
    return j;
}

Status CreateMFSet(MFSet *S)
{
    printf("������������P135 ͼ6.13 ������\n");
    (*S).r = 0;
    (*S).n = 0;  //��ʼ��Ϊ�㣬����������
    int ct;
    for(ct = 0;ct < 10;ct++){
        printf("\n���������±�Ϊ %d �Ľ���ŵ��ַ���\n",ct);
        scanf("%s",&(*S).nodes[ct].data);

        printf("\n������ý���˫��λ����\n");
        scanf("%d",&(*S).nodes[ct].parent);
        (*S).n++;
    }
    return OK;
}

Status CreateMFSet_auto(MFSet *S)
{
    char ch1;
    char ch1_list[10] = {'R','A','B','C','D','E','F','G','H','K'};
    int pos;
    int pos_list[10] = {-1,0,0,0,1,1,3,6,6,6};

    printf("�Զ�����������P135 ͼ6.13 ������\n");
    (*S).r = 0;
    (*S).n = 0;  //��ʼ��Ϊ�㣬����������
    int ct;
    for(ct = 0;ct < 10;ct++){
        ch1 = ch1_list[ct];
        (*S).nodes[ct].data = ch1;

        pos = pos_list[ct];
        (*S).nodes[ct].parent = pos;
        (*S).n++;
    }
    return OK;
}

/*******************************����������**************************************/
int main()
{
    MFSet S;
    CreateMFSet_auto(&S);
    int j = find_mfset(S,4);
    printf("�ڼ���S��4�����Ӽ��ĸ�Ϊ��%d\n",j);
    return 0;
}
