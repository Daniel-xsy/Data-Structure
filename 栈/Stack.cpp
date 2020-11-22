#include"head.h"

int main()
{
	extern MazeType maze;//头文件中定义迷宫

	PosType start = {1,1}; 
	PosType end = {8,8};//设置起点与终点
	if (!MazePath(maze, start, end))
	{
		printf("不能从起点到终点");
	}
	return 0;
}

/*构造一个空栈S*/
Status InitStack(SqStack* S)
{
	(*S).base = (SElemType*)malloc(STACK_INIT_SIZE*sizeof(SElemType));
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
	if (!StackEmpty(S))//空栈
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
			,sizeof(SElemType) * ((*S).stacksize + STACKINCREMENT));
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

/*迷宫代码 
判断迷宫maze中是否存在从入口到出口的通道
路径存在栈中
并打印出路径*/
Status MazePath(MazeType maze, PosType start, PosType end)
{
	PosType curpos;
	SElemType e;
	SqStack S;
	int curstep = 1;

	InitStack(&S);   //初始化栈
	curpos = start;  //现在的位置设定为开始位置
	do
	{
		if (Pass(curpos))//当前位置可通
		{
			FootPrint(curpos);//留下足迹
			e.order = curstep, e.seat = curpos, e.dire = 1;
			/*dire为1 默认先尝试向东移动 
			逻辑是先移动 再判断当然位置是否可行*/
			Push(&S, e);
			if (curpos.x == end.x && curpos.y == end.y)//到达终点
			{
				PrintPath(S);
				return TURE;
			}
			curpos = NextPos(curpos, 1);//向东移动
			curstep++;
	    }//if
		else //当前位置不能通过
		{
			if (!StackEmpty(S))
			{
				Pop(&S, &e);
				while (e.dire==4&&!StackEmpty(S))
				//dire=4表示该位置所有方向都走过了
				{
					MarkPrint(e.seat);
					Pop(&S, &e);
				}//while
				if (e.dire < 4)
				//逐一尝试其他方向
				{
					e.dire++;
					Push(&S, e);
					curpos = NextPos(e.seat, e.dire);
				}//if
			}//if
		}//else
	} while (!StackEmpty(S));//当栈不为空时一直寻径
	return FALSE;//栈空则无法找到路径
}

/*判断当前位置是否可以通过*/
Status Pass(PosType p)
{
	if (maze[p.y][p.x] == 1)
	//mark=2表示已经走过 mark=-1表示完全不通 maze判断是否为墙内
	{
		return 1;
	}
	return 0;
}

void FootPrint(PosType p)
{
	maze[p.y][p.x] = 2;//将迷宫中该点位置设为2 表示已经过
}

PosType NextPos(PosType p, int dire)
{
	switch (dire)
	{
	case 1://向东移动
		p.x += 1;
		break;
	case 2://向南移动
		p.y += 1;
		break;
	case 3://向西移动
		p.x -= 1;
		break;
	case 4://向北移动
		p.y -= 1;
		break;
	default:
		break;
	}
	return p;
}

void MarkPrint(PosType p)
{
	maze[p.y][p.x] = -1; //迷宫中永久性拉黑一个点
}

/*打印路径*/
void PrintPath(SqStack S)
{
	SElemType* p;
	p = S.base;
	printf("路径为\n");
	printf("（1:东 2:南 3:西 4:北）\n");
	while (p<S.top-1)
	{
		printf("第%d步 %d %d 向%d方向移动\n"
			, p->order, p->seat.x, p->seat.y, p->dire);
		p++;
	}
	printf("第%d步 %d %d 到达终点\n",p->order, p->seat.x, p->seat.y);
}