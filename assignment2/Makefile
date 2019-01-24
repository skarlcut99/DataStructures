# Sukhveer Karlcut 
# skarlcut@ucsc.edu
# CMPS 12-M
# Makefile for list.c and listUtil.c with macros

FLAGS = -Wall -std=c99
OBJECTS = main.o list.o listUtil.o
SOURCES = main.c list.c listUtil.c
HEADERS = list.h listUtil.h
EXECBIN = main

all : $(EXECBIN)

$(EXECBIN) : $(OBJECTS) $(HEADERS)
	gcc -o $(EXECBIN) $(OBJECTS)

$(OBJECTS) : $(SOURCES)
	gcc -c $(FLAGS) $(SOURCES)

clean :
	rm -f $(EXECBIN) $(OBJECTS)

check :
	valgrind --leak-check=full main
