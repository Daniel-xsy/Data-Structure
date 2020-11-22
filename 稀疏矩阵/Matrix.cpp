#include"Matrix.h"

int main(void)
{
	TSMatrix T, M, Res, ResT;
	printf("�������һ������\n");
	Init(&M);
	printf("�þ���Ϊ:\n");
	PrintMatrix(M);
	printf("������ڶ�������\n");
	Init(&T);
	printf("�þ���Ϊ:\n");
	PrintMatrix(T);
	printf("�������:\n");
	Multiplication(M, T, &Res);
	PrintMatrix(Res);
	printf("ת�þ���:\n");
	FastTransposeSMatrix(Res, &ResT);
	PrintMatrix(ResT);
	return 0;
}

Status Init(TSMatrix* M)
{
	int row, column;
	int i, j, seq;
	ElemType e;

	printf("�������������:\n");
	scanf_s("%d", &row);
	while (row < 1)
	{
		printf("������������������:\n");
		scanf_s("%d", &row);
	}
	printf("�������������:\n");
	scanf_s("%d", &column);
	while (column < 1)
	{
		printf("������������������:\n");
		scanf_s("%d", &column);
	}
	M->mu = row, M->nu = column;
	for (i = 0, seq = 0; i < row; i++)
	{
		printf("������� %d ��Ԫ��\n", i + 1);
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
	M->tu = seq;//����Ԫ�ظ���
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
	if (M.tu != 0)//�ǿվ���
	{
		for (j = 0, seqT = 0; j < column; j++)//ÿ����һ���ҳ�M��һ��
		{
			for (seqM = 0; seqM < ele_num; seqM++)//����M��Ԫ�� �ҵ�i��
			{
				if (M.data[seqM].j == j)
				{
					T->data[seqT].i = M.data[seqM].j;
					T->data[seqT].j = M.data[seqM].i;
					T->data[seqT].e = M.data[seqM].e;//ת��
					seqT++;
				}
			}
		}
	}
	printf("\n-----һ��ת��-----\n");

	return OK;
}

Status FastTransposeSMatrix(TSMatrix M, TSMatrix* T)
{
	int* col_num, * col_cur;
	int j, n;

	T->tu = M.tu, T->mu = M.nu, T->nu = M.mu;
	col_num = (int*)malloc(M.nu * sizeof(int));//M�е�j�е�һ������Ԫ�ص�λ��
	col_cur = (int*)malloc(M.nu * sizeof(int));//M�е�j�з���Ԫ�ظ���
	if (col_num == NULL || col_cur == NULL)
	{
		exit(OVERFLOW);
	}
	for (j = 0; j < M.nu; j++)
	{
		col_cur[j] = 0;
		col_num[j] = 0;
	}
	for (n = 0; n < M.tu; n++)//����M���Ա�
	{
		++col_num[M.data[n].j];//ͳ��ÿ��Ԫ�ظ���
	}
	for (j = 1; j < M.nu; j++)
		//����T��ÿ�е�һ������Ԫ����M���Ա��е�λ��
	{
		col_cur[j] += col_cur[j - 1] + col_num[j - 1];
	}
	for (n = 0; n < M.tu; n++)//����T,�������M��
	{
		T->data[col_cur[M.data[n].j]].e = M.data[n].e;
		T->data[col_cur[M.data[n].j]].i = M.data[n].j;
		T->data[col_cur[M.data[n].j]].j = M.data[n].i;
		//M.data[col_cur[T->data[n].j]] ��ʾȥM�ж�λT��ǰԪ�ص������Ŀ�ʼλ��
		col_cur[M.data[n].j]++;
	}
	printf("\n-----����ת��-----\n");
	return OK;
}

Status Multiplication(TSMatrix M1, TSMatrix M2, TSMatrix* T)
{
	int* M1_row_cur, * M1_row_num;//�Ϳ���ת����ͬ��˼��ͳ��M2�е�һ����ʼλ��
	int* M2_row_cur, * M2_row_num;
	int i, j, n;//i��ʾ�� j��ʾ�� n��ʾԪ�ظ���
	int* T_row_temp;
	int seq_M1, seq_M2, seq_T;
	int p_end_M1, p_end_M2;

	if (M1.nu != M2.mu)
	{
		printf("\n���󣡾����޷����\n");
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

		/*------------���ɸ���������-------------*/
		for (i = 0; i < M1.mu; i++)
		{
			M1_row_cur[i] = 0;
			M1_row_num[i] = 0;
		}
		for (i = 0; i < M2.mu; i++)
		{
			M2_row_cur[i] = 0;
			M2_row_num[i] = 0;
		}//M1 M2��ͳ�������ʼ��

		for (n = 0; n < M1.tu; n++)
		{
			M1_row_num[M1.data[n].i]++;
		}
		for (i = 1; i < M1.mu; i++)
		{
			M1_row_cur[i] = M1_row_cur[i - 1] + M1_row_num[i - 1];
		}//ͳ��M1������ÿ�п�ʼ��λ��

		for (n = 0; n < M2.tu; n++)
		{
			M2_row_num[M2.data[n].i]++;
		}
		for (i = 1; i < M2.mu; i++)
		{
			M2_row_cur[i] = M2_row_cur[i - 1] + M2_row_num[i - 1];
		}//ͳ��M2������ÿ�п�ʼ��λ��
		/*-----------�������������ɽ���-------------*/

		seq_T = 0;
		for (i = 0; i < M1.mu; i++)//����M1��ÿ��
		{
			for (j = 0; j < T->nu; j++)
			{
				T_row_temp[j] = 0;//T�е�i�е�j�� �ۼƺͳ�ʼ��
			}

			p_end_M1 = (i == M1.mu - 1 ? M1.tu : M1_row_cur[i + 1]);
			//���н�����λ��(��һ�п�ʼ��λ��)
			for (seq_M1 = M1_row_cur[i]; seq_M1 < p_end_M1; seq_M1++)//����M1�е�i�����з���Ԫ��
			{
				j = M1.data[seq_M1].j;//M1�е�i��Ԫ�ض�Ӧ����
				p_end_M2 = (j == M2.mu - 1 ? M2.tu : M2_row_cur[j + 1]);
				for (seq_M2 = M2_row_cur[j]; seq_M2 < p_end_M2; seq_M2++)//����M2�е�j��
				{
					T_row_temp[M2.data[seq_M2].j] += M1.data[seq_M1].e * M2.data[seq_M2].e;
				}//����T�е�i�е�Ԫ��
			}
			//����ѹ���洢
			for (j = 0; j < T->nu; j++)
			{
				if (T_row_temp[j] != 0)//ֻ�洢����Ԫ
				{
					T->data[seq_T].i = i;
					T->data[seq_T].j = j;
					T->data[seq_T].e = T_row_temp[j];
					seq_T++;//�ƶ�����һ��λ��
				}
			}
		}
		T->tu = seq_T;
	}
	return OK;
}