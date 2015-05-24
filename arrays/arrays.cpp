#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <cmath>
#include <stack>
#include <set>
using namespace std;

#define MAX_ELEMS 			20
#define REVERSE(v)			{ 	int a;							\
								a = (v >> 24);					\
								v = (v << 8) | a;				\
																\
								a = (v >> 24);					\
								v = (v << 8) | a;				\
																\
								a = (v >> 24);					\
								v = (v << 8) | a;				\
																\
								a = (v >> 24);					\
								v = (v << 8) | a;				\
							}

int array[MAX_ELEMS];
int N;


void printArray() {
	for (int i=0; i<MAX_ELEMS; i++)  {
		printf(" [%02d]", i);
	}
	printf("\n");

	printf("|");
	for (int i=0; i<=N; i++) {
		printf(" [%02d]", array[i]);
	}
}

void appendRandom(int qtd) {
	for (int i=1; i<=qtd; i++) {
		array[++N] = rand() % MAX_ELEMS;	
	}
}

void appendNSeq(int lo, int hi) {
	for (int i=lo; i<=hi; i++) {
		array[++N] =i;	
	}
}

void removeDuplicates() {
	int i=0, j=i;

	while (j <= N) {
		printf("Copying array[%d]=%d to array[%d]=%d\n", j, array[j], i, array[i]);
		array[i] = array[j];
		while (array[i] == array[j] && j<=N) j++;
		i++;
	}
	printf("i = %d\n", i);
	N = i-1;
}

int cmpInt(const void *p1, const void *p2) {
	int *pi1 = (int *) p1;
	int *pi2 = (int *) p2;

	return *pi1 - *pi2;
}

void sort() {
	if (N < 0) return ;

	qsort(array, N+1, sizeof(int), cmpInt);
}

int binSearch(int lo, int hi, int key) {
	int midIdx = ceil((lo + hi) / 2);
	int midVal = array[midIdx];

	while (lo <= hi) {
		if (midVal == key) return midIdx;
		else if (midVal > key) return binSearch(lo, midIdx-1, key);
		else return binSearch(midIdx+1, hi, key);
	}

	return -1;
}

void showMenu() {
	system("clear");
	printf("00) Finish execution.\n");
	printf("01) Append N random integers.\n");
	printf("02) Append N seq integers.\n");
	printf("03) Remove duplicates.\n");
	printf("04) Clear the array.\n");
	printf("05) Sort the array.\n");
	printf("06) Binary search for an element.\n");
	printf("***************\n");
	printf("51) ...\n");
}


int main() {
	N = -1;
	srand( time(NULL) );

	while (true) {
		int cmd = 0;
		int val = 0;

		showMenu();

		printf("\n|-------------------------------------------------------------------------------------------------------|\n");
		printf("|");
		printArray();
		printf("\n");
		printf("|-------------------------------------------------------------------------------------------------------|\n");

		printf("Which option? ");
		scanf("%d", &cmd);

		switch (cmd) {
			case 0: 
				exit(0);
			case 1: {
				printf("How many? ");
				scanf("%d", &val);
				appendRandom(val);
				break;
			}
			case 2: {
				printf("Low? ");
				scanf("%d", &cmd);
				printf("High? ");
				scanf("%d", &val);
				appendNSeq(cmd, val);
				break;
			}
			case 3: {
				removeDuplicates();
				break;
			}
			case 4: {
				N=-1;
				break;
			}
			case 5: {
				sort();
				break;
			}
			case 6: {
				printf("Search for what? ");
				scanf("%d", &val);
				val = binSearch(0, N, val);
				if (val != -1) 
					printf("Val found at %d\n", val);
				else 
					printf("Value not found in the array.\n");
				getchar();
				break;
			}
		}
	}

	return 0;
}
