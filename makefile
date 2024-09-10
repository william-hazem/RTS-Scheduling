# source code
SRC = main.cpp

# library flags
JSONC-DIR = lib/json-c
JSONC-INCLUDE = $(JSONC-DIR)/include
JSONC-LIB     = $(JSONC-DIR)/lib-unix

LOGGER-DIR = lib/logger
LOGGER-INCLUDE = $(LOGGER-DIR)/include
LOGGER-LIB = $(LOGGER-DIR)/lib

CFLAG = -lpthread -Iinclude -I$(JSONC-INCLUDE) -L$(JSONC-LIB) -ljson-c
CFLAG += -I$(LOGGER-INCLUDE) -L$(LOGGER-LIB) -llogger

LIB_DIR = lib
OBJ_DIR = obj

all: logger | main

$(LIB_DIR):
	mkdir -p $(LIB_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

main: $(SRC) | logger
	g++ $(SRC) $(CFLAG) -L$(LIB_DIR) -o main

logger: $(LOGGER-DIR) | $(OBJ_DIR)
	gcc -c $(LOGGER-DIR)/include/logger.c -o $(OBJ_DIR)/logger.o
	ar rcs $(LOGGER-LIB)/liblogger.a $(OBJ_DIR)/logger.o

clean: 
	rm -rf obj