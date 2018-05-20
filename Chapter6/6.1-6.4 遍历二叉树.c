#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

#define SIZE 100
typedef int Status;
typedef char TElemType;
typedef char SElemType;
typedef struct BiTNode
{
    TElemType data;
    struct BiTNode *lchild,*rchild;  //�����Һ���ָ��
}BiTNode,*BiTree,*Position;

typedef struct SNode
{
    BiTree data;
    struct SNode *next;
}SNode;
typedef struct
{
    SNode *base;  //��ջ����֮ǰ������֮��base��ֵΪNULL
    SNode *top;  //ջ��ָ��
}SqStack;

/*******************************��������****************************************/

Status InitStack(SqStack *S);
//��ʼ��ջ
Status Pop(SqStack *S,BiTree *e);
//ɾ��ջ��Ԫ�أ�����e����ջ��Ԫ��
Status InitBiTree(BiTree *T);
//���������
Status Push(SqStack *S,BiTree e);
//��Ԫ��eѹ��ջ
Status StackEmpty(SqStack S);
//�ж��Ƿ�ջ��
Status GetTop(SqStack *S,BiTree *e);
//ȡջ��Ԫ�أ���e����
Status InitBiTree(BiTree *T);
//����ն�����
Status BiTreeEmpty(BiTree T);
//��������TΪ�գ��򷵻�TRUE������FALSE
TElemType Root(BiTree T);
//����T�ĸ�
Status CreateBiTree(BiTree *T);
//���ȴ�������������н���ֵ��һ���ַ������ո��ַ���ʾ������
//������������ʾ�Ķ�����T
Status Visit(TElemType e);
Status PreOrderTraverse(BiTree T,Status(*Visit)(TElemType e));  //�ݹ�
//���ö�������洢�ṹ������ݹ����������T�ĵݹ��㷨
Status InOrderTraverse(BiTree T,Status(*Visit)(TElemType e));  //�ݹ�
//���ö�������洢�ṹ������ݹ����������T�ĵݹ��㷨
Status PostOrderTraverse(BiTree T,Status(*Visit)(TElemType e));  //�ݹ�
//���ö�������洢�ṹ������ݹ����������T�ĵݹ��㷨
Status InOrderTraverse_1(BiTree T); //�ǵݹ�;
//���ö�������洢�ṹ������ǵݹ����������T�ĵݹ��㷨
Status InOrderTraverse_2(BiTree T); //�ǵݹ�;
//���ö�������洢�ṹ������ǵݹ����������T�ĵݹ��㷨

/*******************************��������****************************************/

Status InitStack(SqStack *S)
{
    S->top = S->base = NULL;
    return OK;
}

Status Pop(SqStack *S,BiTree *e)
{
    if(S->top == S->base)
        return ERROR;
    SNode *p = S->top;
    S->top = S->top->next;
    *e = p->data;
    free(p);
    return OK;
}

Status Push(SqStack *S,BiTree e)
{
    SNode *p = (SNode*)malloc(sizeof(SNode));
    if(!p)
        exit(OVERFLOW);
    p->data = e;
    p->next = S->top;
    S->top = p;
    return OK;
}

Status StackEmpty(SqStack S)
{
    return S.base==S.top;
}

Status GetTop(SqStack *S,BiTree *e)
{
    if((*S).top == NULL)
        return ERROR;
    *e = (*S).top->data;
    return OK;
}

Status InitBiTree(BiTree *T)
{
    *T = NULL;
    return OK;
}

Status BiTreeEmpty(BiTree T)
{
    return T==NULL;
}

Status BiTreeDepth(BiTree T)
{
    int L,R;
    if(T){
        L = BiTreeDepth(T->lchild);
        R = BiTreeDepth(T->rchild);
        return(L > R ? L:R)+1;
    }
    return 0;
}

TElemType Root(BiTree T)
{
    return T->data;
}

Status CreateBiTree(BiTree *T)
{
    TElemType ch;
    //scanf("%c",&ch); //Ҳ��������
    ch = getchar();
    if(ch == ' ')
        *T = NULL;
    else{
        *T = (BiTree)malloc(sizeof(BiTNode));
        if(!(*T))
            exit(OVERFLOW);
        (*T)->data = ch;  //���ɸ����
        CreateBiTree(&(*T)->lchild);  //����������
        CreateBiTree(&(*T)->rchild);  //����������
    }
    return OK;
}

Status Visit(TElemType e)
{
    printf("%c\t",e);
    return OK;
}

Status PreOrderTraverse(BiTree T,Status(*Visit)(TElemType e))  //�ݹ�
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

Status InOrderTraverse(BiTree T,Status(*Visit)(TElemType e))  //�ݹ�
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

Status PostOrderTraverse(BiTree T,Status(*Visit)(TElemType e))  //�ݹ�
{
    if(T){
        if(PostOrderTraverse(T->lchild,Visit))
            if(PostOrderTraverse(T->rchild,Visit))
                if(Visit(T->data))
                    return OK;
        return ERROR;
    }
    else
        return OK;
}

Status InOrderTraverse_1(BiTree T)  //�ǵݹ�
{
    SqStack S;
    BiTNode *p;
    InitStack(&S);
    Push(&S,T);  //��ָ���ջ
    while(!StackEmpty(S)){
        while(GetTop(&S,&p) && p)
            Push(&S,p->lchild);  //�����ߵ���ͷ
        Pop(&S,&p);  //��ָ����ջ
        if(!StackEmpty(S)){  //���ʽ�㣬����һ��
            Pop(&S,&p);
            if(!Visit(p->data))
                return ERROR;
            Push(&S,p->rchild);
        }
    }
    return OK;
}

Status InOrderTraverse_2(BiTree T)  //�ǵݹ�
{
    SqStack S;
    BiTNode *p;
    InitStack(&S);
    p = T;
    while(p || !StackEmpty(S)){
       if(p){
        Push(&S,p);
        p = p->lchild;  //��ָ���ջ������������
       }
       else{  //��ָ����ջ�����ʸ���㣬����������
        Pop(&S,&p);
        if(!Visit(p->data))
            return ERROR;
        p = p->rchild;
       }
    }//while
    return OK;
}


/*******************************����������**************************************/

int main()
{
    BiTree T;
    InitBiTree(&T);

    //���Ʒֺ�ǰ���ַ�:ABC  DE G  F   ��
    printf("\n����������(����ABC^^DE^G^^F^^^,����'^'��ʾ�ո�)��\n");
    CreateBiTree(&T);

    printf("\n\nǰ�������\n");
    PreOrderTraverse(T,Visit);

    printf("\n\n���������\n");
    InOrderTraverse(T,Visit);

    printf("\n\n���������\n");
    PostOrderTraverse(T,Visit);

    printf("\n\n����ǵݹ����1��\n");
    InOrderTraverse_1(T);

    printf("\n\n����ǵݹ����2��\n");
    InOrderTraverse_2(T);

    printf("\n");
    return 0;
}
