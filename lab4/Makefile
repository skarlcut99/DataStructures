# Sukhveer Karlcut 
# # skarlcut@ucsc.edu
# # CMPS 12-M
# Makefile for Block.c Blockchain.c BlockchainClient.c with macros

FLAGS = -std=c99 -Wall
SOURCES = Block.c Blockchain.c BlockchainClient.c 
OBJECTS = Block.o Blockchain.o BlockchainClient.o
EXEBIN = BlockOut

all: $(EXEBIN)

$(EXEBIN) : $(OBJECTS)
	gcc -o $(EXEBIN) $(OBJECTS)
$(OBJECTS) : $(SOURCES)
	gcc -c $(FLAGS) $(SOURCES)
clean :
	rm -f $(EXEBIN) $(OBJECTS)
check:
	valgrind --leak-check=full BlockOut
