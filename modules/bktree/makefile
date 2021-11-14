default: bktree

bktree: testtree.c
	gcc -o bktree testtree.c bktree.o distance.o -lm
	./bktree


bktree.o: bktree.c
	gcc -c bktree.c

distance.o: distance.c
	gcc -c -static distance.c -lm


