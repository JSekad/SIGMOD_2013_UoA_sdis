# Copyright (c) 2013 KAUST - InfoCloud Group (All Rights Reserved)
#
# Permission is hereby granted, free of charge, to any person
# obtaining a copy of this software and associated documentation
# files (the "Software"), to deal in the Software without
# restriction, including without limitation the rights to use,
# copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the
# Software is furnished to do so, subject to the following
# conditions:
#
# The above copyright notice and this permission notice shall be
# included in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
# OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
# HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
# WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
# OTHER DEALINGS IN THE SOFTWARE.
#
# Authors: Amin Allam  <amin.allam@kaust.edu.sa>,
#          Fuad Jamour <fuad.jamour@kaust.edu.sa>
#
# Current version: 1.0 (initial release)
	
TEST_NEW_O=test_driver/test_through.o
IMPL_O=ref_impl/core.o   ../../modules/entry/entry.o ../../modules/vector/vector.o ../../modules/doc/doc.o ../../modules/hash_table/hashTable.o ../../modules/entry_list/entry_list.o ../../modules/query/query.o ../../modules/payload/payload.o ../../modules/bktree/distance.o ../../modules/bktree/bktree.o
  

CC  = gcc
CXX = g++
CFLAGS=-O3 -fPIC -Wall -g -I. -I./include
CXXFLAGS=$(CFLAGS)
LDFLAGS=-lpthread

PROGRAMS=new-testdriver

LIBRARY=core

all: $(PROGRAMS)

lib: $(IMPL_O)
	$(CXX) $(CXXFLAGS) -shared -o lib$(LIBRARY).so $(IMPL_O)
	
new-testdriver: clean lib $(TEST_NEW_O)
	$(CXX) $(CXXFLAGS) -o testdriver $(TEST_NEW_O) ./lib$(LIBRARY).so
	./testdriver test_data/small_test.txt 180 > test.txt


clean:
	rm -f testdriver lib$(LIBRARY).so $(IMPL_O) result.txt test.txt
	find . -name '*.o' -print | xargs rm -f

gdb: clean lib $(TEST_NEW_O)
	$(CXX) $(CXXFLAGS) -o testdriver $(TEST_NEW_O) ./lib$(LIBRARY).so
	gdb ./testdriver test_data/small_test.txt 180


valgrind: clean lib $(TEST_NEW_O)
	$(CXX) $(CXXFLAGS) -o testdriver $(TEST_NEW_O) ./lib$(LIBRARY).so
	valgrind --leak-check=full --leak-resolution=med --track-origins=yes ./testdriver test_data/small_test.txt 180
