CC       = g++
CPPFLAGS = -Wall -g
BIN_DIR  = bin
GTEST_LL = -I /usr/local/opt/gtest/include/ -l gtest -l gtest_main -pthread

all: $(BIN_DIR)/myset.o $(BIN_DIR)/mdparser.o $(BIN_DIR)/webpage.o $(BIN_DIR)/searcheng.o $(BIN_DIR)/search

$(BIN_DIR)/myset.o: myset.cpp myset.h $(BIN_DIR)/.dirstamp
	$(CC) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/mdparser.o: mdparser.cpp mdparser.h
	$(CC) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/webpage.o: webpage.cpp webpage.h $(BIN_DIR)/myset.o $(BIN_DIR)/mdparser.o
	$(CC) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/searcheng.o: searcheng.cpp searcheng.h $(BIN_DIR)/myset.o $(BIN_DIR)/mdparser.o $(BIN_DIR)/webpage.o
	$(CC) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/search: search.cpp $(BIN_DIR)/searcheng.o $(BIN_DIR)/myset.o $(BIN_DIR)/mdparser.o $(BIN_DIR)/webpage.o
	$(CC) $(CPPFLAGS) $^ -o $@

.PHONY: clean

clean: 
	rm -rf $(BIN_DIR)

$(BIN_DIR)/.dirstamp:
	mkdir -p $(BIN_DIR)
	touch $(BIN_DIR)/.dirstamp