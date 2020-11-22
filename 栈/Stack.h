#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<stddef.h>
#define TURE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

typedef int Status;

typedef struct
{
	int x;
	int y;
}PosType;   //坐标信息

typedef int MazeType[10][10];

MazeType maze =
{
{0,0,0,0,0,0,0,0,0,0},
{0,1,1,0,1,1,1,0,1,0},
{0,1,1,0,1,1,1,0,1,0},
{0,1,1,1,1,0,0,1,1,0},
{0,1,0,0,0,1,1,1,1,0},
{0,1,1,1,0,1,1,1,1,0},
{0,1,0,1,1,1,0,1,1,0},
{0,1,0,0,0,1,0,0,1,0},
{0,0,1,1,1,1,1,1,1,0},
{0,0,0,0,0,0,0,0,0,0}
};

typedef struct
{
	int order;
	PosType seat;
	int dire;
}SElemType; //数据类型
 
typedef struct
{
	SElemType* base;
	SElemType* top;
	int stacksize;
}SqStack;



//构造一个空栈S
Status InitStack(SqStack* S);
//销毁栈S
Status DestroyStack(SqStack* S);
//把S置为空栈
Status ClearStack(SqStack* S);
//判断是否为空栈
Status StackEmpty(SqStack S);
//计算栈的元素个数
int StackLength(SqStack S);
//若栈不为空，用e返回S的栈顶元素
Status GetTop(SqStack S,SElemType* e);
//插入元素e为栈顶元素
Status Push(SqStack* S, SElemType e);
//若栈不为空，删除栈顶元素
Status Pop(SqStack* S, SElemType* e);
//相当于python的map操作

//迷宫代码
Status MazePath(MazeType maze, PosType start, PosType end);
//判断是否可通过
Status Pass(PosType p);
//留下足迹
void FootPrint(PosType p);
//位置移动
PosType NextPos(PosType p, int dire);
//标记不能通过的位置
void MarkPrint(PosType p);
//打印路径
void PrintPath(SqStack S);
