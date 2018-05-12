#include <stdio.h>
#include <string.h>

char S[20]="ABCDEFGHIJK";
char T[5]="DEFG";
int next[5];
int pos=0;

/*******************************��������****************************************/
int index_KMP(char *s,char *t,int pos);
//����ģʽ����t��next������t������s�еĵ�pos��λ��֮���λ�õ�KMP�㷨��t�ǿգ�1<=pos<=Strlength(s)����
void get_next(char * t,int * next);
//��ģʽ��t��next�����Ĳ���������next[]�С�
/*******************************��������****************************************/
int index_KMP(char *s,char *t,int pos)
{
    int i=pos,j=1;

    while (i<=(int)strlen(s)&&j<=(int)strlen(t)){
        if (j==0  ||  s[i]==t[j-1]){ //�������к����ַ����ıȽ�
            i++;
            j++;
        }
        else
            j=next[j]; //ģʽ�������ƶ�
   }
    if (j>(int)strlen(t)) //ƥ��ɹ�
        return i-strlen(t)+1;
    else //ƥ�䲻�ɹ�
        return 0;
}

void get_next(char *t,int *next)
{
    int i=1,j=0;
    next[0]=next[1]=0;
    while (i<(int)strlen(t)) {
        if (j==0 || t[i]==t[j]){
            i++;
            j++;
            next[i]=j;
        } //if
      else
        j=next[j];
    } //while
}

/*******************************����������**************************************/
int main()
{
    int n;
    get_next(T,next);
    n=index_KMP(S,T,pos);
    if(n!=0)
        printf("\nģʽ��T������S�е�%d��λ��\n\n",n);
    else
      printf("\n�����в�������ģʽ����ƥ����Ӵ�!\n\n");
    return 0;
}
