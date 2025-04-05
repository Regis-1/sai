CXXFLAGS=-I$(INC_DIR) -Wall -Wextra

search_engine: main.o tokenizer.o
	$(CXX) -o $(ROOT_DIR)/$@ $^;

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c $^;

tokenizer.o: tokenizer.cpp
	$(CXX) $(CXXFLAGS) -c $^;

.PHONY: clean_engine
clean_engine:
	@echo "removing src/*.o files";
	@rm -f *.o;
	@echo "removing created binery in $(ROOT_DIR)"
	@rm -f $(ROOT_DIR)/search_engine
	@echo "Successfully cleaned engine project."
