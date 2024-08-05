#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/file.h>
#include "cc.h"

int main(int argc, char *argv[]) {
    FILE *fp;
    CComp item;
    char* string;
    int id;

    if(argc != 2) {
		fprintf(stderr, "Usage: ccmatch string\n");
		exit(1);
	}

    string = argv[1];

    fp = fopen("ccdb", "r");
    if (fp == NULL) {
        perror("fopen");
        exit(2);
    }
    flock(fileno(fp), LOCK_SH);

    id = 1;
    fseek(fp, CCsize, SEEK_SET);
    while(fread(&item, CCsize, 1, fp) > 0) {
        if (strstr(item.maker, string) != NULL || strstr(item.cpu, string) != NULL || strstr(item.desc, string) != NULL) {
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
}