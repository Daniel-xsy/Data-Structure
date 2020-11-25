#include"Queue.h"

Status InitQueue(QLinklist* Q)
{
	QueuePtr p;
	p = (QueuePtr)malloc(sizeof(QNode));
	if (p == NULL)
	{
		exit(OVERFLOW);
	}
	Q->front = p;
	Q->rear = p;
	Q->QueueNum = 0;
}

Status DestroyQueue(QLinklist* Q)
{
	QueuePtr p, pre;
	int i;
	p = Q->front;
	pre = Q->front;
	for (i = 0; i < Q->QueueNum + 1; i++)//多算上front结点
	{
		p = p->next;
		free(pre);
		pre = p;
	}
	return OK;
}

Status GetHead(QLinklist Q, QElemType* e)
{
	QueuePtr p;
	p = Q.front->next;
	if (p == NULL)
	{
		*e = '-1';
		return ERROR;
	}
	*e = p->data;
	return OK;
}

Status DelHead(QLinklist* Q)
{
	QueuePtr p;

	p = Q->front->next;
	if (p == NULL)
	{
		Q->QueueNum = 0;
		return ERROR;//空队列
	}
	if (Q->rear == p)//只有一个元素
	{
		Q->rear = Q->front;
	}

	Q->front->next = p->next;
	free(p);
	Q->QueueNum -= 1;
	return OK;
}

Status EnQueue(QLinklist* Q, QElemType e)
{
	QueuePtr p;

	p = (QueuePtr)malloc(sizeof(QNode));
	if (p == NULL)
	{
		exit(OVERFLOW);
	}
	p->data = e;
	p->next = NULL;
	if (Q->QueueNum == 0)
	{
		Q->front->next = p;
	}
	Q->rear->next = p;
	Q->rear = p;
	Q->QueueNum += 1;
	return OK;
}