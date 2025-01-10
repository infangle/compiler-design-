# Compiler and flags
CC = gcc
CFLAGS = -Wall -g

# Directories
SRC_DIR = src
BUILD_DIR = build
TEST_DIR = tests

# Flex/Bison files
LEX_FILE = $(SRC_DIR)/lexer/lexer.l
YACC_FILE = $(SRC_DIR)/parser/parser.y

# Output files
LEX_C = $(BUILD_DIR)/lex.yy.c
YACC_C = $(BUILD_DIR)/y.tab.c
YACC_H = $(BUILD_DIR)/y.tab.h
EXEC = $(BUILD_DIR)/compiler

# Targets
all: $(EXEC)

$(LEX_C): $(LEX_FILE)
	  flex -o $@ $<

$(YACC_C) $(YACC_H): $(YACC_FILE)
	  bison -d -o $(BUILD_DIR)/parser.c $<

$(EXEC): $(LEX_C) $(YACC_C)
	  $(CC) $(CFLAGS) -o $@ $^

clean:
	  rm -rf $(BUILD_DIR)/*

test: $(EXEC)
	  ./$(EXEC) < $(TEST_DIR)/inputs/test1.txt > $(TEST_DIR)/outputs/test1.out

.PHONY: all clean test
