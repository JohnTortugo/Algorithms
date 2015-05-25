#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <string.h>
#include <cmath>
#include <stack>
#include <set>
#include <queue>
using namespace std;

#define MAX_ELEMS 			50

char str[MAX_ELEMS];
int N;


void printStr() {
	printf("[%02d] ", N);
	for (int i=0; i<=N; i++) printf("%c", str[i]);
}

bool checkParentheses() {
	int checks[] = {0, 0, 0};

	for (int i=0; i<=N; i++) {
		if (str[i] != '(' && str[i] != ')' &&
			str[i] != '[' && str[i] != ']' &&
			str[i] != '{' && str[i] != '}') return false;

		if (str[i] == '(')
			checks[0]++;
		else if (str[i] == ')')
			checks[0]--;

		if (str[i] == '[')
			checks[1]++;
		else if (str[i] == ']')
			checks[1]--;

		if (str[i] == '{')
			checks[2]++;
		else if (str[i] == '}')
			checks[2]--;

		if (checks[0] < 0 || checks[1] < 0 || checks[2] < 0) return false;
	}

	if (checks[0] > 0 || checks[1] > 0 || checks[2] > 0) return false;

	return true;
}

void removeDuplicates(char* str) {
	if (str == NULL) return ;

	bool exist[256];
	int i=0, j=0;

	for (i=0; i<256; i++) exist[i] = false;

	for (i=0, j=0; str[j] != '\0'; j++) {
		if (exist[str[j]] == false) {
			exist[str[j]] = true;
			str[i] = str[j];
			i++;
		}
	}

	str[i] = '\0';
	N = strlen(str) - 2;
}

void rleEncode(char* str) {
	int r=0, w=0;
	char c = '0';
	queue<char> aux;

	while (r <= N || !aux.empty()) {
		int qtd = 1;

		if (!aux.empty()) {
			c = aux.front(); aux.pop();
			while (!aux.empty() && aux.front() == c && qtd < 9) {
				aux.pop();
				qtd++;
			}
			if (qtd < 9 && aux.empty()) {
				while (str[r] == c && r <= N && qtd < 9) {
					r++;
					qtd++;
				}
			}
		}
		else {
			c = str[r++];
			while (str[r] == c && r <= N && qtd < 9) {
				r++;
				qtd++;
			}
		}


		if (w == r && r <= N) {
			aux.push(str[r++]);
		}
		w++;

		if (w == r && r <= N) {
			aux.push(str[r++]);
		}
		w++;

		str[w-2] = c;
		str[w-1] = '0' + qtd;
	}

	N = w-1;
}

void rleDecode(char* str) {

}

void showMenu() {
	system("clear");
	printf("00) Finish execution.\n");
	printf("01) Input a string.\n");
	printf("02) Check parenthesization (),[],{}.\n");
	printf("03) Remove duplicates.\n");
	printf("03) Remove duplicates.\n");
	printf("04) RLE Encode.\n");
	printf("05) RLE Decode.\n");
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
		printStr();
		printf("\n");
		printf("|-------------------------------------------------------------------------------------------------------|\n");

		printf("Which option? ");
		scanf("%d", &cmd);
		getchar();

		switch (cmd) {
			case 0: 
				exit(0);
			case 1: {
				printf("Type the str: "); 
				fgets(str, MAX_ELEMS, stdin);
				N = strlen(str) - 2;
				break;
			}
			case 2: {
				printf("The parenthesization is%scorrect.\n", checkParentheses() ? " " : " not ");
				getchar();
				break;
			}
			case 3: {
				removeDuplicates(str);
				break;
			}
			case 4: {
				rleEncode(str);
				break;
			}
			case 5: {
				rleDecode(str);
				break;
			}

		}
	}

	return 0;
}
