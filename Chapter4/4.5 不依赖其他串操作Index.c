//���Ӵ�λ�õĶ�λ����
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OVERFLOW -2
#define MAXSTRLEN 255
#define MAXSIZE 40 //����ַ���

typedef int Status;
typedef unsigned char SString[MAXSTRLEN +1];

/*******************************��������****************************************/

int Index(SString S,SString T,int pos);
//�����Ӵ�T������S�е�pos���ַ�֮���λ�á��������ڣ�����ֵΪ0
//���У�T�ǿգ�1<= pos <= StrLength(S)
Status StrAssign(SString T,char *chars);
//����һ����ֵ����chars�Ĵ�T  ��һ��Ԫ��Ϊ�ַ�������
/*******************************��������****************************************/
int Index(SString S,SString T,int pos)
{
    int i = pos,j = 1;
    while(i<= S[0] && j<=T[0]){
        if(S[i] == T[j]){
            ++i;
            ++j;
        } //�����ȽϺ���ַ�
        else{
            i = i-j+2;
            j = 1;
        }  //ָ��������¿�ʼƥ��
    } //while
    if(j>T[0])
        return i-T[0];
    else
        return 0;
}

Status StrAssign(SString T,char *chars)
{
    int i,ct;
    for(i = 0;i <= MAXSIZE; i++)
        T[i] = '\0';    //ȫ������

    T[0] = strlen(chars);
    for(ct = 1;*chars != '\0';ct++,chars++){
        T[ct] = *chars;
    }
    return OK;
}

/*******************************����������**************************************/

int main()
{
    SString S,T;
    char *chars1 = "abcdef";
    char *chars2 = "def";
    StrAssign(S,chars1);
    StrAssign(T,chars2);
    printf("S[0] = %d,T[0] = %d\n",S[0],T[0]);

    printf("�Ӵ�T������S�е�1���ַ�֮���λ�� = %d.\n",Index(S,T,1));
    return 0;
}


