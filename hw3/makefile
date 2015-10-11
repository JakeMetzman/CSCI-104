CC       = g++
CPPFLAGS = -Wall -g
BIN_DIR  = bin
GTEST_LL = -I /usr/local/opt/gtest/include/ -l gtest -l gtest_main -pthread

all: $(BIN_DIR)/alistint.o $(BIN_DIR)/stackint.o $(BIN_DIR)/boolexpr

$(BIN_DIR)/alistint.o: alistint.cpp alistint.h $(BIN_DIR)/.dirstamp
	$(CC) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/stackint.o: stackint.cpp stackint.h $(BIN_DIR)/alistint.o
	$(CC) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/alisttest: alisttest.cpp $(BIN_DIR)/alistint.o 
	$(CC) $(CPPFLAGS) $^ $(GTEST_LL) -o $@

$(BIN_DIR)/stacktest: stacktest.cpp $(BIN_DIR)/stackint.o $(BIN_DIR)/alistint.o
	$(CC) $(CPPFLAGS) $^ $(GTEST_LL) -o $@

$(BIN_DIR)/boolexpr: boolexpr.cpp $(BIN_DIR)/stackint.o $(BIN_DIR)/alistint.o
	$(CC) $(CPPFLAGS) $^ -o $@

.PHONY: clean alisttests stacktests

alisttest: $(BIN_DIR)/alisttest
	-@$(BIN_DIR)/alisttest
	-@echo "--- All Tested!---"

stacktest: $(BIN_DIR)/stacktest
	-@$(BIN_DIR)/stacktest
	-@echo "--- All Tested!---"

clean: 
	rm -rf $(BIN_DIR)

$(BIN_DIR)/.dirstamp:
	mkdir -p $(BIN_DIR)
	touch $(BIN_DIR)/.dirstamp