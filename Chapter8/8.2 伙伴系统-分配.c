#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW_SELF -2

#define M 3  //�����ÿռ�������64K�ֵ�2���ݴΣ��ӱ�ĸ���ΪM+1 //����Ϊ16

typedef int Status;
typedef int ElemType;
typedef struct WORD_b
{
    struct WORD_b *llink;  //ָ��ǰ�����
    int tag;  //���־��0�����У�1��ռ��
    int kval;  //���С��ֵΪ2�ݴ�K
    struct WORD_b *rlink;  //ͷ����ָ���̽��
}WORD_b,head;  //WORD���ڴ������ͣ����ĵ�һ����Ҳ��Ϊhead
typedef struct HeadNode
{
    int nodesize;  //������Ŀ��п��С
    WORD_b *first;  //������ı�ͷָ��
}FreeList[M+1];  //��ͷ��������

WORD_b *start,*end;
/*******************************��������****************************************/
void InitSpace_b(FreeList avail);
//��ʼ��һ���ڴ��
WORD_b* AllocBuddy(FreeList avail,int n);
//avail[0...M]Ϊ�����ÿռ��nΪ��������������в�С��n�Ŀ��п飬
//�������Ӧ�Ĵ洢�飬���������׵�ַ�����򷵻�NULL
void PrintLayout_b(FreeList avail);
//��ӡ�ڴ��Ŀ��п�
/*******************************��������****************************************/
void InitSpace_b(FreeList avail)
{
    int k;
    WORD_b *r;

    for(k = 0;k<=M;k++){
        avail[k].nodesize = (int)pow(2,k);
        avail[k].first = NULL;
    }
    r = (WORD_b *)malloc((int)pow(2,M) * sizeof(WORD_b));
    r->llink = r->rlink = r;
    r->tag = 0;
    r->kval = M;
    avail[M].first = r;

    start = r;
    end = r + avail[M].nodesize-1;
}

WORD_b* AllocBuddy(FreeList avail,int n)
{
    int k,i;
    WORD_b *pa,*pre,*suc,*pi;

    //�����������Ҫ����ӱ�
    for(k = 0;k<=M && (avail[k].nodesize < n || !avail[k].first); ++k);

    if(k > M)
        return NULL; //����ʧ�ܣ�����NULL
    else{  //���з���
        pa = avail[k].first;  //ָ��ɷ����ӱ�ĵ�һ�����
        pre = pa->llink;
        suc = pa->rlink;  //�ֱ�ָ��ǰ���ͺ��

        if(pa == suc)
            avail[k].first = NULL;  //�������ӱ��ɿձ�
        else{   //���ӱ�ɾȥ*pa���
            pre->rlink = suc;
            suc->llink = pre;
            avail[k].first = suc;
        }//else

        for(i = 1; k-i >= 0 && avail[k-i].nodesize >= n; ++i){
            pi = pa+(int)pow(2,k-i);
            pi->rlink = pi;
            pi->llink = pi;
            pi->tag = 0;
            pi->kval = k-i;
            avail[k-i].first = pi;
        }//for
        pa->tag = 1;
        pa->kval = k-(--i);
    }//else
    return pa;
}

void PrintLayout_b(FreeList avail)
{
    int k;
    WORD_b *r;
    int mark;

    for(k = 0,mark = 0;k<=M;k++){
        if(avail[k].first){
            mark = 1;
            break;
        }
    }

    if(!mark)
        printf("�ڴ��ѱ�ռ����!\n");
    else{
         printf("���п���ֹ��Χ : ");
         for(k = 0;k<=M;k++){
            r = avail[k].first;
            if(r){
                printf("| %d <--> %d |",r-start+1,r+(int)pow(2,r->kval)-start);
                while(r->rlink != avail[k].first){
                    r = r->rlink;
                    printf("| %d <--> %d |\n",r-start+1,r+(int)pow(2,r->kval)-start);
                }//while
            }//if
         }//for
    }//else
    printf("\n");

}
/*******************************����������**************************************/
int main()
{
    FreeList avail;
    WORD_b *p1,*p2;

    InitSpace_b(avail);
    printf("\n��ʼ����һ���ڴ�\n");
    PrintLayout_b(avail);

    p1 = AllocBuddy(avail,1);
    printf("\n�����˴�СΪ 1 ���ڴ�p1\n");
    PrintLayout_b(avail);

    p2 = AllocBuddy(avail,2);
    printf("\n�����˴�СΪ 2 ���ڴ�p2\n");
    PrintLayout_b(avail);

    return 0;
}



