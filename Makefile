# libgll makefile, please have a look to README for further informations

#variables
SHELL = /bin/bash

#fake targets
.PHONY : install
.PHONY : clean
.PHONY : uninstall
.PHONY : test

all: gll.c
	@echo ">> Compiling the sources..."
	@gcc gll.c -c -Wall -Wextra -std=c11 -O2
	@echo ">> Creating libraries..."
	@ar ruv libgll.a gll.o
	@echo ">> Indexing libraries..."
	@ranlib libgll.a
	@echo ">> All done!"

install: all

clean:
	@echo "==> Cleaning binary and object files..."
	@rm -f gll.o libgll.a
	@echo "==> All clean!"

uninstall: clean
