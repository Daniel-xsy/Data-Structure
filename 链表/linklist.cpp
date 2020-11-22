/*ʵ�ֶ���ʽ�Ĳ���
    �����ܽ�
    malloc()�������е��������ʹ�С����ָ��ָ����������� �ᴥ���ж�
*/
#include"head.h"

int main()
{
	polynomial La, Lb;
	int m;

	printf("���������ʽLa����\n");
	scanf_s("%d", &m);
	printf("���������ʽLa(������ϵ����������ָ����ָ���ɴ�С)\n");
	CreatPolyn(&La, m);//��������ʽLa
	printf("����ʽLaΪ\n");
	PrintPolyn(La);

	printf("\n���������ʽLb����\n");
	scanf_s("%d", &m);
	printf("���������ʽLb(������ϵ����������ָ����ָ���ɴ�С)\n");
	CreatPolyn(&Lb, m);//��������ʽLb
	printf("����ʽLbΪ\n");
	PrintPolyn(Lb);
	
	printf("\n����ʽ��ӽ��Ϊ\n");
	AddPolyn(&La, &Lb);//����ʽ���
	PrintPolyn(La);
	
	
	return 0;
}

/*����һ���յ����Ա�L,����ͷ���*/
Status InitList(LinkList* L)
{
	(*L) = (LinkList)malloc(sizeof(List));//�����ڴ�ռ�
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

/*�������Ա�*/
Status DestroyList(LinkList* L)
{
	if (*L != NULL)
	{
		free(*L);
		*L = NULL;
	}
	return OK;
}

/*��������L����Ϊ�ձ����ͷ�ԭ����Ľ��ռ�*/
Status ClearList(LinkList* L)
{
	Link ps, pe, p;
	if (*L == NULL)//���Ա�����
	{
		return ERROR;
	}
	ps = (*L)->head;//����ͷ
	p = ps;
	pe = (*L)->tail;//����β
	while (ps != pe)
	{
		ps = ps->next;//����ƶ�
		free(p);      //�ͷ���һ�����
		p = ps;       //����ΪĿǰ���
	}
	free(ps);         //�ͷ�β���
	(*L)->head = NULL;
	(*L)->tail = NULL;
	(*L)->len = 0;    //����������Ϣ
	return OK;
}

/*��֪hָ��ͷ��㣬��sָ��������ڵ�һ�����֮ǰ
ע�� û�и�������lenֵ
*/
Status InsFirst(Link h, Link s)
{
	if (h == NULL)//���Ա����
	{
		return ERROR;
	}
	if (s == NULL)      //s��Ϊ��ָ��
	{
		return ERROR;
	}
	s->next = h->next;
	h->next = s;
	return OK;
}

/*������pָ���ֵΪe�Ľ��*/
Status MakeNode(Link* p, ElemType e)
{
	*p = (Link)malloc(sizeof(LNode));
	if (*p == NULL)
	{
		return ERROR;
	}
	(*p)->data = e;
	(*p)->next = NULL;//ָ����p��ָ������ΪNULL
	return OK;
}

/*�ͷ�p��ָ�Ľ��*/
void FreeNode(Link* p)
{
	if (*p != NULL)
	{
		free(*p);
	}
}

/*��֪hָ��ͷ��㣬ɾ�������е�һ����㲢��q����
ע�� û�и�������lenֵ
*/
Status DelFirst(Link h, Link* q)
{
	if (h->next == NULL)//���Ա����
	{
		return ERROR;
	}
	*q = h->next;
	h->next = (*q)->next; //ͷ���ָ��ڶ���Ԫ��
	return OK;
}

/*��ָ��s��ָ��һ��������������Ա�L�����һ�����
֮�󣬲��ı�����L��βָ��ָ���µĽ��*/
Status Append(LinkList* L, Link s)
{
	int count = 1;

	if ((*L) == NULL)//���Ա����
	{
		return ERROR;
	}
	if (s == NULL)  //s��Ϊ��ָ��
	{
		return ERROR;
	}
	(*L)->tail->next = s;   //���һ��Ԫ��ָ��ָ��s
	while (s->next != NULL) //���������һ��Ԫ��
	{
		s = s->next;
		count++;
	}
	(*L)->tail = s;    //����βָ��ֵ
	(*L)->len += count;//����������
	return OK;
}

/*ɾ�����Ա�L�е�β��㲢��q���أ��ñ�����L��βָ��*/
Status Remove(LinkList* L, Link* q)
{
	Link p;

	if ((*L) == NULL)//���Ա����
	{
		return ERROR;
	}

	*q = (*L)->tail;  //ָ��βԪ��
	p = (*L)->head;
	while (p->next != *q)//������β���
	{
		p = p->next;
	}
	p->next = NULL; //�����ڶ����������Ϊβ���
	(*L)->tail = p; //��������β�����Ϣ
	(*L)->len -= 1; //����������
	return OK;
}

/*��֪pָ�����������е�һ����㣬��s��ָ��������p��ָ���֮ǰ
���޸�ָ��pָ���²���Ľ��*/
Status InsBefore(LinkList* L, Link p, Link s)
{
	Link q;

	if ((*L) == NULL)//���Ա����
	{
		return ERROR;
	}
	if (p == NULL)  //p��Ϊ��ָ��
	{
		return ERROR;
	}
	if (s == NULL) //s��Ϊ��ָ��
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
	(*L)->len++; //����������

	return OK;
}

/*��֪pָ�����������е�һ����㣬��s��ָ��������p��ָ���֮��
���޸�ָ��pָ���²���Ľ��*/
Status InsAfter(LinkList* L, Link* p, Link s)
{
	if ((*L) == NULL)//���Ա����
	{
		return ERROR;
	}
	if (*p == NULL)  //p��Ϊ��ָ��
	{
		return ERROR;
	}
	if (s == NULL)
	{
		return ERROR;
	}
	s->next = (*p)->next;
	(*p)->next = s;
	(*L)->len += 1; //����������
	return OK;
}

/*��֪pָ�����Ա���һ����㣬��e����p��ָ���������Ԫ�ص�ֵ*/
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

/*��֪pָ�����������е�һ����㣬����p��ָ�����Ԫ�ص�ֵ*/
ElemType GetCurElem(Link p)
{
	if (p == NULL)
	{
		printf("p in GetCurElem is NULL");
		exit(1);
	}
	return p->data;
}

/*�ж����Ա��Ƿ�Ϊ�ձ�*/
Status ListEmpty(LinkList L)
{
	if (L == NULL)
	{
		return ERROR;
	}
	if (L->head == NULL && L->tail == NULL && L->len == 0)
	{
		return 1; //Ϊ�ձ�
	}
	else
	{
		return 0; //��Ϊ�ձ�
	}
}

/*�������Ա�L��Ԫ�ظ���*/
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

/*������������L��ͷ����λ��*/
Position GetHead(LinkList L)
{
	if (L == NULL)
	{
		return ERROR;
	}
	return L->head;
}

/*������������L�����һ������λ��*/
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

/*��֪pָ�����������е�һ����㣬����p��ָ����ֱ��ǰ����λ��*/
Position PriorPos(LinkList L, Link p)
{
	Link q;

	if (L == NULL)
	{
		return ERROR;
	}
	q = L->head;
	if (q->next == p)//pΪ�����һ��Ԫ�� ��ֱ��ǰ��
	{
		return NULL;
	}
	while (q->next != p)
	{
		q = q->next;
	}
	return q;
}

/*��֪pָ�����������е�һ����㣬����p��ָ����ֱ�Ӻ�̵�λ��*/
Position NextPos(LinkList L, Link p)
{
	Link q;

	if (L == NULL)
	{
		return ERROR;
	}
	q = L->tail;
	if (q == p)//pΪ��������һ��Ԫ�� ��ֱ�Ӻ���
	{
		return NULL;
	}
	return p->next;
}

/*����pָʾ��������L�е�i������λ�ò�����OK��iֵ���Ϸ�����ERROR*/
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
	if (count >= i) //iֵ���Ϸ�
	{
		return ERROR;
	}
	*p = q;
	return OK;
}

/*����ab��ָ����С����ֵ*/
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

/*����m��ϵ����ָ��������һԪ����ʽ����������P
ע�� ����β��ͷ���� �����������β���*/
void CreatPolyn(polynomial* P, int m)
{
	Link h,s;
	ElemType e;
	int i;

	InitList(P);
	h=GetHead(*P);
	e.coef = 0.0, e.expn = -1;
	SetCurElem(&h, e); //����ͷ���ֵ

	for (i = 0; i < m; i++)
	{
		scanf_s("%f %d", &(e.coef), &(e.expn));
		if (MakeNode(&s, e))//����һ���ڴ�ռ�s ����ֵΪe
		{
			InsFirst(h, s); //��s���������һ�����֮ǰ
		}
	}
	(*P)->tail = GetLast(*P);//βָ�����
}

/*����һԪ����ʽP*/
void DestroyPolyn(polynomial* P)
{
	DestroyList(P);
}

/*��ӡ���һԪ����ʽP*/
void PrintPolyn(polynomial P)
{
	Link p;
	int count = 0;
	
	if (P == NULL)
	{
		printf("P is NULL in PrintPolyn");
		exit(ERROR);
	}
	p = P->head;//p��ͷָ�뿪ʼ
	while (p != P->tail&&p->next!=NULL)
	{
		p = p->next;
		count++;
		printf("��%d�� ϵ����%.2f ָ����%d\n",count, p->data.coef, p->data.expn);
	}
}

/*����һԪ����ʽ�е�����*/
int PolynLength(polynomial P)
{
	if (P == NULL)
	{
		printf("P is NULL is PolynLength");
		exit(ERROR);
	}
	return ListLength(P);
}

/*��ɶ���ʽ���������*/
void AddPolyn(polynomial* Pa, polynomial* Pb)
{
	Link ha, hb, qa, qb;
	ElemType a, b, sum;

	ha = GetHead(*Pa), hb = GetHead(*Pb);//ha,hb�ֱ�ָ��ͷ���
	qa = NextPos(*Pa, ha), qb = NextPos(*Pb, hb);
	while (qa != NULL && qb != NULL)
	{
		a = GetCurElem(qa), b = GetCurElem(qb);//ȡ�ý��Ԫ��ֵ
		switch (cmp(a,b))//�Ƚ�ָ����С
		{
		case 1:  //a��ָ������
			DelFirst(hb, &qb);//qb����b��Ԫ��
			InsFirst(ha, qb);//�Ѹ�Ԫ�ز��뵽ha֮��
			qb = NextPos(*Pb, hb);//����pbֵ 
			ha = NextPos(*Pa, ha);//����haֵΪ�ղŲ�����
			break;
		case 0:  //ָ����ͬ
			sum.expn = a.expn;
			sum.coef = a.coef + b.coef;
			if (sum.coef != 0)//ϵ����Ӳ�Ϊ0
			{
				SetCurElem(&qa, sum);//��sum���¸ý������
				ha = qa;
			}
			else              //ϵ�����Ϊ0
			{
				DelFirst(ha, &qa);//ɾ��La�иý��
				FreeNode(&qa);
			}
			DelFirst(hb, &qb);//����ָ���Ƿ���ȶ�Ҫɾ��Lb��Ӧ���
			FreeNode(&qb);
			qb = NextPos(*Pb, hb);
			qa = NextPos(*Pa, ha);
			break;
		case -1: //a��ָ����С
			ha = qa;
			qa = NextPos(*Pa, qa);
			break;
		default:
			break;
		}//switch
	}//while
	if (!ListEmpty(*Pb)) //����Pb��ʣ����
	{
		Append(Pa, qb); 
	}
	FreeNode(&hb);
}