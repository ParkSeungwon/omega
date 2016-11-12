#include<stdio.h>
#include<stdlib.h>
extern char board[20][20];
	
char* compress() {
	int n = 0, i = 0;
	char b[400];
	for(int y=0; y<20; y++) for(int x=0; x<20; x++) {
		n++;
		if(n == 128) {
			b[i++] = 0;
			n = 0;
		}
		if(board[y][x] == 'O') {
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
	return r;
}

void decompress(char* data) {
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


