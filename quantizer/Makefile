COMPILER = gcc
SRC = quantizer.c
BIN = ejecutable
COMMANDS = clear
FLAGS = -lm -o

all: build clear run

clear:
	$(COMMANDS)
build:
	$(COMPILER) $(FLAGS) $(BIN) $(SRC)
run:
	./$(BIN)
clean:
	rm $(BIN)
