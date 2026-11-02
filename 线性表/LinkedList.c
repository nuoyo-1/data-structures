/*
 * LinkedList.c —— 单链表（线性表的链式存储）
 *
 * 结点 = 数据域 data + 指针域 next
 * 头结点：数据域不用，next 指向第一个真实结点
 *
 * 现在实现了：初始化、头插法、尾插法、遍历
 *
 * ============ 还差什么（按建议顺序） ============
 *
 * 【一、结构问题，最优先】
 *   1. 缺 LinkedList.h 头文件。现在宏、typedef、结构体、函数全写在 .c 里，
 *      和 LinearList.h 的 OK / ERROR / Status / InitList / PrintList 重名，
 *      两个文件一起编译会报 multiple definition，无法共存。
 *      → 把 #define、typedef、struct Node、函数原型都抽到 LinkedList.h，
 *        本文件改为 #include "LinkedList.h"。
 *   2. 缺函数返回值检查。InitList / ListInsertHead / ListInsertTail 的
 *      返回值在 main 里全被忽略，malloc 失败时程序会带着野指针继续跑。
 *
 * 【二、还没实现的函数】
 *   DestroyList(L)              整个表连头结点一起 free，现在只 malloc 不 free，每次运行都漏内存
 *   ClearList(L)                清空，保留头结点
 *   ListEmpty(L)                判空
 *   ListLength(L)               返回元素个数
 *   GetElem(L, i, *e)           取第 i 个元素（i 从 1 开始，需要先校验 i 的合法性）
 *   LocateElem(L, e)            按值查找，返回位序，找不到返回 0
 *   ListInsert(L, i, e)         按位序插入，链表的核心操作（现在是头插/尾插两个特例）
 *   ListDelete(L, i, *e)        删除第 i 个结点并带出值，最考指针功底，优先写
 *   PriorElem(L, cur, *pre)     求前驱
 *   NextElem(L, cur, *next)     求后继
 *
 * 【三、已实现部分的改进（可选）】
 *   3. ListInsertTail 每次都要从头遍历到尾，O(n)，连插 n 个元素变成 O(n^2)。
 *      → 若需要高效尾插，可额外维护一个尾指针，或让函数接收尾指针的地址。
 *   4. 遍历目前只有 PrintList（打印），没有返回长度的 ListLength。
 *
 * 【四、测试用例（补完函数后要能验证正确性）】
 *     空表删除、删第一个、删中间、删最后一个、删不存在的位序、
 *     查找不存在的值、往空表按位序插入、i 越界插入/删除。
 *
 * 【小问题】
 *   - main 里 printf("你好") 像是调试残留，可以删。
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

Status ListInsertTail( LinkList L, ElemType e)//尾插法
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
    printf("你好");
    return 0;
}