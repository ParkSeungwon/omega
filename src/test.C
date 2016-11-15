#include<stdio.h>
typedef char element;
typedef struct Tree {
	element* data;
	unsigned int* result;
	struct Tree *left, *right;
} Tree;
typedef char element;
int main() {
	Tree* t= NULL;
	t= tinsert(t, "\0\nabslfjafjfafafadfafafafafqerwrrqrqwecfafqwef", 1);
	show_tree(t);
}
