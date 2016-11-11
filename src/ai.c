#include<ctype.h>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>

int find_straight(const char* s);
extern char board[20][20];
const char *win_string[] = {
	"sOOOO", "OsOOO", "OOsOO", "OOOsO", "OOOOs",
	"sXXXX", "XsXXX", "XXsXX", "XXXsX", "XXXXs",
	" sOOO ", " OsOO ", " OOsO ", " OOOs ", "O OsO O",
	" sXXX ", " XsXX ", " XXsX ", " XXXs ", "X XsX X"
};

int check() {
	int r = 0;
	for(int y=0; y<20; y++) for(int x=0; x<20; x++) {
		if(board[y][x] == 'O' || board[y][x] == 'X') {
			for(int y2=y-2; y2 <= y+2; y2++) for(int x2=x-2; x2 <= x+2; x2++) {
				if(y2>=0 && y2<20 && x2>=0 && x2<20 && board[y2][x2] == ' ') {
					board[y2][x2] = 'v';
					r++;
				}
			}
		}
	}
	return r;
}

void put(int n, char ox) {
	int i = 0;
	for(int y=0; y<20; y++) for(int x=0; x<20; x++) {
		if(board[y][x] == 'v') {
			if(i == n) board[y][x] = ox;
			else board[y][x] = ' ';
			i++;
		}
	}
}

int Oai() {
	int xy, i;
	for(i=0; i<20; i++) {
		xy = find_straight(win_string[i]);
		if(xy != -1) {
			board[xy%100][xy/100] = 'O';
			break;
		}
	}
	if(i<5) return xy;
	if(xy == -1) put(rand() % check(), 'O');
	return -1;
}

int Xai() {
	int xy, i;
	for(i=9; i>=0; i--) {
		xy = find_straight(win_string[i]);
		if(xy != -1) {
			board[xy%100][xy/100] = 'X';
			break;
		}
	}
	if(i>4) return xy;
	for(i=19; i>=10; i--) {
		xy = find_straight(win_string[i]);
		if(xy != -1) {
			board[xy%100][xy/100] = 'X';
			break;
		}
	}
	if(xy == -1) put(rand() % check(), 'X');
	return -1;
}

