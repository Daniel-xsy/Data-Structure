#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include"Queue.h"
#include"Tree.h"

#define MAX_VERTEX_NUM 20
#define OK 1
#define ERROR 0
#define OVERFLOW -1
#define DOWNFLOW -2

typedef int InfoType;
typedef char VertexType;
typedef int Status;

typedef struct ArcNode
{
	int adjvex;               //sequence of ajacent vertex
	struct ArcNode* nextarc;  //the next vertex of the link
	InfoType info;           //such as weight
}ArcNode;

typedef struct VNode
{
	VertexType data;          
	ArcNode* firstarc;        //the head of the link
}VNode,AdjList[MAX_VERTEX_NUM];

typedef struct
{
	AdjList vertices;         //the array 
	int vexnum, arcnum; 
	int kind;
}ALGraph;

Status InitDNGraph(ALGraph* G);
//��ʼ��ͼ����
Status CreateDNGraph(ALGraph* G);
//���������½�ͼ
Status DestroyDNGraph(ALGraph* G);
//ɾ��ͼ
void PrintDNGraph(ALGraph G);
//��ӡͼ
int LocateVex(ALGraph G, VertexType u);
//��λ����������λ��
VertexType GetVex(ALGraph G, int v);
//�õ�ָ��λ�ö�Ӧ��
Status PutVex(ALGraph* G, int v, VertexType value);
//�ı��Ӧλ�õ��ֵ
int FirstAdjVex(ALGraph G, int v);
//�ҵ���һ���ڽ���
int NextAdjVex(ALGraph G, int v, int w);
//����һ���ڽ���
Status InsertVex(ALGraph* G, VertexType v);
//�����µ�
Status DeleteVex(ALGraph* G, VertexType v);
//ɾ����
int ExistArc(ALGraph G, int v, int w);
//�ж�ĳ���Ƿ����
int ArcNumber(ALGraph G, int v);
//����ĳ�������
Status InsertArc(ALGraph* G,int v,int w);
//���뻡
Status DeleteArc(ALGraph* G, int v, int w);
//ɾ����
void DFSTraverse(ALGraph G);
void DFS(ALGraph G, int v,int* visit);
//��������㷨 ��ӡ��
void BFSTraverse(ALGraph G);
void BFS(ALGraph G, int v, int* visit);
//��������㷨 ��ӡ��

void DFSorest(ALGraph G, CSTree* T);
void DFSTree(ALGraph G, int v, CSTree* T);
//���������������ɭ��