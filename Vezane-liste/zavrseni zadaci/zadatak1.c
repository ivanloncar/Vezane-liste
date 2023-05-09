#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NAME (256)
#define ERROR_ (-1)

struct Student;
typedef struct Student student;
typedef struct Student* position;

struct Student {
	char ime[MAX_NAME];
	char prezime[MAX_NAME];
	int bodovi;
};

position AllocateAndRead(char*, int*, position);
position Allocate(int);
position UpisStudenta(position, int, FILE*);
int Maksimalni(position, int);
void Ispis(position, int, int);
int main() {
	char* fileName = "student.txt";
	int studentCounter = 0;
	position arrayStudent = NULL;
	int max = 0;

	arrayStudent = AllocateAndRead("studenti.txt", &studentCounter, arrayStudent);
	if (NULL == arrayStudent) {
		puts("Error");
		return ERROR_;
	}

	max = Maksimalni(arrayStudent, studentCounter);
	Ispis(arrayStudent, studentCounter, max);
	free(arrayStudent);

	return 0;
}

position AllocateAndRead(char* fileName, int* counter, position arrayStudent) {
	char c;
	FILE* fp = NULL;
	fp = fopen(fileName, "r");

	if (NULL == fp) {
		puts("AllocateAndRead error!");
		return NULL;
	}

	c = getc(fp);
	if (c == '\n') {
		puts("No students!");
		return NULL;
	}

	while (!feof(fp)) {
		if (c == '\n') {
			(*counter)++;
		}
		c = getc(fp);
	}

	arrayStudent = Allocate(*counter);
	if (NULL == arrayStudent) {
		puts("Allocation error!");
		return NULL;
	}
	rewind(fp);

	arrayStudent = UpisStudenta(arrayStudent, *counter, fp);

	fclose(fp);

	return arrayStudent;
}

position Allocate(int numOfStudents) {
	position pos = NULL;
	pos = (position)malloc(numOfStudents * sizeof(student));
	if (NULL == pos) {
		puts("Allocate function error!");
		return NULL;
	}
	return pos;
}

position UpisStudenta(position arrayStudent, int counter, FILE* fp) {
	for (int i = 0; i < counter; i++) {
		fscanf(fp, " %s %s %d", arrayStudent[i].ime, arrayStudent[i].prezime, &arrayStudent[i].bodovi);
	}
	return arrayStudent;
}
int Maksimalni(position arrayStudent, int counter) {
	int max = 0;
	max = arrayStudent[0].bodovi;
	for (int i = 1; i < counter; i++) {
		if (arrayStudent[i].bodovi > max) {
			max = arrayStudent[i].bodovi;
		}
	}

	return max;
}
void Ispis(position arrayStudent, int counter, int max) {
	for (int i = 0; i < counter; i++) {
		printf("\n\t\r%s %s %d %lf", arrayStudent[i].ime, arrayStudent[i].prezime, arrayStudent[i].bodovi, (double)100 * arrayStudent[i].bodovi / max);
	}
}