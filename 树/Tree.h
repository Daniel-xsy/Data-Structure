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
//����������ȱ����� ���ڲ���parent �� sibling ���ز��ҵ��Ķ���
void InOrderTraverse(BiTree T);
//int Huffman();
BiTree BinSortTree(char* arr, int n);
//���ɶ���������



//--------------------------------------------
typedef BiTree QElemType;

typedef struct QNode     //���н��
{
	QElemType data;
	struct QNode* next;
}QNode, * QueuePtr;

typedef struct QLinklist //����
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
Status GetTop(SqStack S, SElemType* e);
//�ı�ջ��Ԫ��
Status ChangeTop(SqStack* S, SElemType e);
//����Ԫ��eΪջ��Ԫ��
Status Push(SqStack* S, SElemType e);
//��ջ��Ϊ�գ�ɾ��ջ��Ԫ��
Status Pop(SqStack* S, SElemType* e);
//�൱��python��map����