.PHONY: buildall clean cleano

lib_obj = ../lib/log_err.o ../lib/system.o ../lib/tellwait.o 

buildall: 01-8_1-fork

01-8_1-fork:
	make clean
	cd ../lib && $(MAKE) -f lib.mk
	clang -c 01-8_1-fork.c 
	clang -o 01-8_1-fork.out 01-8_1-fork.o $(lib_obj)

cleano:
	cd ../lib && $(MAKE) -f lib.mk cleano
	-rm -f *.o

clean:
	cd ../lib && $(MAKE) -f lib.mk clean
	-rm -f *.o *.out