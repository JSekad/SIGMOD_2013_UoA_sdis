objects=entry.o entry_list.o distance.o bktree.o api.o testAcu.o

main: $(objects)
	gcc $(objects) -o Api -lm
	valgrind --leak-check=full --leak-resolution=med --track-origins=yes --trace-children=yes -s ./Api
	rm $(objects)

entry.o: modules/entry/entry.c
	gcc -c modules/entry/entry.c

entry_list.o: modules/entry_list/entry_list.c
	gcc -c modules/entry_list/entry_list.c

distance.o: modules/bktree/distance.c
	gcc -c modules/bktree/distance.c -lm

bktree.o: modules/bktree/bktree.c
	gcc -c modules/bktree/bktree.c

api.o: api/api.c
	gcc -c api/api.c

testAcu.o: api/testAcu.c
	gcc -c api/testAcu.c

clean:
	rm Api