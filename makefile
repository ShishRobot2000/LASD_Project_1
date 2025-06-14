
cc = g++
cflags = -Wall -pedantic -Wno-sequence-point -O3 -std=c++20 -fsanitize=address

objects = main.o test.o mytest.o container.o exc1as.o exc1af.o exc1bs.o exc1bf.o exc2as.o exc2af.o exc2bs.o exc2bf.o

libcon = container/container.hpp container/testable.hpp container/traversable.hpp container/traversable.cpp container/mappable.hpp container/mappable.cpp container/dictionary.hpp container/dictionary.cpp container/linear.hpp container/linear.cpp

libexc = $(libcon) zlasdtest/container/container.hpp zlasdtest/container/testable.hpp zlasdtest/container/traversable.hpp zlasdtest/container/mappable.hpp zlasdtest/container/dictionary.hpp zlasdtest/container/linear.hpp

libexc1a = $(libexc) vector/vector.hpp vector/vector.cpp list/list.hpp list/list.cpp zlasdtest/vector/vector.hpp zlasdtest/list/list.hpp

libexc1b = $(libexc1a) set/set.hpp set/lst/setlst.hpp set/lst/setlst.cpp set/vec/setvec.hpp set/vec/setvec.cpp zlasdtest/set/set.hpp

libexc2a = $(libexc) heap/heap.hpp heap/vec/heapvec.hpp heap/vec/heapvec.cpp zlasdtest/heap/heap.hpp

libexc2b = $(libexc2a) pq/pq.hpp pq/heap/pqheap.hpp pq/heap/pqheap.cpp zlasdtest/pq/pq.hpp
all: main
main: $(objects)
	$(cc) $(cflags) $(objects) -o main

clean:
	clear; rm -rfv *.o; rm -fv main

main.o: main.cpp
	$(cc) $(cflags) -c main.cpp

test.o: zlasdtest/test.cpp zlasdtest/test.hpp
	$(cc) $(cflags) -c zlasdtest/test.cpp -o test.o

mytest.o: zmytest/test.cpp zmytest/test.hpp
	$(cc) $(cflags) -c zmytest/test.cpp -o mytest.o

container.o: $(libcon) zlasdtest/container/container.cpp zlasdtest/container/container.hpp
	$(cc) $(cflags) -c zlasdtest/container/container.cpp -o container.o

exc1as.o: $(libexc1a) zlasdtest/exercise1a/simpletest.cpp
	$(cc) $(cflags) -c zlasdtest/exercise1a/simpletest.cpp -o exc1as.o

exc1af.o: $(libexc1a) zlasdtest/exercise1a/fulltest.cpp
	$(cc) $(cflags) -c zlasdtest/exercise1a/fulltest.cpp -o exc1af.o

exc1bs.o: $(libexc1b) zlasdtest/exercise1b/simpletest.cpp
	$(cc) $(cflags) -c zlasdtest/exercise1b/simpletest.cpp -o exc1bs.o

exc1bf.o: $(libexc1b) zlasdtest/exercise1b/fulltest.cpp
	$(cc) $(cflags) -c zlasdtest/exercise1b/fulltest.cpp -o exc1bf.o

exc2as.o: $(libexc2a) zlasdtest/exercise2a/simpletest.cpp
	$(cc) $(cflags) -c zlasdtest/exercise2a/simpletest.cpp -o exc2as.o

exc2af.o: $(libexc2a) zlasdtest/exercise2a/fulltest.cpp
	$(cc) $(cflags) -c zlasdtest/exercise2a/fulltest.cpp -o exc2af.o

exc2bs.o: $(libexc2b) zlasdtest/exercise2b/simpletest.cpp
	$(cc) $(cflags) -c zlasdtest/exercise2b/simpletest.cpp -o exc2bs.o

exc2bf.o: $(libexc2b) zlasdtest/exercise2b/fulltest.cpp
	$(cc) $(cflags) -c zlasdtest/exercise2b/fulltest.cpp -o exc2bf.o
