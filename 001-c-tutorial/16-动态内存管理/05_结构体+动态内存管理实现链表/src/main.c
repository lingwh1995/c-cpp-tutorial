#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct ListNode
{
	int data;
	struct ListNode *next;
};

struct ListNode *init_list()
{
	struct ListNode *head = (struct ListNode *)malloc(sizeof(struct ListNode));
	if (NULL == head)
	{
		exit(-1);
	}
	head->next = NULL;
	return head;
}

/**
 * 头插法，最先插入节点在链表尾部
 * @param head
 * @param data
 */
void insert(struct ListNode *head, int data)
{
	assert(head != NULL);
	struct ListNode *current = (struct ListNode *)malloc(sizeof(struct ListNode));
	if (NULL == current)
	{
		exit(1);
	}
	current->data = data;
	current->next = head->next;
	head->next = current;
}

void print_linked_list(struct ListNode *head)
{
	assert(head != NULL);
	struct ListNode *temp = head->next;
	while (NULL != temp)
	{
		printf("%d ", temp->data);
		temp = temp-> next;
	}
}

int main()
{
	struct  ListNode *head = init_list();
	for (int i = 1; i <= 10; i++)
	{
		insert(head, i);
	}
	print_linked_list(head);
	return 0;
}
