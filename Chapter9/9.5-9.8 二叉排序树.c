#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

#define EQ(a,b) ((a) == (b))
#define LT(a,b) ((a) <  (b))
#define LQ(a,b) ((a) <= (b))

typedef int Status;
typedef int KeyType;

typedef struct
{
    KeyType key;
    int weight;
}ElemType;
typedef struct BiTNode
{
    ElemType data;
    struct BiTNode *lchild,*rchild;  //�����Һ���ָ��
}BiTNode,*BiTree,*Position;


/*******************************��������****************************************/
Status InitBiTree(BiTree *T);
BiTree SerchBST_a(BiTree T,KeyType key);
//�ڸ�ָ��T��ָ�����������еݹ����ĳ�ؼ��ֵ���key������Ԫ��
Status SerchBST_b(BiTree T,KeyType key,BiTree f,BiTree *p);
//�ڸ�ָ��T��ָ�����������еݹ����ĳ�ؼ��ֵ���key������Ԫ�أ������ҳɹ�
//��ָ��pָ�������Ԫ�ؽ�㣬������TRUE������ָ��pָ�����·���Ϸ��ʵ����һ����㲢����FALSE
//ָ��fָ��T��˫�ף����ʼ����ֵΪNULL
Status InsertBST(BiTree *T,ElemType e);
//������������T�в����ڹؼ��ֵ���e.key������Ԫ��ʱ������e������TRUE
Status PreOrderTraverse(BiTree T,Status(*Visit)(ElemType e));
Status Visit(ElemType e);
Status DeleteBST(BiTree *T, KeyType key);
//������������T�д��ڹؼ��ֵ���key������Ԫ��ʱ����ɾ��������Ԫ�ؽ��
Status Delete(BiTree *p);
//�Ӷ�����������ɾ�����p�������������������������
/*******************************��������****************************************/
Status InitBiTree(BiTree *T)
{
    *T = NULL;
    return OK;
}

BiTree SerchBST_a(BiTree T,KeyType key)
{
    if((!T) || EQ(key,T->data.key))
        return T;  //���ҽ���
    else if(LT(key,T->data.key))
        return (SerchBST_a(T->lchild,key));  //���������м�������
    else
        return(SerchBST_a(T->rchild,key));  //���������м�������
}

Status SerchBST_b(BiTree T,KeyType key,BiTree f,BiTree *p)
{
    if(!T){  //���Ҳ��ɹ�
        *p = f;
        return FALSE;
    }
    else if(EQ(key,T->data.key)){  //���ҳɹ�
        *p = T;
        return TRUE;
    }
    else if(LT(key,T->data.key))
        return (SerchBST_b(T->lchild,key,T,p));  //���������м�������
    else
        return (SerchBST_b(T->rchild,key,T,p));  //���������м�������
}

Status InsertBST(BiTree *T,ElemType e)
{
    BiTree p,s;
    if(!SerchBST_b(*T,e.key,NULL,&p)){  //���Ҳ��ɹ�
        s = (BiTree)malloc(sizeof(BiTNode));
        s->data = e;
        s->lchild = s->rchild = NULL;
        if(!p)
            *T = s;  //������*sΪ�µĸ����
        else if(LT(e.key,p->data.key))
            p->lchild = s;  //������*sΪ����
        else
            p->rchild = s;  //������*sΪ�Һ���
        return TRUE;
    }//IF
    else
        return FALSE;
}

Status PreOrderTraverse(BiTree T,Status(*Visit)(ElemType e))  //�ݹ�
{
    if(T){
        if(Visit(T->data))
            if(PreOrderTraverse(T->lchild,Visit))
                if(PreOrderTraverse(T->rchild,Visit))
                    return OK;
        return ERROR;
    }
    else
        return OK;
}

Status InOrderTraverse(BiTree T,Status(*Visit)(ElemType e))  //�ݹ�
{
    if(T){
        if(InOrderTraverse(T->lchild,Visit))
            if(Visit(T->data))
                if(InOrderTraverse(T->rchild,Visit))
                    return OK;
        return ERROR;
    }
    else
        return OK;
}

Status Visit(ElemType e)
{
    printf("%d ",e);
    return OK;
}

Status DeleteBST(BiTree *T, KeyType key)
{
    if(!T)
        return FALSE;
    if(EQ(key,(*T)->data.key))  //�ҵ�
        return Delete(T);
    else if(LT(key,(*T)->data.key))
        return DeleteBST(&(*T)->lchild,key);
    else
        return DeleteBST(&(*T)->rchild,key);
}

Status Delete(BiTree *p)
{
    BiTree q,s;
    if(!(*p)->rchild){  //�������գ������ؽ�����������
        q = *p;
        *p = (*p)->lchild;
        free(q);
    }
    else if(!(*p)->lchild){  //�������գ������ؽ�����������
        q = *p;
        *p = (*p)->rchild;
        free(q);
    }
    else{  //��������������
        q = *p;
        s = (*p)->lchild;
        while(s->rchild){  //ת��Ȼ�����ҵ���ͷ
            q = s;
            s = s->rchild;
        }
        (*p)->data = s->data;   //sָ��ɾ����ǰ��
        if(q != *p)
            q->rchild = s->lchild;  //�ؽ�*q��������
        else
            q->lchild = s->lchild;  //�ؽ�*q��������
        free(s);

    }
}
/*******************************����������**************************************/
int main()
{
    BiTree T;
    ElemType a,b,c,d,e,f,g;
    a.key = 45;
    b.key = 24;
    c.key = 53;
    d.key = 45;
    e.key = 12;
    f.key = 24;
    g.key = 90;

    printf("\n��ʼ������������,����ҵĹؼ�������Ϊ\n45,24,53,45,12,24,90\n");
    InitBiTree(&T);
    InsertBST(&T,a);
    InsertBST(&T,b);
    InsertBST(&T,c);
    InsertBST(&T,d);
    InsertBST(&T,e);
    InsertBST(&T,f);
    InsertBST(&T,g);

    printf("\nǰ��������ɵĶ���������Ϊ��\n");
    PreOrderTraverse(T,Visit);

    printf("\n����������ɵĶ���������Ϊ��\n");
    InOrderTraverse(T,Visit);

    printf("\n\nɾ��key = 24��Ԫ�أ�\n");
    DeleteBST(&T,24);
    printf("\nǰ�������ǰ�Ķ���������Ϊ��\n");
    PreOrderTraverse(T,Visit);

    printf("\n���������ǰ�Ķ���������Ϊ��\n");
    InOrderTraverse(T,Visit);

    printf("\n");
    return 0;
}



