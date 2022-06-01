CC = g++

CCFLAGSBASE = -std=c++20 -g -march=native -O3

all: ex01.out

ex01.out: ex01.cc Makefile
	$(CC) $(CCFLAGSBASE) -o $@ $<

run:
	./ex01.out

clean:
	rm -rf ex01.out
