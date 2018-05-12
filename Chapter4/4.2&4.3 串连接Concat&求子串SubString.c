/*  ���Ķ���˳��洢��ʾ  */
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 40
#define MAXSTRLEN 6 //����ַ���
typedef int Status;
typedef char SString[MAXSIZE+1];
//�˴�������SString[maxsize+1]�������飬��SubString����Ϊָ��ʹ�ã�

//��λ��ָ�룬SString[0]���ʵ������ĵ�ַ��ʹ��ʱ���ü�*��&��ֱ�Ӵ��������ֵ

/*******************************��������****************************************/
Status StrAssign(SString *T,char *chars);
//����һ����ֵ����chars�Ĵ�T  ��һ��Ԫ��Ϊ�ַ�������
Status SubString(SString Sub, SString T,int pos,int len);
//��Sub���ش�T�ĵ�pos���ַ��𳤶�Ϊlen���Ӵ�
Status Concat(SString T,SString S1,SString S2);
//��T������S1��S2���Ӷ��ɵ��´�

/*Status SubString(SString Sub, SString T,int pos,int len)*/
int StrCompare(SString S,SString T);
int StrLength(SString S);
int StrEmpty(SString S);
Status StrCopy(SString S,SString *T);
Status ClearString(SString S);

/*******************************��������****************************************/

Status StrAssign(SString *T,char *chars)
{
    int i,ct;
    for(i = 0;i <= MAXSIZE; i++)
        (*T)[i] = '\0';    //ȫ������

    (*T)[0] = strlen(chars);
    for(ct = 1;*chars != '\0';ct++,chars++){
        (*T)[ct] = *chars;
    }
    return OK;
}

Status SubString(SString Sub, SString T,int pos,int len)
{
    if(pos<1 || pos>T[0] || len<0 || len>T[0]-pos+1)
        return ERROR;

    int ct,cnt;
    for(ct = 1,cnt = pos;cnt <= len+pos;ct++,cnt++){
        Sub[ct]=T[cnt];
    }
    Sub[0] = len+1;
    return OK;
}
/*
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
*/
Status Concat(SString T,SString S1,SString S2)
{
    int count,i;
    int uncut;
    //���һ�������ýضϣ�ֱ�Ӹ���S1��S2��T��
    if(S1[0]+S2[0] <= MAXSTRLEN){
        T[0] = S1[0] + S2[0];
        for(count = 1;count <= S1[0];count++){   //����S1��ֵ��T��
            T[count] = S1[count];
        }
        for(count = S1[0]+1,i = 1;count <= T[0];count++,i++){ //����S2��ֵ��T��
            T[count] = S2[i];
        }
        uncut = TRUE;
    }//if

    //���������Ϊ���ȳ������ƣ���ض�S2������Ӵ�
    else if( S1[0] < MAXSTRLEN){
        T[0] = MAXSTRLEN;
        for(count = 1;count <= S1[0];count++){   //����S1��ֵ��T��
            T[count] = S1[count];
        }
        for(count = S1[0]+1,i = 1;count <= T[0];count++,i++){ //���ƽضϵ�S2��ֵ��T��
            T[count] = S2[i];
        }
        uncut = FALSE;
    }//else if

    //���������ΪS1�ĳ����Ѿ��ﵽ��󳤶ȣ�TֻȡS1
    else{
        T[0] = MAXSTRLEN;
        for(count = 1;count <= S1[0];count++){   //����S1��ֵ��T��
            T[count] = S1[count];
        }
    }//else
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

int StrEmpty(SString S)
{
    return S[0] == 0;
}

Status StrCopy(SString S,SString *T)
{
    int i;
    for(i = 0;i<=S[0];i++)
        (*T)[i] = S[i];
    return OK;
}

Status ClearString(SString S)
{
    S[0] = 0;
}
/*******************************����������**************************************/
int main()
{
    SString T,S1,S2;
    //��֤���һ
    /*char *chars1 = "abcd";
    char *chars2 = "e";*/


    //��֤�����
   /* char *chars1 = "abcd";
    char *chars2 = "efghijk";*/

    //��֤�����
    char *chars1 = "abcdef";
    char *chars2 = "efghijk";


    StrAssign(&S1,chars1);
    StrAssign(&S2,chars2);
    Concat(T,S1,S2);

    //��ӡT�е�ֵ
    int i;
    for(i = 1;i<=T[0];i++)
        printf("%c",T[i]);

    return 0;
}




