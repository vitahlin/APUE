.PHONY: build clean

lib_obj = ../lib/log_err.o ../lib/system.o ../lib/tellwait.o 

all: 01-8_1-fork

01-8_1-fork:
	cd ../lib && $(MAKE) -f lib.mk
	clang -c 01-8_1-fork.c 
	clang -o 01-8_1-fork.out 01-8_1-fork.o $(lib_obj)

clean:
	cd ../lib && $(MAKE) -f lib.mk clean
	-rm -f *.o *.out