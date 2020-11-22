#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<stddef.h>
#define TURE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2

typedef int Status;

typedef struct           //数据类型
{
	float coef;          //系数
	int expn;            //指数
}term, ElemType;

typedef struct LNode     //结点类型
{
	ElemType data;       //数据
	struct LNode* next;  //指针
}*Link, *Position;      

typedef struct           //链表类型
{
	Link head, tail;     //分别指向头结点和最后一个节点
	int len;             //元素个数
}List,*LinkList;

typedef LinkList polynomial;//带表头结点的有序链表

/*
ElemType 是元素中装载数据类型
Link Position 是指向每一个结点的指针
LinkList 是指向整个链表信息的指针
*/

//基础操作函数

//构造一个空的线性表L
Status InitList(LinkList* L);
//销毁线性表
Status DestroyList(LinkList* L);
//将线链表L重置为空表，并释放原链表的结点空间
Status ClearList(LinkList* L);
//已知h指向头结点，将s指向结点插入在第一个结点之前
Status InsFirst(Link h, Link s);
//分配由p指向的值为e的结点
Status MakeNode(Link* p, ElemType e);
//释放p所指的结点
void FreeNode(Link* p);
//已知h指向头结点，删除链表中第一个结点并以q返回
Status DelFirst(Link h, Link* q);
/*将指针s所指的一串结点链接在线性表L的最后一个结点
之后，并改变链表L的尾指针指向新的结点*/
Status Append(LinkList* L, Link s);
//删除线性表L中的尾结点并以q返回，该表链表L的尾指针
Status Remove(LinkList* L, Link* q);
/*已知p指向线性链表中的一个结点，将s所指结点插入在p所指结点之前
并修改指针p指向新插入的结点*/
Status InsBefore(LinkList* L, Link p, Link s);
/*已知p指向线性链表中的一个结点，将s所指结点插入在p所指结点之后
并修改指针p指向新插入的结点*/
Status InsAfter(LinkList* L, Link* p, Link s);
//已知p指向线性表中一个结点，用e更新p所指结点中数据元素的值
Status SetCurElem(Link* p, ElemType e);
//已知p指向线性链表中的一个结点，返回p所指结点中元素的值
ElemType GetCurElem(Link p);
//判断线性表是否为空表
Status ListEmpty(LinkList L);
//返回线性表L中元素个数
int ListLength(LinkList L);
//返回线性链表L中头结点的位置
Position GetHead(LinkList L);
//返回线性链表L中最后一个结点的位置
Position GetLast(LinkList L);
//已知p指向线性链表中的一个结点，返回p所指结点的直接前驱的位置
Position PriorPos(LinkList L, Link p);
//已知p指向线性链表中的一个结点，返回p所指结点的直接后继的位置
Position NextPos(LinkList L, Link p);
//返回p指示线性链表L中第i个结点的位置并返回OK，i值不合法返回ERROR
Status LocatePos(LinkList L, int i, Link* p);

//多项式操作函数

void CreatPolyn(polynomial* P, int m);
//输入m项系数和指数，建立一元多项式的有序链表P
void DestroyPolyn(polynomial* P);
//销毁一元多项式P
void PrintPolyn(polynomial P);
//打印输出一元多项式P
int PolynLength(polynomial P);
//返回一元多项式中的项数
void AddPolyn(polynomial* Pa, polynomial* Pb);
//完成多项式的相加运算
int cmp(term a, term b);
//按照ab中指数大小返回值