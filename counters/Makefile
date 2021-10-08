# Makefile for 'counters' module
#
# Taken largely from the makefile in Bag
# Brian Yu
# 10/5/21 

OBJS = counterstest.o counters.o ../lib/file.o ../lib/mem.o 
LIBS = 

# uncomment the following to turn on verbose memory logging
#TESTING=-DMEMTEST

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I../lib
CC = gcc
MAKE = make
# for memory-leak tests
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

counterstest: $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

counterstest.o: counters.h ../lib/file.h
counters.o: counters.h
../lib/file.o: ../lib/file.h

.PHONY: test valgrind clean

# prints it out to testing.out
test: counterstest 
	./counterstest > testing.out

# expects a file `test.names` to exist; it can contain any text.
valgrind: counterstest test.names
	$(VALGRIND) ./counterstest < test.names

clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f bagtest
	rm -f core
