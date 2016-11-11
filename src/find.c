#include<string.h>
#include"queue.h"
extern char board[20][20];
extern struct Queue queue;
const char *win_string[] = {"sOOOO", "OsOOO", "OOsOO", "OOOsO", "OOOOs"};
const char *check_string[] = {" sOOO ", " OsOO ", " OOsO ", " OOOs ", "O OsO O"};

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
