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
typedef int ElemType;

#define MAXSIZE 40
#define MAXSTRLEN 6 //����ַ���

typedef char SString[MAXSIZE+1];
typedef char AtomType;
typedef enum{ATOM,LIST}ElemTag;  //ATOM==0:ԭ�ӣ�LIST==1���ӱ�

typedef struct GLNode
{
    int mark;
    ElemTag tag;  //�������֣���������ԭ�ӽ��ͱ���
    union{    //ԭ�ӽ��ͱ�������ϲ���
        AtomType atom;    //atom��ԭ�ӽ���ֵ��
        struct{
            struct GLNode *hp,*tp;
        }ptr;  //ptr�Ǳ����ָ����ptr.hp��ptr.tp�ֱ�ָ���ͷ�ͱ�β
    };
}GLNode,*GList;  //�����eixing




/*******************************��������****************************************/
Status StrAssign(SString *T,char *chars);
int StrCompare(SString S,SString T);
int StrLength(SString S);
Status SubString(SString Sub, SString T,int pos,int len);
int StrEmpty(SString S);
Status StrCopy(SString T,SString S);
Status ClearString(SString S);
Status StrDelete(SString S,int pos,int len);
Status CreateCList(GList *L,SString S);
//�ɹ�������д��ʽ��S���������L
Status sever(SString *hstr,SString *str);
//���ǿմ�str�ָ�������֣�hstrΪ��һ��','֮ǰ���Ӵ���strΪ֮����Ӵ�
void MarkList(GList GL);
//�����ǿչ����GL��GL != NULL �� GL->mark == 0�����Ա�������δ�ӱ�־�Ľ��ӱ�־
/*******************************��������****************************************/
Status StrAssign(SString *T,char *chars)
{
    int i,ct,len;

    len = strlen(chars);
    (*T)[0] = len;
    for(i = 1;i<=len;i++)
        (*T)[i] = chars[i-1];
    return OK;
}

int StrCompare(SString S,SString T)
{

    int i = 1;

    while(i<=S[0] && i<= T[0]){
        if(S[i] == T[i])
            i++;
        else
            return S[i]- T[i];
    }
    return S[0] - T[0];
}

int StrLength(SString S)
{
    return S[0];
}

Status SubString(SString Sub, SString T,int pos,int len)
{
    if(pos<1 || pos>T[0] || len<0 || len>T[0]-pos+1)
        return ERROR;
    int i ;
    for(i = 1;i<=len;i++)
        Sub[i] = T[pos+i-1];
    Sub[0] = len;
    return OK;
}

int StrEmpty(SString S)
{
    return S[0] == 0 ? TRUE : FALSE;
}

Status StrCopy(SString T,SString S)
{
    int i;
    for(i = 0;i<=S[0];i++)
        T[i] = S[i];
    return OK;
}

Status ClearString(SString S)
{
    S[0] = 0;
}

Status StrDelete(SString S,int pos,int len)
{
    int i;
    if(pos <1 || pos+len-1 > S[0] || len<0)
        return ERROR;
    for(i = pos+len;i<=S[0] ;i++)
        S[i-len] = S[i];
    S[0] -= len;
    return OK;
}

Status CreateCList(GList *L,SString S)
{
    SString sub,hsub,emp;
    GList p,q;

    StrAssign(&emp,"()");

    if( ! StrCompare(S,emp))
        *L = NULL; //�����ձ�

    else{
        *L = (GList)malloc(sizeof(GLNode));

        if(StrLength(S) == 1){
            (*L)->tag = ATOM;
            (*L)->atom = S[1];  //������ԭ�ӹ����
        }
        else{
            (*L)->tag = LIST;
            p = *L;
            StrCopy(sub,S);
            do{  //�ظ�����n���ӱ�
                sever(&hsub,&sub);   //��sub�з������ͷ��husb
                CreateCList(&(p->ptr.hp),hsub);
                if(StrCompare(sub,emp)){  //��β����
                    q = p;
                    p = (GList)malloc(sizeof(GLNode));
                    p->tag = LIST;
                    p->mark = 0;
                    q->ptr.tp = p;
                }//if
            }while(StrCompare(sub,emp));
            p->ptr.tp = NULL;
        }//else
    }//else
    return OK;
}

Status sever(SString *hstr,SString *str)
{
    int n,i,k;
    SString ch;
    i = 1;
    k = 0; //k����δ��Ե������Ÿ���

    SubString(ch,*str,2,StrLength(*str)-2);
    n = StrLength(ch);

    while(i<n && (ch[i]!=',' || k != 0)){
        if(ch[i] == '(')
            k++;
        else if(ch[i] == ')')
            k--;
        i++;
    }

    if(i<n)
        SubString(*hstr,ch,1,i-1);
    else
        StrCopy(*hstr,ch);

    StrDelete(*str,2,i);
}

void MarkList(GList GL)
{
    GList t,p,q;
    Status finished;
    t = NULL;  //tָʾp��ĸ��
    p = GL;
    finished = FALSE;
    while(!finished){
        while(p->mark == 0){
            p->mark = 1;
            q = p->ptr.hp;  //qָ��*p�ı�ͷ
            if(q && q->mark == 0){
                if(q->tag == 0)  //ATOM����ͷΪԭ�ӽ��
                    q->mark = 1;
                else{      //���������ӱ�
                    p->ptr.hp = t;
                    p->tag = 0;
                    t = p;
                    p = q;
                }//else
            }//if
        }//whie p->mark  //��ɶԱ�ͷ�ı�־
        q = p->ptr.hp;  //qָ��*p�ı�β
        if(q && q->mark == 0){   //����������β
            p->ptr.tp = t;
            t = p;
            p = q;
        }//if
        else{
            while(t && t->tag == 1){  //LIST�����㣬�ӱ�β����
                q = t;
                t = q->ptr.tp;
                q->ptr.tp = p;
                p = q;
            }//while
            if(!t)
                finished = TRUE;  //����
            else{   //�ӱ�ͷ����
                q = t;
                t = q->ptr.hp;
                q->ptr.hp = p;
                p = q;
                p->tag = 1;
            }//else  //����������β
        }//else
    }//while

}
/*******************************����������**************************************/
int main()
{
    SString S;
    GList L;
    char *chars = "((),(e),(a,(b,c,d)))";
    StrAssign(&S,chars);
    CreateCList(&L,S);
    MarkList(L);
    return 0;
}



