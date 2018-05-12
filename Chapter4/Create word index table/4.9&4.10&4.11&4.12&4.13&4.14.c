#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <conio.h>
#include <ctype.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OVERFLOW -2

#define MaxBookNum 1000 //����ֻ��1000���齨��������(1000)
#define MaxKeyNum 2500  //��������������(2500)
#define MaxLineLen 500  //��Ŀ������󳤶�(500)
#define MaxWordNum 10  //�ʱ���������
#define MaxWordLength 30 //���ʵ���󳤶�

typedef int Status;
typedef int ElemType; //�������������Ԫ������Ϊ����
typedef int Boolean;

typedef struct
{
    char item[MaxWordNum][MaxWordLength]; //�ַ���������
    int last;  //�ʱ�ĳ���
}WordListType;  //�ʱ�����ͣ�˳���

typedef struct
{
    char *ch;  //����Ƿǿմ����򰴴�������洢��������chΪNULL
    int length;  //������
}HString;

typedef struct LNode
{
    ElemType data;
    struct LNode *next;
}LNode,*Link,*Position;

typedef struct
{
    Link head,tail;
    int len;
}LinkList;

typedef struct
{
    HString key;   //�ؼ���
    LinkList bnolist;  //����������������
}IdxTermType;  //����������

typedef struct
{
    IdxTermType item[MaxKeyNum+1];
    int last;
}IdxListType;   //����������

//----------------��Ҫ����--------------
char buf[MaxLineLen];  //��Ŀ��������
WordListType wdlist;  //�ؼ��ִʱ�
IdxListType idxlist;  //������
char oftenwords[6][10] = {"an","a","of","and","to","the"};

/*******************************��������****************************************/

//--------------��������---------

void InitIdxList (IdxListType *idxlist);
//��ʼ����������������idxlistΪ�ձ�����idxlist.item[0]��һ�մ�

void GetLine (FILE *f);
//���ļ�F����һ����Ŀ��Ϣ����Ŀ��������buf

void ExtractKeyWord (int *Num);
//Status ExtractKeyWord(char* Buffer,WordListType *w,int *Num);
//��buf����ȡ�����ؼ��ʵ��ʱ�wdlist����Ŵ���bno

Status InsIdxList (IdxListType *idxlist,ElemType bno);
//�����Ϊbno�������ؼ��ʰ��ʵ�˳�����������idxlist

void PutText (FILE *g,IdxListType idxlist);
//�����ɵ�������idxlist������ļ�g

//--------------Ϊʵ�����������Ͻ��в��룬Ҫ��ʵ�����в���-----------

void GetWord (int i,HString *wd);
//��wd���شʱ�wdist�е�i���ؼ���

int Locate (IdxListType *idxlist,HString wd,Boolean *b);
//��������idxlist�в�ѯ�Ƿ������wd��ȵĹؼ��ʡ������ڣ��򷵻�����������
//�е�λ�ã���bȡֵTRUE�����򷵻ز���λ�ã���bȡֵFALSE

void InsertNewKey(int j,HString wd);
//��������idxli�ĵ�i���ϲ����¹ؼ���wd������ʼ���������������Ϊ�ձ�

Status InsertBook (int i,int bno);
//��������idxlist�ĵ�i���в������Ϊbno������

//------------���Ķѷ���洢��ʾ-----------

Status StrAssign(HString *T,char *chars);
//����һ����ֵ���ڴ�����chars�Ĵ�T

int StrCompare(HString S,HString T);
//��S>T���򷵻�ֵ>0,��S=T���򷵻�ֵ = 0����S<T���򷵻�ֵ<0

Status StrCopy(HString *T, HString S);
//�ɴ�S���Ƶô�T

//----------------��ͷ������������-------------

Status InitList(LinkList *L);
//����һ���յ���������L

Status MakeNode(Link *p,ElemType e);
//������pָ��ֵe�Ľ�㣬������OK��������ʧ�ܣ��򷵻�ERROR

Status Append (LinkList *L,Link s);
//��ָ��s��ָ��һ�������������������L�����һ�����
//֮�󣬸ı�����L��βָ��ָ���µ�β���

/*******************************��������****************************************/

Status StrAssign(HString *T,char *chars)
{
    int i = strlen(chars);
    if((*T).ch)
        free((*T).ch);
    if(!i){  //��charsΪ��
        (*T).ch = NULL;
        (*T).length = 0;
    }
    else{  //chars����
        if(!((*T).ch = (char *)malloc(i * sizeof(char))))  //ΪT����chars����Ĵ洢�ռ�
            exit(OVERFLOW);
        int count;
        for(count = 0;count <= i;count++) //��chars����T��
            (*T).ch[count] = chars[count];
        (*T).length = i;
    } //else
    return OK;
}

void InitString(HString *T)
{
    (*T).length = 0;
    (*T).ch = NULL;
}

int StrCompare(HString S,HString T)
{
    int count;
    for(count = 0;count<S.length && count<T.length;count++){
        if(S.ch[count] != T.ch[count])
                return S.ch[count]-T.ch[count] ;
    }
    return S.length-T.length;
}

Status StrCopy(HString *T, HString S)
{
    int j;
    if((*T).ch)
        free((*T).ch);  //ɾ��T����ԭ��ֵ
    (*T).ch = (char*)malloc(S.length * sizeof(char));
    if(!(*T).ch)
        exit(OVERFLOW);
    for(j = 0; j <= S.length; j++)
        (*T).ch[j] = S.ch[j];
    (*T).length = S.length;
    return OK;
}

Status InitList(LinkList *L)
{
    Link p;
    p = (Link)malloc(sizeof(LNode));
    if(!p)
        exit(OVERFLOW);
    p->next = NULL;
    (*L).head = (*L).tail = p;
    (*L).len = 0;
    return OK;
}

Status MakeNode(Link *p,ElemType e)
{
    *p = (Link)malloc(sizeof(LNode));
    if(!(*p))
        exit(OVERFLOW);
    (*p)->data = e;
    (*p)->next = NULL;
    return OK;
}

Status Append (LinkList *L,Link s)
{
    int i = 1;
    (*L).tail->next = s;
    while(s->next){
        s = s->next;
        i++;
    }
    (*L).tail = s;
    (*L).len += i;
    return OK;
}

void GetWord(int i,HString *wd)
{
    char *p;
    p = *(wdlist.item +i);
    StrAssign(wd,p);  //���ɹؼ����ַ���
}

int Locate(IdxListType *idxlist,HString wd,Boolean *b)
{
    int i,m;
    for(i = (*idxlist).last-1; ( m=StrCompare((*idxlist).item[i].key,wd) ) >0; --i);

    if(m == 0){   //�ҵ�
        *b = TRUE;
        return i;
    }
    else{
        *b = FALSE;
        return i+1;
    }
}

void InsertNewKey(int j,HString wd)
{
    int count;
    InitList(&idxlist.item[idxlist.last+1].bnolist);
    for(count = idxlist.last-1; count>=j; --count){  //����������
        idxlist.item[count+1] = idxlist.item[count];
    }
    InitString(&idxlist.item[j].key);
    StrCopy(&idxlist.item[j].key,wd);  //�����µ������� //����ֵ
    InitList(&idxlist.item[j].bnolist);  //��ʼ�����������Ϊ�ձ�
    ++idxlist.last;
}

Status InsertBook (int i,int bookno)
{
    Link p;
    if(!MakeNode(&p,bookno))
        return ERROR;
    Append(&idxlist.item[i].bnolist,p);
    return OK;
}

Status InsertIdxList(IdxListType *idxlist,int bno)
{
    int i,j;
    HString wd;
    Boolean b;
    InitString(&wd);
    for(i= 0;i<wdlist.last;++i){
        GetWord(i,&wd);    //��ȡwdlist�б���ĵ���
        j = Locate(idxlist,wd,&b);   //�����Ƿ��Ѵ�����idxlist��
        if(!b)  //������
            InsertNewKey(j,wd);  //������µĹؼ���
        InsertBook(j,bno);  //�������
    }
    return OK;
}

void InitIdxList (IdxListType *idxlist)
{
    int i;
    (*idxlist).last = 0;
    for(i = 0;i<MaxKeyNum;i++){
        InitList(&(*idxlist).item[i].bnolist); //��ʼ����������Ŀ�е���ŵ�����
    }
}

void ExtractKeyWord (int *BookNum)
{
    int i = 0,j = 0,k = 0,m;
    wdlist.last = 0;  //����Ҫ
    Boolean Ignore;
    char TempChar[30];
    for(m = 0;m<=30;m++)
        TempChar[m] = '\0';   //���TempChat[]
    while(*(buf+i) != ' '){  //��ȡ��Ŀ�����������е����
        TempChar[i] = *(buf+i); //��������ַ������ͱ����ڸ�������
        i++;
    }
    TempChar[i] = '\0';
    *BookNum = atoi(TempChar); //�����תΪint

    for(m = 0;m<=i;m++)
        TempChar[m] = '\0';   //���TempChat[]
    i++;  //�ƽ�һλ����ǰ*(buf+i)��ʼΪ����
    while(*(buf+i) != '\n' && *(buf+i) != '\0'){
        //ÿ���ַ���ĩβ���н�����\n
        if(*(buf+i) != ' '){  //���ǿ��ַ�
            if(*(buf+i) >= 'A' && *(buf+i) <= 'Z'){
                *(buf+i) -= 'A' - 'a';  //��Ϊ��д����תΪСд
            }
            TempChar[j] = *(buf+i);  //�ѵ�ǰ�ַ�����TempChar��//------------
            j++;
            i++;
        } //if
        else{  //��Ϊ���ַ����������ǰTempChar�б�����ַ����Ƿ�Ϊ���ô�
            Ignore = FALSE;  //��IgnoreΪTRUE����Ϊ���ôʣ�ΪFALSE���ǳ��ô�

            for(m = 0;m<6;m++){     //�����Ƿ�Ϊ���ô�
                if(strcmp(TempChar,oftenwords[m]) == 0){
                    Ignore = TRUE;  //�ǳ��ô�
                    break;
                }//if
            }//for
            if(Ignore){
               for(m = 0;m<=j;m++)
                    TempChar[m] = '\0';   //���TempChat[]
                i++;
                j = 0;
            }//if
            else{  //���ǳ��ô�
                for(m = 0;m<=j;m++)  //���ôʲ���wdlist��
                    wdlist.item[wdlist.last][m] = TempChar[m];
                for(m = 0;m<=j;m++)
                    TempChar[m] = '\0';   //���TempChat[]
                k++;
                wdlist.last++;
                i++;
                j=0;
            }//else
        }//else

    }//while
}

void GetLine(FILE *f)
{
    fgets(buf,MaxLineLen,f);
}

void PutText (FILE *g,IdxListType idxlist)
{
    int i,j,k;
    Link p;
    for(i = 0;i<=idxlist.last;i++){
        for(j = 0;j<idxlist.item[i].key.length; j++)
            putc(*(idxlist.item[i].key.ch + j),g);
        putc('\t',g);
        if(idxlist.item[i].key.length < 8)
            putc('\t',g);
        p = idxlist.item[i].bnolist.head;
        for(k = 0;k<idxlist.item[i].bnolist.len ; k++){
            p = p->next;
            fprintf(g,"%03d",p->data);
            putc(' ',g);
        }//for
        putc('\n',g);
    }//for
}

void PrintFile(FILE *FileName)
{
    char ch;
    rewind(FileName);
    ch = getc(FileName);
    while(ch != EOF){
        putchar(ch);
        ch = getc(FileName);
    }
    printf("\n");
    rewind(FileName);
}

/*******************************����������**************************************/

int main()
{
    FILE *f,*g;
    int ct;
    int BookNo;
    if((f = fopen("BookName.txt","r")) == NULL){
        printf("ERROR in open BookName.txt\n");
        exit(1);
    }
    if((g = fopen("KeyWordIndex_self.txt","w"))==NULL){
        printf("ERROR in open KeyWordIndex_self.txt\n");
        exit(1);
    }
    printf("�鵥�ļ���\n");
    PrintFile(f);
    InitIdxList(&idxlist);
    WordListType w;
    while(!feof(f)){
        GetLine(f);   //��ȡ�鵥�ļ��е�һ�е�������
        ExtractKeyWord(&BookNo);
        InsertIdxList(&idxlist,BookNo);
    }
    PutText(g,idxlist);
    fclose(f);
    fclose(g);
    printf("\n������£�\n");
    if((g = fopen("KeyWordIndex_self.txt","r"))==NULL){
        printf("ERROR in open KeyWorkIndex_self.txt\n");
        exit(1);
    }
    PrintFile(g);
    fclose(g);
    return 0;
}
