BIN=testped
WARN=-Wall -Wextra
VALGRIND_OPT=--leak-check=full --show-leak-kinds=all --track-origins=yes --verbose
VALGRIND_OUT=--log-file=valgrind-log.txt

all:
	g++ *.cpp $(WARN) -o $(BIN)

valgrind:
	valgrind $(VALGRIND_OPT) $(VALGRIND_OUT) ./$(BIN)

clean:
	rm $(BIN)
