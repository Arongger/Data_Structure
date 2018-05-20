#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

#define MAXSIZE 40
#define MAXSTRLEN 6 //����ַ���

typedef int Status;
typedef int ElemType;
typedef char SString[MAXSIZE+1];
typedef char AtomType;
typedef enum{ATOM,LIST}ElemTag;  //ATOM==0:ԭ�ӣ�LIST==1���ӱ�

typedef struct GLNode
{
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
int GListDepth(GList L);
//������L�����
Status CopyGList(GList *T,GList L);
//�ɹ����L���Ƶõ������T
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
       //     SubString(sub,S,2,StrLength(S)-2);  //���������
            StrCopy(sub,S);
      /*      int i = 0;
            for(i = 0;i<=sub[0];i++)
                printf("sub[%d] = %c \n ",i,sub[i]);*/


            do{  //�ظ�����n���ӱ�
                sever(&hsub,&sub);   //��sub�з������ͷ��husb
            /*    int i = 0;
                for(i = 0;i<=hsub[0];i++)
                printf("hsub[%d] = %c \n ",i,hsub[i]);*/
                CreateCList(&(p->ptr.hp),hsub);
              //  q = p;
                if(StrCompare(sub,emp)){  //��β����
                    q = p;
                    p = (GList)malloc(sizeof(GLNode));
                    p->tag = LIST;
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
   /* do{
        ++i;
        SubString(ch,str,i,1);
        if(ch[1] == '(')
            ++k;
        else if(ch[1] == ')')
            --k;
    }while(i<n && (ch[1]!=',' || k != 0));*/
    while(i<n && (ch[i]!=',' || k != 0)){
        if(ch[i] == '(')
            k++;
        else if(ch[i] == ')')
            k--;
        i++;
    }
  //  printf("i = %d\n",i);

    if(i<n){
        SubString(*hstr,ch,1,i-1);
      //  SubString(hstr,str,1,i-1);
      //  SubString(str,str,i+1,n-i);
    }
    else{
        StrCopy(*hstr,ch);
        //StrCopy(hstr,str);
        //ClearString(str);
    }
 //   printf("len = %d\n",*hstr[0]);
/*    int ct = 0;
    for(ct = 0;ct<=*hstr[0];ct++)
        printf("hsub[%d] = %c \n ",ct,hstr[ct]);*/
    StrDelete(*str,2,i);
}

int GListDepth(GList L)
{
    int max,dep;
    GList p;
    if(!L)
        return ERROR;
    if(L->tag == ATOM)
        return 0;
    for(max = 0,p = L; p ;p = p->ptr.tp){
        dep = GListDepth(p->ptr.hp);
        if(dep > max)
            max = dep;
    }
    return max+1;
}

Status CopyGList(GList *T,GList L)
{
    if(!L)
        *T = NULL;
    else{
        *T = (GList)malloc(sizeof(GLNode));
        if(!(*T))
            exit(OVERFLOW);
        (*T)->tag = L->tag;
        if(L->tag == ATOM)
            (*T)->atom = L->atom;  //���Ƶ�ԭ��
        else{
            CopyGList(&(*T)->ptr.hp,L->ptr.hp);
            CopyGList(&(*T)->ptr.tp,L->ptr.tp);
        }//else
    }//else
    return OK;
}
/*******************************����������**************************************/

int main()
{
    SString S;
    GList L,T;
    int depth;

    char *chars = "((),(e),(a,(b,c,d)))";
    StrAssign(&S,chars);
    CreateCList(&L,S);
    depth = GListDepth(L);
    printf("�����LΪ((),(e),(a,(b,c,d)))\n");
    printf("L�����Ϊ%d\n",depth);

    CopyGList(&T,L);
    printf("\n���ƹ����L��T\n");
    printf("T�����Ϊ%d\n",GListDepth(T));
    return 0;
}


