#include"mystring.h"
#include<stdio.h>

int main(void)
{
	SString text;
	char command = '1';
	SString change1, change2;
	int pos, len;

	printf("请输入文本\n");
	gets(text);
	while (command != 0)
	{
		command = menu();

		switch (command)
		{
		case 1:
			getchar();
			printf("请输入被替换的文本:\n");
			gets(change1);
			printf("请输入替换文本\n");
			gets(change2);
			Replace(&text, change1, change2);
			break;
		case 2:
			getchar();
			printf("请输入要插入的文本:\n");
			gets(change1);
			printf("请选择要插入的位置\n");
			scanf_s("%d", &pos);
			StrInsert(&text, pos, change1);
			break;
		case 3:
			printf("请输入要删除的位置与长度\n");
			scanf_s("%d %d", &pos, &len);
			StrDelete(&text, pos, len);
			break;
		case 4:
			printf("请输入要增添的文本\n");
			getchar();
			gets(change1);
			StrCopy(&change2, text);
			Concat(&text, change2, change1);
			break;
		case 5:
			getchar();
			ClearString(&text);
			printf("删除成功\n");
			break;
		default:
			break;
		}
		printf("%s\n", text);
	}
}

int menu(void)
{
	int i;
	int command;
	for (i = 0; i < 25; i++)
	{
		printf("-");
	}
	printf("\n1: replace\n");
	printf("2: insert\n");
	printf("3: delete\n");
	printf("4: add\n");
	printf("5: clear\n");
	printf("0: quit\n");
	for (i = 0; i < 25; i++)
	{
		printf("-");
	}
	printf("\n请选择操作:\n");
	scanf_s("%d", &command);
	while (command > 5 || command < 0)
	{
		printf("输入有误！请重新输入:\n");
		scanf_s("%d", &command);
	}
	return command;
}

Status StrCopy(SString* T, char* S)
{
	int strlen;
	int i;
	char* pt, * ps;

	if (S == NULL || *T == NULL)
	{
		return ERROR;
	}

	strlen = StrLength(S);
	pt = *T, ps = S;
	for (i = 0; i < strlen; i++)
	{
		*pt++ = *ps++;
	}
	*pt = '\0';
	return OK;
}

Status StrEmpty(SString S)
{
	if (S == NULL)
	{
		return ERROR;
	}

	if (StrLength(S) == 0)
	{
		return TRUE;
	}
	return FALSE;
}

Status StrCompare(SString S, SString T)
{
	int strlen, i;
	char* ps, * pt;

	if (S == NULL || T == NULL)
	{
		return -2;
	}

	ps = S, pt = T;
	strlen = StrLength(S) < StrLength(T) ? 
		StrLength(S) : StrLength(T);
	for (i = 0; i < strlen; i++)
	{
		if (*ps == *pt)
		{
			ps++, pt++;
			continue;
		}
		return *ps - *pt > 0 ? 1 : -1;
	}
	return 0;
}

Status ClearString(SString* S)
{
	if (*S == NULL)
	{
		return ERROR;
	}

	*(*S) = '\0';
	return OK;
}

Status Concat(SString* T, SString S1, SString S2)
{
	char* pt,*ps;
	int strlen, i;
	if (S1 == NULL || S2 == NULL)
	{
		return ERROR;
	}

	pt = *T;
	ps = S1;
	strlen = StrLength(S1);
	for (i = 0; i < strlen; i++)
	{
		*pt++ = *ps++;
	}
	ps = S2;
	for (i = 0; i < (MAXSTRLEN < strlen + StrLength(S2) ?
		MAXSTRLEN - strlen : StrLength(S2));i++)
	{
		*pt++ = *ps++;
	}
	*pt = '\0';
	return OK;
}

//没有统计'\0'
int StrLength(SString S)
{
	char* ch;
	int count;

	if (S == NULL)
	{
		return ERROR;
	}

	for (ch = S, count = 0; *ch != '\0'; count++,ch++);
	return count;
}

Status SubString(SString* Sub, SString S, int len, int pos)
{
	char* psub, * ps;
	int strlen, i;
	if (S == NULL || pos<0 || pos>MAXSTRLEN - 1)
	{
		return ERROR;
	}
	
	psub = *Sub;
	ps = S;
	strlen = len + pos < MAXSTRLEN ? len + pos : MAXSTRLEN;
	for (i = 0; i < pos; i++)
	{
		ps++;
	}
	for (i = pos; i < strlen; i++)
	{
		*psub++ = *ps++;
	}
	*psub = '\0';
	return OK;
}

Status Index(SString S, SString T, int pos)
{
	int i;
	SString substr;
	if (S == NULL || StrLength(T) == 0
		|| pos<0 || pos>MAXSTRLEN - 1)
	{
		return -1;
	}
	if (StrLength(T) + pos > MAXSTRLEN)
	{
		return -1;
	}

	for (i = 0; i < StrLength(S) - StrLength(T)-pos + 1; i++)
	{
		SubString(&substr, S, StrLength(T), pos+i);
		if (StrCompare(substr, T) == 0)
		{
			return pos + i;
		}
	}
	return -1;
}


Status Replace(SString* S, SString T, SString V)
{
	int index;
	int strlenT, strlenV;

	if (*S == NULL || T == NULL || V == NULL)
	{
		return ERROR;
	}

	strlenT = StrLength(T);
	strlenV = StrLength(V);
	index = Index(*S, T, 0);
	while (index != -1)
	{
		StrDelete(S, index, strlenT);
		StrInsert(S, index, V);
		index = Index(*S, T, index + strlenV);
	}
    return OK;
}


Status StrInsert(SString* S, int pos, SString T)
{
	char* pcur, * pt, * pnew;
	int strlen,i;
	int strlens;

	strlen = StrLength(T);
	strlens = StrLength(*S);
	if (strlen + strlens > MAXSTRLEN)
	{
		return ERROR;
	}
	if (pos<0 || pos>strlens)
	{
		return ERROR;
	}
	pcur = *S, pt = T;
	pnew = *S;

	for (i = 0; i < strlens + strlen; i++)//指移动后的位置
	{
		pnew++;
	}
	*pnew = '\0';
	pnew--;
	for (i = 0; i < strlens-pos;i++)//先腾出空间
	{
		*pnew = *(pnew - strlen);
		pnew--;
	}
	for (i = 0; i < pos; i++, pcur++);//指向插入位置
	for (i = 0; i < strlen; i++)
	{
		*pcur++ = *pt++;//插入
	}
	return OK;
}

Status StrDelete(SString* S, int pos, int len)
{
	char* pcur, * p;
	int i;

	if (*S == NULL || pos + len > StrLength(*S) || pos < 0)
	{
		return ERROR;
	}
	pcur = *S;
	for (i = 0; i < pos; i++, pcur++);//指向被删除位置
	p = pcur + len;
	if (*p == '\0')//删除子串位于末尾
	{
		*pcur = '\0';
		return OK;
	}
	for (i = 0; i < StrLength(*S)-len-pos; i++)//整体移动
	{
		*pcur++ = *p++;
	}
	*(p-len) = '\0';
	return OK;
}
