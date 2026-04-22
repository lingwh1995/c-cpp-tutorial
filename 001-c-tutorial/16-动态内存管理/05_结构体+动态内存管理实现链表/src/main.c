#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct Node
{
	int data;
	struct Node *next;
} Node;

Node *init_list()
{
	Node *head = malloc(sizeof(Node));
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
void insert_head(Node *head, const int data)
{
	assert(head != NULL);
	Node *current = malloc(sizeof(Node));
	if (NULL == current)
	{
		exit(1);
	}
	current->data = data;
	current->next = head->next;
	head->next = current;
}

void print_linked_list(const Node *head)
{
	assert(head != NULL);
	const Node *temp = head->next;
	while (NULL != temp)
	{
		printf("%d ", temp->data);
		temp = temp-> next;
	}
}

int main()
{
	Node *head = init_list();
	for (int i = 1; i <= 10; i++)
	{
		insert_head(head, i);
	}
	print_linked_list(head);
	return 0;
}
