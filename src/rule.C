//should be compiled with gcc -x c option to force C compile (.C -> g++ default)
#include<stdio.h>
#include<time.h>
#include<string.h>
#include<stdlib.h>
#include<dirent.h>
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

int main(int c, char** v)
{
	if(c < 2) {
		printf("usage : %s [times]", v[0]);
		return 0;
	}


    DIR *dp;
    struct dirent *dirp;
    dp  = opendir(".");
    while ((dirp = readdir(dp)) != NULL) {
		int file_num;
        if(file_num = is_dat(dirp->d_name)) {
			FILE* f = fopen(dirp->d_name, "r");
			printf("opening %s\n", dirp->d_name);
			hash[file_num] = tload(hash[file_num], f);
			fclose(f);
		}
    }
    closedir(dp);


	srand(time(NULL));
	int game = atoi(v[1]);
	while(game) {
		init();
		for(int i=0; i<200; i++) {
			int xy = Oai();
		//	show();
			if(xy != -1) {
				printf("O win\n");
				break;
			}
			xy = Xai();
		//	show();
			if(xy != -1) {
				printf("X win\n");
				break;
			}
		}
		game--;
		printf("game %d\n", game);
	}
	show();
	for(int i=0; i<400; i++) if(hash[i]) {
		char b[10];
		snprintf(b, 10, "%d", i);
		strcat(b, ".dat");
		FILE* f = fopen(b, "w");
		tsave(hash[i], f);
		fclose(f);
		tfree(hash[i]);
	}
}
