#include<dirent.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
typedef char element;
typedef struct Tree {
	element* data;
	unsigned int* result;
	struct Tree *left, *right;
} Tree;
extern struct Tree* tree;
extern Tree* hash[400];

void read_dat() {
    DIR *dp;
    struct dirent *dirp;
    dp  = opendir(".");
    while (dirp = readdir(dp)) {
		int file_num;
        if(file_num = is_dat(dirp->d_name)) {
			FILE* f = fopen(dirp->d_name, "r");
		//	printf("opening %s\n", dirp->d_name);
			hash[file_num] = tload(hash[file_num], f);
			fclose(f);
		}
    }
    closedir(dp);
}

void write_dat() {
	for(int i=0; i<400; i++) if(hash[i]) {
		char b[10];
		snprintf(b, 10, "%d", i);
		strcat(b, ".dat");
		FILE* f = fopen(b, "w");
		tsave(hash[i], f);
		fclose(f);
		tfree(hash[i]);
	}
}
