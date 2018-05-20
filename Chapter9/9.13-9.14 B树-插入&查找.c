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

#define EQ(a,b) ((a) == (b))
#define LT(a,b) ((a) <  (b))
#define LQ(a,b) ((a) <= (b))
#define M 3
typedef int Status;
typedef int ElemType;
typedef int KeyType;
typedef struct
{
    ElemType *elem; //unit elem[0] keep NULL
    int length;   //length of table
}SSTable;
typedef struct BTNode
{
    int keynum;   //����йؼ��ָ����������Ĵ�С
    struct BTNode *parent;  //point to Parent node
    KeyType key[M+1];    //�ؼ���������0�ŵ�Ԫδ��
    struct BTNode *ptr[M+1];  //����ָ������
}BTNode,*BTree;
typedef struct
{
    BTNode *pt;  //ָ���ҵ��Ľ��
    int i;   //1...M���ڽ���еĹؼ������
    int tag;  //1:found,0:unfound
}Result;  //B-Tree �Ĳ��ҽ������
/*******************************��������****************************************/
int Search(BTree p,KeyType K);
//��p->key[1...keynum]�в��ң�����ֵiʹ�ã�p->key[i] <= K < p->key[i+1]
Result SearchBTree(BTree T,KeyType K);
//��M��B��T�ϲ��ҹؼ���K�����ؽ����pt,i,tag),�����ҳɹ���������ֵtag = 1��
//ָ��pt��ָ����е�i���ؼ��ֵ���K����������ֵtag = 0������K�Ĺؼ���Ӧ����
//��ָ��pt��ָ����е�i���͵�i+1���ؼ���֮��
Status insert(BTree q,int i,KeyType x,BTree ap);
//��x��ap�ֱ���뵽q->key[i+1]��q->ptr[i+1]
Status split(BTree q,int s,BTree *ap);
//��q->key[s+1...M],q->ptr[s...M]��q->recptr[s+1...M]�����½��*ap
Status NewRoot(BTree *T,BTree q,KeyType x,BTree ap);
//���ɺ���Ϣ(T,x,ap)���µĸ����*T��ԭT��apΪ����ָ��
Status InsertBTree(BTree *T,KeyType K,BTree q,int i);
//��M��B��T�Ͻ��*q��key[i]��key[i+1]֮�����ؼ���K��
//���������������˫�������б�Ҫ�Ľ����ѵ�����ʹT����M��B��
Status CreateTalbe(SSTable *L);
Status InitTable(SSTable *L);

/*******************************��������****************************************/
int Search(BTree p,KeyType K)
{
    int i,j;
    for(i = 0,j = 1;j <= p->keynum;j++){
        if(p->key[j] <= K)
            i = j;
        else
            break;
    }
    return i;
}

Result SearchBTree(BTree T,KeyType K)
{
    BTree p,q;
    int found,i;

    p = T;  //��ʼ����pָ������㣬qָ��p��˫��
    q = NULL;
    found = FALSE;
    i = 0;

    while(p && !found){
        i = Search(p,K);
        if(i > 0 && p->key[i] == K)
            found = TRUE;  //�ҵ��ؼ���
        else{
            q = p;
            p = p->ptr[i];
        }
    }//while
    if(found){
        Result R1;
        R1.pt = p;
        R1.i = i;
        R1.tag = 1;
        return R1;
    }
    else{
        Result R0;
        R0.pt = q;
        R0.i = i;
        R0.tag = 0;
        return R0;
    }
}

Status Insert(BTree q,int i,KeyType x,BTree ap)
{
    int j;

    for(j = q->keynum;j > i;j--){   //����Ԫ�غ���
        q->key[j+1] = q->key[j];
        q->ptr[j+1] = q->ptr[j];
    }

    q->key[i+1] = x;
    q->ptr[i+1] = ap;
    q->keynum++;
    return OK;
}

Status split(BTree q,int s,BTree *ap)
{
    int i;

    (*ap) = (BTree)malloc(sizeof(BTNode));
    (*ap)->ptr[0] = q->ptr[s];

    for(i = s+1; i <= M;i++){
        (*ap)->key[i-s] = q->key[i];
        (*ap)->ptr[i-s] = q->ptr[i];
    }

    (*ap)->keynum = M - s;
    q->keynum = s-1;
    (*ap)->parent = q->parent;

    for(i = 0;i<=(*ap)->keynum;i++){
        if((*ap)->ptr[i])
            (*ap)->ptr[i]->parent = *ap;
    }
}

Status NewRoot(BTree *T,BTree q,KeyType x,BTree ap)
{
    BTree p;
    p = (BTree)malloc(sizeof(BTNode));
    p->keynum = 1;
    p->parent = NULL;
    p->key[1] = x;
    p->ptr[0] = *T;
    p->ptr[1] = ap;

    if(p->ptr[0])
        p->ptr[0]->parent = p;
    if(p->ptr[1])
        p->ptr[1]->parent = p;
    *T = p;
}

Status InsertBTree(BTree *T,KeyType K,BTree q,int i)
{
    KeyType x;
    BTree ap;
    int finished,s;

    x = K;
    ap = NULL;
    finished = FALSE;

    while(q && !finished){
        Insert(q,i,x,ap);
        if(q->keynum < M)
            finished = TRUE;  //Insert complete
        else{  //split the node *q
            s =ceil((double)M/2);
            split(q,s,&ap);
            x = q->key[s];
            q = q->parent;
            if(q)
                i = Search(q,x);
        }//else
    }//while
    if(!finished)
        NewRoot(T,q,x,ap);
    return OK;
}

Status CreateTalbe(SSTable *L)
{
  /*  int i;
    printf("������˳���ĳ���:");
    scanf("%d",&L->length);
    for(i = 1;i<=L->length;i++){
        printf("������� %d ��Ԫ�ص�ֵ��",i);
        scanf("%d",&L->elem[i].key);
    }*/
    L->length = 15;
    L->elem[1] = 24;
    L->elem[2] = 45;
    L->elem[3] = 50;
    L->elem[4] = 53;
    L->elem[5] = 100;
    L->elem[6] = 37;
    L->elem[7] = 12;
    L->elem[8] = 61;
    L->elem[9] = 90;
    L->elem[10] = 70;
    L->elem[11] = 3;
    L->elem[12] = 30;
    L->elem[13] = 26;
    L->elem[14] = 85;
    L->elem[15] = 7;
    return OK;
}

Status InitTable(SSTable *L)
{
    (*L).elem = (ElemType *)malloc(100 * sizeof(ElemType));
    if(!(*L).elem)
        exit(OVERFLOW);
    (*L).length = 0;
    return OK;
}

Status CreateBTree(BTree *T,SSTable L)
{
    int i;
    *T = NULL;
    Result R;

    if(L.length){
        for(i = 1;i<=L.length;i++){
            R = SearchBTree(*T,L.elem[i]);
            if(!InsertBTree(T, L.elem[i], R.pt, R.i)){
                printf("����ʧ��!\n");
                break;
            }
        }
    }
    printf("�������\n");
    return OK;
}

void PrintBT_InOrder(BTree T)
{
    int j;
    if(T){
        for(j = 0;j<= T->keynum;j++){
            PrintBT_InOrder(T->ptr[j]);
            if(j < T->keynum)
                printf("%d ",T->key[j+1]);
        }
    }
}
/*******************************����������**************************************/
int main()
{
    SSTable L;
    BTree T;

    printf("\n����һ��˳������£�\n");
    InitTable(&L);
    CreateTalbe(&L);

    int i;
    for(i = 1;i<= L.length;i++)
        printf("%d ",L.elem[i]);

    printf("\n\n����һ��B��,���β���˳����Ԫ��\n");
    CreateBTree(&T,L);

    printf("\n�������B����\n");
    PrintBT_InOrder(T);

    printf("\n\nѰ���Ƿ����Ԫ�� 88 ��\n");
    Result R;
    R = SearchBTree(T,88);
    printf("����ǣ�%d \n",R.tag);

    printf("\n����Ԫ�� 88 ���뵽B���У�\n");
    InsertBTree(&T, 88, R.pt, R.i);
    printf("�������\n");

    printf("\n�ٴ��������B����\n");
    PrintBT_InOrder(T);
    printf("\n");

}



