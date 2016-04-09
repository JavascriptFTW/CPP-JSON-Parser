CC = g++

CFLAGS = -W -Wall

SRC_DIR = src

OBJS = $(SRC_DIR)/main.o $(SRC_DIR)/Lexer.o

TARGET = main

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(CFLAGS)

$(SRC_DIR)/main.o: $(SRC_DIR)/main.cpp $(SRC_DIR)/Lexer.o
	$(CC) $(SRC_DIR)/main.cpp -c -o $(SRC_DIR)/main.o $(CFLAGS)

$(SRC_DIR)/Tokenizer.o: $(SRC_DIR)/Lexer.cpp $(SRC_DIR)/Lexer.hpp
	$(CC) $(SRC_DIR)/Lexer.cpp -c -o $(SRC_DIR)/Lexer.o $(CFLAGS)
