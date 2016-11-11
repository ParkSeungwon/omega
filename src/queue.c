#include<stdio.h>
#include<stdlib.h>
#include"queue.h"

void qinsert(Queue* q, element n) {
	if(q_is_full(q)) exit(1);
	q->data[(q->rear)++] = n;
	if(q->rear == MAX) q->rear = 0;
}

element qpop(Queue* q) {
	if(q_is_empty(q)) exit(1);
	element r = q->data[q->front++];
	if(q->front == MAX) q->front = 0;
	return r;
}

void qshow(Queue* q) {
	for(int i=q->front; i!=q->rear; i++) {
		printf("%c ", q->data[i]);
		if(i == MAX -1) i = -1;
	}
	printf("\n");
}

int q_is_empty(Queue* q) {
	return q->front == q->rear;
}

int q_is_full(Queue* q) {
	return q->front == q->rear + 1 || (q->front == 0 && q->rear == MAX);
}
void qinit(Queue* q) {
	q->front = q->rear = 0;
}
int qcompare(Queue* q, element* s) {
	for(int i = q->front, j=0; i != q->rear; i++) {
		if(s[j] == '\0') return 1;//correct
		if(s[j++] != q->data[i]) return 0;//wrong
		if(i == MAX-1) i = -1;
	}
	return -1;//same until now
}
