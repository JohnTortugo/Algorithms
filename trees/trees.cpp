#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <cmath>
#include <stack>
#include <set>
#include <queue>
#include <deque>
using namespace std;

#define MAX_LEVELS		10


////////////////////////////////////////////////////////////
typedef struct node {
	int data;
	int size;
	struct node* left;
	struct node* right;
	struct node* next;
} TreeNode;

typedef TreeNode* 	TreeNode_p;
typedef TreeNode** 	TreeNode_pp;

TreeNode_p byLevels[] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL}; 


////////////////////////////////////////////////////////////
void showMenu() {
	system("clear");
	printf("00) Finish execution.\n");
	printf("01) Clear the current trees.\n");
	printf("02) Create random Binary Search Tree.\n");
	printf("03) Create random Binary Tree.\n");
	printf("04) Print the B[S]T by level.\n");
	printf("05) Compare if both trees are equal.\n");
	printf("06) Print all paths.\n");
	printf("07) Are trees complete BT?.\n");
	printf("08) Are trees BST?.\n");
	printf("09) Insert into BT.\n");
	printf("10) Search for a key.\n");
	printf("11) Show the rank.\n");
	printf("12) Delete a node from the tree.\n");
	printf("13) Connect by levels.\n");
	printf("14) Print in radial order.\n");
}

TreeNode_p clearTree(TreeNode_p root) {
	if (root == NULL) return NULL;	

	root->left = clearTree(root->left);
	root->right = clearTree(root->right);

	free(root);

	return NULL;
}

TreeNode_p createRandBST(int lo, int hi) {
	if (lo > hi) return NULL;

	int midVal = (lo + hi) / 2;
	TreeNode_p newNode = (TreeNode_p) malloc(sizeof(TreeNode));
	newNode->data = midVal;
	newNode->left = createRandBST(lo, midVal-1);
	newNode->right = createRandBST(midVal+1, hi);

	return newNode;
}

TreeNode_p createRandBT(int size) {
	if (size < 1) return NULL;	

	srand( rand() );

	int halfSize = size / 2;
	int nodeVal  = rand() % 100;

	TreeNode_p newNode = (TreeNode_p) malloc(sizeof(TreeNode));
	newNode->data = nodeVal;
	newNode->left = createRandBT(halfSize);
	newNode->right = createRandBT(halfSize);

	return newNode;
}

bool compareTrees(TreeNode_p root1, TreeNode_p root2) {
	if (root1 == NULL && root2 != NULL) return false;
	if (root1 != NULL && root2 == NULL) return false;
	if (root1 == NULL && root2 == NULL) return true;

	return 	(root1->data == root2->data) 				&& 
			compareTrees(root1->left, root2->left) 		&& 
			compareTrees(root1->right, root2->right);
}

void printInOrder(TreeNode_p root) {
	if (root == NULL) return ;

	printInOrder(root->left);
	printf("%02d ", root->data);
	printInOrder(root->right);
}

void printPosOrder(TreeNode_p root) {
	if (root == NULL) return ;

	printPosOrder(root->left);
	printPosOrder(root->right);
	printf("%02d ", root->data);
}

void printPreOrder(TreeNode_p root) {
	if (root == NULL) return ;

	printf("%02d ", root->data);
	printPreOrder(root->left);
	printPreOrder(root->right);
}

void printByLevel(TreeNode_p root) {
	if (root == NULL) return ;

	queue<pair<TreeNode_p, int>> nexts;

	int prevLevel = -1;

	nexts.push(make_pair(root, 0));

	while (nexts.empty() == false) {
		pair<TreeNode_p, int> p = nexts.front(); 
								  nexts.pop();
		TreeNode_p node = p.first;
		int lvl = p.second;

		if (prevLevel != lvl) {
			printf("\nLevel %d: ", lvl);
			prevLevel = lvl;
		}

		printf("%02d ", node->data);

		if (node->left) nexts.push( make_pair(node->left, lvl+1) );
		if (node->right) nexts.push( make_pair(node->right, lvl+1) );
	}

	printf("\n");
}

void printAllPaths(TreeNode_p root, int path[], int size) {
	if (root == NULL) return ;

	path[++size] = root->data;

	printAllPaths(root->left, path, size);
	printAllPaths(root->right, path, size);

	if (root->left == NULL && root->right == NULL) {
		for (int i=0; i<=size; i++) {
			printf("%02d ", path[i]);
		}
		printf("\n");
	}
}

bool isCompleteTree(TreeNode_p root, int* prev, int curr) {
	if (root == NULL) return true;	

	if (root->left == NULL && root->right == NULL) {
		if (*prev == -1) {
			*prev = curr;
			return true;
		}
		else if (*prev == curr) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		if (isCompleteTree(root->left, prev, curr+1))
			return isCompleteTree(root->right, prev, curr+1);

		return false;
	}
}

bool isBST(TreeNode_p root) {
	if (root == NULL) return false;

	if (root->left != NULL) {
		if (root->data < root->left->data) return false;
		if (isBST(root->left) == false) return false;
	}

	if (root->right != NULL) {
		if (root->data > root->right->data) return false;
		if (isBST(root->right) == false) return false;
	}

	return true;
}

TreeNode_p insert(TreeNode_p root, int data) {
	if (root == NULL) {
		TreeNode_p novo = (TreeNode_p) malloc(sizeof(TreeNode));
		novo->data = data;
		novo->left = NULL;
		novo->right = NULL;
		novo->size = 1;
		return novo;
	}

	if (root->data > data)
		root->left = insert(root->left, data);
	else
		root->right = insert(root->right, data);
	
	root->size = 1 + ((root->left != NULL) ? root->left->size : 0) +
					 ((root->right != NULL) ? root->right->size : 0);
}

int leftmost(TreeNode_p root) {
	if (root == NULL) return -1;

	while (root->left != NULL) 
		root = root->left;

	return root->data;
}

TreeNode_p deleteNode(TreeNode_p root, int data) {
	if (root == NULL) return NULL;

	if (root->data > data) {
		root->left = deleteNode(root->left, data);
	}
	else if (root->data < data) {
		root->right = deleteNode(root->right, data);
	}
	else {
		TreeNode_p aux = NULL;

		if (root->left == NULL && root->right == NULL) {
			free(root);
			return NULL;
		}
		else if (root->left == NULL) {
			aux = root->right;
			free(root);
			return aux;
		}
		else if (root->right == NULL) {
			aux = root->left;
			free(root);
			return aux;
		}
		else {
			root->data  = leftmost(root->right);
			root->right = deleteNode(root->right, root->data);
		}
	}

	return root;
}

bool search(TreeNode_p root, int data) {
	if (root == NULL) return false;
	if (root->data == data) return true;
	else if (root->data > data) return search(root->left, data);
	else return search(root->right, data);
}

int treeRank(TreeNode_p root, int data) {
	if (root == NULL) return 0;

	if (root->data == data)
		return (root->left != NULL) ? root->left->size : 0;
	else if (root->data > data)
		return treeRank(root->left, data);
	else
		return 1 + ((root->left != NULL) ? root->left->size : 0) + 
				   treeRank(root->right, data);
}

void updateLevel(TreeNode_p root, int currLevel) {
	if (byLevels[currLevel] != NULL)
		byLevels[currLevel]->next = root;

	byLevels[currLevel] = root;
}

void connectByLevels(TreeNode_p root, int currLevel) {
	if (root == NULL) return ;

	updateLevel(root, currLevel);

	connectByLevels(root->left, currLevel+1);
	connectByLevels(root->right, currLevel+1);
}

void printRadial(TreeNode_p root) {
	if (root == NULL) return ;

	deque<TreeNode_p> A;
	deque<TreeNode_p> B;

	A.push_front(root);

	do {
		while (!A.empty()) {
			TreeNode_p no = A.front(); A.pop_front();
			printf("%d ", no->data);
			if (no->left != NULL) B.push_front(no->left);
			if (no->right != NULL) B.push_front(no->right);
		}
		printf("\n");

		while (!B.empty()) {
			TreeNode_p no = B.front(); B.pop_front();
			printf("%d ", no->data);
			if (no->right != NULL) A.push_front(no->right);
			if (no->left != NULL) A.push_front(no->left);
		}
		printf("\n");
	} while (!A.empty());
}

int main() {
	TreeNode_p tree[] = {NULL, NULL};

	srand( time(NULL) );

	while (true) {
		int cmd = 0;
		int val = 0;

		showMenu();

		printf("\n|--------------------- In Order ------------------------------------------------|\n");
		printf("| ");
		printInOrder(tree[0]);
		printf("\n| ");
		printInOrder(tree[1]);
		printf("\n|--------------------- Pre Order -----------------------------------------------|\n");
		printf("| ");
		printPreOrder(tree[0]);
		printf("\n| ");
		printPreOrder(tree[1]);
		printf("\n");
		printf("|--------------------- Pos Order -----------------------------------------------|\n");
		printf("| ");
		printPosOrder(tree[0]);
		printf("\n| ");
		printPosOrder(tree[1]);
		printf("\n");
		printf("|-------------------------------------------------------------------------------|\n\n");


		printf("Which option? ");
		scanf("%d", &cmd);
		getchar();

		switch (cmd) {
			case 0: 
				exit(0);
			case 1: {
				int wh;
				printf("which? "); scanf("%d", &wh); getchar();
				tree[wh] = clearTree(tree[wh]);
				break;
			}
			case 2: {
				int lo, hi, wh;
				printf("which? "); scanf("%d", &wh); getchar();
				printf("lo? "); scanf("%d", &lo); getchar();
				printf("hi (2^n-1)? "); scanf("%d", &hi); getchar();
				tree[wh] = createRandBST(lo, hi);	
				break;
			}
			case 3: {
				int sz, wh;
				printf("size (2^n-1)? "); scanf("%d", &sz); getchar();
				printf("which? "); scanf("%d", &wh); getchar();
				tree[wh] = createRandBT(sz);	
				break;
			}
			case 4: {
				printf("Tree 1: \n");
				printByLevel(tree[0]);	
				printf("-------\nTree 2: \n");
				printByLevel(tree[1]);	
				getchar();
				break;
			}
			case 5: {
				bool equal = compareTrees(tree[0], tree[1]);	
				printf("These tress are%sequal.\n", equal ? " " : " not ");
				getchar();
				break;
			}
			case 6: {
				int path[1000];
				printf("Tree 1: \n");
				printAllPaths(tree[0], path, -1);
				printf("-------\nTree 2: \n");
				printAllPaths(tree[1], path, -1);	
				getchar();
				break;
			}
			case 7: {
				int prev = -1;
				printf("Tree [0]%sis a complete Binary Tree.\n", isCompleteTree(tree[0], &prev, 0) ? " " : " not ");
				printf("Tree [1]%sis a complete Binary Tree.\n", isCompleteTree(tree[1], &prev, 0) ? " " : " not ");
				getchar();
				break;
			}
			case 8: {
				printf("Tree [0]%sis a Binary Search Tree.\n", isBST(tree[0]) ? " " : " not ");
				printf("Tree [1]%sis a Binary Search Tree.\n", isBST(tree[1]) ? " " : " not ");
				getchar();
				break;
			}
			case 9: {
				int vl, wh;
				printf("which? "); scanf("%d", &wh); getchar();
				printf("value? "); scanf("%d", &vl); getchar();
				tree[wh] = insert(tree[wh], vl);	
				break;
			}
			case 10: {
				int vl, wh;
				printf("which? "); scanf("%d", &wh); getchar();
				printf("value? "); scanf("%d", &vl); getchar();
				printf("Value %d%sfound in the tree.\n", vl, search(tree[wh], vl) ? " " : " not ");	
				getchar();
				break;
			}
			case 11: {
				int vl, wh;
				printf("which? "); scanf("%d", &wh); getchar();
				printf("value? "); scanf("%d", &vl); getchar();
				printf("Rank of %d is %d.\n", vl, treeRank(tree[wh], vl));	
				getchar();
				break;
			}
			case 12: {
				int vl, wh;
				printf("which? "); scanf("%d", &wh); getchar();
				printf("value? "); scanf("%d", &vl); getchar();
				tree[wh] = deleteNode(tree[wh], vl);	
				break;
			}
			case 13: {
				int wh;
				printf("which? "); scanf("%d", &wh); getchar();
				connectByLevels(tree[wh], 0);	
				break;
			}
			case 14: {
				int wh;
				printf("which? "); scanf("%d", &wh); getchar();
				printRadial(tree[wh]);	
				getchar();
				break;
			}
		}
	}

	return 0;
}
