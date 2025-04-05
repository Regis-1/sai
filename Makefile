# SAI project main Makefile
# author: Jakub Dudziński jdudzinski101@gmail.com

ROOT_DIR=$(shell pwd)
INC_DIR=$(ROOT_DIR)/include

export ROOT_DIR
export INC_DIR

all: search_engine

.PHONY: search_engine test cleanengine cleantest
search_engine:
	@make -C src $@;
	@echo "Successfully compiled search engine.";

test:
	@make -C test $@;
	@echo "Successfully compiled test to test/bin directory.";

clean: clean_engine clean_test

clean_engine:
	@make -C src $@;

clean_test:
	@make -C test $@;
