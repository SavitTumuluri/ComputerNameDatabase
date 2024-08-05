#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>
#include "cc.h"

int
main(int argc, char *argv[])
{
	CComp item;
	FILE *fp;
	int id;

	if(argc != 1) {
		fprintf(stderr, "Usage: cclist\n");
		exit(1);
	}
	fp = fopen("ccdb", "r");
	if(fp == NULL) {
		perror("fopen");
		exit(2);
	}
	flock(fileno(fp), LOCK_SH);
	
	id = 1;
	fseek(fp, CCsize, SEEK_SET);
	while(fread(&item, CCsize, 1, fp) > 0) {
		if(id == item.id) {
			printf("\n");
			printf("ID: %d\n", item.id);
			printf("Maker: %s\n", item.maker);
			printf("Model: %s\n", item.model);
			printf("Year: %d\n", item.year);
			printf("CPU: %s\n", item.cpu);
			printf("Desc: %s\n", item.desc);
			printf("----------------\n");
		}
		id++;
	}
	flock(fileno(fp), LOCK_UN);
	fclose(fp);
	exit(0);
}