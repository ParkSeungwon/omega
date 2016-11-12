#include<stdio.h>
#include<stdlib.h>

typedef char element;
typedef struct Tree {
	element* data;
	int vcount;
	unsigned int* result;
	struct Tree *left, *right;
} Tree;

Tree* tinsert(Tree* p, element* data, int win) {//win 1 lose 0
	if(!p) {
		p = (Tree*)malloc(sizeof(Tree));
		p->data = data;
		char* c = compress();
		init();
		decompress(data);
		p->result = (unsigned*)calloc(2 * sizeof(unsigned), p->vcount = check());
		init();
		decompress(c);
		free(c);
		p->result[2*(data[2] * 100 + data[3]) + win]++;
		return p;
	}
	for(int i=4; i < p->data[0] * 100 + p->data[1]; i++) {
		if(p->data[i] > data[i]) p->left = tinsert(p->left, data, win);
		else if(p->data[i] < data[i]) p->right = tinsert(p->right, data, win);
	}
	p->result[2 * (data[2] * 100 + data[3]) + win]++;//if same
}

void free_tree(Tree* p) {
	free_tree(p->left);
	free_tree(p->right);
	free(p->result);
	free(p->data);
	free(p);
}
