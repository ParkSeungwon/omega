#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define HEADER_SIZE 6
typedef char element;
typedef struct Tree {
	element* data;
	unsigned int* result;
	struct Tree *left, *right;
} Tree;

Tree* tinsert(Tree* p, element* data, int win) {//win 1 lose 0
	int sz = data[0] * 100 + data[1] + HEADER_SIZE;
	if(!p) {
		p = (Tree*)malloc(sizeof(Tree));
		p->data = (char*)malloc(sz);
		for(int i=0; i<sz; i++) p->data[i] = data[i];
		p->result = (unsigned*)calloc(2 * sizeof(unsigned), data[4]*100 + data[5]);
		p->result[2*(data[2] * 100 + data[3]) + win]++;
		p->left = NULL;
		p->right = NULL;
		return p;
	}
	int equal = 1;
	for(int i=HEADER_SIZE; equal && i < sz; i++) {
		if(p->data[i] > data[i]) {
			p->left = tinsert(p->left, data, win);
			equal = 0;
		} else if(p->data[i] < data[i]) {
			p->right = tinsert(p->right, data, win);
			equal = 0;
		}
	}
	if(equal) p->result[2 * (data[2] * 100 + data[3]) + win]++;//if same
	return p;
}

void tfree(Tree* p) {
	if(p->left) tfree(p->left);
	if(p->right) tfree(p->right);
	free(p->result);
	free(p->data);
	free(p);
}

void tshow(Tree* p) {
	if(p) {
		printf("\nBoard : \n");
		for(int i=0; i<p->data[0]*100 + p->data[1] + HEADER_SIZE; i++) 
			printf("%d,", p->data[i]);
		printf("\nLose, Win\n");
		for(int i=0; i < 2*(p->data[4]*100 + p->data[5]); i++) 
			printf("%d,", p->result[i]);
		tshow(p->left);
		tshow(p->right);
	} 
}
