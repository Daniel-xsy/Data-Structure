#pragma once
#include<stdio.h>
#include<stdlib.h>
#include"graph.h"
#include"Queue.h"
#include"stack.h"

typedef int Status;
typedef char TElemType;

typedef struct CSNode
{
	TElemType data;
	struct CSNode* firstchild, * nextsibling;
}CSNode,*CSTree;

Status InitTree(CSTree* T);
Status DestroyTree(CSTree* T);
Status CreateTree(CSTree* T);//
int TreeEmpty(CSTree T);
CSTree Root(CSTree T, TElemType Node);//��Ƶ�����
CSTree Parent(CSTree T, CSTree Node);
CSTree LeftChild(CSTree Node);
CSTree RightChild(CSTree Node);
CSTree NextChild(CSTree Node, CSTree child);
Status InsertChild(CSTree Node, int i, TElemType c);
Status DeleteChild(CSTree Node, int i, TElemType c);
int Degree(CSTree Node);
int NodeExist(CSTree T, TElemType c);
void TreeDFS(CSTree T, Stack S);
//����ݹ��㷨 ���ҽ���Ƿ����
void PreOrderDFS(CSTree T);//���� ������ȱ�����
void TreeBFS(CSTree T);