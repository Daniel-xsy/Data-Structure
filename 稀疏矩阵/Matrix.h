#pragma once
#include<stdio.h>
#include<stdlib.h>
#define OK 1
#define ERROR 0
#define FALSE -1
#define OVERFLOW -1
#define MAXSIZE 225

typedef int Status;
typedef int ElemType;
typedef struct
{
	int i, j;
	ElemType e;
}Triple;//使用三元表存储矩阵
typedef struct
{
	Triple data[MAXSIZE + 1];
	int mu, nu, tu;
}TSMatrix;

Status Init(TSMatrix* M);
void PrintMatrix(TSMatrix M);
Status TransposSMatrix(TSMatrix M, TSMatrix* T);
//方法一转置矩阵
Status FastTransposeSMatrix(TSMatrix X, TSMatrix* T);
//快速转置矩阵
Status Multiplication(TSMatrix M1, TSMatrix M2, TSMatrix* T);
//矩阵乘法