//should be compiled with gcc -x c option to force C compile (.C -> g++ default)
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"queue.h"

char board[20][20];
Queue queue;

void init() {
	for(int y=0; y<20; y++) for(int x=0; x<20; x++) board[y][x] = ' ';
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

char* crop() {
	int minx=19, maxx=0, miny=19, maxy=0;
	for(int y=0; y<20; y++) for(int x=0; x<20; x++) if(board[y][x] != ' ') {
		minx = min(minx, x);
		maxx = max(maxx, x);
		miny = min(miny, y);
		maxy = max(maxy, y);
	}
	int w = maxx - minx + 1;
	int h = maxy - miny + 1;
	char *r = (char*)malloc(w * h + 2);
	r[0] = w; r[1] = h;
	int n = 2;
	for(int y=miny; y<=maxy; y++) for(int x=minx; x<=maxx; x++) r[n++] = board[y][x];
	return r;
}

int find_straight(const char* str) {//" rOOO " -> r: return space
	char st[10] = {};
	strcpy(st, str);
	int rx = 0, ry = 0, r;
	int length, i;
	for(i=0; st[i] != '\0'; i++) {
		if(st[i] == 's') {
			r = i;//record r position
			st[i] = ' ';//change to space
		}
	}
	length = i;

	qinit(&queue);
	for(int y=0; y<20; y++) {
		qinit(&queue);
		for(int x=0; x<20; x++) {
			while(!qcompare(&queue, st)) qpop(&queue);//pop until queue == st
			if(qcompare(&queue, st) == -1) qinsert(&queue, board[y][x]);
			if(qcompare(&queue, st) == 1) {
				rx = x - length + r;
				ry = y;
				return rx * 100 + ry;
			}
		}
	}
	qinit(&queue);
	for(int x=0; x<20; x++) {
		qinit(&queue);
		for(int y=0; y<20; y++) {
			while(!qcompare(&queue, st)) qpop(&queue);//pop until queue == st
			if(qcompare(&queue, st) == -1) qinsert(&queue, board[y][x]);
			if(qcompare(&queue, st) == 1) {
				rx = x;
				ry = y - length + r;
				return rx * 100 + ry;
			}
		}
	}
	qinit(&queue);
	for(int x=0; x<20; x++) {
		qinit(&queue);
		for(int y=0; y<20 && x+y < 20; y++) {
			while(!qcompare(&queue, st)) qpop(&queue);//pop until queue == st
			if(qcompare(&queue, st) == -1) qinsert(&queue, board[y][x+y]);
			if(qcompare(&queue, st) == 1) {
				rx = x +y - length + r;
				ry = y - length + r;
				return rx * 100 + ry;
			}
		}
	}
	qinit(&queue);
	for(int y=0; y<20; y++) {
		qinit(&queue);
		for(int x=0; x<20 && x+y < 20; x++) {
			while(!qcompare(&queue, st)) qpop(&queue);//pop until queue == st
			if(qcompare(&queue, st) == -1) qinsert(&queue, board[x+y][x]);
			if(qcompare(&queue, st) == 1) {
				rx = x - length + r;
				ry = x + y - length + r;
				return rx * 100 + ry;
			}
		}
	}
	qinit(&queue);
	for(int x=0; x<20; x++) {
		qinit(&queue);
		for(int y=0; y<20 && x-y >= 0; y++) {
			//printf("(%d,%d)", x-y, y);
			while(!qcompare(&queue, st)) qpop(&queue);//pop until queue == st
			if(qcompare(&queue, st) == -1) qinsert(&queue, board[y][x-y]);
			if(qcompare(&queue, st) == 1) {
				rx = x - y + length - r;
				ry = y - length + r;
				return rx * 100 + ry;
			}
		}
	}
	qinit(&queue);
	for(int y=0; y<20; y++) {
		qinit(&queue);
		for(int x=19; y<20 && x >=0; x--) {
			//printf("(%d,%d)", x,19-x+y);
			while(!qcompare(&queue, st)) qpop(&queue);//pop until queue == st
			if(qcompare(&queue, st) == -1) qinsert(&queue, board[19-x+y][x]);
			if(qcompare(&queue, st) == 1) {
				rx = x + length - r;
				ry = 19 - x + y - length + r;
				return rx * 100 + ry;
			}
		}
	}
	return 21;
}


int main() {
	init();
	qinit(&queue);
	board[0][5] = 'X';
	board[1][4] = 'X';
	board[5][12] = 'O';
	board[17][19] = 'O';
	board[18][18] = 'O';
	show();
	char *p = crop();
	printf("%d X %d : ", p[0], p[1]);
	for(int i=2; i<p[0]*p[1]+2; i++) printf("%c", p[i]);
	printf("\n");
	printf("%d", find_straight("OOs"));
}
