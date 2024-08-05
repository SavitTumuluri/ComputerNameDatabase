#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/file.h>
#include "cc.h"

int
main(int argc, char *argv[]) {
    CComp newcomp;
    FILE *fp;
    struct stat buf;
    int largest_id;
    
    
    if(argc != 8) {
        fprintf(stderr, "Usage: ID maker model year cpu memory description"); 
        return 1;        
    }

    memset(&newcomp, 0, CCsize);

    if (strcmp(argv[1], "-a") == 0) {
        if (stat("ccdb", &buf) == 0) {
            largest_id = buf.st_size / CCsize;
        }
        newcomp.id = largest_id;
    }
    else {
        newcomp.id = atoi(argv[1]);
    }

    strncpy(newcomp.maker, argv[2], Nmaker);
    strncpy(newcomp.model, argv[3], Nmodel);
    newcomp.year = atoi(argv[4]);
    strncpy(newcomp.cpu, argv[5], Ncpu);
    strncpy(newcomp.memory, argv[6], Nmemory);
    strncpy(newcomp.desc, argv[7], Ndesc);

    fp = fopen("ccdb", "r+");
    if(fp == NULL) {
        fp = fopen("ccdb", "w");
        if(fp == NULL) {
            perror("ccdb");
            return 2;
        }
    }
    flock(fileno(fp), LOCK_EX);
    fseek(fp, newcomp.id * CCsize, SEEK_SET);
    fwrite(&newcomp, CCsize, 1, fp);
    flock(fileno(fp), LOCK_UN);
    fclose(fp);
    return 0;
}
