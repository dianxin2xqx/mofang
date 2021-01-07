

//改作业为链表的插入删除和查找

#include "stdio.h"
#include "stdlib.h"
#include "time.h"

#define ture 1
#define false 0
#define OK 1
#define ERROR 1
typedef int Status;
typedef int ElemType;

typedef struct LNode {//线性表的单链表存储结构
	ElemType data;
	struct LNode* next;
}LNode, * LinkList;

Status InitList_Sq(LinkList& L) {
	//构造一个空的线性链表L。
	//产生头结点，并使L指向头结点
	int node;
	L = (LinkList)malloc(sizeof(LNode));
	if (!L)exit(ERROR);		//存储分配失败
	L->next = NULL;				  		//指针域为空 
	return OK;
}//InitList_Sq

int ListLength(LinkList &L)
{
	//初始条件：线性表L已存在，操作结果：返回L中数据元素个数
	int i = 0;
	LinkList p = L->next;	//p指向第一个结点
	while (p) {//没到表尾
		i++;
		p = p->next;
	}
	return i;
}

Status ListInsert_L(LinkList& L, int i, int e) {
	//在带头结点的单链线性表L中第i 个位置之前插入元素e
	int j = 0;
	LinkList p,  q, s;
	p = L;
	while (p && j < i - 1) { p = p->next; ++j; }
	if (!p || j > i - 1)return ERROR;
	s = (LinkList)malloc(sizeof(LNode));
	s->data = e; s->next = p->next;
	p->next = s;
	return OK;
}//ListInsert_L 

Status ListDelet_L(LinkList& L, int i, int& e) {
	//在带头结点的单链线性表L中，删除第i个元素，并由e返回其值
	int j = 0;
	LinkList p,q; 
	p = L;
	while (p->next && j < i - 1) {//寻找第i个结点，并令p指向其前驱
		p = p->next; ++j;
	}
	if (!(p->next) || j > i - 1)return ERROR;	//删除位置不合理
	q = p->next; p->next = q->next;				//删除并释放结点
	e = q->data;	free(q);
	return OK;
}//ListDelete_L

void ShowAddress(LinkList L)
{
	int i;
	LinkList p = L->next;
	if (p != NULL) {
		printf("\n头结点的地址为： \t%p\n", L);
		for (i = 1; p != NULL; i++) {
			printf("第%d个结点的值为： \t%d;\t地址为：%p\n", i, p->data, p);
			p = p->next;
		}
	}
}
int main()
{
	int num = 0, A[8];
	srand((unsigned int)time(NULL));
	for (; num < 8; num++)
	{
		A[num] = rand() % 100 + 1;
	}
	int i, j, e = 111;
	LinkList head,p;
	InitList_Sq(head);
	for (i = 1, j = 0; i <= 8; i++, j++)
		ListInsert_L(head, i, A[j]);
	printf("\n当前列表的状态为： \n");
	ShowAddress(head);
	i = 3;							//插入位置
	printf("\n把%d插入到第%d个位置后，单链表的状态为：\n", e, i);
	ListInsert_L(head, i, e);
	ShowAddress(head);
	i = 6;							//删除位置
	printf("\n删除第 %d 结点后单链表状态：\n", i);
	ListDelet_L(head, i, e);
	ShowAddress(head);
}