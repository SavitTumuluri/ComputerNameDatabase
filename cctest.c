#include <stdio.h>
#include <string.h>
#include <sys/file.h>
#include "cc.h"

int
main() {
    FILE *fp;
    CComp newcomp;

    memset(&newcomp, 0, CCsize);
    newcomp.id = 6;
    strcpy(newcomp.maker, "Apple");
    strcpy(newcomp.model, "Apple ][");
    newcomp.year = 1977;
    strcpy(newcomp.cpu, "6502");
    strcpy(newcomp.memory, "48k");
    strcpy(newcomp.desc, "The classic Apple computer");

    fp = fopen("ccdb", "r+");
    if(fp == NULL) {
        fp = fopen("ccdb", "w");
        if(fp == NULL) {
            perror("test");
            return 1;
        }
    }
    flock(fileno(fp), LOCK_SH);

    fseek(fp, newcomp.id * CCsize, SEEK_SET);
    fwrite(&newcomp, CCsize, 1, fp);
    flock(fileno(fp), LOCK_UN);
    fclose(fp);
}