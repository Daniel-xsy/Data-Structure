#pragma once
#include<stdio.h>
#include<stdlib.h>
#include"graph.h"
#include"Queue.h"
#include"Tree.h"

typedef int Status;
typedef TElemType SElemtype;

typedef struct SNode
{
	SElemtype data;
	SNode* next;
}SNode,*SLink;

typedef struct Stack
{
	SLink bottom;
	SLink top;
}Stack;

Status InitStack(Stack* S);
Status DestroyStack(Stack* S);
Status StackEmpty(Stack S);
int StackLength(Stack S);
Status GetTop(Stack S, SElemtype* e);
Status Push(Stack* S, SElemtype e);
Status Pop(Stack* S, SElemtype* e);
