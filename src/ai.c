#include<ctype.h>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
typedef char element;
typedef struct Tree {
	element* data;
	unsigned int* result;
	struct Tree *left, *right;
} Tree;
int find_straight(const char* s);
void tfree(Tree*);
Tree* tinsert(Tree* p, element* data, int win);
char* compress();

char board[20][20];
struct Tree* tree = NULL;

static const char *win_string[] = {
	"sOOOO", "OsOOO", "OOsOO", "OOOsO", "OOOOs",//승리O
	"sXXXX", "XsXXX", "XXsXX", "XXXsX", "XXXXs",
	" sOOO ", " OsOO ", " OOsO ", " OOOs ", "O OsO O",//결정적 
	" sXXX ", " XsXX ", " XXsX ", " XXXs ", "X XsX X"
};
char* Ogibo[200];//static or ={}선언시 실행시 크래시 ???
char* Xgibo[200];
Tree* hash[400];

void win(char ox) {
	int sz;
	for(int i=0; Ogibo[i]; i++) {
		//save
		sz = Ogibo[i][0] * 100 + Ogibo[i][1];
		hash[sz] = tinsert(hash[sz], Ogibo[i], ox == 'O');
		free(Ogibo[i]);
		Ogibo[i] = NULL;
	}
	for(int i=0; Xgibo[i]; i++) {
		sz = Xgibo[i][0] * 100 + Xgibo[i][1];
		hash[sz] = tinsert(hash[sz], Xgibo[i], ox == 'X');
		free(Xgibo[i]);
		Xgibo[i] = NULL;
	}
}

int check() {//2칸 이내에 v마크를 하고 v마크의 개수를 리턴
	int r = 0;
	for(int y=0; y<20; y++) for(int x=0; x<20; x++) {
		if(board[y][x] == 'O' || board[y][x] == 'X') {
			for(int y2=y-2; y2 <= y+2; y2++) for(int x2=x-2; x2 <= x+2; x2++) {
				if(y2>=0 && y2<20 && x2>=0 && x2<20 && board[y2][x2] == ' ') {
					board[y2][x2] = 'v';
					r++;
				}
			}
		}
	}
	return r;
}

int record(char* gibo[]) {
	int i=0;
	while(gibo[i]) i++;
	char* cp = gibo[i] = compress();//현 상태의 기보를 저장.
	int count_v = check();
	int v = rand() % count_v;//두 칸 내에서 랜덤으로 고른후
	gibo[i][2] = v / 100;//랜덤 값을 저장한다.
	gibo[i][3] = v % 100;
	gibo[i][4] = count_v / 100;
	gibo[i][5] = count_v % 100;
	return v;
}

int put(int n, char ox) {//v마크를 지우고 n번째 v마크에 바둑돌을 둔다.
	int i = 0, r;
	for(int y=0; y<20; y++) for(int x=0; x<20; x++) {
		if(board[y][x] == 'v') {
			if(i == n) {
				board[y][x] = ox;
				r = 100 * x + y;
			} else board[y][x] = ' ';
			i++;
		}
	}
	return r;
}

int Oai() {
	int xy, i;
	for(i=0; i<20; i++) {
		xy = find_straight(win_string[i]);
		if(xy != -1) {
			board[xy%100][xy/100] = 'O';
			break;
		}
	}
	if(i<5) {
		win('O');
		return xy;// 이 위로는 필연적인 룰에 따라 
	}
	i = 0;//reuse
	if(xy == -1) put(record(Ogibo), 'O');//랜덤으로 고르는 부분
	return -1;
}

int OH() {
	int xy, i;
	for(i=0; i<20; i++) {
		xy = find_straight(win_string[i]);
		if(xy != -1) {
			board[xy%100][xy/100] = 'O';
			break;
		}
	}
	if(i<5) {
		win('O');
		return xy;// 이 위로는 필연적인 룰에 따라 
	}
	i = 0;//reuse
	int r;
	if(xy == -1) {
		char* data = compress();
		int sz = data[0] * 100 + data[1];
		int rsz = 2 * check();
		Tree* p = tfind(hash[sz], data);
		int sum = 0, max = 0;
		if(p) for(int i=0; i<rsz; i++) sum += p->result[i];
		if(sum < 100 || !p) for(int i=0; i<rsz/2; i++) {
			for(int j=0; j<10; j++) {
				init();
				decompress(data);
				check();
				put(i, 'O');
				pre_cog('X');//simulate
			}
		}
		init();
		decompress(data);
		p = tfind(hash[sz], data);
		for(int i=0; i<rsz; i++) {
			if(i % 2) {
				float f = (float)p->result[i] / (p->result[i-1] + 1);
				if(f > max) {
					max = f;
					r = i/2;
				}
			}
		}
		check();
		put(r, 'O');
		free(data);
	}
	return -1;
}

int Xai() {
	int xy, i;
	for(i=9; i>=0; i--) {
		xy = find_straight(win_string[i]);
		if(xy != -1) {
			board[xy%100][xy/100] = 'X';
			break;
		}
	}
	if(i>4) {
		win('X');
		return xy;
	}
	if(xy == -1) {
		for(i=19; i>=10; i--) {
			xy = find_straight(win_string[i]);
			if(xy != -1) {
				board[xy%100][xy/100] = 'X';
				break;
			}
		}//이 위로는 필연적인 룰에 따라 고르는 부분
	}
	i = 0;
	if(xy == -1) put(record(Xgibo), 'X');//랜덤으로 고르는 부분
	return -1;
}

int valid(int x, int y) {
	if(x >= 0 && y >= 0 && x < 20 && y < 20) return 1;
	else return 0;
}

int Human(char ox) {
	show();
	int x = 20, y = 20;
	while(board[y][x] != ' ' || !valid(x, y)) {
		printf("좌표를 넣으세요.(x y)");
		scanf("%d %d", &x, &y);
	}

	//이겼는지 확인
	board[y][x] = ox;
	int i, j, k;
	for(i=y, j=x; board[i][j] == ox && i>=0; i--);
	for(k=0; board[++i][j] == ox && i<20; k++);
	if(k < 5) {
		for(i=y, j=x; board[i][j] == ox && j>=0; j--);
		for(k=0; board[i][++j] == ox && j<20; k++);
	}
	if(k < 5) {
		for(i=y, j=x; board[i][j] == ox && valid(j, i); i--, j--);
		for(k=0; board[++i][++j] == ox && valid(j, i); k++);
	}
	if(k < 5) {
		for(i=y, j=x; board[i][j] == ox && valid(j, i); i--, j++);
		for(k=0; board[++i][--j] == ox && valid(j, i); k++);
	}
	if(k > 4) {
		win(ox);
		return 100*x + y;
	} else return -1;
}

void pre_cog(char ox) {
	if(ox == 'X') Xai();
	for(int i=0; i<200; i++) {
		if(Oai() != -1) break;
		if(Xai() != -1) break;
	}
}


