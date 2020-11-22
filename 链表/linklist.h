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

typedef struct           //��������
{
	float coef;          //ϵ��
	int expn;            //ָ��
}term, ElemType;

typedef struct LNode     //�������
{
	ElemType data;       //����
	struct LNode* next;  //ָ��
}*Link, *Position;      

typedef struct           //��������
{
	Link head, tail;     //�ֱ�ָ��ͷ�������һ���ڵ�
	int len;             //Ԫ�ظ���
}List,*LinkList;

typedef LinkList polynomial;//����ͷ������������

/*
ElemType ��Ԫ����װ����������
Link Position ��ָ��ÿһ������ָ��
LinkList ��ָ������������Ϣ��ָ��
*/

//������������

//����һ���յ����Ա�L
Status InitList(LinkList* L);
//�������Ա�
Status DestroyList(LinkList* L);
//��������L����Ϊ�ձ����ͷ�ԭ����Ľ��ռ�
Status ClearList(LinkList* L);
//��֪hָ��ͷ��㣬��sָ��������ڵ�һ�����֮ǰ
Status InsFirst(Link h, Link s);
//������pָ���ֵΪe�Ľ��
Status MakeNode(Link* p, ElemType e);
//�ͷ�p��ָ�Ľ��
void FreeNode(Link* p);
//��֪hָ��ͷ��㣬ɾ�������е�һ����㲢��q����
Status DelFirst(Link h, Link* q);
/*��ָ��s��ָ��һ��������������Ա�L�����һ�����
֮�󣬲��ı�����L��βָ��ָ���µĽ��*/
Status Append(LinkList* L, Link s);
//ɾ�����Ա�L�е�β��㲢��q���أ��ñ�����L��βָ��
Status Remove(LinkList* L, Link* q);
/*��֪pָ�����������е�һ����㣬��s��ָ��������p��ָ���֮ǰ
���޸�ָ��pָ���²���Ľ��*/
Status InsBefore(LinkList* L, Link p, Link s);
/*��֪pָ�����������е�һ����㣬��s��ָ��������p��ָ���֮��
���޸�ָ��pָ���²���Ľ��*/
Status InsAfter(LinkList* L, Link* p, Link s);
//��֪pָ�����Ա���һ����㣬��e����p��ָ���������Ԫ�ص�ֵ
Status SetCurElem(Link* p, ElemType e);
//��֪pָ�����������е�һ����㣬����p��ָ�����Ԫ�ص�ֵ
ElemType GetCurElem(Link p);
//�ж����Ա��Ƿ�Ϊ�ձ�
Status ListEmpty(LinkList L);
//�������Ա�L��Ԫ�ظ���
int ListLength(LinkList L);
//������������L��ͷ����λ��
Position GetHead(LinkList L);
//������������L�����һ������λ��
Position GetLast(LinkList L);
//��֪pָ�����������е�һ����㣬����p��ָ����ֱ��ǰ����λ��
Position PriorPos(LinkList L, Link p);
//��֪pָ�����������е�һ����㣬����p��ָ����ֱ�Ӻ�̵�λ��
Position NextPos(LinkList L, Link p);
//����pָʾ��������L�е�i������λ�ò�����OK��iֵ���Ϸ�����ERROR
Status LocatePos(LinkList L, int i, Link* p);

//����ʽ��������

void CreatPolyn(polynomial* P, int m);
//����m��ϵ����ָ��������һԪ����ʽ����������P
void DestroyPolyn(polynomial* P);
//����һԪ����ʽP
void PrintPolyn(polynomial P);
//��ӡ���һԪ����ʽP
int PolynLength(polynomial P);
//����һԪ����ʽ�е�����
void AddPolyn(polynomial* Pa, polynomial* Pb);
//��ɶ���ʽ���������
int cmp(term a, term b);
//����ab��ָ����С����ֵ