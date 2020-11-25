#include"Tree.h"

int main(void)
{
	/*
	BiTree Root, target;
	int depth, n;

	Root = CreateTree();
	target=PreOrderTraverse(Root, Root->rchild->rchild, LeftSibling);
	depth = TreeDepth(Root);
	printf("���������Ϊ: %d \n", depth);
	*/
	char* arr;
	int n, depth;
	BiTree Root;

	printf("�����������������:\n");
	scanf_s("%d", &n);
	arr = (char*)malloc(n * sizeof(char));
	if (arr == NULL)
	{
		exit(OVERFLOW);
	}
	for (int i = 0; i < n; i++)
	{
		printf("������� %d / %d ���ַ�:\n",i+1,n);
		scanf_s(" %c", &(arr[i]));
	}

	printf("����������...\n");
	Root = BinSortTree(arr, n);
	depth = TreeDepth(Root);
	printf("�����Ϊ: %d\n", depth);
	printf("�����ӡ������:\n");
	InOrderTraverse(Root);
	return 0;
}

Status InitTree(BiTree* T, TElemType e)
{
	BiTree p;

	p = (BiTree)malloc(sizeof(BiTNode));
	if (p == NULL)
	{
		exit(OVERFLOW);
	}
	*T = p;
	(*T)->data = e;
	(*T)->lchild = NULL;
	(*T)->rchild = NULL;
	return OK;
}

Status DestroyTree(BiTree* T)
{
	if (*T != NULL)
	{
		free(*T);
		*T = NULL;
	}
	return OK;
}

int TreeDepth(BiTree T)
{
	static int depth = 1;
	static int count = 1;
	if (T != NULL)
	{
		count += 1;
		TreeDepth(T->lchild);
		count += 1;
		TreeDepth(T->rchild);
	}
	count -= 1;
	if (count > depth)
	{
		depth = count;
	}
	return depth;
}

BiTree CreateTree(void)
{
	BiTree Root,Parent;
	TElemType e;
	QLinklist Queue;
	int NodeNum,layer;
	int i;

	printf("��������ڵ�(#�˳�):\n");
	scanf_s(" %c", &e,1);
	if (e == '#')
	{
		return NULL;
	}
	InitTree(&Root, e);
	InitQueue(&Queue);

	EnQueue(&Queue, Root);//��������

	NodeNum = 2, layer = 1;
	while (Queue.QueueNum!=0)
	{
		NodeNum = 2*Queue.QueueNum;
		printf("����������� %d ����,�� %d ��(#:�˳� *��):\n",layer,NodeNum);
		for (i = 0; i < NodeNum; i++)
		{
			scanf_s(" %c", &e,1);
			if (e == '#')//�˳�
			{
				return Root;
			}
			if (e != '*')
			{
				if (i % 2 == 0)//i��ż�� ���һ��Ϊ����
				{
					GetHead(Queue, &Parent);//����
					InsertLeftChild(Parent, e);//����Ϊ����
					EnQueue(&Queue, Parent->lchild);//���
					continue;
				}
				else//i������ ���һ��Ϊ�Һ���
				{
					GetHead(Queue, &Parent);
					InsertRightChild(Parent, e);//����Ϊ�Һ���
					EnQueue(&Queue, Parent->rchild);//�Һ������
				}
			}
			if (i % 2 == 1)
			{
				DelHead(&Queue);//ɾ������
			}
		}
		layer++;
	}
	DestroyQueue(&Queue);
	return Root;
}

void PrintTree(BiTree T)
{
	QLinklist Queue;//��������㷨 ʹ�ö���
	BiTree p;

	InitQueue(&Queue);
	if (T != NULL)
	{
		p = T;
		EnQueue(&Queue, p);
		while (Queue.QueueNum != 0)//���в�Ϊ��
		{
			GetHead(Queue, &p);
			printf("p.");//������ֲ�ͬ�㼶???
			if (p->lchild != NULL)
			{
				EnQueue(&Queue, p->lchild);
			}
			if (p->rchild != NULL)
			{
				EnQueue(&Queue, p->rchild);
			}
		}
	}
}

Status InsertRightChild(BiTree T,TElemType e)
{
	BiTree RChild;

	if (T == NULL)
	{
		return ERROR;
	}
	InitTree(&RChild,e);
	T->rchild = RChild;
	return OK;
}

Status InsertLeftChild(BiTree T, TElemType e)
{
	BiTree LChild;

	if (T == NULL)
	{
		return ERROR;
	}
	InitTree(&LChild, e);
	T->lchild = LChild;
	return OK;
}

Status DeleteRightChild(BiTree T,TElemType* e)
{
	if (T == NULL||T->rchild==NULL)
	{
		return ERROR;
	}
	*e = T->rchild->data;
	free(T->rchild);
	T->rchild = NULL;
	return OK;
}

Status DeleteLeftChild(BiTree T, TElemType* e)
{
	if (T == NULL || T->lchild == NULL)
	{
		return ERROR;
	}
	*e = T->lchild->data;
	free(T->lchild);
	T->lchild = NULL;
	return OK;
}

BiTree Parent(BiTree T, BiTree Node)
{
	if (T->lchild == Node || T->rchild==Node)
	{
		return T;
	}
	return NULL;
}

BiTree RightSibling(BiTree T, BiTree Node)
{
	if (T->lchild == Node)
	{
		return T->rchild;
	}
	return NULL;
}

BiTree LeftSibling(BiTree T, BiTree Node)
{
	if (T->rchild == Node)
	{
		return T->lchild;
	}
	return NULL;
}

BiTree PreOrderTraverse(BiTree T,BiTree Node,BiTree(*visit)(BiTree, BiTree))
{
	BiTree target, pre;
	SqStack Stack;
	SElemType p;

	InitStack(&Stack);
	p = *T;
	Push(&Stack, p);//���ڵ���ջ
	while (!StackEmpty(Stack))//ջ��Ϊ��
	{
		GetTop(Stack, &p);
		if ((target = visit(&p, Node)) != NULL)//���ҵ�
		{
			DestroyStack(&Stack);
			return target;
		}
		if (p.lchild != NULL)
		{
			pre = p.lchild;
			p.lchild = NULL;
			ChangeTop(&Stack, p);//��ֹ���η���
			Push(&Stack, *(pre));
			continue;
		}
		if (p.rchild != NULL)
		{
			pre = p.rchild;
			p.rchild = NULL;
			ChangeTop(&Stack, p);//��ֹ���η���
			Push(&Stack, *(pre));
			continue;
		}
		Pop(&Stack, &p);//��û�в��ҵ���Ҳû�����Һ���pop
	}
	return NULL;//δ���ҵ����
}

void InOrderTraverse(BiTree T)
{
	if (T != NULL)
	{
		InOrderTraverse(T->lchild);
		printf("%c ", T->data);
		InOrderTraverse(T->rchild);
	}
}

/*
int Huffman()
{
	int num, i;
	int* record, count;//���ڼ�¼ɭ������Щ���ʹ�ù�
	double min_1, min_2;
	BiTree* forest;
	BiTree p;
	TElemType e;

	printf("�����빹��Huffman��������:\n");
	scanf_s("%d", &num);

	forest = (BiTree*)malloc(num * sizeof(BiTree));
	record = (int*)malloc(num * sizeof(int));
	if (forest == NULL||record==NULL)
	{
		exit(OVERFLOW);
	}

	for (i = 0; i < num; i++)
	{
		printf("������� %d/%d �����(������):\n",i+1,num);
		forest[i] = 0;//��ʼ��
		scanf_s(" %c", &e,1);
		InitTree(&forest[i], e);
	}
	while (1)
	{
		min_1 = atof(&(forest[0]->data));
		min_2 = atof(&(forest[0]->data));
		for (i = 0; i < num; i++)
		{
			if (record[i] != 1)//�ý���Դ���ɭ����
			{
				if (min_1 > atof(&(forest[i]->data)))
				{
					min_1 = atof(&(forest[i]->data));
				}
				if (min_2 > atof(&(forest[i]->data)) ||
					atof(&(forest[i]->data)) > min_1)
				{
					min_2 = atof(&(forest[i]->data));
				}
			}
		}
	}

}
*/

BiTree BinSortTree(char*arr,int n)
{
	BiTree root, p, pre;
	TElemType e;
	int i,dire=0;//dire��¼���� 0:left 1:right

	//e = (TElemType*)malloc(sizeof(TElemType));
	//_itoa_s(arr[0], e, 1, 10);
	e = arr[0];
	InitTree(&root, e);

	for (i = 1; i < n; i++)
	{
		p = root, pre = root;//ÿ�α���ʱ��ʼ��
		while (p!=NULL)
		{
			if (arr[i] > p->data)//���ڣ���������������
			{
				pre = p;//��¼parent
				dire = 1;
				p = p->rchild;
				continue;
			}
			else
			{
				pre = p;
				dire = 0;
				p = p->lchild;
				continue;
			}
		}
		e = arr[i];
		if (dire == 0)
		{
			InsertLeftChild(pre, e);//����Ϊ������
		}
		else
		{
			InsertRightChild(pre, e);
		}
	}
	return root;
}



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
	for (i = 0; i < Q->QueueNum + 1; i++)//������front���
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
		*e = NULL;
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
		return ERROR;//�ն���
	}
	if (Q->rear == p)//ֻ��һ��Ԫ��
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



/*����һ����ջS*/
Status InitStack(SqStack* S)
{
	(*S).base = (SElemType*)malloc(STACK_INIT_SIZE * sizeof(SElemType));
	//�����ڴ�ռ�
	if ((*S).base == NULL)
	{
		return OVERFLOW;
	}
	(*S).top = (*S).base;
	(*S).stacksize = STACK_INIT_SIZE;
	return OK;
}

/*����ջS*/
Status DestroyStack(SqStack* S)
{
	if ((*S).base != NULL)
	{
		free((*S).base);
		(*S).base = NULL;
	}
	(*S).stacksize = 0;
	return OK;
}

/*��S��Ϊ��ջ*/
Status ClearStack(SqStack* S)
{
	if ((*S).base == NULL)//ջ������
	{
		return ERROR;
	}
	(*S).top = (*S).base;//topָ��ָ��base����
	return OK;
}

/*�ж��Ƿ�Ϊ��ջ*/
Status StackEmpty(SqStack S)
{
	if (S.base == S.top)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/*����ջ��Ԫ�ظ���*/
int StackLength(SqStack S)
{
	int len;

	if (S.top == NULL || S.base == NULL)
	{
		return -1;
	}
	len = S.top - S.base;
	return len;
}

/*��ջ��Ϊ�գ���e����S��ջ��Ԫ��*/
Status GetTop(SqStack S, SElemType* e)
{
	if (StackEmpty(S))//��ջ
	{
		return ERROR;
	}
	*e = *(S.top - 1);
	return OK;
}

/*����Ԫ��eΪջ��Ԫ��
ע�� PUSH����ʱ��Ҫ���ջ�ռ��Ƿ����
*/
Status Push(SqStack* S, SElemType e)
{
	int len;
	SElemType* p;

	if ((*S).base == NULL)//���Ա�����
	{
		return ERROR;
	}
	len = StackLength(*S);
	if (len >= (*S).stacksize)//�ڴ����
	{
		p = (SElemType*)realloc((*S).base
			, sizeof(SElemType) * ((*S).stacksize + STACKINCREMENT));
		if (p == NULL)
		{
			return OVERFLOW;
		}
		(*S).base = p;
		(*S).stacksize += STACKINCREMENT;//ջ��������
		(*S).top = (*S).base + (*S).stacksize;
	}
	*(*S).top = e; //pushֵ
	(*S).top++;    //topָ�����
	return OK;
}

/*��ջ��Ϊ�գ�ɾ��ջ��Ԫ��*/
Status Pop(SqStack* S, SElemType* e)
{
	if ((*S).top == (*S).base)
	{
		return ERROR;
	}
	(*S).top -= 1;
	*e = *((*S).top);
	return OK;
}

Status ChangeTop(SqStack* S, SElemType e)
{
	if (S == NULL || StackEmpty(*S))
	{
		return ERROR;
	}
	*((S->top)-1) = e;
	return OK;
}