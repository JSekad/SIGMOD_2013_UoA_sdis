objects=entry.o entry_list.o distance.o  test.o   payload.o   hashTable.o  query.o

main: $(objects)
	g++ $(objects) -o Api -lm
	valgrind --leak-check=full --leak-resolution=med --track-origins=yes ./Api
	rm $(objects)

entry.o: ../entry/entry.cpp
	g++ -c ../entry/entry.cpp

entry_list.o: ../entry_list/entry_list.cpp
	g++ -c ../entry_list/entry_list.cpp

distance.o: ../bktree/distance.cpp
	g++ -c ../bktree/distance.cpp -lm

hashTable.o: ../hash_table/hashTable.cpp
	g++ -c ../hash_table/hashTable.cpp 


querry.o: query.cpp
	g++ -c query.cpp 


payload.o: ../payload/payload.cpp
	g++ -c ../payload/payload.cpp

#api.o: api/api.c
#	gcc -c api/api.c

test.o: test.cpp
	g++ -c test.cpp

clean:
	rm Api $(objects)