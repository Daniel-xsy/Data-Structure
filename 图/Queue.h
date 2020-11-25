#pragma once
#include<stdio.h>
#include<stdlib.h>
#include"graph.h"
#include"Tree.h"

typedef int QElemType;
typedef int Status;

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