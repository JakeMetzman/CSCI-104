CXX = g++
CPPFLAGS = -g -Wall
BIN_DIR = bin

all: $(BIN_DIR)/is_present $(BIN_DIR)/splitlist $(BIN_DIR)/llistint_tests

$(BIN_DIR)/is_present: is_present.cpp $(BIN_DIR)/.dirstamp
	g++ -g -Wall is_present.cpp -o $(BIN_DIR)/is_present
$(BIN_DIR)/splitlist: splitlist.cpp $(BIN_DIR)/.dirstamp
	g++ -g -Wall splitlist.cpp -o $(BIN_DIR)/splitlist
$(BIN_DIR)/llistint_tests: llistint_tests.cpp llistint.cpp llistint.h $(BIN_DIR)/.dirstamp
	g++ -g -Wall llistint_tests.cpp -o $(BIN_DIR)/llistint_tests

.PHONY: clean
clean:
	rm -rf $(BIN_DIR)

$(BIN_DIR)/.dirstamp:
	mkdir -p $(BIN_DIR)
	touch $(BIN_DIR)/.dirstamp