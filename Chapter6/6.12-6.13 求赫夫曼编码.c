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
typedef struct
{
    unsigned int weight;  //Ȩ��
    unsigned int parent,lchild,rchild;
}HTNode,*HuffmanTree;  //��̬��������洢�շ�����
typedef char **HuffmanCode;  //��̬��������洢�շ��������

/*******************************��������****************************************/

void HuffmanCoding_1(HuffmanTree *HT,HuffmanCode *HC,int *w,int n);
//w���n���ַ���Ȩ��ֵ����>0��������շ�����HT�������n���ַ��ĺշ�������HC
void Select (HuffmanTree *HT,int i,int *S1,int *S2);
//��HT[1...n]��ѡ��parentΪ0��weight��С��������㣬����ŷֱ�ΪS1��S2
void HuffmanCoding_2(HuffmanTree *HT,HuffmanCode *HC,int *w,int n);
//w���n���ַ���Ȩ��ֵ����>0��������շ�����HT�������n���ַ��ĺշ�������HC
void PrintfCode(HuffmanCode HC,int n);
//��ӡ�շ�������

/*******************************��������****************************************/

int min(HuffmanTree *HT,int i)
{
    int k,j,flag;
    k = 100;  //Ԥ��һ�����ֵ
    for(j = 1;j<= i;j++){
        if((*HT)[j].weight < k && (*HT)[j].parent == 0){
            k = (*HT)[j].weight;
            flag = j;
        }
    }//for
    (*HT)[flag].parent = 1;
    return flag;
}

void Select(HuffmanTree *HT,int i,int *S1,int *S2)
{
    int j;
    *S1 = min(HT,i);
    *S2 = min(HT,i);

    if(*S1 > *S2){
        j = *S1;
        *S1 = *S2;
        *S2 = j;
    }
}

void HuffmanCoding_1(HuffmanTree *HT,HuffmanCode *HC,int *w,int n)
{
    int m,i,s1,s2,start,c,f;
    char *cd;
    if(n<=1)
        return;
    m = 2*n-1;
    *HT = (HuffmanTree)malloc((m+1) * sizeof(HTNode));  //0�ŵ�Ԫδ��

    for(i = 1; i<=n; i++){
        (*HT)[i].weight = w[i-1];
        (*HT)[i].parent = 0;
        (*HT)[i].rchild = 0;
        (*HT)[i].lchild = 0;
    }

    for(; i<=m; i++){
        (*HT)[i].weight = 0;
        (*HT)[i].parent = 0;
        (*HT)[i].rchild = 0;
        (*HT)[i].lchild = 0;
    }
    printf("HT�ĳ�̬��\n");
    printf("   weight  parent  lchild   rchild\n");
    for(i = 1;i<=m;i++){
        printf("%2d   %2d     %2d      %2d       %2d  \n",i,(*HT)[i].weight,(*HT)[i].parent,
               (*HT)[i].lchild,(*HT)[i].rchild);
    }
    for(i = n+1;i<=m;i++){   //���շ�����
        Select(HT,i-1,&s1,&s2);
        (*HT)[s1].parent = i;
        (*HT)[s2].parent = i;
        (*HT)[i].lchild = s1;
        (*HT)[i].rchild = s2;
        (*HT)[i].weight = (*HT)[s1].weight+(*HT)[s2].weight;
    }


    //---------��Ҷ�ӵ���������ÿ���ַ��ĺշ�������---------
    *HC = (HuffmanCode)malloc((n+1)*sizeof(char*));  //����n���ַ������ͷָ������
    cd = (char *)malloc(n*sizeof(char));   //���������Ĺ����ռ�
    cd[n-1] = '\0';  //���������
    for(i = 1;i<=n;++i){   //����ַ���շ�������
        start = n-1;  //���������λ��
        for(c = i,f = (*HT)[i].parent; f!=0;c = f,f = (*HT)[f].parent){  //��Ҷ�ӵ������������
            if((*HT)[f].lchild == c)
                cd[--start] = '0';
            else
                cd[--start] = '1';
        }
        (*HC)[i] = (char *)malloc((n-start) * sizeof(char));  //Ϊ��i���ַ��������ռ�
        strcpy((*HC)[i],&cd[start]);
    }
    free(cd);  //�ͷŹ����ռ�
    printf("\n\nHT����̬��\n");
    printf("   weight  parent  lchild   rchild\n");
    for(i = 1;i<=m;i++){
        printf("%2d   %2d     %2d      %2d       %2d  \n",i,(*HT)[i].weight,(*HT)[i].parent,
               (*HT)[i].lchild,(*HT)[i].rchild);
    }
}

void HuffmanCoding_2(HuffmanTree *HT,HuffmanCode *HC,int *w,int n)
{
    int m,i,s1,s2,start,c,f;
    int p,cdlen;
    char *cd;
    if(n<=1)
        return;
    m = 2*n-1;
    *HT = (HuffmanTree)malloc((m+1) * sizeof(HTNode));  //0�ŵ�Ԫδ��

    for(i = 1; i<=n; i++){
        (*HT)[i].weight = w[i-1];
        (*HT)[i].parent = 0;
        (*HT)[i].rchild = 0;
        (*HT)[i].lchild = 0;
    }

    for(; i<=m; i++){
        (*HT)[i].weight = 0;
        (*HT)[i].parent = 0;
        (*HT)[i].rchild = 0;
        (*HT)[i].lchild = 0;
    }
    for(i = n+1;i<=m;i++){   //���շ�����
        Select(HT,i-1,&s1,&s2);
        (*HT)[s1].parent = i;
        (*HT)[s2].parent = i;
        (*HT)[i].lchild = s1;
        (*HT)[i].rchild = s2;
        (*HT)[i].weight = (*HT)[s1].weight+(*HT)[s2].weight;
    }

    //------------��ջ�ǵݹ�����շ���������շ�������------------
    *HC = (HuffmanCode)malloc((n+1) * sizeof(char *));
    cd = (char*)malloc(n*sizeof(char));

    p = m;
    cdlen = 0;

    for(i = 1;i <= m;++i)
        (*HT)[i].weight = 0;  //�����շ�����ʱ�������״̬��־
    while(p){
        if((*HT)[p].weight == 0){   //����
            (*HT)[p].weight = 1;

            if((*HT)[p].lchild != 0){
                p = (*HT)[p].lchild;
                cd[cdlen++] = '0';
            }//if

            else if((*HT)[p].rchild == 0){  //�Ǽ�Ҷ�ӽ����ַ��ı���
                (*HC)[p] = (char*)malloc((cdlen+1)*sizeof(char));
                cd[cdlen] = '\0';
                strcpy((*HC)[p],cd);
            }//else if

        }//if
        else if((*HT)[p].weight == 1){  //����

            (*HT)[p].weight = 2;
            if((*HT)[p].rchild != 0){
                p = (*HT)[p].rchild;
                cd[cdlen++] = '1';
            }//if
        }//else if

        else{   //HT[p].weight == 2  �˻�
            (*HT)[p].weight = 0;
            p = (*HT)[p].parent;
            --cdlen;   //�˵�����㣬�����ǶǼ�һ
        }//else
    }//while
    free(cd);
}

void PrintfCode(HuffmanCode HC,int n)
{
    int i;
    printf("����Ϊ:\n");
    for(i=1;i<=n;i++)
        printf(" %s /",HC[i]);
}

/*******************************����������**************************************/
int main()
{
    int i;
    HuffmanTree HTree1,HTree2;
    HuffmanCode HCode1,HCode2;
    int w1[8] = {5,29,7,8,14,23,3,11};   //��Ӧ����P148 ��6-2
    printf("\nʹ�õ�һ�ַ�������Ҷ�ӵ���������ÿ���ַ��ĺշ�������\n");
    HuffmanCoding_1(&HTree1,&HCode1,w1,8);
    PrintfCode(HCode1,8);
    printf("\n\n");

    int w2[4] = {7,5,2,4};  //��Ӧ���� P146 ͼ6.25 ��ABCD
    printf("\nʹ�õڶ��ַ�������ջ�ǵݹ�����շ���������շ�������\n");
    HuffmanCoding_2(&HTree2,&HCode2,w2,4);
    PrintfCode(HCode2,4);
    printf("\n\n");
	return 0;
}
