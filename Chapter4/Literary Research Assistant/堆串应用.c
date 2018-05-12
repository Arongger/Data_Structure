#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OVERFLOW -2

typedef int Status;
typedef int ElemType; //�������������Ԫ������Ϊ����
typedef int Boolean;

typedef struct
{
    char *ch;  //����Ƿǿմ����򰴴�������洢��������chΪNULL
    int length;  //������
}HString;
#define MaxLen 500  //��󳤶�(500)
char buf[MaxLen];  //������
int next[5];
int pos=0;

/*******************************��������****************************************/

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

void GetLine(FILE *f)
{
    fgets(buf,MaxLen,f);
}

void ShowFile(FILE *FileName)
{
    printf("�ļ����ݣ�\n");
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

void InputFile(FILE *FileName)
{
    printf("д���ļ���Ctrl+Z������룩:\n");
    char s[MaxLen];
    char ch;
    FILE *g;
    if((g = fopen("writefile.txt","w")) == NULL){
        printf("ERROR in open the file.txt\n");
        exit(1);
    }
    while((ch = getchar()) != EOF)
        fprintf(g,"%c",ch);

    fclose(g);
}

void SearchWordInFile(FILE *FileName)
{
    FILE *f;
    int row_loc,col_Loc;
    if((f = fopen("readfile.txt","r")) == NULL){
        printf("ERROR in open the readfile.txt\n");
        exit(1);
    }
    ShowFile(f);
    char SearchWord[20];
    printf("����Ҫ���ҵĵ��ʣ�\n");
    scanf("%s",&SearchWord);
    row_loc = 0;
    while(!feof(f)){
        GetLine(f);   //��ȡ�ļ��е�һ�е�������
        row_loc++;
        if((col_Loc = index_KMP(buf,SearchWord,pos)) != 0){
            printf("�ҵ����ڵ�%d�У���%d��λ��\n",row_loc,col_Loc);
            return;
        }
    }
    printf("�Բ����Ҳ�����\n");
}

/*******************************����������**************************************/

int main()
{
    FILE *f,*g;
    if((f = fopen("readfile.txt","r")) == NULL){
        printf("ERROR in open the readfile.txt\n");
        exit(1);
    }
    if((g = fopen("writefile.txt","r")) == NULL){
        printf("ERROR in open the writefile.txt\n");
        exit(1);
    }
    int choice = -1;
    printf("��ѡ��\n 1.��ȡreadfile�ļ�\n 2.�½�һ��writefile�ļ�\n 3.����һ������\n 0.�˳�\n");
    while(choice != 0){
        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
            ShowFile(f);
            printf("\n");
            break;
        case 2:
            InputFile(g);
            ShowFile(g);
            printf("\n");
            break;
        case 3:
            SearchWordInFile(f);
            printf("\n");
            break;
        case 0:
            break;
        default:
            printf("û�и�ѡ�����������\n");
            printf("\n");

        }
    if(choice != 0)
        printf("��ѡ��\n 1.��ȡreadfile�ļ�\n 2.�½�һ��writefile�ļ�\n 3.����һ������\n 0.�˳�\n");
    }
    fclose(f);
    fclose(g);
    printf("���������...\n");
    _getch();

    return 0;
}
