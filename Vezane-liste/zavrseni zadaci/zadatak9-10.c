#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void ExchangeSort(int* niz,int size);
void CalcTimeExchangeSort(int* array, clock_t* start, clock_t* end,int size);
void CopySort(int*,int*,int size);
int main() {
    clock_t start, end;
    int i = 0;

    srand(time(NULL));

    int array1[10] = {0};
    int array1Copy[10] = { 0 };
    for (i = 0; i < 10; i++) {
        array1[i] = rand();
        array1Copy[i] = array1[i];
    }

    int array2[100] = {0};
    int array2Copy[100] = { 0 };
    for (i = 0; i < 100; i++) {
        array2[i] = rand();
        array2Copy[i] = array2[i];
    }

    int array3[1000] = {0};
    int array3Copy[1000] = {0};
    for (i = 0; i < 1000; i++) {
        array3[i] = rand();
        array3Copy[i] = array3[i];
    }
    int array4[10000] = {0};
    int array4Copy[10000] = { 0 };
    for (i = 0; i < 10000; i++) {
        array4[i] = rand();
        array4Copy[i] = array4[i];
    }

    //ExchangeSort through 4 array
    CalcTimeExchangeSort(array1, &start, &end, 10);
    CopySort(array1,array1Copy,10);
    CalcTimeExchangeSort(array2, &start, &end, 100);
    CopySort(array2, array2Copy, 100);
    CalcTimeExchangeSort(array3, &start, &end, 1000);
    CopySort(array3, array3Copy, 1000);
    CalcTimeExchangeSort(array4, &start, &end, 10000);
    CopySort(array4, array4Copy, 10000);

	return EXIT_SUCCESS;
}

void ExchangeSort(int* array, int size) {
    int i, j, temp;
    for (i = 0; i < (size - 1); i++)
    {
        for (j = (i + 1); j < size; j++)
        {
            if (array[i] > array[j])
            {
                temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
    }
}

void CalcTimeExchangeSort(int* array, clock_t* start, clock_t* end, int size) {
    start = clock();
    ExchangeSort(array, size);
    end = clock();
    printf("\nExchangeSort time: %lf", (double)(end - start));
}

void CopySort(int* array, int* arrayCopy, int size) {
    int i = 0;

    for (i = 0; i < size; i++) {
        array[i] = arrayCopy[i];
    }
}