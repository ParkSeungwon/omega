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
char board[20][20];

void init() {
	for(int y=0; y<20; y++) for(int x=0; x<20; x++) board[y][x] = ' ';
	board[10][10] = 'X';
}

void show() {
	printf(" ");
	for(int i=0; i<10; i++) printf("%d", i);
	for(int i=0; i<10; i++) printf("%d", i);
	printf("\n");
	for(int y=0; y<20; y++) {
		printf("%d", y%10);
		for(int x=0; x<20; x++) printf("%c", board[y][x]);
		printf("%d\n", y%10);
	}
	printf(" ");
	for(int i=0; i<10; i++) printf("%d", i);
	for(int i=0; i<10; i++) printf("%d", i);
	printf("\n");
}

char* crop() {//not use for simplicity
	int minx=19, maxx=0, miny=19, maxy=0;
	int rx, ry;
	for(int y=0; y<20; y++) for(int x=0; x<20; x++) {
		if(board[y][x] == 'x' || board[y][x] == 'o') {
			rx = x; ry = y;
		} else if(board[y][x] != ' ') {
			minx = min(minx, x);
			maxx = max(maxx, x);
			miny = min(miny, y);
			maxy = max(maxy, y);
		}
	}
	int w = maxx - minx + 1;
	int h = maxy - miny + 1;
	char *r = (char*)malloc(w * h + 4);
	r[0] = w; r[1] = h;
	int n = 2;
	for(int y=miny; y<=maxy; y++) for(int x=minx; x<=maxx; x++) r[n++] = board[y][x];
	r[n++] = rx - minx; 
	r[n++] = ry - miny;
	return r;
}

	
int main() {
	srand(time(NULL));
	init();
	char *p = crop();
	printf("%d X %d : ", p[0], p[1]);
	int i;
	for(i=2; i<p[0]*p[1]+2; i++) printf("%c", p[i]);
	printf("%d X %d : ", p[i++], p[i++]);
	printf("\n");
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
	int pl = check();
	printf("%d\n", pl);
	free(p);
	free(co);
}
