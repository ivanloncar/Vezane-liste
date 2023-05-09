#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct Number;
typedef struct Number number;
typedef number* position;

struct Number {
	int num;
	position next;
};


position AllocateNode();
void InsertAfter(position what, position where);
int InsertSorted(position temp, position p);
int FileToList(position p, char* fileName);
int PrintList(position p);
void DeleteList(position p);
void DeleteAll(position l1, position l2, position un, position in);
int UnionList(position l1, position l2, position un);
int IntersectionList(position l1, position l2, position in);

int main() {
	number l1, l2, un, in;

	l1.next = NULL;
	l1.num = 0;

	l2.next = NULL;
	l2.num = 0;

	un.next = NULL;
	un.num = 0;

	in.next = NULL;
	in.num = 0;

	if (FileToList(&l1, "L1.txt")) { //LISTE IZ FILEA U PROGRAM
		DeleteAll(&l1, &l2, &un, &in);
		puts("Exiting program! (FileToList(&l1, L1.txt))");
		return EXIT_FAILURE;
	}
	if (FileToList(&l2, "L2.txt")) {
		DeleteAll(&l1, &l2, &un, &in);
		puts("Exiting program! (FileToList(&l1, L2.txt))");
		return EXIT_FAILURE;
	}
	if (UnionList(&l1, &l2, &un)) {
		DeleteAll(&l1, &l2, &un, &in);
		puts("Exiting program! (UnionList(&l1, &l2, &un))");
		return EXIT_FAILURE;
	}
	if (IntersectionList(&l1,&l2,&in)) {
		DeleteAll(&l1, &l2, &un, &in);
		puts("Exiting program! (IntersectionList(&l1,&l2,&in))");
		return EXIT_FAILURE;
	}

	if (PrintList(&l1)) {
		DeleteAll(&l1, &l2, &un, &in);
		puts("Exiting program! (PrintList)");
		return EXIT_FAILURE;
	}
	if (PrintList(&l2)) {
		DeleteAll(&l1, &l2, &un, &in);
		puts("Exiting program! (PrintList)");
		return EXIT_FAILURE;
	}
	if (PrintList(&un)) {
		DeleteAll(&l1, &l2, &un, &in);
		puts("Exiting program! (PrintList)");
		return EXIT_FAILURE;
	}
	if (PrintList(&in)) {
		DeleteAll(&l1, &l2, &un, &in);
		puts("Exiting program! (PrintList)");
		return EXIT_FAILURE;
	}
	puts("");
	puts("Program exiting succesfully");
	DeleteAll(&l1, &l2, &un, &in); // BRISANJE U SLUCAJU USPJESNOG KRAJA PROGRAMA

	return EXIT_SUCCESS;
}

position AllocateNode() {
	return (position)malloc(sizeof(number));
}

void InsertAfter(position what, position where) {
	what->next = where->next;
	where->next = what;
}

int InsertSorted(position temp, position p) {

	while (p->next != NULL && temp->num > p->next->num) {
		p = p->next;
	}
	if (NULL == p->next) {
		InsertAfter(temp, p);
		return EXIT_SUCCESS;
	}
	if (temp->num < p->next->num) {
		InsertAfter(temp, p);
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}

int FileToList(position p, char* fileName) {
	FILE* fp = NULL;
	position temp = NULL;

	fp = fopen(fileName,"r");
	if (NULL == fp) {
		puts("FileToList file opening error!");
		return EXIT_FAILURE;
	}

	while (!feof(fp)) {
		temp = AllocateNode();
		if (NULL == temp) {
			puts("FileToList temp allocation error!");
			return EXIT_FAILURE;
		}
		fscanf(fp, "%d", &temp->num);
		temp->next = NULL;
		InsertSorted(temp, p);
	}

	fclose(fp);
	return EXIT_SUCCESS;
}

void DeleteList(position p) {
	position temp = NULL;

	while (p->next != NULL) {
		temp = p->next;			// spremit varijablu za brisanje
		p->next = temp->next; 		// prebacivanje pointera
		free(temp); 			//oslobadanje memorije 
	}
}

int PrintList(position p) {
	if (NULL == p->next) {
		puts("List is empty!");
		return EXIT_SUCCESS;
	}

	while (p->next != NULL) {
		printf("\n\t%d", p->next->num);
		p = p->next;
	}
	puts("");

	return EXIT_SUCCESS;
}

void DeleteAll(position l1, position l2, position un, position in) {
	DeleteList(l1);
	DeleteList(l2);
	DeleteList(un);
	DeleteList(in);
}

int UnionList(position p, position q, position un) {
	position temp = NULL;

	while (NULL != p->next && NULL != q->next) {
		if (p->next->num == q->next->num) {

			temp = AllocateNode();
			if (NULL == temp) {
				puts("Allocation error");
				return EXIT_FAILURE;
			}
			temp->num = p->next->num;
			temp->next = NULL;
			InsertAfter(temp, un);

			p = p->next;
			q = q->next;
			un = un->next;
		}
		else if (p->next->num > q->next->num) {

				temp = AllocateNode();
				if (NULL == temp) {
					puts("Allocation error");
					return EXIT_FAILURE;
				}
				temp->num = q->next->num;
				temp->next = NULL;
				InsertAfter(temp, un);

				q = q->next;
				un = un->next;
		}
		else if (p->next->num < q->next->num) {
				if (q->next != NULL)
					temp = AllocateNode();
				if (NULL == temp) {
					puts("Allocation error");
					return EXIT_FAILURE;
				}
				temp->num = p->next->num;
				temp->next = NULL;
				InsertAfter(temp, un);

				p = p->next;
				un = un->next;
			
		}

		if (p->next == NULL) {
			while (q->next != NULL) {
				temp = AllocateNode();
				if (NULL == temp) {
					puts("Allocation error");
					return EXIT_FAILURE;
				}
				temp->num = q->next->num;
				temp->next = NULL;
				InsertAfter(temp, un);

				q = q->next;
				un = un->next;
			}
		}
		if (q->next == NULL) {
			while (p->next != NULL) {
				temp = AllocateNode();
				if (NULL == temp) {
					puts("Allocation error");
					return EXIT_FAILURE;
				}
				temp->num = p->next->num;
				temp->next = NULL;
				InsertAfter(temp, un);

				p = p->next;
				un = un->next;
			}
		}
	}
	return EXIT_SUCCESS;
}

int IntersectionList(position p, position q, position in) {
	position temp = NULL;

	while (NULL != p->next && NULL != q->next) {
		if (p->next->num == q->next->num) {

			temp = AllocateNode();
			if (NULL == temp) {
				puts("Allocation error");
				return EXIT_FAILURE;
			}
			temp->num = p->next->num;
			temp->next = NULL;
			InsertAfter(temp, in);

			p = p->next;
			q = q->next;
			in = in->next;
		}
		else if (p->next->num > q->next->num) {

				temp = AllocateNode();
				if (NULL == temp) {
					puts("Allocation error");
					return EXIT_FAILURE;
				}
				q = q->next;
		}
		else if (p->next->num < q->next->num) {

				if (q->next != NULL)
					temp = AllocateNode();
				if (NULL == temp) {
					puts("Allocation error");
					return EXIT_FAILURE;
				}
				p = p->next;
	
		}
	}
	return EXIT_SUCCESS;
}