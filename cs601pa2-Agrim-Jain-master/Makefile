# Makefile for Finite Element Method (FEM) Simulation

# Compiler and Compilation Flags
CC = g++
CFLAGS = -Wall -Werror -g -I /home/resiliente/cs601software/eigen-3.3.9

# Source and Binary Directories
SRC = src/
BIN = bin/
CLEANOBJ = $(BIN)

# Default Problem and Number of Elements
PROB ?= 0
N ?= 0

# Target Rules
all: isBin bin/FEM.o run

compile: isBin bin/FEM.o

$(BIN)FEM.o: $(SRC)main.cpp 
	$(CC) $^ $(CFLAGS) -o $(BIN)FEM.o

run: 
	@echo $(PROB) $(N)
	$(BIN)FEM.o $(PROB) $(N)

isBin:
	if [ ! -d $(BIN) ]; then mkdir $(BIN); fi

# Clean Generated Files
clean:
	if [ -d $(CLEANOBJ) ]; then rm -r $(CLEANOBJ); fi

# Display Team Information
team:
	@echo 210030035 - Srihari K G
	@echo 210010058 - Vivek Pillai
	@echo 210010003 - Agrim Jain
