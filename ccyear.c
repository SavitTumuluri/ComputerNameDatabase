#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/file.h>
#include "cc.h"

int main(int argc, char *argv[]) {
    FILE *fp;
    CComp item;
    int id, year_1, year_2;

    if(argc != 3) {
		fprintf(stderr, "Usage: ccyear year_1 year_2\n");
		exit(1);
	}

    year_1 = atoi(argv[1]);
    year_2 = atoi(argv[2]);

    fp = fopen("ccdb", "r");
    if (fp == NULL) {
        perror("fopen");
        exit(2);
    }

    if (year_2 < year_1) {
        int temp;
        temp = year_1;
        year_1 = year_2;
        year_2 = temp;
    }
    
    id = 1;
    fseek(fp, CCsize, SEEK_SET);
    while(fread(&item, CCsize, 1, fp) > 0) {
        if (item.year >= year_1 && item.year <= year_2) {
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
    fclose(fp);
}