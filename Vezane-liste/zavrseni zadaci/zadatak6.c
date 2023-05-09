#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Node;
typedef struct Node node;
typedef node* position;

struct Node {
	int num;
	position next;
};	

position AllocateNode();
void InsertAfter(position what, position where);
void PrintList(position p);
void DeleteList(position p);
int RandomNumber();
int StackAndArrayPushFive(position p);
void StackPopFive(position p);
void ArrayPopFive(position p);

int main() {
	node list;

	list.next = NULL;
	list.num = 0;
	srand(time(0));

	puts("Stack: ");
	if (StackAndArrayPushFive(&list)) {
		puts("Exiting application");
		DeleteList(&list);
		return EXIT_FAILURE;
	}
	StackPopFive(&list);

	puts("");
	puts("Array: ");
	if (StackAndArrayPushFive(&list)) {
		puts("Exiting application");
		DeleteList(&list);
		return EXIT_FAILURE;
	}
	ArrayPopFive(&list);

	DeleteList(&list);
	return EXIT_SUCCESS;
}

void DeleteList(position p) {
	position temp = NULL;

	while (p->next != NULL) {
		temp = p->next;			
		p->next = temp->next; 	
		free(temp); 			
	}
}

void PrintList(position p) {
	if (NULL == p->next) {
		puts("List is empty!");
		return;
	}

	while (p->next != NULL) {
		printf("\n\t%d", p->next->num);
		p = p->next;
	}
	puts("");

}

void InsertAfter(position what, position where) {
	what->next = where->next;
	where->next = what;
}

position AllocateNode() {
	return (position)malloc(sizeof(node));
}

int RandomNumber() {
	int x;

	x = (rand() %(90 + 1)) + 10;

	return x;
}

int StackAndArrayPushFive(position p) {
	position ne = NULL;
	int counter = 0;

	while (counter < 5) {
		ne = AllocateNode();
		if (NULL == ne) {
			puts("StackAndArrayPushFive allocation error!");
			return EXIT_FAILURE;
		}
		ne->num = RandomNumber();
		InsertAfter(ne, p);
		PrintList(p);
		counter++;
	}
	return EXIT_SUCCESS;
}

void StackPopFive(position p) {
	int counter = 0;
	position temp = NULL;

	while (counter < 5) {
		PrintList(p);
		temp = p->next;
		p->next = p->next->next;
		free(temp);
		counter++;
	}
}

void ArrayPopFive(position p) {
	int counter = 0;
	position temp = NULL;
	position bookmark = NULL;

	bookmark = p;
	while (counter < 5) {
		p = bookmark;
		while (p->next->next != NULL) {
			p = p->next;
		}
		PrintList(bookmark);
		temp = p->next;
		p->next = p->next->next;
		free(temp);
		counter++;
	}
}
