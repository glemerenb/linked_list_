#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct test_struct {
	int data;
	struct test_struct *next;
};

struct test_struct *head = NULL;
struct test_struct *current = NULL;

struct test_struct *create_list(int data) {
	printf("\n Creating list with headnode as [%d] \n", data);
	struct test_struct *ptr = (struct test_struct*)malloc(sizeof(struct test_struct));
	if (ptr == NULL) {
		printf("\n Node creation failed \n");
		return NULL;
	}

	ptr->data = data;
	ptr->next = NULL;

	head = current = ptr;
	return ptr;
}

struct test_struct *add_to_list(int data, bool add_to_end) {
	if (head == NULL) {
		return create_list(data);
	}

	if (add_to_end) {
		printf("\n Adding new node at the end of list with data as [%d] \n", data);
	}
	else {
		printf("\n Adding new node at the beginning of list with data as [%d] \n", data);
	}

	struct test_struct *ptr = (struct test_struct*)malloc(sizeof(struct test_struct));
	if (ptr == NULL) {
		printf("\n Node creation failed \n");
	}

	ptr->data = data;
	ptr->next = NULL;

	if (add_to_end == true) {
		current->next = ptr;
		current = ptr;
	}
	else {
		ptr->next = head;
		head = ptr;
	}
	return ptr;
}

struct test_struct *search_in_list(int data, struct test_struct **prev) {
	struct test_struct *tmp = NULL;
	struct test_struct *ptr = head;
	bool found = false;

	printf("\n Searching the list for data as [%d] \n", data);

	while (ptr != NULL) {
		if (ptr->data == data) {
			found = true;
			break;
		}
		else {
			tmp = ptr;
			ptr = ptr->next;
		}
	}

	if (found == true) {
		if (prev != NULL)
			*prev = tmp;
		return ptr;
	}
	else {
		return NULL;
	}
}

int delete_from_list(int data) {
	struct test_struct *del = NULL;
	struct test_struct *prev = NULL;

	printf("\n Deleting data [%d] from list \n", data);

	del = search_in_list(data, &prev);
	if (del == NULL) {
		return -1;
	}
	else {
		if (prev != NULL) {
			prev->next = del->next;
		}
		if (del == current) {
			prev->next = current->next;
		}
		else if (del == head) {
			head = del->next;
		}
	}
	free(del);
	del = NULL;

	return 0;
}

void print_list(void) {
	struct test_struct *ptr = head;

	printf("\n Printing list Start \n");
	while (ptr != NULL) {
		printf("\n [%d] \n", ptr->data);
		ptr = ptr->next;
	}
	printf("\n Printing list End \n");

	return;

}

int main() {
	int i = 0, ret = 0;
	struct test_struct *ptr = NULL;

	print_list();

	for (i = 56; i < 60; i++) {
		add_to_list(i, true);
	}

	print_list();

	for (i = 55; i > 49; i--) {
		add_to_list(i, false);
	}

	print_list();

	for (i = 50; i < 60; i += 4) {
		ptr = search_in_list(i, NULL);
		if (ptr == NULL) {
			printf("\n Search [data = %d] failed, no such element found \n", i);
		}
		else {
			printf("\n Search [data = %d] passed \n", ptr->data);
		}


		ret = delete_from_list(i);
		if (ret != 0) {
			printf("\n Delete [data = %d] failed, no such element found \n", i);
		}
		else {
			printf("\n Delete [data = %d] passed  \n", i);
		}

		print_list();
	}
	return 0;
}