/*实现多项式的操作
    调试总结
    malloc()若括号中的数据类型大小不是指针指向的数据类型 会触发中断
*/
#include"head.h"

int main()
{
	polynomial La, Lb;
	int m;

	printf("请输入多项式La项数\n");
	scanf_s("%d", &m);
	printf("请输入多项式La(先输入系数，再输入指数，指数由大到小)\n");
	CreatPolyn(&La, m);//创建多项式La
	printf("多项式La为\n");
	PrintPolyn(La);

	printf("\n请输入多项式Lb项数\n");
	scanf_s("%d", &m);
	printf("请输入多项式Lb(先输入系数，再输入指数，指数由大到小)\n");
	CreatPolyn(&Lb, m);//创建多项式Lb
	printf("多项式Lb为\n");
	PrintPolyn(Lb);
	
	printf("\n多项式相加结果为\n");
	AddPolyn(&La, &Lb);//多项式相加
	PrintPolyn(La);
	
	
	return 0;
}

/*构造一个空的线性表L,创建头结点*/
Status InitList(LinkList* L)
{
	(*L) = (LinkList)malloc(sizeof(List));//分配内存空间
	if ((*L) == NULL)
	{
		return OVERFLOW;
	}
	(*L)->head = (Link)malloc(sizeof(LNode));
	if ((*L)->head == NULL)
	{
		printf("memory ditribution error in InitList");
		exit(ERROR);
	}
	(*L)->head->next = NULL;
	(*L)->tail = NULL;
	(*L)->len = 0;
	return OK;
}

/*销毁线性表*/
Status DestroyList(LinkList* L)
{
	if (*L != NULL)
	{
		free(*L);
		*L = NULL;
	}
	return OK;
}

/*将线链表L重置为空表，并释放原链表的结点空间*/
Status ClearList(LinkList* L)
{
	Link ps, pe, p;
	if (*L == NULL)//线性表不存在
	{
		return ERROR;
	}
	ps = (*L)->head;//链表头
	p = ps;
	pe = (*L)->tail;//链表尾
	while (ps != pe)
	{
		ps = ps->next;//结点移动
		free(p);      //释放上一个结点
		p = ps;       //更新为目前结点
	}
	free(ps);         //释放尾结点
	(*L)->head = NULL;
	(*L)->tail = NULL;
	(*L)->len = 0;    //更新链表信息
	return OK;
}

/*已知h指向头结点，将s指向结点插入在第一个结点之前
注意 没有更新链表len值
*/
Status InsFirst(Link h, Link s)
{
	if (h == NULL)//线性表存在
	{
		return ERROR;
	}
	if (s == NULL)      //s不为空指针
	{
		return ERROR;
	}
	s->next = h->next;
	h->next = s;
	return OK;
}

/*分配由p指向的值为e的结点*/
Status MakeNode(Link* p, ElemType e)
{
	*p = (Link)malloc(sizeof(LNode));
	if (*p == NULL)
	{
		return ERROR;
	}
	(*p)->data = e;
	(*p)->next = NULL;//指向后把p的指针设置为NULL
	return OK;
}

/*释放p所指的结点*/
void FreeNode(Link* p)
{
	if (*p != NULL)
	{
		free(*p);
	}
}

/*已知h指向头结点，删除链表中第一个结点并以q返回
注意 没有更新链表len值
*/
Status DelFirst(Link h, Link* q)
{
	if (h->next == NULL)//线性表存在
	{
		return ERROR;
	}
	*q = h->next;
	h->next = (*q)->next; //头结点指向第二个元素
	return OK;
}

/*将指针s所指的一串结点链接在线性表L的最后一个结点
之后，并改变链表L的尾指针指向新的结点*/
Status Append(LinkList* L, Link s)
{
	int count = 1;

	if ((*L) == NULL)//线性表存在
	{
		return ERROR;
	}
	if (s == NULL)  //s不为空指针
	{
		return ERROR;
	}
	(*L)->tail->next = s;   //最后一个元素指针指向s
	while (s->next != NULL) //索引至最后一个元素
	{
		s = s->next;
		count++;
	}
	(*L)->tail = s;    //更新尾指针值
	(*L)->len += count;//更新链表长度
	return OK;
}

/*删除线性表L中的尾结点并以q返回，该表链表L的尾指针*/
Status Remove(LinkList* L, Link* q)
{
	Link p;

	if ((*L) == NULL)//线性表存在
	{
		return ERROR;
	}

	*q = (*L)->tail;  //指向尾元素
	p = (*L)->head;
	while (p->next != *q)//索引到尾结点
	{
		p = p->next;
	}
	p->next = NULL; //倒数第二个结点设置为尾结点
	(*L)->tail = p; //更新链表尾结点信息
	(*L)->len -= 1; //更新链表长度
	return OK;
}

/*已知p指向线性链表中的一个结点，将s所指结点插入在p所指结点之前
并修改指针p指向新插入的结点*/
Status InsBefore(LinkList* L, Link p, Link s)
{
	Link q;

	if ((*L) == NULL)//线性表存在
	{
		return ERROR;
	}
	if (p == NULL)  //p不为空指针
	{
		return ERROR;
	}
	if (s == NULL) //s不为空指针
	{
		return ERROR;
	}
	q = (*L)->head;
	while (q->next != p)
	{
		q = q->next;
	}
	s->next = p;
	q->next = s;
	(*L)->len++; //更新链表长度

	return OK;
}

/*已知p指向线性链表中的一个结点，将s所指结点插入在p所指结点之后
并修改指针p指向新插入的结点*/
Status InsAfter(LinkList* L, Link* p, Link s)
{
	if ((*L) == NULL)//线性表存在
	{
		return ERROR;
	}
	if (*p == NULL)  //p不为空指针
	{
		return ERROR;
	}
	if (s == NULL)
	{
		return ERROR;
	}
	s->next = (*p)->next;
	(*p)->next = s;
	(*L)->len += 1; //更新链表长度
	return OK;
}

/*已知p指向线性表中一个结点，用e更新p所指结点中数据元素的值*/
Status SetCurElem(Link* p, ElemType e)
{
	if (*p == NULL)
	{
		return ERROR;
	}
	(*p)->data.coef = e.coef;
	(*p)->data.expn = e.expn;
	return OK;
}

/*已知p指向线性链表中的一个结点，返回p所指结点中元素的值*/
ElemType GetCurElem(Link p)
{
	if (p == NULL)
	{
		printf("p in GetCurElem is NULL");
		exit(1);
	}
	return p->data;
}

/*判断线性表是否为空表*/
Status ListEmpty(LinkList L)
{
	if (L == NULL)
	{
		return ERROR;
	}
	if (L->head == NULL && L->tail == NULL && L->len == 0)
	{
		return 1; //为空表
	}
	else
	{
		return 0; //不为空表
	}
}

/*返回线性表L中元素个数*/
int ListLength(LinkList L)
{
	int count = 0;
	Link p;

	if (L == NULL)
	{
		return ERROR;
	}
	p = L->head;
	while (p != L->tail)
	{
		p = p->next;
		count++;
	}
	count++;
	return count;
}

/*返回线性链表L中头结点的位置*/
Position GetHead(LinkList L)
{
	if (L == NULL)
	{
		return ERROR;
	}
	return L->head;
}

/*返回线性链表L中最后一个结点的位置*/
Position GetLast(LinkList L)
{
	Link p;
	if (L == NULL)
	{
		return ERROR;
	}
	p = L->head;
	while (p->next != NULL)
	{
		p = p->next;
	}
	return p;
}

/*已知p指向线性链表中的一个结点，返回p所指结点的直接前驱的位置*/
Position PriorPos(LinkList L, Link p)
{
	Link q;

	if (L == NULL)
	{
		return ERROR;
	}
	q = L->head;
	if (q->next == p)//p为链表第一个元素 无直接前驱
	{
		return NULL;
	}
	while (q->next != p)
	{
		q = q->next;
	}
	return q;
}

/*已知p指向线性链表中的一个结点，返回p所指结点的直接后继的位置*/
Position NextPos(LinkList L, Link p)
{
	Link q;

	if (L == NULL)
	{
		return ERROR;
	}
	q = L->tail;
	if (q == p)//p为链表第最后一个元素 无直接后驱
	{
		return NULL;
	}
	return p->next;
}

/*返回p指示线性链表L中第i个结点的位置并返回OK，i值不合法返回ERROR*/
Status LocatePos(LinkList L, int i, Link* p)
{
	Link q = L->head;
	int count = 0;

	if (L == NULL)
	{
		return ERROR;
	}
	while (count < i && q != NULL)
	{
		q = q->next;
		count++;
	}
	if (count >= i) //i值不合法
	{
		return ERROR;
	}
	*p = q;
	return OK;
}

/*按照ab中指数大小返回值*/
int cmp(term a, term b)
{
	if (a.expn > b.expn)
	{
		return 1;
	}
	else if (a.expn == b.expn)
	{
		return 0;
	}
	else
	{
		return -1;
	}
}

/*输入m项系数和指数，建立一元多项式的有序链表P
注意 是由尾到头创建 最先输入的是尾结点*/
void CreatPolyn(polynomial* P, int m)
{
	Link h,s;
	ElemType e;
	int i;

	InitList(P);
	h=GetHead(*P);
	e.coef = 0.0, e.expn = -1;
	SetCurElem(&h, e); //设置头结点值

	for (i = 0; i < m; i++)
	{
		scanf_s("%f %d", &(e.coef), &(e.expn));
		if (MakeNode(&s, e))//分配一块内存空间s 数据值为e
		{
			InsFirst(h, s); //把s插入链表第一个结点之前
		}
	}
	(*P)->tail = GetLast(*P);//尾指针更新
}

/*销毁一元多项式P*/
void DestroyPolyn(polynomial* P)
{
	DestroyList(P);
}

/*打印输出一元多项式P*/
void PrintPolyn(polynomial P)
{
	Link p;
	int count = 0;
	
	if (P == NULL)
	{
		printf("P is NULL in PrintPolyn");
		exit(ERROR);
	}
	p = P->head;//p从头指针开始
	while (p != P->tail&&p->next!=NULL)
	{
		p = p->next;
		count++;
		printf("第%d项 系数：%.2f 指数：%d\n",count, p->data.coef, p->data.expn);
	}
}

/*返回一元多项式中的项数*/
int PolynLength(polynomial P)
{
	if (P == NULL)
	{
		printf("P is NULL is PolynLength");
		exit(ERROR);
	}
	return ListLength(P);
}

/*完成多项式的相加运算*/
void AddPolyn(polynomial* Pa, polynomial* Pb)
{
	Link ha, hb, qa, qb;
	ElemType a, b, sum;

	ha = GetHead(*Pa), hb = GetHead(*Pb);//ha,hb分别指向头结点
	qa = NextPos(*Pa, ha), qb = NextPos(*Pb, hb);
	while (qa != NULL && qb != NULL)
	{
		a = GetCurElem(qa), b = GetCurElem(qb);//取该结点元素值
		switch (cmp(a,b))//比较指数大小
		{
		case 1:  //a的指数更大
			DelFirst(hb, &qb);//qb返回b中元素
			InsFirst(ha, qb);//把该元素插入到ha之后
			qb = NextPos(*Pb, hb);//更新pb值 
			ha = NextPos(*Pa, ha);//更新ha值为刚才插入结点
			break;
		case 0:  //指数相同
			sum.expn = a.expn;
			sum.coef = a.coef + b.coef;
			if (sum.coef != 0)//系数相加不为0
			{
				SetCurElem(&qa, sum);//用sum更新该结点数据
				ha = qa;
			}
			else              //系数相加为0
			{
				DelFirst(ha, &qa);//删除La中该结点
				FreeNode(&qa);
			}
			DelFirst(hb, &qb);//无论指数是否相等都要删除Lb相应结点
			FreeNode(&qb);
			qb = NextPos(*Pb, hb);
			qa = NextPos(*Pa, ha);
			break;
		case -1: //a的指数更小
			ha = qa;
			qa = NextPos(*Pa, qa);
			break;
		default:
			break;
		}//switch
	}//while
	if (!ListEmpty(*Pb)) //链接Pb中剩余结点
	{
		Append(Pa, qb); 
	}
	FreeNode(&hb);
}