# Sukhveer Karlcut 
# skarlcut@ucsc.edu
# CMPS 12-M
# Makefile for BST.c BSTClient.c with macros

FLAGS = -std=c99 -Wall
SOURCES = BST.c BSTClient.c
OBJECTS = BST.o BSTClient.o
EXEBIN = BSTClient

all: $(EXEBIN)

$(EXEBIN) : $(OBJECTS)
	gcc -o $(EXEBIN) $(OBJECTS)
$(OBJECTS) : $(SOURCES)
	gcc -c $(FLAGS) $(SOURCES)
clean :
	rm -f $(EXEBIN) $(OBJECTS)
check:
	valgrind --leak-check=full BSTClient
