CC=clang
DEPENDENCIES=-lm -lssl -lcrypto -lcjson -lb64
DEBFLGS=-g -Wall  -pedantic 
OPFLGS=-O3  
PREFIX ?= /usr/local



SRC_DIR=.
INC_DIRS = $(shell find $(SRC_DIR) -type d)
INCLUDE_FLAGS = $(addprefix -I, $(INC_DIRS))


SRC_FILES = $(shell find $(SRC_DIR) -type f -name "*.c")
FILES= $(SRC_FILES) $(INCLUDE_FLAGS)

Locker :
	$(CC) $(DEPENDENCIES) $(FILES) -o $@

optimization_testing :
	$(CC) $(OPFLGS) $(DEPENDENCIES) $(FILES) -o $@
debug :
	$(CC)  $(DEBFLGS) $(DEPENDENCIES) $(FILES) -o $@
clean:
	rm debug optimization_testing Locker


