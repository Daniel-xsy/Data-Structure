#include"stack.h"

Status InitStack(Stack* S)
{
	SLink q;

	q = (SLink)malloc(sizeof(SNode));
	if (q == NULL)
	{
		exit(OVERFLOW);
	}
	q->data = '\0';
	q->next = NULL;
	S->bottom = q;
	S->top = q;
	return OK;
}

Status DestroyStack(Stack* S)
{
	SLink p, pre;
	int len, i;
	if (S->top == NULL)//栈不存在
	{
		return ERROR;
	}
	len = StackLength(*S);
	p = S->top;
	pre = S->top;
	for (i = 0; i < len + 1; i++)
	{
		p = p->next;
		free(pre);
		pre = p;
	}
	return OK;

}

Status StackEmpty(Stack S)
{
	if (S.bottom == S.top)
	{
		return 1;
	}
	return 0;
}

int StackLength(Stack S)
{
	int len = 0;
	SLink p;

	if (S.top == NULL||S.bottom==NULL)//栈不存在
	{
		return ERROR;
	}

	p = S.top;
	while (p != S.bottom)
	{
		p = p->next;
		len += 1;
	}
	return len;
}

Status GetTop(Stack S, SElemtype* e)
{
	SLink p;

	p = S.top->next;
	if (S.top == NULL||p==NULL)//栈不存在或无元素
	{
		*e = '\0';
		return ERROR;
	}
	*e = p->data;
	return OK;
}

Status Push(Stack* S, SElemtype e)
{
	SLink q, p;
	int len;

	if (S->top == NULL)//栈不存在
	{
		return ERROR;
	}
	q = (SLink)malloc(sizeof(SNode));
	if (q == NULL)
	{
		exit(OVERFLOW);
	}

	len = StackLength(*S);
	if (len == 0)//若为第一个元素 修改bottom指针
	{
		S->bottom = q;
	}
	q->data = e;
	p = S->top->next;
	q->next = p;
	S->top->next = q;
	

	return OK;
}

Status Pop(Stack* S, SElemtype* e)
{
	SLink p;
	int len;
	p = S->top->next;
	if (S->top == NULL||p==NULL)//栈不存在或无元素
	{
		return ERROR;
	}
	len = StackLength(*S);
	if (len == 1)//只有一个元素 也要修改bottom指针
	{
		S->bottom = S->top;
	}
	S->top->next = p->next;
	free(p);
	return OK;
}