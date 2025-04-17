CXXFLAGS=-I$(INC_DIR) -Wall -Wextra

libindexer.a: tokenizer.o indexer.o
	mkdir -p $(ROOT_DIR)/lib;
	ar crf $(ROOT_DIR)/lib/$@ $^;

tokenizer.o: tokenizer.cpp
	$(CXX) $(CXXFLAGS) -c $^;

indexer.o: indexer.cpp
	$(CXX) $(CXXFLAGS) -c $^;

.PHONY: clean_engine
clean_indexer:
	@echo "removing src/*.o files";
	@rm -f *.o;
	@echo "removing created lib in $(ROOT_DIR)/lib directory"
	@rm -f $(ROOT_DIR)/lib/libindexer.a
	@echo "Successfully cleaned engine project."
