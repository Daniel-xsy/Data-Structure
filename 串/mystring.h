#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<stddef.h>
#include<string.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAXSTRLEN 255

typedef int Status;
typedef char SString[MAXSTRLEN];

Status StrCopy(SString* T, char* S);
Status StrEmpty(SString S);
Status StrCompare(SString S, SString T);
int StrLength(SString S);
Status ClearString(SString* S);
Status Concat(SString* T, SString S1, SString S2);
Status SubString(SString* Sub, SString S, int len, int pos);
Status Index(SString S, SString T, int pos);
Status Replace(SString* S, SString T, SString V);
Status StrInsert(SString* S, int pos, SString T);
Status StrDelete(SString* S, int pos, int len);
int menu(void);