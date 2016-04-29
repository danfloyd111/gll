# libgll makefile, please have a look to README for further informations

#variables
SHELL = /bin/bash

#fake targets
.PHONY : install
.PHONY : clean
.PHONY : uninstall
.PHONY : test

all: src/gll.c
	@echo ">> Compiling the sources..."
	@mkdir lib
	@gcc src/gll.c -c -Wall -Wextra -std=c11 -O2 -o lib/gll.o
	@gcc src/gll-test.c -o gll-test -Wall -Wextra -std=c11 -O2 -L lib/ -lgll
	@echo ">> Creating libraries..."
	@ar ruv lib/libgll.a lib/gll.o
	@echo ">> Indexing libraries..."
	@ranlib lib/libgll.a
	@echo ">> All done!"

install: all

clean:
	@echo ">> Cleaning binary and object files..."
	@rm -r -f lib
	@echo ">> All clean!"

uninstall: clean

test: all
	@echo ">> Compiling test..."
	@echo ">> Running test..."
