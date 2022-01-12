objects=entry.o entry_list.o distance.o  test.o hashTable.o payload.o doc.o vector.o

main: $(objects)
	g++ $(objects) -o Api -lm
	valgrind ./Api
	rm $(objects)

entry.o: ../entry/entry.cpp
	g++ -c ../entry/entry.cpp

entry_list.o: ../entry_list/entry_list.cpp
	g++ -c ../entry_list/entry_list.cpp

distance.o: ../bktree/distance.cpp
	g++ -c ../bktree/distance.cpp -lm

hashTable.o: ../hash_table/hashTable.cpp
	g++ -c ../hash_table/hashTable.cpp 

payload.o: ../payload/payload.cpp
	g++ -c ../payload/payload.cpp


doc.o: doc.cpp
	g++ -c doc.cpp


vector.o: ../vector/vector.cpp
	g++ -c ../vector/vector.cpp

#bktree.o: modules/bktree/bktree.c
#	gcc -c modules/bktree/bktree.c

#api.o: api/api.c
#	gcc -c api/api.c

test.o: test.cpp
	g++ -c test.cpp

clean:
	rm Api $(objects)