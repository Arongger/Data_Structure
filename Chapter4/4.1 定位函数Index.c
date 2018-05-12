#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 40 //����ַ���
typedef int Status;
typedef char SString[MAXSIZE+1];
//�˴�������SString[maxsize+1]�������飬��SubString����Ϊָ��ʹ�ã�
//��λ��ָ�룬SString[0]���ʵ������ĵ�ַ��ʹ��ʱ���ü�*��&��ֱ�Ӵ��������ֵ
/*******************************��������****************************************/
Status StrAssign(SString T,char *chars);
//����һ����ֵ����chars�Ĵ�T  ��һ��Ԫ��Ϊ�ַ�������
int StrLength(SString S);
//�������������S��Ԫ�ظ�������Ϊ���ĳ���
int StrCompare(SString S,SString T);
//�����������S>T���򷵻�ֵ>0����S = T���򷵻�ֵ =0����S<T���򷵻�ֵ<0
Status SubString(SString Sub, SString T,int pos,int len);
//��Sub���ش�T�ĵ�pos���ַ��𳤶�Ϊlen���Ӵ�
int Index(SString S,SString T,int pos);
//������S�д��ںʹ�Tֵ��ͬ���Ӵ����򷵻����������е�pos���ַ�֮���һ�γ��ֵ�λ�ã�������ֵΪ0
/*******************************��������****************************************/
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

int StrLength(SString S)
{
    return S[0];
}

int StrCompare(SString S,SString T)
{
    int cnt = 1;
    while(cnt <= S[0] && cnt <= T[0]){   //�ǿ�ǰ����

        if(S[cnt] == T[cnt]){  //���
            cnt++;
        }
        else{    //�����
            return S[cnt] - T[cnt];
        }

    }
    return S[0]-T[0];
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

int Index(SString S,SString T,int pos)
{
    SString Sub;

    int i = pos;
    if(pos > 0){
        int n = StrLength(S),m = StrLength(T);

        while( i<= n-m+1){

            SubString(Sub,S,i,m-1);
            if(StrCompare(Sub,T)==0)
                return i;
            else
                i++;
            }
    }//if
    printf("������\n");
    return 0;  //S�в�������T��ȵ��Ӵ�
}//Index

/*******************************����������**************************************/
int main()
{
    char *chars1 = "abcdefhg";
    char *chars2 = "defhg";
    SString S,T;

    StrAssign(S,chars1);
    StrAssign(T,chars2);

    int ANSWER = Index(S,T,1);
    printf("�ҵ��Ӵ�T��S�е�λ�� = %d\n",ANSWER);
    return 0;
}
