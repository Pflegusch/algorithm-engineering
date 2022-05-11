CC = g++

CCFLAGSBASE = -std=c++20 -march=native -O3

all: ex01

ex01: ex01.cc Makefile
	$(CC) $(CCFLAGSBASE) -o $@ $<

run:
	./ex01

clean:
	rm -rf ex01
