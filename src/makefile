CC=gcc
FLAGS= -std=c99 -Wall -g -o

DEP=graphs.h array.h dijkstra.h stack.h main.h
SRC=graphs.c main.c array.c dijkstra.c stack.c

BIN=graphs

.PHONY: all clean

all: $(SRC)
	gcc $(FLAGS) $(BIN) $(SRC) $(DEP)

test: $(TEST)
	gcc $(FLAGS) $(TEST_BIN) $(TEST) $(TEST_DEP)

clean:
	$(RM) $(BIN) *~
