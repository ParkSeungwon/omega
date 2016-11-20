//should be compiled with gcc -x c option to force C compile (.C -> g++ default)
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
int Xai(); 
int Oai();
int Human(char);
void read_dat();
void write_dat();
char ox;

int main(int c, char** v)
{
	if(c < 2) {
		printf("usage : %s [times]", v[0]);
		return 0;
	}

	read_dat();

	srand(time(NULL));
	char ox = 'C';
	int game = 1;
	if(*v[1] == 'O') ox = 'O';
	else if(*v[1] == 'X') ox = 'X';
	else game = atoi(v[1]);
	while(game--) {
		printf("game %d\n", game);
		init();
		for(int i=0; i<200; i++) {
			int xy;
			if(ox == 'O') xy = Human(ox);
			else if(ox == 'X') xy = OH();
			else xy = Oai();
		//	show();
			if(xy != -1) {
				printf("O win\n");
				break;
			}
			if(ox == 'X') xy = Human(ox);
			else xy = Xai();
		//	show();
			if(xy != -1) {
				printf("X win\n");
				break;
			}
		}
		show();
	}

	write_dat();
}
