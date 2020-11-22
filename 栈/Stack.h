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
}PosType;   //������Ϣ

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
}SElemType; //��������
 
typedef struct
{
	SElemType* base;
	SElemType* top;
	int stacksize;
}SqStack;



//����һ����ջS
Status InitStack(SqStack* S);
//����ջS
Status DestroyStack(SqStack* S);
//��S��Ϊ��ջ
Status ClearStack(SqStack* S);
//�ж��Ƿ�Ϊ��ջ
Status StackEmpty(SqStack S);
//����ջ��Ԫ�ظ���
int StackLength(SqStack S);
//��ջ��Ϊ�գ���e����S��ջ��Ԫ��
Status GetTop(SqStack S,SElemType* e);
//����Ԫ��eΪջ��Ԫ��
Status Push(SqStack* S, SElemType e);
//��ջ��Ϊ�գ�ɾ��ջ��Ԫ��
Status Pop(SqStack* S, SElemType* e);
//�൱��python��map����

//�Թ�����
Status MazePath(MazeType maze, PosType start, PosType end);
//�ж��Ƿ��ͨ��
Status Pass(PosType p);
//�����㼣
void FootPrint(PosType p);
//λ���ƶ�
PosType NextPos(PosType p, int dire);
//��ǲ���ͨ����λ��
void MarkPrint(PosType p);
//��ӡ·��
void PrintPath(SqStack S);
