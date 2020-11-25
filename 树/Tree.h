#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stddef.h>

#define OK 1
#define ERROR 0
#define OVERFLOW -1
#define TRUE 1
#define FALSE 0

typedef int Status;
typedef char TElemType;

typedef struct BiTNode {
	TElemType  data;
	struct BiTNode*lchild,* rchild;
} BiTNode, * BiTree;

Status InitTree(BiTree* T,TElemType e);
Status DestroyTree(BiTree* T);
BiTree CreateTree(void);
void PrintTree(BiTree T);
int TreeDepth(BiTree T);
BiTree Parent(BiTree T, BiTree Node);
BiTree RightSibling(BiTree T, BiTree Node);
BiTree LeftSibling(BiTree T, BiTree Node);
Status InsertRightChild(BiTree T, TElemType e);
Status InsertLeftChild(BiTree T, TElemType e);
Status DeleteRightChild(BiTree T, TElemType* e);
Status DeleteLeftChild(BiTree T, TElemType* e);
BiTree PreOrderTraverse(BiTree T,BiTree Node,BiTree (*visit)(BiTree,BiTree));
//先序深度优先遍历树 用于查找parent 和 sibling 返回查找到的对象
void InOrderTraverse(BiTree T);
//int Huffman();
BiTree BinSortTree(char* arr, int n);
//生成二叉排序树



//--------------------------------------------
typedef BiTree QElemType;

typedef struct QNode     //队列结点
{
	QElemType data;
	struct QNode* next;
}QNode, * QueuePtr;

typedef struct QLinklist //队列
{
	QueuePtr front;
	QueuePtr rear;
	int QueueNum;
}QLinklist;

Status InitQueue(QLinklist* Q);
Status DestroyQueue(QLinklist* Q);
Status GetHead(QLinklist Q, QElemType* e);
Status DelHead(QLinklist* Q);
Status EnQueue(QLinklist* Q, QElemType e);

//--------------------------------------------------
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

typedef BiTNode SElemType;
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
Status GetTop(SqStack S, SElemType* e);
//改变栈顶元素
Status ChangeTop(SqStack* S, SElemType e);
//插入元素e为栈顶元素
Status Push(SqStack* S, SElemType e);
//若栈不为空，删除栈顶元素
Status Pop(SqStack* S, SElemType* e);
//相当于python的map操作