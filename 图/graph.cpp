#include"graph.h"

Status InitDNGraph(ALGraph* G)
{
	int i;
	for (i = 0; i < MAX_VERTEX_NUM; i++)
	{
		G->vertices[i].data = '\0';
		G->vertices[i].firstarc = NULL;
	}
	G->arcnum = 0;
	G->vexnum = 0;
	G->kind = 0;
	return OK;
}

Status CreateDNGraph(ALGraph* G)
{
	int i;
	VertexType v;
	VertexType s, e;
	int sIndex,eIndex ;

	for (i = 0; i < MAX_VERTEX_NUM; i++)
	{
		printf("请输入第 %d 个点(输入#停止) : ", i);
		scanf_s("%c", &v, 1);

		if (isspace(v))
		{
			scanf_s("%c", &v, 1);
		}

		if (v == '#')
		{
			break;
		}

		InsertVex(G, v);
	}

	printf("请输入边\n(实例:a b 表示a-->b)\n输入#停止\n");
	for (i = 0;; i++)
	{
		printf("第 %d 条边\n", i+1);
		scanf_s("%c", &s, 1);//起点

		while (isspace(s))
		{
			scanf_s("%c", &s, 1);
		}

		if (s == '#')
		{
			break;
		}

		scanf_s("%c", &e, 1);//终点
		while (isspace(e))
		{
			scanf_s("%c", &e, 1);
		}

		sIndex = LocateVex(*G, s);
		eIndex = LocateVex(*G, e);

		if (eIndex == -1 || sIndex == -1)
		{
			printf("vertex不存在!请重新输入\n");
			i -= 1;
			continue;
		}

		if (eIndex == sIndex)
		{
			printf("vertex重复!请重新输入\n");
			i -= 1;
			continue;
		}

		if (!ExistArc(*G, sIndex, eIndex))
		{

			InsertArc(G, sIndex, eIndex);
			continue;
		}
		i -= 1;
		printf("该边已存在！请重新输入\n");
	}
	return OK;
}

Status DestroyDNGraph(ALGraph* G)
{
	int i, k;
	ArcNode* p, *pre;
	int arcnum;
	
	for (i = 0; i < G->vexnum; i++)
	{
		p = G->vertices[i].firstarc;
		pre = G->vertices[i].firstarc;
		arcnum = ArcNumber(*G, i);
		for (k = 0; k < arcnum; k++)
		{
			p = p->nextarc;
			free(pre);
			pre = p;
		}
	}
	return OK;
}

void PrintDNGraph(ALGraph G)
{
	int i, k;
	int ArcNum;
	VertexType s,e;
	ArcNode* p;

	printf("vertex:\n");
	for (i = 0; i < G.vexnum; i++)
	{
		printf("%d : %c\n", i, G.vertices[i].data);
	}
	printf("in tatal : %d \n", G.vexnum);
	printf("edges:\n");
	for (i = 0; i < G.vexnum; i++)
	{
		p = G.vertices[i].firstarc;
		ArcNum = ArcNumber(G, i);
		s = GetVex(G, i);
		for (k = 0; k < ArcNum; k++)
		{
			e = GetVex(G, p->adjvex);
			printf("%c ---> %c\n", s,e);
			p = p->nextarc;
		}
	}
	printf("in tatal : %d \n",G.arcnum);
}

int LocateVex(ALGraph G, VertexType u)
{
	int i;
	if (G.vertices <= 0)
	{
		return OVERFLOW;
	}
	for (i = 0; i < G.vexnum; i++)
	{
		if (G.vertices[i].data == u)
		{
			return i;
		}
	}
	return -1;//未检索到信息
}

VertexType GetVex(ALGraph G, int v)
{
	if (v >= G.vexnum || v < 0)
	{
		return OVERFLOW;
	}
	return G.vertices[v].data;
}

Status PutVex(ALGraph* G, int v, VertexType value)
{
	if (v >= G->vexnum || v < 0)
	{
		return OVERFLOW;
	}
	G->vertices[v].data = value;
	return OK;
}

int FirstAdjVex(ALGraph G, int v)
{
	int location;

	if (v >= G.vexnum || v < 0)
	{
		return OVERFLOW;
	}

	if (G.vertices[v].firstarc == NULL)
	{
		return -1;//没有邻结点
	}

	location = G.vertices[v].firstarc->adjvex;
	return location;
}

int NextAdjVex(ALGraph G, int v, int w)
{
	ArcNode* p;
	if (v >= G.vexnum || v < 0)
	{
		return OVERFLOW;
	}
	p = G.vertices[v].firstarc;
	while (p->adjvex!=w||p!=NULL)
	{
		p = p->nextarc;
	}

	if (p == NULL)//没有w
	{
		return OVERFLOW;
	}

	p = p->nextarc;

	if (p == NULL)//w为最后一个
	{
		return OVERFLOW;
	}

	return p->adjvex;
}

Status InsertVex(ALGraph* G, VertexType v)
{
	if (G->vexnum == MAX_VERTEX_NUM)
	{
		return ERROR;
	}
	G->vertices[G->vexnum].data = v;
	G->vertices[G->vexnum].firstarc = NULL;
	G->vexnum += 1;
	return OK;
}

Status DeleteVex(ALGraph* G, VertexType v)
{
	int i;
	VNode* p;
	ArcNode* pv, * pre;
	int position;
	int FirstArcPosition;
	int NextArcPosition;

	p = G->vertices;
	for (i = 0; i < G->vexnum; i++, p++)
	{
		if (p->data == v)
		{
			break;
		}
	}
	if (i == G->vexnum)
	{
		return ERROR;//v don't exist
	}
	//删除该点的弧
	
	p->data = '\0';
	pv = p->firstarc;
	pre = p->firstarc;
	while (pv != NULL)
	{
		pv = pv->nextarc;
		free(pre);
		pre = pv;//释放结点
	}

	//删除指向该点的弧
	position = LocateVex(*G, v);
	for (i = 0; i < G->vexnum; i++)
	{
		FirstArcPosition =FirstAdjVex(*G, i);

		if (FirstArcPosition == -1)
		{
			continue;//没有邻结点
		}

		if (FirstArcPosition == position)//若在头结点
		{
			G->vertices[i].firstarc->info = -1;//表示去除该边
			break;
		}
		pv = G->vertices[i].firstarc->nextarc;
		if (pv == NULL)
		{
			continue;
		}
		while ((NextArcPosition = pv->adjvex) != -1||pv!=NULL)//依次查找
		{
			if (position == NextArcPosition)
			{
				pv->info = -1;
				break;
			}
			pv = pv->nextarc;
		}
	}
	G->vexnum -= 1;
	return OK;
}

int ExistArc(ALGraph G, int v, int w)
{
	ArcNode* p;
	p = G.vertices[v].firstarc;
	while (p != NULL)
	{
		if (p->adjvex == w)
		{
			return 1;
		}
		p = p->nextarc;
	}
	return 0;
}

int ArcNumber(ALGraph G, int v)
{
	int count = 0;
	ArcNode* p;
	if (v >= G.vexnum || v < 0)
	{
		return OVERFLOW;
	}
	if (G.vertices[v].data == '\0')
	{
		return ERROR;//该点不存在
	}
	p = G.vertices[v].firstarc;
	while (p != NULL)
	{
		p = p->nextarc;
		count += 1;
	}
	return count;
}

Status InsertArc(ALGraph* G, int v, int w)
{
	ArcNode* p;
	ArcNode* pnew;
	if ((v < 0 || v >= G->vexnum) || (w < 0 || w >= G->vexnum))
	{
		return OVERFLOW;//索引值溢出
	}
	if (G->vertices[v].data == '\0' || G->vertices[w].data == '\0')
	{
		return ERROR;//该点不存在
	}

	if ((p = G->vertices[v].firstarc) == NULL)
	{
		pnew = (ArcNode*)malloc(sizeof(ArcNode));
		if (pnew == NULL)
		{
			exit(OVERFLOW);
		}
		pnew->adjvex = w;
		pnew->info = 1;
		pnew->nextarc = NULL;
		G->vertices[v].firstarc = pnew;
	}
	else
	{
		while (p->nextarc != NULL)
		{
			p = p->nextarc;
		}
		pnew = (ArcNode*)malloc(sizeof(ArcNode));
		if (pnew == NULL)
		{
			exit(OVERFLOW);
		}
		pnew->adjvex = w;
		pnew->info = 1;
		pnew->nextarc = NULL;
		p->nextarc = pnew;
	}
	G->arcnum += 1;
	return OK;
}

Status DeleteArc(ALGraph* G, int v, int w)
{
	ArcNode* p=NULL, *pre=NULL;

	if ((v < 0 || v >= G->vexnum) || (w < 0 || w >= G->vexnum))
	{
		return OVERFLOW;//索引值溢出
	}
	if (G->vertices[v].data == '\0' || G->vertices[w].data == '\0')
	{
		return ERROR;//该点不存在
	}
	if (!ExistArc(*G, v, w))//该边不存在
	{
		return ERROR;
	}

	p = G->vertices[v].firstarc;
	if (p->adjvex == w)//w是第一个邻结点
	{
		G->vertices[v].firstarc = p->nextarc;
		free(p);
		return OK;
	}

	while (p->adjvex != w)
	{
		pre = p;
		p = p->nextarc;
	}
	pre->nextarc = p->nextarc;
	free(p);
	G->arcnum -= 1;
	return OK;
}

//深度优先遍历图
void DFSTraverse(ALGraph G)
{
	int* visit;
	int i;
	visit = (int*)malloc(G.vexnum * sizeof(int));//分配内存

	printf("使用深度优先算法遍历:\n");

	if (visit == NULL)
	{
		exit(OVERFLOW);
	}
	for (i = 0; i < G.vexnum; i++)
	{
		visit[i] = 0;//初始化为0
	}
	for (i = 0; i < G.vexnum; i++)
	{
		if (visit[i] == 0)
		{
			DFS(G, i, visit);
		}
 	}
	printf("结束\n");
	free(visit);
}

void DFS(ALGraph G, int v, int* visit)
{
	VertexType vertex;
	ArcNode* p;

	if (visit[v] == 0)
	{
		visit[v] = 1;
		vertex = GetVex(G, v);
		printf("%c ---> ", vertex);
		p = G.vertices[v].firstarc;
		if (p != NULL)
		{
			DFS(G, p->adjvex, visit);
		}
	}
	return;
}

//广度优先遍历图
void BFSTraverse(ALGraph G)
{
	int* visit;
	int i;

	printf("使用广度优先算法遍历:\n");

	visit = (int*)malloc(G.vexnum * sizeof(int));
	if (visit == NULL)
	{
		exit(OVERFLOW);
	}

	for (i = 0; i < G.vexnum; i++)
	{
		visit[i] = 0;
	}

	for (i = 0; i < G.vexnum; i++)
	{
		if (visit[i] == 0)
		{
			//EnQueue(&Q, i);//入队
			BFS(G, i, visit);
		}
	}
	printf("结束\n");
	free(visit);
}

void BFS(ALGraph G, int v, int* visit)
{
	VertexType vertex;
	ArcNode* p;
	QElemType e;
	int i;
	QLinklist Q;

	visit[v] = 1;
	InitQueue(&Q);//队列初始化
	EnQueue(&Q, v);

	vertex = GetVex(G, v);
	printf("%c ---> ", vertex);

	while (Q.front!=Q.rear)//队列不为空
	{
		GetHead(Q, &e);
		DelHead(&Q);
		p = G.vertices[e].firstarc;
		if (p == NULL)
		{
			continue;//该结点无出度
		}
		for (i = 0; i < ArcNumber(G, e); i++)//未访问邻点加入队列
		{
			if (visit[p->adjvex] == 0)
			{
				visit[p->adjvex] = 1;
				vertex = GetVex(G, p->adjvex);
				printf("%c ---> ", vertex);
				EnQueue(&Q, p->adjvex);
			}
			p = p->nextarc;
		}
	}
	DestroyQueue(&Q);
	return;
}

