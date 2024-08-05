all: ccitem cclist ccadd ccdel ccmatch ccyear ccedit

ccadd: ccadd.c cc.h
	gcc -o ccadd ccadd.c

ccitem: ccitem.c cc.h
	gcc -o ccitem ccitem.c

cclist: cclist.c cc.h
	gcc -o cclist cclist.c

ccdel: ccdel.c cc.h
	gcc -o ccdel ccdel.c

ccmatch: ccmatch.c cc.h
	gcc -o ccmatch ccmatch.c

ccyear: ccyear.c cc.h
	gcc -o ccyear ccyear.c

ccedit: ccedit.c cc.h
	gcc -o ccedit ccedit.c
