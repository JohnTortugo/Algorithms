#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <cmath>
#include <stack>
using namespace std;

struct node {
	int data;
	struct node* next;
};

void append(struct node** headRef, int data) {
	if (headRef == NULL) return ;

	if (*headRef == NULL) {
		*headRef 		 = (struct node*) malloc(sizeof(struct node));
		(*headRef)->next = NULL;
		(*headRef)->data = data;
	}
	else {
		struct node* last = *headRef;

		while (last->next != NULL) last = last->next;

		struct node* newNode = (struct node*) malloc(sizeof(struct node));
		newNode->next = NULL;
		newNode->data = data;

		last->next = newNode;
	}
}

void push(struct node** headRef, int data) {
	if (headRef == NULL) return;

	struct node* newNode = (struct node*) malloc(sizeof(struct node));
	newNode->next	 	 = *headRef;
	newNode->data	 	 = data;

	*headRef	 		 = newNode;
}

void insertAfter(struct node* prevNode, int data) {
	struct node* newNode = (struct node*) malloc(sizeof(struct node));
	newNode->next		 = prevNode->next;
	newNode->data		 = data;
	prevNode->next		 = newNode;
}

void deleteNode(struct node** headRef, int data) {
	if (headRef == NULL || *headRef == NULL) return;

	if ((*headRef)->data == data) {
		struct node* aux = *headRef;
		*headRef 		 = aux->next;
		free(aux);
		return ;
	}

	struct node* curr = *headRef;	

	while (curr->next != NULL && curr->next->data != data) {
		curr = curr->next;
	}

	if (curr->next == NULL || curr->next->data != data) return ;

	struct node* aux = curr->next;
	curr->next 		 = aux->next;

	free(aux);
}

void printList(struct node* head) {
	if (head == NULL) {
		printf("empty");
		return ;
	}

	printf("[%02d]", head->data);

	int count = 2;
	head = head->next;
	while (head != NULL) {
		printf(" [%02d]", head->data);
		head = head->next;
		if (!(count % 10) && head != NULL) printf("\n|");
		count++;
	}
}

int listLength(struct node* head) {
	int count = 0;

	while (head != NULL) head = head->next, count++;

	return count;
}

int listLengthRecur(struct node* head) {
	if (head == NULL) return 0;
	return 1 + listLengthRecur(head->next);
}

int getMedian(struct node* head) {
	int mid = ceil((double)listLength(head) / 2);
	int pos = 1;

	while (head != NULL) {
		if (pos == mid) return head->data;

		head = head->next;
		pos++;
	}

	return -1;
}

int getMedianRecur(struct node* head) {
	if (head == NULL) return -1;

	struct node* slow_ptr = head;
	struct node* fast_ptr = head;

	while (fast_ptr != NULL && fast_ptr->next != NULL) {
		fast_ptr = fast_ptr->next->next;
		slow_ptr = slow_ptr->next;
	}

	return slow_ptr->data;
}

int getNth(struct node* head, int idx) {
	int i=0;
	while (head != NULL) {
		if (i == idx) return head->data;
		i++;
		head = head->next;
	}
}

int getNthToLast(struct node* head, int idx) {
	if (head == NULL) return -1;

	int id = 1 + getNthToLast(head->next, idx);

	if (id == idx) printf("%d", head->data);

	return id;
}

void reverse(struct node** headRef) {
	if (headRef == NULL || *headRef == NULL) return ;

	struct node* prev = *headRef;
	struct node* aux  = NULL;
	struct node* curr = prev->next;
						prev->next = NULL;

	while (curr != NULL) {
		aux = curr->next;
		curr->next = prev;
		prev = curr;
		curr = aux;
	}

	*headRef = prev;
}

void clear(struct node** headRef) {
	while (*headRef != NULL) {
		struct node* aux = (*headRef)->next;

		free(*headRef);

		*headRef = aux;
	}
}

void build15(struct node** headRef) {
	append(headRef, 5);
	append(headRef, 4);
	append(headRef, 3);
	append(headRef, 2);
	append(headRef, 1);
}

bool isPalindromeStack(struct node* head) {
	if (head == NULL) return false;
	struct node* curr = head;
	stack<int> pilha;

	while (curr != NULL) {
		pilha.push(curr->data);
		curr = curr->next;
	}

	while (head != NULL) {
		int aux = pilha.top(); pilha.pop();
		if (aux != head->data) return false;
		head = head->next;
	}

	return true;
}

bool isPalinRec(struct node* head, struct node** backRef) {
	if (head == NULL) return true;

	bool palin 	= isPalinRec(head->next, backRef) && ((*backRef)->data == head->data);
	*backRef 	= (*backRef)->next;

	return palin;
}

bool isPalinRecursive(struct node* head) {
	if (head == NULL) return false;
	return isPalinRec(head, &head);
}

void randList(struct node** left) {
	srand(time(NULL));

	int newNodes = 0;
	while (newNodes == 0) 
		newNodes = rand() % 10;

	for (int i=1; i<=newNodes; i++) {
		append(left, rand() % 100);
	}
}


struct node* merge(struct node* left, struct node* right) {
	if (left == NULL) return right;
	if (right == NULL) return left;

	struct node* aux = NULL;
	struct node* prev = NULL;
	struct node* cleft = left;
	struct node* cright = right;

	while (cleft != NULL && cright != NULL) {
		if (cright->data < cleft->data) {
			aux = cright->next;
			if (prev == NULL) {
				cright->next = left;
				prev = cright;
				left = prev;
			}
			else {
				prev->next = cright;
				cright->next = cleft;
				prev = cright;
			}
			cright = aux;
		}
		else {
			prev = cleft;
			cleft = cleft->next;
		}
	}

	if (cright != NULL)
		prev->next = cright;

	return left;
}

void partition(struct node* head, struct node** left, struct node** right) {
	int mid = ceil((double)listLength(head) / 2);
	int idx = 1;

	*left  = head;
	*right = NULL;
	while (head != NULL) {
		if (idx == mid) {
			*right = head->next;
			head->next = NULL;
			break;
		}
		idx++;
		head = head->next;
	}
}

struct node* mergesort(struct node* list) {
	if (list == NULL) return NULL;
	if (list->next == NULL) return list;

	struct node* left  = NULL;
	struct node* right = NULL;

	partition(list, &left, &right);

	left = mergesort(left);
	right = mergesort(right);

	return merge(left, right);
}


void showMenu() {
	system("clear");
	printf("0) Finish execution.\n");
	printf("1) Insert into list.\n");
	printf("2) Remove from list.\n");
	printf("3) Append to list.\n");
	printf("4) Print Nth element.\n");
	printf("5) Print Nth to last element.\n");
	printf("6) Reverse the list.\n");
	printf("7) Clear the list.\n");
	printf("8) Create a list with {5, 4, 3, 2, 1}.\n");
	printf("9) Append a random list.\n");
	printf("***************\n");
	printf("10) Mergesort the list.\n");
}


int main() {
	struct node* head = NULL;

	while (true) {
		int cmd = 0;
		int val = 0;

		showMenu();

		printf("\n|--------------------------------------------------------------------------|\n");
		printf("| ");
		printList(head);
		printf("\n");
		printf("|--------------------------------------------------------------------------|\n");
		printf("| Size = {%d, %d}\n", listLength(head), listLengthRecur(head));
		printf("|--------------------------------------------------------------------------|\n");
		printf("| Median = {%d, %d}\n", getMedian(head), getMedianRecur(head));
		printf("|--------------------------------------------------------------------------|\n");
		printf("| Palindrome = {%d, %d}\n", isPalindromeStack(head), isPalinRecursive(head));
		printf("|--------------------------------------------------------------------------|\n\n");

		printf("Which option? ");
		scanf("%d", &cmd);

		switch (cmd) {
			case 0: 
				exit(0);
			case 1: {
				printf("Val? ");
				scanf("%d", &val);
				push(&head, val);
				break;
			}
			case 2: {
				printf("Val? ");
				scanf("%d", &val);
				deleteNode(&head, val);
				break;
			}
			case 3: {
				printf("Val? ");
				scanf("%d", &val);
				append(&head, val);
				break;
			}
			case 4: {
				printf("Val? ");
				scanf("%d", &val);
				printf("The %d-th element is %d\n", val, getNth(head, val));
				sleep(2);
				break;
			}
			case 5: {
				printf("Val? ");
				scanf("%d", &val);
				printf("The %d-th to last element is ", val);
				getNthToLast(head, val);
				printf("\n");
				sleep(2);
				break;
			}
			case 6: {
				reverse(&head);
				break;
			}
			case 7: {
				clear(&head);
				break;
			}
			case 8: {
				build15(&head);
				break;
			}
			case 9: {
				randList(&head);
				break;
			}
			case 10: {
				head = mergesort(head);
				break;
			}



		}
	}

	return 0;
}
