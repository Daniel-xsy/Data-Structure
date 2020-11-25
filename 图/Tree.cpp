#include"Tree.h"

Status InitTree(CSTree* T)
{
	CSTree p;
	p = (CSTree)malloc(sizeof(CSNode));
	if (p == NULL)
	{
		exit(OVERFLOW);
	}
	(*T) = p;
	(*T)->data = '\0';
	(*T)->firstchild = NULL;
	(*T)->nextsibling = NULL;
}

Status DestroyTree(CSTree* T)
{

}

Status CreateTree(CSTree* T)
{

}

int TreeEmpty(CSTree T)
{
	if (T == NULL)
	{
		return ERROR;//��������
	}
	
	if (T->firstchild->firstchild == NULL)
	{
		return 1;//Ϊ����
	}
}

CSTree Root(CSTree T,CSTree Node)
{

}

CSTree Parent(CSTree T, CSTree Node)
{

}

CSTree LeftChild(CSTree Node)
{
	if (Node == NULL)//�����ڸý��
	{
		return NULL;
	}

	if (Node->firstchild == NULL)
	{
		return NULL;
	}

	return Node->firstchild;
}

CSTree RightChild(CSTree Node)
{
	int degree, i;
	CSTree p;

	if (Node == NULL)//�����ڸý��
	{
		return NULL;
	}

	if (Node->firstchild == NULL)//û�к��ӽ��
	{
		return NULL;
	}

	degree = Degree(Node);
	p = Node->firstchild;

	for (i = 1; i < degree; i++)
	{
		p = p->nextsibling;
	}

	return p;
}

CSTree NextChild(CSTree Node, CSTree child)
{
	int degree, i;
	CSTree p;

	degree = Degree(Node);
	if (degree == 0)//û�к���
	{
		return NULL;
	}

	p = Node->firstchild;
	for (i = 0; i < degree; i++)
	{
		if (p == child)
		{
			return p->nextsibling;
		}
		p = p->nextsibling;
	}
	return NULL;//û�в��ҵ���һ������
}

//i��1��ʼ
Status InsertChild(CSTree Node, int i, TElemType c)
{
	int degree, k;
	CSTree p,pre, q;

	//������
	if (Node == NULL)//�����ڸý��
	{
		return NULL;
	}
	degree = Degree(Node);
	if (i< 1|| i>degree+1)
	{
		return OVERFLOW;
	}
	/*
	if(NodeExist(c))
	{
	    return ERROR //�Ѿ����� ���䣡����
	}
	*/
	//qָ���´����Ľ��
	q = (CSTree)malloc(sizeof(CSNode));
	if (q == NULL)
	{
		exit(OVERFLOW);
	}
	q->data = c;
	q->firstchild = NULL;

	pre = Node;
	p = Node->firstchild;

	if (i == 1)//�ڵ�һ��λ�ò���
	{
		q->nextsibling = Node->firstchild;
		Node->firstchild = q;
		return OK;
	}

	for (k = 1; k < i; k++)//������λ�ò���
	{
		p = p->nextsibling;
		if (pre == Node)
		{
			pre = pre->firstchild;
		}
		else
		{
			pre = pre->nextsibling;
		}
	}
	pre->nextsibling = q;
	q->nextsibling = p;
	return OK;
}

Status DeleteChild(CSTree Node, int i, TElemType c)
{

}

int Degree(CSTree Node)
{
	CSTree p;
	int count = 0;

	if (Node == NULL)
	{
		return -1;
	}
	p = Node->firstchild;
	while (p != NULL)
	{
		count += 1;
		p = p->nextsibling;
	}
	return count;
}

static int flag;//������ǲ�����Ϣ

//������ȱ�������������ôд������
int NodeExist(CSTree T, TElemType c)
{
	Stack S;
	CSTree p;
	int degree, i;

	InitStack(&S);
	Push(&S, T->data);//���ڵ���ջ
	degree = Degree(T);
	p = T->firstchild;
	for (i = 1; i < degree; i++)
	{
		p = p->nextsibling;
		Push(&S, p->data);
		TreeDFS(p, S);
	}
	
}

void TreeDFS(CSTree T, Stack S)
{
	if (true)
	{

	}
}