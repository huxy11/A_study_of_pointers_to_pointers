/*
 ============================================================================
 Name        : LinkList.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct list_t {
	int value;
	struct list_t* next;
}*node;

static struct list_t list[100];
static node head = list, sentinel;


void init_list(void)
{
	int i = 0;
	for (; i < 100; i++) {
		list[i].value = i;
		list[i].next = &list[i + 1];
	}
	list[99].next = 0;
}

void base_rm(int flag)
{
	node cur, pre;
	for (cur = head, pre = head; cur; cur = cur->next) {
		if (cur->value == flag) { //remove
			if (cur == head) { //remove the list head
				head = cur->next;
				pre = head;
				//free if necessary
			} else { //remove normal list node
				pre->next = cur->next;
				//free if necessary
			}
		} else if (cur != head)
			pre = pre->next;//maintain the pre
	}
}

void sentinel_rm(int flag)
{
	/* the sentinel may be used to store some information such as list length in some cases */
	sentinel = malloc(sizeof(struct list_t));
	sentinel->next = head;
	node cur, pre = sentinel;
	for (cur = sentinel->next; cur; cur = cur->next, pre = pre->next)
		if (cur->value == flag)
			pre->next = cur->next;
}

void p2p_rm(int flag)
{
	node *cur;//pointer to pointer to list node
	for (cur = &head; *cur;)
	{
		/*
		 * let us think that there is a node entry = *cur;
		 * just like a sentinel
		 * only this entry is not always pointer to the head
		 */
		if ((*cur)->value == flag)
			*cur = (*cur)->next;
			//free if necessary
		else cur = &(*cur)->next;
	}
}

void print_result()
{
	node cur;
	if (sentinel) {
		for (cur = sentinel->next; cur; cur = cur->next)
			printf("sentinel:%d\n", cur->value);
		return;
	}
	for (cur =head; cur; cur = cur->next)
		printf("nomal:%d\n", cur->value);
}

int main(void)
{
	/* Init Link List */
	init_list();
	/* Base */
//	base_rm(55);
	/* Use sentinel*/
//	sentinel_rm(0);
	/* Pointers to pointers */
	p2p_rm(0);
	/* Print the result */
	print_result();
	return 0;
}
