default: bktree

bktree: testtree.c bktree.o distance.o
	gcc -o bktree testtree.c bktree.o distance.o -lm

bktree.o: bktree.c distance.h bktree.h
	gcc -c bktree.c 

distance.o: distance.h
	gcc -c distance.c -lm
