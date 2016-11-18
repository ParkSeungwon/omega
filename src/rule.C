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
typedef struct Tree {
	element* data;
	unsigned int* result;
	struct Tree *left, *right;
} Tree;
extern struct Tree* tree;
extern Tree* hash[400];

int main(int c, char** v) {
	tree = NULL;
	srand(time(NULL));
	init();
	int i;
	printf("%d", find_straight("OOs"));
	int place; 
	int game = atoi(v[1]);
	while(game) {
		init();
		for(int i=0; i<200; i++) {
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
		game--;
		printf("game %d\n", game);
	}
//	char *co = compress();
//	init();
//	show();
//	decompress(co);
//	show();
	tshow(hash[3]);
	for(int i=0; i<400; i++) if(hash[i]) tfree(hash[i]);
//	free(co);
}
