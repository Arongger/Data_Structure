/*  ���Ķѷ���洢��ʾ  */
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OVERFLOW -2
typedef int Status;
typedef struct
{
    char *ch;  //����Ƿǿմ����򰴴�������洢��������chΪNULL
    int length;  //������
}HString;

/*******************************��������****************************************/

Status StrAssign(HString *T,char *chars);
//����һ����ֵ���ڴ�����chars�Ĵ�T
Status StrInsert (HString *S,int pos,HString T);
//1<=pos<=StrLength(S)+1.�ڴ�S�ĵ�pos���ַ�֮ǰ���봮T
int StrLength(HString S);
//����S��Ԫ�ظ�������Ϊ���ĳ���
int StrCompare(HString S,HString T);
//��S>T���򷵻�ֵ>0,��S=T���򷵻�ֵ = 0����S<T���򷵻�ֵ<0
Status ClearString(HString *S);
//��S���
Status Concat(HString *T,HString S1,HString S2);
//��T������S1��S2���Ӷ��ɵ��´�
Status SubString(HString *Sub,HString S,int pos,int len);
//��Sub���ش�S�ĵ�pos���ַ��𳤶�Ϊlen���Ӵ�
//����,1<= pos<= StrLength(S) �� 0<= len <= StrLength(S)-pos+1
Status StrCopy(HString *T, HString S);
/*******************************��������****************************************/

Status StrAssign(HString *T,char *chars)
{
    if((*T).ch){  //�ͷžɿռ�
        free((*T).ch);
    }
    int i = strlen(chars);
    if(!i){  //��charsΪ��
        (*T).ch = NULL;
        (*T).length = 0;
    }
    else{  //chars����
        if(!((*T).ch = (char *)malloc(i * sizeof(char))))  //ΪT����chars����Ĵ洢�ռ�
            exit(OVERFLOW);
        int count;
        for(count = 0;count <= i-1;count++){  //��chars����T��
            (*T).ch[count] = chars[count];
            (*T).length = i;
        } //for
    } //else
    return OK;
}

int StrLength(HString S)
{
    return S.length;
}

int StrCompare(HString S,HString T)
{
    int count;
    for(count = 0;count < S.length && count < T.length;count++){
        if(S.ch[count] != T.ch[count])
            return S.ch[count] - T.ch[count];
    }
    return S.length - T.length;
}

Status ClearString(HString *S)
{
    if((*S).ch){
        free((*S).ch);
        (*S).ch = NULL;
    }
    (*S).length = 0;
    return OK;
}

Status Concat(HString *T,HString S1,HString S2)
{
    if((*T).ch){  //�ͷžɿռ�
        free((*T).ch);
    }
    if(!((*T).ch = (char *)malloc((S1.length+S2.length)* sizeof(char))))
        exit(OVERFLOW);
    int count,cnt;
    for(count = 0;count <= S1.length;count++){  //��S1����T��
        (*T).ch[count] = S1.ch[count];
    }
    (*T).length = S1.length + S2.length;  //����T�ĳ���Ϊ����֮��
    for(count = S1.length,cnt = 0;count <= (*T).length;count++,cnt++){
        (*T).ch[count] = S2.ch[cnt];  //��S2����T��
    }
    return OK;
}

Status SubString(HString *Sub,HString S,int pos,int len)
{
    if(pos<1 || pos>S.length || len<0 || len >S.length-pos+1)
        return ERROR;
    if((*Sub).ch){  //�ͷžɿռ�
        free((*Sub).ch);
    }
    if(!len){
        (*Sub).ch = NULL;
        (*Sub).length = 0;  //���Ӵ�
    }
    else{  //�����Ӵ�
        (*Sub).ch = (char *)malloc(len*sizeof(char));
        int count,cnt;
        for(count = 0,cnt = pos-1;count <= len-1;count++,cnt++){
            (*Sub).ch[count] = S.ch[cnt];
        }
        (*Sub).length = len;
    }//else
    return OK;
}

Status StrInsert (HString *S,int pos,HString T)
{
    if(pos<1 || pos >(*S).length+1)
        return ERROR;  //pos���Ϸ�
    if(T.length){
        if(!((*S).ch = (char*)realloc((*S).ch,((*S).length + T.length)*sizeof(char))))
            exit(OVERFLOW);
        int count,cnt;
        for(count = (*S).length-1;count>= pos-1;count--){
            (*S).ch[count+T.length-1] = (*S).ch[count];  //Ϊ����T�ڳ�λ��
        }
        for(count = pos-1,cnt = 0;cnt<= T.length-1;count++,cnt++)
        (*S).ch[count] = T.ch[cnt];  //����T
        (*S).length += T.length;
    }//if
    return OK;
}

Status StrCopy(HString *T, HString S){
    int j;
    if((*T).ch)
        free((*T).ch);
    (*T).ch = (char*)malloc(S.length * sizeof(char));
    if(!(*T).ch)
        exit(OVERFLOW);
    for(j = 0; j < S.length; j++)
        (*T).ch[j] = S.ch[j];
    (*T).length = S.length;
    return OK;
}

/*******************************����������**************************************/

int main()
{
    HString T,S,S1,S2,Sub;
    char *charsT = "abcd";
    char *chars1 = "abc";
    char *chars2 = "AAAA";

    StrAssign(&T,charsT);
    StrAssign(&S,chars1);
    StrAssign(&S1,chars1);
    StrAssign(&S2,chars2);
    int count;
    printf("T�ĳ���Ϊ��%d\n",T.length);
    printf("T������Ϊ��");
    for(count = 0;count <T.length;count++){
        printf("%c",T.ch[count]);
    }
    printf("\n");

    printf("\nStrCompare(S,T) = %d\n",StrCompare(S,T));

    Concat(&T,S1,S2);
    printf("\n����S1��S2ΪT֮��\n");
    printf("T�ĳ���Ϊ��%d\n",T.length);
    printf("T������Ϊ��");
    for(count = 0;count <T.length;count++){
        printf("%c",T.ch[count]);
    }
    printf("\n");

    printf("\nS�ĳ���Ϊ��%d\n",S.length);
    printf("S������Ϊ��");
    for(count = 0;count <S.length;count++){
        printf("%c",S.ch[count]);
    }
    printf("��Sub����S�ĵ�1���ַ��𳤶�Ϊ2���Ӵ�\n");
    SubString(&Sub,S,1,2);
    printf("Sub�ĳ���Ϊ��%d\n",Sub.length);
    printf("Sub������Ϊ��");
    for(count = 0;count <Sub.length;count++){
        printf("%c",Sub.ch[count]);
    }
    printf("\n");

    printf("\n�ڴ�S�ĵ�1���ַ�֮ǰ���봮T\n");
    StrInsert(&S,1,T);
    printf("S�ĳ���Ϊ��%d\n",S.length);
    printf("S������Ϊ��");
    for(count = 0;count <S.length;count++){
        printf("%c",S.ch[count]);
    }
    return 0;
}

