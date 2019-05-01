COMPILER = gcc
SRC = dequantizer.c ../leyMu/compressor.c
BIN = ejecutable
COMMANDS = clear
FLAGS = -lm -o

all: build clear run clean

clear:
	$(COMMANDS)
build:
	$(COMPILER) $(FLAGS) $(BIN) $(SRC)
run:
	./$(BIN)
clean:
	rm $(BIN)
