#include<stdio.h>
typedef char element;
typedef struct Tree {
	element* data;
	unsigned int* result;
	struct Tree *left, *right;
} Tree;
typedef char element;
extern char board[20][20];

int main() {
	Tree* t= NULL;
	init();
	char* data = compress();
	for(int i=0; i < data[0]*100 + data[1] + 6; i++) printf("%d,", data[i]);
	printf("\n");
	t = tinsert(t, data, 1);
	tshow(t);
	tfree(t);
}
