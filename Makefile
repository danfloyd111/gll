# libgll makefile, please have a look to README for further informations

#variables
SHELL = /bin/bash

#fake targets
.PHONY : install
.PHONY : clean
.PHONY : uninstall
.PHONY : test

all: gll.c
	@echo "==> Compiling the sources..."
	@gcc gll.c -c -Wall -Wextra -std=c11 -o2
	@echo "==> Compilation done!"

install: all

clean:
	@echo "==> Cleaning binary and object files..."
	@rm -f 2 gll.o libgll.a
	@echo "==> All clean!"

uninstall: clean
