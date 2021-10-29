objects=entry.o entry_list.o api.o test.o

main: $(objects)
	gcc $(objects) -o Api
	./Api

entry.o: modules/entry/entry.c
	gcc -c modules/entry/entry.c

entry_list.o: modules/entry_list/entry_list.c
	gcc -c modules/entry_list/entry_list.c

api.o: api/api.c
	gcc -c api/api.c

test.o: api/test.c
	gcc -c api/test.c

clean:
	rm Api $(objects)