CC = g++

CCFLAGSBASE = -std=c++20 -march=native -O3

all: ex02.out

ex02.out: ex02.cc Makefile
	$(CC) $(CCFLAGSBASE) -o $@ $<

run:
	./ex02.out

clean:
	rm -rf ex02
