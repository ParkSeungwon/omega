#define MAX 10
#define min(a,b) ((a)<(b) ? (a) : (b))
#define max(a,b) ((a)>(b) ? (a) : (b))

typedef char element;
typedef struct Queue {
	element data[MAX];
	int front, rear;
} Queue;

void qinsert(Queue* q, element n);
element qpop(Queue* q);
void qshow(Queue* q);
void qinit(Queue* q);
int q_is_empty(Queue* q);
int q_is_full(Queue* q);
int qcompare(Queue* q, element* s);
int find_straight(const char* str);
