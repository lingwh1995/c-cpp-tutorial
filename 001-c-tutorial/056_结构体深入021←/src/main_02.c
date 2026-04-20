#include <stdio.h>

/**
 * 链表节点结构体
 */
typedef struct Node {
    int data;
    struct Node *next;
} Node;

// 推荐单独链表指针别名
typedef Node *LinkedList;

void print_linked_list(const Node *head)
{
    if (head == NULL)
    {
        printf("链表为空\n");
        return;
    }

    /**
     * 1. 不推荐直接用 head，因为会丢失头指针位置
     * 2. 遍历指针的类型，必须和链表头指针的类型完全一致！
     */
    const Node *current = head;
    while (current != NULL)
    {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

#if 0
#endif
int main()
{
    // 静态创建链表节点
	Node node_1 = { 1, NULL };
	Node node_2 = { 2, NULL };
	Node node_3 = { 3, NULL };

    // 构建链表关系
    node_1.next = &node_2;
    node_2.next = &node_3;

    // 链表头指针
    LinkedList head = &node_1;

    // 打印输出
    print_linked_list(head);

    return 0;
}

