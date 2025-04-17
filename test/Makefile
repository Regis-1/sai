SRC_DIR=$(ROOT_DIR)/src
GTEST_DIR=$(ROOT_DIR)/extlibs/googletest
BIN_DIR=bin

CXXFLAGS=-I$(INC_DIR) -I$(GTEST_DIR)/googletest/include -Wall -Wextra
LDFLAGS=-L$(GTEST_DIR)/build/lib -lgtest -L$(LIB_DIR) -lindexer

.PHONY: $(BIN_DIR) clean_test
all: test

test: $(BIN_DIR)/tokenizerTests $(BIN_DIR)/indexerTests

$(BIN_DIR)/tokenizerTests: tokenizerTests.o $(BIN_DIR)
	$(CXX) -o $@ tokenizerTests.o $(LDFLAGS);

tokenizerTests.o: tokenizerTests.cpp
	$(CXX) $(CXXFLAGS) -c $^;

$(BIN_DIR)/indexerTests: indexerTests.o $(BIN_DIR)
	$(CXX) -o $@ indexerTests.o $(LDFLAGS);

indexerTests.o: indexerTests.cpp
	$(CXX) $(CXXFLAGS) -c $^;

$(BIN_DIR):
	mkdir -p $(BIN_DIR);

clean_test:
	@echo "removing test/bin directory";
	rm -rf $(BIN_DIR);
	@echo "removing test/*.o files";
	rm -f *.o;
	@echo "Successfully cleaned tests."
