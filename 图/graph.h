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
//初始化图数组
Status CreateDNGraph(ALGraph* G);
//键盘输入新建图
Status DestroyDNGraph(ALGraph* G);
//删除图
void PrintDNGraph(ALGraph G);
//打印图
int LocateVex(ALGraph G, VertexType u);
//定位点在数组中位置
VertexType GetVex(ALGraph G, int v);
//得到指定位置对应点
Status PutVex(ALGraph* G, int v, VertexType value);
//改变对应位置点的值
int FirstAdjVex(ALGraph G, int v);
//找到第一个邻近点
int NextAdjVex(ALGraph G, int v, int w);
//找下一个邻近点
Status InsertVex(ALGraph* G, VertexType v);
//插入新点
Status DeleteVex(ALGraph* G, VertexType v);
//删除点
int ExistArc(ALGraph G, int v, int w);
//判断某弧是否存在
int ArcNumber(ALGraph G, int v);
//返回某点出度数
Status InsertArc(ALGraph* G,int v,int w);
//插入弧
Status DeleteArc(ALGraph* G, int v, int w);
//删除弧
void DFSTraverse(ALGraph G);
void DFS(ALGraph G, int v,int* visit);
//广度优先算法 打印点
void BFSTraverse(ALGraph G);
void BFS(ALGraph G, int v, int* visit);
//深度优先算法 打印点

void DFSorest(ALGraph G, CSTree* T);
void DFSTree(ALGraph G, int v, CSTree* T);
//深度优先生成树和森林