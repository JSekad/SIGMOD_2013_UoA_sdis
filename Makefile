objects=entry.o entry_list.o distance.o bktree.o api.o test.o

main: $(objects)
	gcc $(objects) -o Api -lm
	valgrind --leak-check=full --leak-resolution=med --track-origins=yes --trace-children=yes ./Api

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

test.o: api/test.c
	gcc -c api/test.c

clean:
	rm Api $(objects)