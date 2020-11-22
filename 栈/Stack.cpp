#include"head.h"

int main()
{
	extern MazeType maze;//ͷ�ļ��ж����Թ�

	PosType start = {1,1}; 
	PosType end = {8,8};//����������յ�
	if (!MazePath(maze, start, end))
	{
		printf("���ܴ���㵽�յ�");
	}
	return 0;
}

/*����һ����ջS*/
Status InitStack(SqStack* S)
{
	(*S).base = (SElemType*)malloc(STACK_INIT_SIZE*sizeof(SElemType));
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
	if (!StackEmpty(S))//��ջ
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
			,sizeof(SElemType) * ((*S).stacksize + STACKINCREMENT));
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

/*�Թ����� 
�ж��Թ�maze���Ƿ���ڴ���ڵ����ڵ�ͨ��
·������ջ��
����ӡ��·��*/
Status MazePath(MazeType maze, PosType start, PosType end)
{
	PosType curpos;
	SElemType e;
	SqStack S;
	int curstep = 1;

	InitStack(&S);   //��ʼ��ջ
	curpos = start;  //���ڵ�λ���趨Ϊ��ʼλ��
	do
	{
		if (Pass(curpos))//��ǰλ�ÿ�ͨ
		{
			FootPrint(curpos);//�����㼣
			e.order = curstep, e.seat = curpos, e.dire = 1;
			/*direΪ1 Ĭ���ȳ������ƶ� 
			�߼������ƶ� ���жϵ�Ȼλ���Ƿ����*/
			Push(&S, e);
			if (curpos.x == end.x && curpos.y == end.y)//�����յ�
			{
				PrintPath(S);
				return TURE;
			}
			curpos = NextPos(curpos, 1);//���ƶ�
			curstep++;
	    }//if
		else //��ǰλ�ò���ͨ��
		{
			if (!StackEmpty(S))
			{
				Pop(&S, &e);
				while (e.dire==4&&!StackEmpty(S))
				//dire=4��ʾ��λ�����з����߹���
				{
					MarkPrint(e.seat);
					Pop(&S, &e);
				}//while
				if (e.dire < 4)
				//��һ������������
				{
					e.dire++;
					Push(&S, e);
					curpos = NextPos(e.seat, e.dire);
				}//if
			}//if
		}//else
	} while (!StackEmpty(S));//��ջ��Ϊ��ʱһֱѰ��
	return FALSE;//ջ�����޷��ҵ�·��
}

/*�жϵ�ǰλ���Ƿ����ͨ��*/
Status Pass(PosType p)
{
	if (maze[p.y][p.x] == 1)
	//mark=2��ʾ�Ѿ��߹� mark=-1��ʾ��ȫ��ͨ maze�ж��Ƿ�Ϊǽ��
	{
		return 1;
	}
	return 0;
}

void FootPrint(PosType p)
{
	maze[p.y][p.x] = 2;//���Թ��иõ�λ����Ϊ2 ��ʾ�Ѿ���
}

PosType NextPos(PosType p, int dire)
{
	switch (dire)
	{
	case 1://���ƶ�
		p.x += 1;
		break;
	case 2://�����ƶ�
		p.y += 1;
		break;
	case 3://�����ƶ�
		p.x -= 1;
		break;
	case 4://���ƶ�
		p.y -= 1;
		break;
	default:
		break;
	}
	return p;
}

void MarkPrint(PosType p)
{
	maze[p.y][p.x] = -1; //�Թ�������������һ����
}

/*��ӡ·��*/
void PrintPath(SqStack S)
{
	SElemType* p;
	p = S.base;
	printf("·��Ϊ\n");
	printf("��1:�� 2:�� 3:�� 4:����\n");
	while (p<S.top-1)
	{
		printf("��%d�� %d %d ��%d�����ƶ�\n"
			, p->order, p->seat.x, p->seat.y, p->dire);
		p++;
	}
	printf("��%d�� %d %d �����յ�\n",p->order, p->seat.x, p->seat.y);
}