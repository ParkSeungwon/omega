#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tree {
	int num;
	char name[10];
	int is_thread;
	struct Tree *left, *right;
} Tree;

typedef struct Queue {
	Tree* data;
	struct Queue* next;
} Queue;

Queue tree_visit_order;//중위 순회시 순서를 집어 넣을 큐

void push(Queue* q, Tree* n) {
	Queue* p = q;
	while(p->next) p = p->next;
	p->next = (Queue*)malloc(sizeof(Queue));
	p->next->data = n;
	p->next->next = NULL;
}

Tree* pop(Queue* q) {
	q->data = q->next->data;
	Queue* tmp = q->next->next;
	free(q->next);
	q->next = tmp;
	return q->data;
}

Tree* insert(Tree* p, int num, char* name) {//삽입 재귀 함수
	if(!p) {
		p = (Tree*)malloc(sizeof(Tree));
		p->num = num;
		strcpy(p->name, name);
		p->is_thread = 0;
		p->left = NULL;
		p->right = NULL;
	} else if(num > p->num) p->right = insert(p->right, num, name);
	else p->left = insert(p->left, num, name);
	return p;//리턴값은 (재귀적 호출시)항상 부모와 연결할 값이라고 생각하면 된다.
}

void show(Tree* p) {//중위 순회 출력 함수
	if(p->left) show(p->left);
	printf("%d : %s\n", p->num, p->name);
	if(p->right) show(p->right);
}

Tree* del_node(Tree* p) {//p가 가르키는 노드를 삭제한다.
	if(!p->left && !p->right) {//자식이 없을 때
		free(p);
		return NULL;
	} else if(!p->right) {//오른쪽만 널일때
		Tree *r = p->left;
		free(p);
		return r;//리턴값을 대입하는 형식으로 부모와 연결한다.
	} else if(!p->left) {//왼쪽만 널일때
		Tree *r = p->right;
		free(p);
		return r;
	} else {//둘 다 자식일때
		Tree* prev = p;
		Tree* q = p->right;
		for(; q->left; q = q->left) prev = q;
		p->num = q->num;
		strcpy(p->name, q->name);
		if(prev == p) prev->right = del_node(q);//q를 재귀적으로 삭제하고 이어준다.
		else prev->left = del_node(q);
		return p;
	}
}

Tree* del(Tree* p, int num) {//num 요소를 삭제한다. 
	if(!p) return NULL;
	if(p->num == num) return del_node(p);//del_node를 호출한다.
	if(p->num > num) p->left = del(p->left, num);
	if(p->num < num) p->right = del(p->right, num);
	return p;
}

Tree* find(Tree* p, int num) {//조회
	if(!p) return NULL;
	if(p->num == num) return p;
	if(p->num > num) return find(p->left, num);
	if(p->num < num) return find(p->right, num);
}

void push_queue(Tree* p) {
	if(p->left) push_queue(p->left);
	push(&tree_visit_order, p);
	if(p->right) push_queue(p->right);
}

Tree* find_succesor(Tree* p) {
	if(p->is_thread) return p->right;//우측이 쓰레드이면 반환
	if(!p->is_thread) {//우측이 자식이면 그 자식의 맨 왼쪽 끝으로 간다.
		p = p->right;//쓰레드 상에서 우측은 마지막 쓰레드을 제외하곤 널이 될 수 없다.
		while(p->left) p = p->left;
		return p;//
	}
}

int main()
{
	tree_visit_order.next = NULL;
	//트리의 삽입, 삭제, 조회 등.
	Tree* tree = NULL;
	tree = insert(tree, 2016110056, "박승원");//최초 삽입 이외에는
	insert(tree, 2016113456, "박김강");//tree에서는 삽입시 루트가 바뀌지 않으므로 
	insert(tree, 2014113456, "박김");//대입하지 않아도 된다.
	insert(tree, 2011113456, "박r김");
	insert(tree, 2012113456, "김");
	show(tree);
	printf("===============\n");
	tree = del(tree, 2016113456);//삭제 
	printf("삭제후의 출력 \n");
	show(tree);
	int n = 2014113456;
	printf("학번 %d은 %s입니다.\n", n, find(tree, n)->name);//조회

	//이 이하는 쓰레드 이진 트리입니다.
	push_queue(tree);//이진 트리의 중위순환시 방문 순서를 큐에 넣은 후 
	Queue* q = &tree_visit_order;
	Tree* vt;
	while(q->next) {//여기에서 우측 자식을 쓰레드 연결해서 만들어 줍니다.
		vt = pop(q);
		if(!vt->right) {
			vt->is_thread = 1;
			if(q->next) vt->right = q->next->data;
			else vt->right = NULL;
		}
	}

	//쓰레드를 이용하여 반복 순환하는 부분.
	Tree* p = tree;
	while(p->left) p = p->left;
	do {
		printf("%d : %s\n", p->num, p->name);
		p = find_succesor(p);
	} while(p);

}
