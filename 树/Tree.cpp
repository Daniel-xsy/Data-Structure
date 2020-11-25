#include"Tree.h"

int main(void)
{
	/*
	BiTree Root, target;
	int depth, n;

	Root = CreateTree();
	target=PreOrderTraverse(Root, Root->rchild->rchild, LeftSibling);
	depth = TreeDepth(Root);
	printf("该树的深度为: %d \n", depth);
	*/
	char* arr;
	int n, depth;
	BiTree Root;

	printf("请输入待排序数个数:\n");
	scanf_s("%d", &n);
	arr = (char*)malloc(n * sizeof(char));
	if (arr == NULL)
	{
		exit(OVERFLOW);
	}
	for (int i = 0; i < n; i++)
	{
		printf("请输入第 %d / %d 个字符:\n",i+1,n);
		scanf_s(" %c", &(arr[i]));
	}

	printf("生成排序树...\n");
	Root = BinSortTree(arr, n);
	depth = TreeDepth(Root);
	printf("树深度为: %d\n", depth);
	printf("中序打印排序树:\n");
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

	printf("请输入根节点(#退出):\n");
	scanf_s(" %c", &e,1);
	if (e == '#')
	{
		return NULL;
	}
	InitTree(&Root, e);
	InitQueue(&Queue);

	EnQueue(&Queue, Root);//根结点入队

	NodeNum = 2, layer = 1;
	while (Queue.QueueNum!=0)
	{
		NodeNum = 2*Queue.QueueNum;
		printf("请依次输入第 %d 层结点,共 %d 个(#:退出 *空):\n",layer,NodeNum);
		for (i = 0; i < NodeNum; i++)
		{
			scanf_s(" %c", &e,1);
			if (e == '#')//退出
			{
				return Root;
			}
			if (e != '*')
			{
				if (i % 2 == 0)//i是偶数 结点一定为左孩子
				{
					GetHead(Queue, &Parent);//队首
					InsertLeftChild(Parent, e);//插入为左孩子
					EnQueue(&Queue, Parent->lchild);//入队
					continue;
				}
				else//i是奇数 结点一定为右孩子
				{
					GetHead(Queue, &Parent);
					InsertRightChild(Parent, e);//插入为右孩子
					EnQueue(&Queue, Parent->rchild);//右孩子入队
				}
			}
			if (i % 2 == 1)
			{
				DelHead(&Queue);//删除队首
			}
		}
		layer++;
	}
	DestroyQueue(&Queue);
	return Root;
}

void PrintTree(BiTree T)
{
	QLinklist Queue;//广度优先算法 使用队列
	BiTree p;

	InitQueue(&Queue);
	if (T != NULL)
	{
		p = T;
		EnQueue(&Queue, p);
		while (Queue.QueueNum != 0)//队列不为空
		{
			GetHead(Queue, &p);
			printf("p.");//如何区分不同层级???
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
	Push(&Stack, p);//根节点入栈
	while (!StackEmpty(Stack))//栈不为空
	{
		GetTop(Stack, &p);
		if ((target = visit(&p, Node)) != NULL)//查找到
		{
			DestroyStack(&Stack);
			return target;
		}
		if (p.lchild != NULL)
		{
			pre = p.lchild;
			p.lchild = NULL;
			ChangeTop(&Stack, p);//防止二次访问
			Push(&Stack, *(pre));
			continue;
		}
		if (p.rchild != NULL)
		{
			pre = p.rchild;
			p.rchild = NULL;
			ChangeTop(&Stack, p);//防止二次访问
			Push(&Stack, *(pre));
			continue;
		}
		Pop(&Stack, &p);//既没有查找到，也没有左右孩子pop
	}
	return NULL;//未查找到结果
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
	int* record, count;//用于记录森林中哪些结点使用过
	double min_1, min_2;
	BiTree* forest;
	BiTree p;
	TElemType e;

	printf("请输入构造Huffman树结点个数:\n");
	scanf_s("%d", &num);

	forest = (BiTree*)malloc(num * sizeof(BiTree));
	record = (int*)malloc(num * sizeof(int));
	if (forest == NULL||record==NULL)
	{
		exit(OVERFLOW);
	}

	for (i = 0; i < num; i++)
	{
		printf("请输入第 %d/%d 个结点(浮点数):\n",i+1,num);
		forest[i] = 0;//初始化
		scanf_s(" %c", &e,1);
		InitTree(&forest[i], e);
	}
	while (1)
	{
		min_1 = atof(&(forest[0]->data));
		min_2 = atof(&(forest[0]->data));
		for (i = 0; i < num; i++)
		{
			if (record[i] != 1)//该结点仍存在森林中
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
	int i,dire=0;//dire记录左右 0:left 1:right

	//e = (TElemType*)malloc(sizeof(TElemType));
	//_itoa_s(arr[0], e, 1, 10);
	e = arr[0];
	InitTree(&root, e);

	for (i = 1; i < n; i++)
	{
		p = root, pre = root;//每次遍历时初始化
		while (p!=NULL)
		{
			if (arr[i] > p->data)//大于，则向右子树查找
			{
				pre = p;//记录parent
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
			InsertLeftChild(pre, e);//插入为左子树
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



/*构造一个空栈S*/
Status InitStack(SqStack* S)
{
	(*S).base = (SElemType*)malloc(STACK_INIT_SIZE * sizeof(SElemType));
	//分配内存空间
	if ((*S).base == NULL)
	{
		return OVERFLOW;
	}
	(*S).top = (*S).base;
	(*S).stacksize = STACK_INIT_SIZE;
	return OK;
}

/*销毁栈S*/
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

/*把S置为空栈*/
Status ClearStack(SqStack* S)
{
	if ((*S).base == NULL)//栈不存在
	{
		return ERROR;
	}
	(*S).top = (*S).base;//top指针指向base即可
	return OK;
}

/*判断是否为空栈*/
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

/*计算栈的元素个数*/
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

/*若栈不为空，用e返回S的栈顶元素*/
Status GetTop(SqStack S, SElemType* e)
{
	if (StackEmpty(S))//空栈
	{
		return ERROR;
	}
	*e = *(S.top - 1);
	return OK;
}

/*插入元素e为栈顶元素
注意 PUSH操作时需要检测栈空间是否溢出
*/
Status Push(SqStack* S, SElemType e)
{
	int len;
	SElemType* p;

	if ((*S).base == NULL)//线性表不存在
	{
		return ERROR;
	}
	len = StackLength(*S);
	if (len >= (*S).stacksize)//内存溢出
	{
		p = (SElemType*)realloc((*S).base
			, sizeof(SElemType) * ((*S).stacksize + STACKINCREMENT));
		if (p == NULL)
		{
			return OVERFLOW;
		}
		(*S).base = p;
		(*S).stacksize += STACKINCREMENT;//栈容量更新
		(*S).top = (*S).base + (*S).stacksize;
	}
	*(*S).top = e; //push值
	(*S).top++;    //top指针更新
	return OK;
}

/*若栈不为空，删除栈顶元素*/
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