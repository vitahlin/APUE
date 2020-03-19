.PHONY: buildall clean cleano

cleano:
	cd ../lib && $(MAKE) -f lib.mk cleano
	-rm -f *.o
clean:
	cd ../lib && $(MAKE) -f lib.mk clean
	-rm -f *.o *.out

lib_obj = ../lib/log_err.o ../lib/system.o ../lib/tellwait.o 

buildall: 01-8_1-fork 02-8_3-vfork

01-8_1-fork:
	make clean
	cd ../lib && $(MAKE) -f lib.mk
	clang -c 01-8_1-fork.c 
	clang -o 01-8_1-fork.out 01-8_1-fork.o $(lib_obj)

02-8_3-vfork:
	make clean
	cd ../lib && $(MAKE) -f lib.mk
	clang -c 02-8_3-vfork.c 
	clang -o 02-8_3-vfork.out 02-8_3-vfork.o $(lib_obj)