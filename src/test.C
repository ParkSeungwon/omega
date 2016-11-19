#include<stdio.h>
#include<dirent.h>
typedef char element;
typedef struct Tree {
	element* data;
	unsigned int* result;
	struct Tree *left, *right;
} Tree;
typedef char element;
extern char board[20][20];

int main() {
    DIR *dp;
    struct dirent *dirp;
    dp  = opendir(".");
    while ((dirp = readdir(dp)) != NULL) {
		int file_num;
		printf("read %s\n", dirp->d_name);

        if(file_num = is_dat(dirp->d_name)) {
			FILE* f = fopen(dirp->d_name, "r");
			printf("opening %s\n", dirp->d_name);
			fclose(f);
		}
    }
    closedir(dp);
}
