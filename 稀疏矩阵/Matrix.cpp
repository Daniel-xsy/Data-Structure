#include"Matrix.h"

int main(void)
{
	TSMatrix T, M, Res, ResT;
	printf("请输入第一个矩阵\n");
	Init(&M);
	printf("该矩阵为:\n");
	PrintMatrix(M);
	printf("请输入第二个矩阵\n");
	Init(&T);
	printf("该矩阵为:\n");
	PrintMatrix(T);
	printf("矩阵相乘:\n");
	Multiplication(M, T, &Res);
	PrintMatrix(Res);
	printf("转置矩阵:\n");
	FastTransposeSMatrix(Res, &ResT);
	PrintMatrix(ResT);
	return 0;
}

Status Init(TSMatrix* M)
{
	int row, column;
	int i, j, seq;
	ElemType e;

	printf("请输入矩阵行数:\n");
	scanf_s("%d", &row);
	while (row < 1)
	{
		printf("输入有误！请重新输入:\n");
		scanf_s("%d", &row);
	}
	printf("请输入矩阵列数:\n");
	scanf_s("%d", &column);
	while (column < 1)
	{
		printf("输入有误！请重新输入:\n");
		scanf_s("%d", &column);
	}
	M->mu = row, M->nu = column;
	for (i = 0, seq = 0; i < row; i++)
	{
		printf("请输入第 %d 行元素\n", i + 1);
		for (j = 0; j < column; j++)
		{
			scanf_s("%d", &e);
			if (e != 0)
			{
				(M->data)[seq].e = e;
				M->data[seq].i = i;
				M->data[seq].j = j;
				seq++;
			}
		}
		putchar('\n');
	}
	M->tu = seq;//非零元素个数
	return OK;
}

void PrintMatrix(TSMatrix M)
{
	int row, column, ele_num;
	int i, j, n;
	row = M.mu, column = M.nu, ele_num = M.tu;
	for (i = 0, n = 0; i < row; i++)
	{
		for (j = 0; j < column; j++)
		{
			if (M.data[n].i == i && M.data[n].j == j)
			{
				printf("%d ", M.data[n].e);
				n++;
			}
			else
                printf("0 ");
		}
		putchar('\n');
	}
}

Status TransposSMatrix(TSMatrix M, TSMatrix* T)
{
	int ele_num, column;
	int j, seqM, seqT;
	ele_num = M.tu, column = M.nu;
	T->tu = M.tu, T->mu = M.nu, T->nu = M.mu;
	if (M.tu != 0)//非空矩阵
	{
		for (j = 0, seqT = 0; j < column; j++)//每遍历一次找出M中一列
		{
			for (seqM = 0; seqM < ele_num; seqM++)//遍历M中元素 找第i列
			{
				if (M.data[seqM].j == j)
				{
					T->data[seqT].i = M.data[seqM].j;
					T->data[seqT].j = M.data[seqM].i;
					T->data[seqT].e = M.data[seqM].e;//转置
					seqT++;
				}
			}
		}
	}
	printf("\n-----一般转置-----\n");

	return OK;
}

Status FastTransposeSMatrix(TSMatrix M, TSMatrix* T)
{
	int* col_num, * col_cur;
	int j, n;

	T->tu = M.tu, T->mu = M.nu, T->nu = M.mu;
	col_num = (int*)malloc(M.nu * sizeof(int));//M中第j列第一个非零元素的位置
	col_cur = (int*)malloc(M.nu * sizeof(int));//M中第j列非零元素个数
	if (col_num == NULL || col_cur == NULL)
	{
		exit(OVERFLOW);
	}
	for (j = 0; j < M.nu; j++)
	{
		col_cur[j] = 0;
		col_num[j] = 0;
	}
	for (n = 0; n < M.tu; n++)//遍历M线性表
	{
		++col_num[M.data[n].j];//统计每列元素个数
	}
	for (j = 1; j < M.nu; j++)
		//计算T中每列第一个非零元素在M线性表中的位置
	{
		col_cur[j] += col_cur[j - 1] + col_num[j - 1];
	}
	for (n = 0; n < M.tu; n++)//遍历T,逐个放入M中
	{
		T->data[col_cur[M.data[n].j]].e = M.data[n].e;
		T->data[col_cur[M.data[n].j]].i = M.data[n].j;
		T->data[col_cur[M.data[n].j]].j = M.data[n].i;
		//M.data[col_cur[T->data[n].j]] 表示去M中定位T当前元素的列数的开始位置
		col_cur[M.data[n].j]++;
	}
	printf("\n-----快速转置-----\n");
	return OK;
}

Status Multiplication(TSMatrix M1, TSMatrix M2, TSMatrix* T)
{
	int* M1_row_cur, * M1_row_num;//和快速转置相同的思想统计M2列第一个开始位置
	int* M2_row_cur, * M2_row_num;
	int i, j, n;//i表示行 j表示列 n表示元素个数
	int* T_row_temp;
	int seq_M1, seq_M2, seq_T;
	int p_end_M1, p_end_M2;

	if (M1.nu != M2.mu)
	{
		printf("\n错误！矩阵无法相乘\n");
		return ERROR;
	}
	T->mu = M1.mu, T->nu = M2.nu;
	if (T->mu * T->nu != 0)
	{
		M1_row_cur = (int*)malloc(M1.mu * sizeof(int));
		M1_row_num = (int*)malloc(M1.mu * sizeof(int));
		M2_row_cur = (int*)malloc(M2.mu * sizeof(int));
		M2_row_num = (int*)malloc(M2.mu * sizeof(int));
		T_row_temp = (int*)malloc(T->nu * sizeof(int));
		if (M1_row_cur == NULL || M1_row_num == NULL || T_row_temp==NULL||
			M2_row_cur == NULL || M2_row_num == NULL)
		{
			exit(OVERFLOW);
		}

		/*------------生成辅助行向量-------------*/
		for (i = 0; i < M1.mu; i++)
		{
			M1_row_cur[i] = 0;
			M1_row_num[i] = 0;
		}
		for (i = 0; i < M2.mu; i++)
		{
			M2_row_cur[i] = 0;
			M2_row_num[i] = 0;
		}//M1 M2行统计数组初始化

		for (n = 0; n < M1.tu; n++)
		{
			M1_row_num[M1.data[n].i]++;
		}
		for (i = 1; i < M1.mu; i++)
		{
			M1_row_cur[i] = M1_row_cur[i - 1] + M1_row_num[i - 1];
		}//统计M1矩阵中每行开始的位置

		for (n = 0; n < M2.tu; n++)
		{
			M2_row_num[M2.data[n].i]++;
		}
		for (i = 1; i < M2.mu; i++)
		{
			M2_row_cur[i] = M2_row_cur[i - 1] + M2_row_num[i - 1];
		}//统计M2矩阵中每行开始的位置
		/*-----------辅助行向量生成结束-------------*/

		seq_T = 0;
		for (i = 0; i < M1.mu; i++)//遍历M1中每行
		{
			for (j = 0; j < T->nu; j++)
			{
				T_row_temp[j] = 0;//T中第i行第j列 累计和初始化
			}

			p_end_M1 = (i == M1.mu - 1 ? M1.tu : M1_row_cur[i + 1]);
			//该行结束的位置(下一行开始的位置)
			for (seq_M1 = M1_row_cur[i]; seq_M1 < p_end_M1; seq_M1++)//遍历M1中第i行所有非零元素
			{
				j = M1.data[seq_M1].j;//M1中第i行元素对应的列
				p_end_M2 = (j == M2.mu - 1 ? M2.tu : M2_row_cur[j + 1]);
				for (seq_M2 = M2_row_cur[j]; seq_M2 < p_end_M2; seq_M2++)//遍历M2中第j行
				{
					T_row_temp[M2.data[seq_M2].j] += M1.data[seq_M1].e * M2.data[seq_M2].e;
				}//生成T中第i行的元素
			}
			//进行压缩存储
			for (j = 0; j < T->nu; j++)
			{
				if (T_row_temp[j] != 0)//只存储非零元
				{
					T->data[seq_T].i = i;
					T->data[seq_T].j = j;
					T->data[seq_T].e = T_row_temp[j];
					seq_T++;//移动到下一个位置
				}
			}
		}
		T->tu = seq_T;
	}
	return OK;
}