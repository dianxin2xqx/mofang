

//����ҵΪ����Ĳ���ɾ���Ͳ���

#include "stdio.h"
#include "stdlib.h"
#include "time.h"

#define ture 1
#define false 0
#define OK 1
#define ERROR 1
typedef int Status;
typedef int ElemType;

typedef struct LNode {//���Ա�ĵ�����洢�ṹ
	ElemType data;
	struct LNode* next;
}LNode, * LinkList;

Status InitList_Sq(LinkList& L) {
	//����һ���յ���������L��
	//����ͷ��㣬��ʹLָ��ͷ���
	int node;
	L = (LinkList)malloc(sizeof(LNode));
	if (!L)exit(ERROR);		//�洢����ʧ��
	L->next = NULL;				  		//ָ����Ϊ�� 
	return OK;
}//InitList_Sq

int ListLength(LinkList &L)
{
	//��ʼ���������Ա�L�Ѵ��ڣ��������������L������Ԫ�ظ���
	int i = 0;
	LinkList p = L->next;	//pָ���һ�����
	while (p) {//û����β
		i++;
		p = p->next;
	}
	return i;
}

Status ListInsert_L(LinkList& L, int i, int e) {
	//�ڴ�ͷ���ĵ������Ա�L�е�i ��λ��֮ǰ����Ԫ��e
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
	//�ڴ�ͷ���ĵ������Ա�L�У�ɾ����i��Ԫ�أ�����e������ֵ
	int j = 0;
	LinkList p,q; 
	p = L;
	while (p->next && j < i - 1) {//Ѱ�ҵ�i����㣬����pָ����ǰ��
		p = p->next; ++j;
	}
	if (!(p->next) || j > i - 1)return ERROR;	//ɾ��λ�ò�����
	q = p->next; p->next = q->next;				//ɾ�����ͷŽ��
	e = q->data;	free(q);
	return OK;
}//ListDelete_L

void ShowAddress(LinkList L)
{
	int i;
	LinkList p = L->next;
	if (p != NULL) {
		printf("\nͷ���ĵ�ַΪ�� \t%p\n", L);
		for (i = 1; p != NULL; i++) {
			printf("��%d������ֵΪ�� \t%d;\t��ַΪ��%p\n", i, p->data, p);
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
	printf("\n��ǰ�б��״̬Ϊ�� \n");
	ShowAddress(head);
	i = 3;							//����λ��
	printf("\n��%d���뵽��%d��λ�ú󣬵������״̬Ϊ��\n", e, i);
	ListInsert_L(head, i, e);
	ShowAddress(head);
	i = 6;							//ɾ��λ��
	printf("\nɾ���� %d ��������״̬��\n", i);
	ListDelet_L(head, i, e);
	ShowAddress(head);
}