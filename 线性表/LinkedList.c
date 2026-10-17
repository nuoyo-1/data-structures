/*
 * LinkedList.c —— 单链表（线性表的链式存储）
 *
 * 结点 = 数据域 data + 指针域 next
 * 头结点：数据域不用，next 指向第一个真实结点
 *
 * 现在实现了：初始化、头插法、遍历
 */

#include <stdio.h>
#include <stdlib.h>

#define OK      1
#define ERROR   0

typedef int Status;
typedef int ElemType;

/* 单链表结点 */
typedef struct Node {
    ElemType     data;
    struct Node *next;
} Node, *LinkList;      /* LinkList 就是 Node*，指头结点 */

/* 初始化：建一个只有头结点的空链表 */
Status InitList(LinkList *L)
{
    *L = (Node *)malloc(sizeof(Node));   /* 生成头结点 */
    if (*L == NULL) return ERROR;        /* 内存不够 */
    (*L)->next = NULL;                   /* 空表 */
    return OK;
}

/* 头插法：把 e 插到链表最前面 */
Status ListInsertHead(LinkList L, ElemType e)
{
    LinkList p = (Node *)malloc(sizeof(Node));  /* 新结点 */
    if (p == NULL) return ERROR;

    p->data = e;
    p->next = L->next;   /* ① 新结点指向原来的第一个结点 */
    L->next = p;         /* ② 头结点指向新结点 12不能调换位置*/

    return OK;
}

Status ListInsertTail( LinkList L, ElemType e)
{
    LinkList p =(Node *)malloc(sizeof(Node));
    if(p == NULL) return ERROR;
    p->data = e;
    p->next = NULL;
    while (L->next != NULL) {
        L = L->next;  /* 找到最后一个结点 */
    }
    L->next = p;
    return OK;
}




/* 遍历打印 */
void PrintList(LinkList L)
{
    LinkList p = L->next;   /* 从第一个真实结点开始，跳过头结点 */
    while (p != NULL) {
        printf("%d ", p->data);
        p = p->next;        /* 往后走一格 */
    }
    printf("\n");
}

int main(void)
{
    LinkList list;

    InitList(&list);          /* 建空表 */
    ListInsertHead(list, 1);  /* 插 1 */
    ListInsertHead(list, 2);  /* 插 2 */
    ListInsertHead(list, 3);  /* 插 3 */
    ListInsertTail(list, 4);  /* 插 4 */
    PrintList(list);          /* 打印 */
    printf("list->next->data = %d\n", list->next->data);  /* 打印头结点下一节点数据域 */

    return 0;
}