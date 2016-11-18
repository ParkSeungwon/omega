//should be compiled with gcc -x c option to force C compile (.C -> g++ default)
#include<stdio.h>
#include<time.h>
#include<string.h>
#include<stdlib.h>
#include"queue.h"
int Xai(); 
int Oai();
char* compress();
void decompress(char*);
extern char board[20][20];
extern struct Tree* tree;

int main() {
	tree = NULL;
	srand(time(NULL));
	init();
	int i;
	printf("%d", find_straight("OOs"));
	int place; 
	for(int i=0; i<90; i++) {
		int xy = Oai();
		show();
		if(xy != -1) {
	//		board[xy%100][xy/100] = 'o';
			printf("O win\n");
			break;
		}
		xy = Xai();
		show();
		if(xy != -1) {
	//		board[xy%100][xy/100] = 'x';
			printf("X win\n");
			break;
		}
	}
	char *co = compress();
	init();
	show();
	decompress(co);
	show();
	tshow(tree);
	tfree(tree);
	free(co);
}
