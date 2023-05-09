#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NAME (64)
#define _ERROR (NULL)

struct Person;
typedef struct Person person;
typedef person* position;

struct Person {
	char name[MAX_NAME];
	char surname[MAX_NAME];
	int year;

	position next;
};

void InsertAfter(position what, position where);
int InsertFront(position p);
position AllocatePerson();//alociraj stvorenu osobu
position CreatePerson();//deklarirat varijablu osobe
int PrintList(position p);
int InsertEnd(position p);
void FindElement(position p);
void DeleteElement(position p);
void DeleteList(position p);

int main() {
	//deklaracija
	int isError;
	int isAppRunning;
	int menuChoice;
	person head;
	position temp;

	//inicijalizacija
	isError = 0;
	isAppRunning = 1;
	menuChoice = 0;
	head.next = NULL;
	temp = NULL;

	do
	{
		puts("\nChoose an action:");
		puts("1.Add element to beginning of list!");
		puts("2.Print list!");
		puts("3.Add element to end of list!");
		puts("4.Find element by surname!");
		puts("5.Delete an element by surname!");
		puts("11.Close application!");
		scanf(" %d", &menuChoice);
		switch (menuChoice)
		{
		case 1:
			isError = InsertFront(&head);
			break;
		case 2:
			isError = PrintList(head.next);
			break;
		case 3:
			isError = InsertEnd(&head);
			break;
		case 4:
			FindElement(&head);
			break;
		case 5:
			DeleteElement(&head);
			break;
		case 11:
			isAppRunning = 0;
			break;
		default:
			puts("\nWrong input, please repeat!");
			break;
		}

		if (isError) {
			DeleteList(&head);
			puts("Exiting program!");
			return EXIT_FAILURE;
		}
	} while (isAppRunning);

	DeleteList(&head);

	return 0;
}

void InsertAfter(position what, position where) {
	what->next = where->next;
	where->next = what;
}

int InsertFront(position p) {
	position temp;
	temp = CreatePerson();
	if (NULL == temp) {
		puts("InsertFront function error!");
		return EXIT_FAILURE;
	}
	InsertAfter(temp, p);

	return EXIT_SUCCESS;
}

position AllocatePerson() {
	return (position)malloc(sizeof(person));
}

position CreatePerson() {
	position el = NULL;

	el = AllocatePerson();
	if (NULL == el) {
		puts("Allocation failed!");
		return _ERROR;
	}

	puts("Insert: <name> <surname> <yearOfBirth> ");
	scanf(" %s %s %d", el->name, el->surname, &el->year);

	return el;
}

int PrintList(position p) {
	if (NULL == p) {
		puts("Error - list is empty");
		return EXIT_SUCCESS;
	}
	while (p != NULL) {
		printf("\n\t%s %s %d", p->name, p->surname, p->year);
		p = p->next;
	}
	puts("");

	return EXIT_SUCCESS;
}

int InsertEnd(position p) {
	position temp = NULL;
	while (p->next != NULL) {
		p = p->next;
	}
	temp = CreatePerson();
	if (NULL == temp) {
		puts("InsertEnd function error!");
		return EXIT_FAILURE;
	}
	InsertAfter(temp, p);
}

void FindElement(position p) {
	char tempName[MAX_NAME];

	puts("Enter a surname: ");
	scanf(" %s", &tempName);

	while (p->next != NULL) {
		if (_strcmpi(tempName, p->next->surname) == 0) {
			printf("\n\t The element you were looking for: %s %s %d", p->next->name, p->next->surname, p->next->year);
			break;
		}
		p = p->next;
	}
	if (NULL == p->next) {
		puts("Element not found!");
	}
}

void DeleteElement(position p) {
	position target = NULL;
	char tempName[MAX_NAME];

	puts("Enter a surname to be deleted: ");
	scanf(" %s", &tempName);

	while (p->next != NULL && _strcmpi(tempName, p->next->surname) != 0) {
		p = p->next;
	}
	if (NULL == p->next) {
		puts("Element not found!");
		return;
	}
	if (_strcmpi(tempName, p->next->surname) == 0) {
		target = p->next;
		p->next = p->next->next;
		free(target);
	}
	else {
		puts("Element not found!");
	}
}
void DeleteList(position p) {
	position temp = NULL;

	while (p->next != NULL) {
		temp = p->next;
		p->next = temp->next;
		free(temp);
	}
}