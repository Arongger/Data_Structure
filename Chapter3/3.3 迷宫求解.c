#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define STACK_INIT_SIZE 100  //�洢�ռ��ʼ������
#define STACKINCREMENT 10  //�洢�ռ��������
typedef int Status;
typedef struct
{
    int row;
    int col;
}PosType;
typedef struct
{
    int ord;  //ͨ������·���ϵġ���š�
    PosType seat;  //ͨ�������Թ��еġ�����λ�á�
    int di;  //�Ӵ�ͨ����������һͨ����ġ�����
}SElemType;

typedef struct
{
    SElemType *base;  //��ջ����֮ǰ������֮��base��ֵΪNULL
    SElemType *top;  //ջ��ָ��
    int stacksize;  //��ǰ�ѷ���Ĵ洢�ռ䣬��Ԫ��Ϊ��λ
}SqStack;

int MazeMap[10][10] =    //�Թ���ͼΪȫ�ֱ���
{
   //0,1,2,3,4,5,6,7,8,9
    {0,0,0,0,0,0,0,0,0,0}, //0
    {0,1,1,0,1,1,1,0,1,0}, //1
    {0,1,1,0,1,1,1,0,1,0}, //2
    {0,1,1,1,1,0,0,1,1,0}, //3
    {0,1,0,0,0,1,1,1,1,0}, //4
    {0,1,1,1,0,1,1,1,1,0}, //5
    {0,1,0,1,1,1,0,1,1,0}, //6
    {0,1,0,0,0,1,0,0,1,0}, //7
    {0,0,1,1,1,1,1,1,1,0}, //8
    {0,0,0,0,0,0,0,0,0,0}  //9
};
//***************ע����������������Ĳ�ͬ��ʾ���������׻���

/*******************************��������****************************************/

/*******************************��������****************************************/
Status InitStack(SqStack *S)
{
    (*S).base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));
    if(!(*S).base)
        exit(OVERFLOW);

    (*S).top = (*S).base;
    (*S).stacksize = STACK_INIT_SIZE;
    return OK;
}

Status Push(SqStack *S,SElemType e)
{
    *(*S).top++ = e;
    return OK;
}

Status Pop(SqStack *S,SElemType *e)
{
    if((*S).top == (*S).base)
        return ERROR;
    *e = *(--(*S).top);
    return OK;
}

Status StackEmpty(SqStack S)
{
    if(S.top==S.base)
        return OK;
    return ERROR;
}

void PrintMaze( )
{
    printf("\n �Թ��ĵ�ͼΪ��\n\n");
    int i,j;
    for(i = 0;i<10;i++){
        for(j = 0;j<10;j++)
            printf(" %3d",MazeMap[i][j]);
        printf("\n");
    }
}

Status FootPrint(PosType pos,int curstep)
{
    MazeMap[pos.row][pos.col] = curstep;
}

Status Pass(PosType pos)
{
    if(MazeMap[pos.row][pos.col] == 1)
        return TRUE;

    return FALSE;
}

PosType NextPos(PosType CurPos,int i)
{
    switch(i)
    {
    case 1:
        ++CurPos.row;  //��
            break;
    case 2:
        ++CurPos.col;  //��
            break;
    case 3:
        --CurPos.row;  //��
            break;
    case 4:
        --CurPos.col; //��

            break;
    }//switch
    return CurPos;
}

void MakePrint(PosType pos)
{
    printf("(%d,%d)�߲�ͨ\n",pos.row,pos.col);
    MazeMap[pos.row][pos.col] = 0;  //���߲�ͨ�Ŀ��滻Ϊǽ��
}

Status MazePath(PosType start,PosType end)
{
    SqStack S;
    PosType curpos;
    SElemType e;
    int curstep;

    InitStack(&S);
    curpos = start; //�趨����ǰλ�á�Ϊ�����λ�á�
    curstep = 1; //̽����һ��
    printf("��㣺(%d,%d)",start.row,start.col);
    do{
        if(Pass(curpos)){  //��ǰλ�ÿ���ͨ������ʹδ���ߵ�����ͨ����
            FootPrint(curpos,curstep);  //�����㼣
            printf("  ->(%3d,%3d)\n",curpos.row,curpos.col);
            e.ord = curstep;
            e.seat = curpos;
            e.di = 1;
            Push(&S,e);  //����·��

            if(curpos.row == end.row && curpos.col == end.col){  //�����յ�
                printf("�����յ㣺(%3d,%3d)\n",e.seat.col,e.seat.row);
                return TRUE;
            }
            curpos = NextPos(curpos,1);   //��һλ���ǵ�ǰλ�õĶ���
            curstep++;  //̽����һ��
            printf("step:%d",curstep);
        }//if
        else{  //��ǰλ�ò���ͨ��
            if(!StackEmpty(S)){

                Pop(&S,&e);
                while(e.di == 4 && !StackEmpty(S)){
                    MakePrint(e.seat);
                    Pop(&S,&e);
                    curstep--;
                    printf("���˵�(%3d,%3d)\n",e.seat.col,e.seat.row);
                }//while
                if(e.di < 4){
                    ++e.di;  //����һ������̽��
                    Push(&S,e);
                    curpos = NextPos(e.seat,e.di); //�趨��ǰλ���Ǹ��·����ϵ����ڿ�
                }//if
            }//if
        }//else
    }while(!StackEmpty(S));
    printf("�Բ����Ҳ�������\n");
    return FALSE;
}


/*******************************����������**************************************/

int main()
{
    PrintMaze();
    PosType Start,End;
    Start.col = 1;
    Start.row = 1;
    End.col = 8;
    End.row = 8;
    MazePath(Start,End);
    PrintMaze();
    return 0;
}


