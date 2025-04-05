# SAI project main Makefile
# author: Jakub Dudziński jdudzinski101@gmail.com

ROOT_DIR=$(shell pwd)
INC_DIR=$(ROOT_DIR)/include
LIB_DIR=$(ROOT_DIR)/lib

export ROOT_DIR
export INC_DIR
export LIB_DIR

all: libindexer test

.PHONY:  clean_indexer clean_test test lib/libindexer.a
libindexer: lib/libindexer.a
	@echo "Successfully compiled indexer.";

lib/libindexer.a:
	@make -C src libindexer.a;

test:
	@make -C test $@;
	@echo "Successfully compiled test to test/bin directory.";

clean: clean_indexer clean_test

clean_indexer:
	@make -C src $@;

clean_test:
	@make -C test $@;
