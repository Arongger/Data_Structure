#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

#define MAX 1000
#define E 10
#define FootLoc(p) p+p->size-1
typedef int Status;
typedef int ElemType;

typedef struct WORD  //WORD:�ڴ�������
{
    union{
        struct WORD *llink;  //ͷ����ָ��ǰ�����
        struct WORD *uplink;  //�ײ���ָ�򱾽��ͷ��
    };
    int tag;  //���־��0������ 1��ռ�ã�ͷ����β������
    int size;  //ͷ���򣬿��С
    struct WORD *rlink;  //ͷ����ָ���̽��
}WORD,head,foot,*Space;  //*Space�������ÿռ�ָ������

Space p;  //ȫ�ֱ���
/*******************************��������****************************************/
void InitSpace(WORD memory[MAX+2]);
//��ʼ��һ���ڴ��
Space AllocBountTag(Space *pav,int n);
//���в�С��n�Ŀ��п飬�������Ӧ�Ĵ洢�飬���������׵�ַ�����򷵻�NULL
//�����������ÿռ���գ���pavָ����иշ�����Ľ��ĺ�̽��
void PrintLayout(Space p,Space pav);
//��ӡ�ڴ��Ŀ��п�
/*******************************��������****************************************/
void InitSpace(WORD memory[MAX+2])
{
    Space pav;
    pav = &memory[0];
    memory[0].llink = pav;
    memory[0].tag = 0;
    memory[0].size = MAX;
    memory[0].rlink = pav;
    memory[MAX-1].uplink = pav;
    memory[MAX-1].tag = 0;
    p = pav;
}

Space AllocBountTag(Space *pav,int n)
{
    Space p,f;
    //���Ҳ�С��n�Ŀ��п�
    for(p = *pav; p && p->size < n && p->rlink != *pav; p = p->rlink);
    if(!p || p->size <n){  //�Ҳ��������ؿ�ָ��
        printf("û�п��ÿ��п�\n");
        return NULL;
    }
    //pָ���ҵ��Ŀ��п�
    f = FootLoc(p);  //fָ��ײ�
    *pav = p->rlink;   //pavָ��*p���ĺ�̽��
    if(p->size-n <= E){  //������䣬������<=e��ʣ����
        if(*pav == p)  //�����ÿռ���Ϊ�ձ�
            *pav = NULL;
        else{  //�ڱ���ɾ������Ľ��
           (*pav)->llink = p->llink;
            p->llink->rlink = *pav;
        }//else
        p->tag = f->tag = 1;  //�޸ķ������ͷ���͵ײ���־
    }//if
    else{  //����ÿ�ĺ�n����
        f->tag = 1;  //�޸ķ����ĵײ���־
        p->size -= n;  //��ʣ���Ĵ�С
        f = FootLoc(p);   //ָ��ʣ���ײ�
        f->tag = 0;  //����ʣ���ײ�
        f->uplink = p;
        p = f+1;  //ָ������ͷ��
        p->tag = 1;  //���÷����ͷ��
        p->size = n;
    }//else
    return p;
}

void PrintLayout(Space p,Space pav)
{
    Space r;
    r = pav;
    printf("���п���ֹ��Χ : |");
    printf("%4d <--> %4d | \n",r-p+1,r+r->size-p);
    while(r->rlink != pav){
        r = r->rlink;
        printf("%4d <--> %4d | \n",r-p+1,r+r->size-p);
    }
}

/*******************************����������**************************************/

int main()
{
    Space pav,p1,p2;
    WORD memory[MAX];
    InitSpace(memory);
    pav = p;
    printf("\n��ʼ��һ���ڴ��pav:\n");
    PrintLayout(p,pav);

    p1 = AllocBountTag(&pav,100);
    printf("\n�����СΪ100���ڴ��p1:\n");
    PrintLayout(p,pav);

    p2 = AllocBountTag(&pav,300);
    printf("\n�����СΪ300���ڴ��p2:\n");
    PrintLayout(p,pav);


    return 0;
}



