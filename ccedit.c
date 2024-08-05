#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/file.h>
#include "cc.h"

int main(int argc, char *argv[]) {
    CComp item;
    FILE *fp;
    int n, id;
    char str[201];

	if (argc != 2) {
        fprintf(stderr, "Usage: ccedit id\n");
        exit(1);
    }

	fp = fopen("ccdb", "r+");
    if (fp == NULL) {
        perror("ccdb");
        exit(2);
    }

	flock(fileno(fp), LOCK_EX);
    id = atoi(argv[1]);
    fseek(fp, id * CCsize, SEEK_SET);
    n = fread(&item, CCsize, 1, fp);

	if (n == 0 || item.id != id) {
        fclose(fp);
        fprintf(stderr, "No such item %d in database\n", id);
        exit(3);
    }
    if (n < 0) {
        fclose(fp);
        perror("fread");
        exit(3);
    }
	
	printf("Maker: %s\n", item.maker);
    printf("If you want to change the maker, type yes. Type anything else if you want to keep the original");
    fgets(str, sizeof(str), stdin);
    if (strncmp(str, "yes", 1) == 0) {
        printf("Enter the new maker: ");
        fgets(str, sizeof(str), stdin);
        str[strcspn(str, "\n")] = '\0';
        strcpy(item.maker, str);
    }

	printf("Model: %s\n", item.model);
    printf("If you want to change the model, type yes. Type anything else if you want to keep the original");
    fgets(str, sizeof(str), stdin);
    if (strncmp(str, "yes", 1) == 0) {
        printf("Enter the new model: ");
        fgets(str, sizeof(str), stdin);
        str[strcspn(str, "\n")] = '\0';
        strcpy(item.model, str);
    }

    printf("Year: %d\n", item.year);
    printf("If you want to change the year, type yes. Type anything else if you want to keep the original");
    fgets(str, sizeof(str), stdin);
    if (strncmp(str, "yes", 1) == 0) {
        printf("Enter the new year: ");
        fgets(str, sizeof(str), stdin);
        item.year = atoi(str);
    }

	printf("CPU: %s\n", item.cpu);
    printf("If you want to change the CPU, type yes. Type anything else if you want to keep the original");
    fgets(str, sizeof(str), stdin);
    if (strncmp(str, "yes", 1) == 0) {
        printf("Enter the new CPU: ");
        fgets(str, sizeof(str), stdin);
        str[strcspn(str, "\n")] = '\0';
        strcpy(item.cpu, str);
    }

	printf("Memory: %s\n", item.memory);
    printf("If you want to change the memory, type yes. Type anything else if you want to keep the original");
    fgets(str, sizeof(str), stdin);
    if (strncmp(str, "yes", 1) == 0) {
        printf("Enter the new memory: ");
        fgets(str, sizeof(str), stdin);
        str[strcspn(str, "\n")] = '\0';
        strcpy(item.memory, str);
    }

	printf("Desc: %s\n", item.desc);
    printf("If you want to change the description, type yes. Type anything else if you want to keep the original");
    fgets(str, sizeof(str), stdin);
    if (strncmp(str, "yes", 1) == 0) {
        printf("Enter the new description: ");
        fgets(str, sizeof(str), stdin);
        str[strcspn(str, "\n")] = '\0';
        strcpy(item.cpu, str);
    }
	printf("----------------\n");
	printf("Updated Item:\n");
	printf("ID: %d\n", item.id);
	printf("Maker: %s\n", item.maker);
	printf("Model: %s\n", item.model);
	printf("Year: %d\n", item.year);
	printf("CPU: %s\n", item.cpu);
	printf("Memory: %s\n", item.memory);
	printf("Desc: %s\n", item.desc);
	return 0;
}