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
		p->left = NULL;
		p->right = NULL;
		return p;
	}
	for(int i=4; i < p->data[0] * 100 + p->data[1] + 4; i++) {
		if(p->data[i] > data[i]) p->left = tinsert(p->left, data, win);
		else if(p->data[i] < data[i]) p->right = tinsert(p->right, data, win);
	}
	p->result[2 * (data[2] * 100 + data[3]) + win]++;//if same
	return p;
}

void free_tree(Tree* p) {
	if(p->left) free_tree(p->left);
	if(p->right) free_tree(p->right);
	free(p->result);
	free(p);
}
