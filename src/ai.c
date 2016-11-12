#include<ctype.h>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>

int find_straight(const char* s);
char* compress();
extern char board[20][20];
static const char *win_string[] = {
	"sOOOO", "OsOOO", "OOsOO", "OOOsO", "OOOOs",//승리O
	"sXXXX", "XsXXX", "XXsXX", "XXXsX", "XXXXs",
	" sOOO ", " OsOO ", " OOsO ", " OOOs ", "O OsO O",//결정적 
	" sXXX ", " XsXX ", " XXsX ", " XXXs ", "X XsX X"
};
char* Ogibo[200];//static or ={}선언시 실행시 크래시 ???
char* Xgibo[200];

void finish(char* g[], char win) {
	for(int i=0; g[i]; i++) {
		if(win == 'W') {
		} else {
		}
		free(g[i]);
		g[i] = NULL;
	}
}

int check() {//2칸 이내에 v마크를 하고 v마크의 개수를 리턴
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

void put(int n, char ox) {//v마크를 지우고 n번째 v마크에 바둑돌을 둔다.
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
	if(i<5) {
		finish(Ogibo, 'W');
		finish(Xgibo, 'L');
		return xy;// 이 위로는 필연적인 룰에 따라 
	}
	i = 0;//reuse
	if(xy == -1) {//이 아래는 랜덤으로 고르는 부분
		while(Ogibo[i]) i++;
		Ogibo[i] = compress();//현 상태의 기보를 저장.
		int v = rand() % check();//두 칸 내에서 랜덤으로 고른후
		Ogibo[i][2] = v /100;//랜덤 값을 저장한다.
		Ogibo[i][3] = v % 100;
		put(v, 'O');
	}
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
	if(i>4) {
		finish(Xgibo, 'W');
		finish(Ogibo, 'L');
		return xy;
	}
	for(i=19; i>=10; i--) {
		xy = find_straight(win_string[i]);
		if(xy != -1) {
			board[xy%100][xy/100] = 'X';
			break;
		}
	}//이 위로는 필연적인 룰에 따라 고르는 부분
	i = 0;
	if(xy == -1) {//이 아래는 랜덤으로 고르는 부분
		while(Xgibo[i]) i++;
		Xgibo[i] = compress();
		int v = rand() % check();//두 칸 내에서 랜덤으로 고른후
		Xgibo[i][2] = v /100;//랜덤 값을 저장한다.
		Xgibo[i][3] = v % 100;
		put(v, 'X');
	}
	return -1;
}

