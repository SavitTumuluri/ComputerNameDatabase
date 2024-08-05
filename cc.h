typedef struct CComp CComp;

enum {
    Nmaker = 16, 
    Nmodel = 16,
    Ncpu = 8,
    Nmemory = 8,
    Ndesc = 200,
};

struct CComp {
    int id;
    char maker[Nmaker];
    char model[Nmodel];
    int year;
    char cpu[Ncpu];
    char memory[Nmemory];
    char desc[Ndesc];
};

enum {
    CCsize = sizeof(CComp),
};