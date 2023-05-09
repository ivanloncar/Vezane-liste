#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Node;
struct NodeArray;

typedef struct Node node;
typedef node* position;

typedef struct NodeArray nodeArray;
typedef nodeArray* positionArray;

struct Node {
	int num;
	position next;
};


struct NodeArray {
	int num;
	int priority;
	positionArray next;
};


position AllocateNode();
positionArray AllocateNodeArray();
void InsertAfter(position what, position where);
void InsertAfterArray(positionArray what, positionArray where);
void PrintList(position p);
void PrintListArray(positionArray p);
void DeleteList(position p);
void DeleteListArray(positionArray p);
int RandomNumber(int upper, int lower);
int StackPush(position p, int range);
int ArrayPushFive(positionArray p);
void StackPop(position p, int range);
void ArrayPopFive(positionArray p);

int main() {
	node list;
	nodeArray listArray;
	int range;

	list.next = NULL;
	list.num = 0;
	range = 0;
	listArray.next = NULL;
	listArray.num = 0;
	listArray.priority = 0;


	srand(time(0));

	puts("Please insert the size of the stack: ");
	scanf("%d", &range);

	if (StackPush(&list, range)) {
		puts("Exiting application");
		DeleteList(&list);
		DeleteListArray(&listArray);
		return EXIT_FAILURE;
	}
	StackPop(&list, range);

	puts("");
	puts("Array: ");
	if (ArrayPushFive(&listArray)) {
		puts("Exiting application");
		DeleteList(&list);
		DeleteListArray(&listArray);
		return EXIT_FAILURE;
	}
	ArrayPopFive(&listArray);

	DeleteList(&list);
	DeleteListArray(&listArray);
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

void DeleteListArray(positionArray p) {
	positionArray temp = NULL;

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

void PrintListArray(positionArray p) {
	if (NULL == p->next) {
		puts("List is empty!");
		return;
	}

	while (p->next != NULL) {
		printf("\n\t%d %d", p->next->num, p->next->priority);
		p = p->next;
	}
	puts("");

}

void InsertAfter(position what, position where) {
	what->next = where->next;
	where->next = what;
}

void InsertAfterArray(positionArray what, positionArray where) {
	what->next = where->next;
	where->next = what;
}

position AllocateNode() {
	return (position)malloc(sizeof(node));
}

positionArray AllocateNodeArray() {
	return (positionArray)malloc(sizeof(nodeArray));
}

int RandomNumber(int upper, int lower) {
	int x;

	x = (rand() % (upper - lower + 1)) + lower;

	return x;
}

int StackPush(position p, int range) {
	position ne = NULL;
	int counter = 0;

	while (counter < range) {
		ne = AllocateNode();
		if (NULL == ne) {
			puts("StackPush allocation error!");
			return EXIT_FAILURE;
		}
		ne->num = RandomNumber(100, 10);
		InsertAfter(ne, p);
		PrintList(p);
		counter++;
	}
	return EXIT_SUCCESS;
}

int ArrayPushFive(positionArray p) {
	positionArray ne = NULL;
	int counter = 0;
	positionArray bookmark = NULL;

	bookmark = p;

	while (counter < 5) {
		ne = AllocateNodeArray();
		if (NULL == ne) {
			puts("ArrayPushFive allocation error!");
			return EXIT_FAILURE;
		}
		ne->num = RandomNumber(100, 10);
		ne->priority = RandomNumber(5, 1);
		while (p->next!=NULL && ne->priority < p->next->priority) {
			p = p->next;
		}
		InsertAfterArray(ne, p);
		PrintListArray(bookmark);
		counter++;
		p = bookmark;
	}
	return EXIT_SUCCESS;
}

void StackPop(position p, int range) {
	int counter = 0;
	position temp = NULL;

	while (counter < range) {
		PrintList(p);
		temp = p->next;
		p->next = p->next->next;
		free(temp);
		counter++;
	}
}

void ArrayPopFive(positionArray p) {
	int counter = 0;
	positionArray temp = NULL;
	positionArray bookmark = NULL;

	bookmark = p;
	while (counter < 5) {
		p = bookmark;
		while (p->next->next != NULL) {
			p = p->next;
		}
		PrintListArray(bookmark);
		temp = p->next;
		p->next = p->next->next;
		free(temp);
		counter++;
	}
}
