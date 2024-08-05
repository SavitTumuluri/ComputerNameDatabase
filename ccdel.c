#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>
#include <string.h>
#include "cc.h"

int
main(int argc, char *argv[]) {
    CComp item;
    FILE *fp;
    int n, inum;

    if(argc != 2) {
		fprintf(stderr, "Usage: ccdel num\n");
		exit(1);
	}

    fp = fopen("ccdb", "r+");
	if(fp == NULL) {
		perror("fopen");
		exit(2);
	}
	flock(fileno(fp), LOCK_EX);

    inum = atoi(argv[1]);
    fseek(fp, inum * CCsize, SEEK_SET);
	n = fread(&item, CCsize, 1, fp);
    
    if(n == 0 || item.id != inum) {
		fprintf(stderr, "No such item %d in database\n", inum);
		exit(3);
	}
    
    if(n < 0) {
		perror("fread");
		exit(3);
	}

    memset(&item, 0, CCsize);
    fseek(fp, inum * CCsize, SEEK_SET);

    fwrite(&item, CCsize, 1, fp);
	flock(fileno(fp), LOCK_UN);
	fclose(fp);
    return 0;
}