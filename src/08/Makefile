include ../lib/Makefile

.PHONY: build cleanall

lib_obj = ../lib/log_err.o ../lib/system.o ../lib/tellwait.o 

all: 01-8_1-fork

01-8_1-fork:
	cd ../lib && $(MAKE)
	clang -c 01-8_1-fork.c 
	clang -o 01-8_1-fork.out 01-8_1-fork.o $(lib_obj)


cleanall:
	cd ../lib && $(MAKE) clean