# libgll makefile, please have a look to README for further informations

#variables
SHELL = /bin/bash

#fake targets
.PHONY : install
.PHONY : clean
.PHONY : uninstall
.PHONY : test

all: src/gll.c src/gll.h
	@echo ">> Compiling the sources..."
	@mkdir -p lib
	@gcc src/gll.c -c -Wall -Wextra -std=c11 -O2 -o lib/gll.o
	@echo ">> Creating libraries..."
	@ar ruv lib/libgll.a lib/gll.o
	@echo ">> Indexing libraries..."
	@ranlib lib/libgll.a
	@echo ">> All done!"

install: all

clean:
	@echo ">> Cleaning binary and object files..."
	@rm -r -f lib bin
	@echo ">> All clean!"

uninstall: clean

test: all src/gll-test.c
	@echo ">> Compiling test..."
	@mkdir -p bin
	@gcc src/gll-test.c -o bin/gll-test -Wall -Wextra -std=c11 -O2 -L lib/ -lgll
	@echo ">> Running test..."
	@bin/gll-test
	@echo ">> Test end!"
