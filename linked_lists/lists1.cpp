#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <cmath>
#include <stack>
#include <set>
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
		printf("empty\n");
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

	printf("\n");
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

void removeDuplicates(struct node* head) {
	if (head == NULL) return ;

	set<int> present;
	present.insert(head->data);

	struct node* prev 	= head;
	head 				= head->next;

	while (head != NULL) {
		if ( present.find(head->data) != present.end() ) {
			prev->next = head->next;
			free(head);
			head = prev->next;
		}
		else {
			present.insert(head->data);
			prev = head;
			head = head->next;
		}
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

/// connect the final of the shorter list to the middle of the larger
void createCommonNode(struct node* A, struct node* B) {
	if (A == NULL || B == NULL) return ;

	int sza = listLength(A);
	int szb = listLength(B);
	struct node* prev = NULL;

	if (sza < szb) {
		/// go to end of A
		while (A != NULL) {
			prev = A;
			A = A->next;
		}

		/// go to "mid" of B
		szb = ceil(szb / 2);
		while (szb != 0 && B != NULL) {
			szb--;
			B = B->next;
		}

		/// connect end of A to middle of B
		prev->next = B;
	}
	else {
		while (B != NULL) {
			prev = B;
			B = B->next;
		}

		/// go to "mid" of B
		sza = ceil(sza / 2);
		while (sza != 0 && A != NULL) {
			sza--;
			A = A->next;
		}

		/// connect end of A to middle of B
		prev->next = A;
	}
}

void firstCommonNode(struct node* A, struct node* B) {
	if (A == NULL || B == NULL) return ;

	int sza = listLength(A);
	int szb = listLength(B);
	int diff = sza - szb;

	if (diff < 0) {
		while (diff != 0) {
			B = B->next;
			diff++;		// two lines here
		}
	}
	else {
		while (diff != 0) {
			A = A->next;
			diff--;		/// two lines here
		}
	}

	while (A != NULL && B != NULL) {
		if (A == B) {
			printf("Intersect at %02d\n", A->data);
			break;
		}

		A = A->next;
		B = B->next;
	}
}

bool isIn(int key, struct node* head) {
	if (head == NULL) return false;

	if (head->data == key) return true;
	else return isIn(key, head->next);
}

struct node* listIntersec(struct node* A, struct node* B) {
	if (A == NULL || B == NULL) return NULL;

	A->next = listIntersec(A->next, B);

	if ( isIn(A->data, B) ) {
		return A;
	}
	else {
		struct node* next = A->next;
		free(A);
		return next;
	}
}

void showMenu() {
	system("clear");
	printf("00) Finish execution.\n");
	printf("01) Insert into list.\n");
	printf("02) Remove from list.\n");
	printf("03) Append to list.\n");
	printf("04) Print Nth element.\n");
	printf("05) Print Nth to last element.\n");
	printf("06) Reverse the list.\n");
	printf("07) Clear the list.\n");
	printf("08) Create a list with {5, 4, 3, 2, 1}.\n");
	printf("09) Append a random list.\n");
	printf("10) Remove duplicates.\n");
	printf("11) Create a common node.\n");
	printf("12) Find first common node.\n");
	printf("13) Intersect the two lists.\n");
	printf("***************\n");
	printf("51) Mergesort the list.\n");
}


int main() {
	struct node* lists[] = {NULL, NULL};

	while (true) {
		int cmd = 0;
		int val = 0;

		showMenu();

		printf("\n|--------------------------------------------------------------------------|\n");
		printf("| List-0: ");
		printList(lists[0]);
		printf("| List-1: ");
		printList(lists[1]);
		printf("|--------------------------------------------------------------------------|\n");
		printf("| Size-0 = {%d, %d}\n", listLength(lists[0]), listLengthRecur(lists[0]));
		printf("| Size-1 = {%d, %d}\n", listLength(lists[1]), listLengthRecur(lists[1]));
		printf("|--------------------------------------------------------------------------|\n");
		printf("| Median-0 = {%d, %d}\n", getMedian(lists[0]), getMedianRecur(lists[0]));
		printf("| Median-1 = {%d, %d}\n", getMedian(lists[1]), getMedianRecur(lists[1]));
		printf("|--------------------------------------------------------------------------|\n");
		printf("| Palindrome-0 = {%d, %d}\n", isPalindromeStack(lists[0]), isPalinRecursive(lists[0]));
		printf("| Palindrome-1 = {%d, %d}\n", isPalindromeStack(lists[1]), isPalinRecursive(lists[1]));
		printf("|--------------------------------------------------------------------------|\n\n");

		printf("Which option? ");
		scanf("%d", &cmd);
		getchar();

		switch (cmd) {
			case 0: 
				exit(0);
			case 1: {
				printf("Val? ");
				scanf("%d", &val);
				push(&lists[0], val);
				break;
			}
			case 2: {
				printf("Val? ");
				scanf("%d", &val);
				deleteNode(&lists[0], val);
				break;
			}
			case 3: {
				printf("Val? ");
				scanf("%d", &val);
				append(&lists[0], val);
				break;
			}
			case 4: {
				printf("Val? ");
				scanf("%d", &val);
				printf("The %d-th element is %d\n", val, getNth(lists[0], val));
				sleep(2);
				break;
			}
			case 5: {
				printf("Val? ");
				scanf("%d", &val);
				printf("The %d-th to last element is ", val);
				getNthToLast(lists[0], val);
				printf("\n");
				sleep(2);
				break;
			}
			case 6: {
				reverse(&lists[0]);
				break;
			}
			case 7: {
				printf("Which? ");
				scanf("%d", &val);
				clear(&lists[val]);
				break;
			}
			case 8: {
				build15(&lists[0]);
				break;
			}
			case 9: {
				printf("Which? ");
				scanf("%d", &val);
				randList(&lists[val]);
				break;
			}
			case 10: {
				removeDuplicates(lists[0]);
				break;
			}
			case 11: {
				createCommonNode(lists[0], lists[1]);
				printf("Done. Watch out!\n");
				getchar();
				break;
			}
			case 12: {
				firstCommonNode(lists[0], lists[1]);
				getchar();
				break;
			}
			case 13: {
				lists[0] = listIntersec(lists[0], lists[1]);
				break;
			}
			case 51: {
				lists[0] = mergesort(lists[0]);
				break;
			}



		}
	}

	return 0;
}
