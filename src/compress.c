#include<stdio.h>
#include<stdlib.h>
extern char board[20][20];
	
char* compress() {//현재의 보드를 압축
	int n = 0, i = 0;
	char b[400];
	for(int y=0; y<20; y++) for(int x=0; x<20; x++) {
		n++;
		if(n == 128) {//128개의 space가 연달아 올경우 0을 집어넣는다.
			b[i++] = 0;
			n = 0;
		}
		if(board[y][x] == 'O') {//그 전의 O또는 X에서의 거리만큼 값으로 
			b[i++] = n;
			n = 0;
		} else if(board[y][x] == 'X') {
			b[i++] = -n;
			n = 0;
		}
	}
	char *r = (char*)malloc(i+2);
	r[0] = i/100;
	r[1] = i%100;
	for(int j=2; j<i+2; j++) r[j] = b[j-2];
	for(int j=0; j<i+2; j++) printf("%d ", r[j]);
	return r;//첫두바이트는 사이즈, 다음부터 데이터
}

void decompress(char* data) {//압축된 데이터를 바둑판에 다시 편다. 
	int sz = data[0] * 100 + data[1];
	int n = 0, i = 2;

	for(int y=0; y<20; y++) for(int x=0; x<20; x++) {
		n++;
		if(n == data[i]) {
			board[y][x] = 'O';
			n = 0;
			i++;
		} else if(n == -data[i]) {
			board[y][x] = 'X';
			n = 0;
			i++;
		} else if(n == 128) {
			i++;
			n = 0;
		}
		if(i == sz+2) break;
	}
}


