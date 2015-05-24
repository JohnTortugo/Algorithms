#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <cmath>
#include <stack>
#include <set>
using namespace std;

int heap[1000000];
int array[1000000];
int lastIdx;
int heapN;


void swapArr(int i, int j) {
	int aux = array[i];
	array[i] = array[j];
	array[j] = aux;
}

void heapSwap(int i, int j) {
	int aux = heap[i];
	heap[i] = heap[j];
	heap[j] = aux;
}

void addVal(int val) {
	array[++lastIdx] = val;
}

void printArray() {
	if (lastIdx >= 0) 
		printf("[%02d]", array[0]);

	for (int i=1; i<=lastIdx; i++)  {
		printf(" [%02d]", array[i]);

		if ( ((i+1) % 16) == 0) 
			printf("\n|");
	}
}

void printHeap() {
	if (heapN >= 1) 
		printf("[%02d]", heap[1]);

	for (int i=2; i<=heapN; i++)  {
		printf(" [%02d]", heap[i]);
	}
}


void appendRandom() {
	srandom( time(NULL) );

	for (int i=1; i<=10; i++) {
		int val = rand() % 100;
		addVal(val);
	}
}

void checkSorted() {
	if (lastIdx < 0) return ;

	int prev = array[0];

	for (int i=1; i<=lastIdx-1; i++) {
		if (prev > array[i]) {
			printf("WARNING: Not sorted!!! %d > %d\n", prev, array[i]);
			sleep(2);
			return ;
		}
		prev = array[i];
	}
}

void selectionSort() {
	for (int i=0; i<=lastIdx-1; i++) {
		int minVal = 1000000000;
		int minIdx = i;

		for (int j=i; j<=lastIdx; j++) {
			if (array[j] < minVal) {
				minVal = array[j];
				minIdx = j;
			}
		}

		swapArr(i, minIdx);
	}
}

void insertionSort() {
	for (int i=1; i<=lastIdx; i++) {
		for (int j=i-1; j>=0; j--) {
			if (array[j] > array[j+1]) {
				swapArr(j, j+1);
			}
			else {
				break;
			}
		}
	}
}


void sink(int k) {
	while (2*k+1 <= heapN) {
		int pos = 2*k;
		if (heap[pos] < heap[pos+1]) pos++;
		if (heap[k] > heap[pos]) break;
		heapSwap(k, pos);
		k = pos;
	}
}

void swim(int k) {
	while (k > 1 && heap[k/2] < heap[k]) {
		heapSwap(k/2, k);
		k = k / 2;
	}
}

int getMax() {
	int max = heap[1];
	heapSwap(1, heapN);
	heap[heapN] = -1;
	heapN--;
	sink(1);
	return max;
}

void insert(int data) {
	heapN++;
	heap[heapN] = data;
	swim(heapN);
}

void printHeaders() {
	printf("[%02d]", 1);

	for (int i=2; i<=16; i++)  {
		printf(" [%02d]", i);
	}
}

void heapify() {
	for (int k=ceil(heapN/2.0); k>=1; k--)
		sink(k);
}

void heapSort() {
	heapify();

	int aux = heapN;

	while (heapN > 1) {
		heapSwap(1, heapN--);
		sink(1);
	}

	heapN = aux;
}

void bubbleSort() {
	for (int i=0; i<=lastIdx-1; i++) {
		for (int j=0; j<=lastIdx-1; j++) {
			if (array[j] > array[j+1])
				swapArr(j, j+1);
		}
	}
}

void showMenu() {
	system("clear");
	printf("00) Finish execution.\n");
	printf("01) Append 10 random values.\n");
	printf("02) Insert into list.\n");
	printf("03) Insert into heap.\n");
	printf("04) Maximum from heap.\n");

	printf("***********\n");
	printf("50) Apply selection sort.\n");
	printf("51) Apply insertion sort.\n");
	printf("52) Apply heap sort.\n");
	printf("53) Apply bubble sort.\n");
}

int main() {
	lastIdx=-1;
	heapN=0;

	while (true) {
		int cmd = 0;
		int val = 0;

		showMenu();

		printf("\n|-------------------------------------------------------------------------------|\n");
		printf("| ");
		printHeaders();
		printf("\n|-------------------------------------------------------------------------------|\n");
		printf("| ");
		printArray();
		printf("\n");
		printf("|-------------------------------------------------------------------------------|\n");
		printf("| ");
		printHeap();
		printf("\n");
		printf("|-------------------------------------------------------------------------------|\n");



		printf("Which option? ");
		scanf("%d", &cmd);

		switch (cmd) {
			case 0: 
				exit(0);
			case 1: {
				appendRandom();	
				break;
			}
			case 2: {
				printf("Val? ");
				scanf("%d", &val);
				addVal(val);
				break;
			}
			case 3: {
				printf("Val? ");
				scanf("%d", &val);
				insert(val);
				break;
			}
			case 4: {
				printf("Max from heap is %d.\n", getMax());
				sleep(2);
				break;
			}
	
			case 50: {
				selectionSort();	
				checkSorted();
				break;
			}
			case 51: {
				insertionSort();	
				checkSorted();
				break;
			}
			case 52: {
				heapSort();	
				break;
			}
			case 53: {
				bubbleSort();	
				break;
			}

		}
	}

	return 0;
}
