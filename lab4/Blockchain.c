/*
 * Name: Sukhveer Karlcut
 * ID: skarlcut
 * Class: 12B/M
 * This file contains methods to construct, destruct, and edit Blockchains, and also methods to give information about a Blockchain
 */

#include "Blockchain.h"
#include "assert.h"
#define BLOCKCHAIN_SIZE 100

/*
 * Struct for type BlockchainObj
 * Exported reference type
 */
struct BlockchainObj{
	Block chain[BLOCKCHAIN_SIZE];
	int size;
};

/*
 * newBlockchain()
 * Constructor for the Blockchain type
 *
 * Inputs:
 * 	none
 *
 * Outputs:
 * 	Blockchain B: newly created Blockchain with allocated memory
 */
Blockchain newBlockchain(){
	Blockchain B = malloc(sizeof(Blockchain));
	assert(B!=NULL);
	B->size = 0;
	return B;
}

/*
 * freeBlockchain()
 * destructor for the Blockchain type
 *
 * Inputs:
 * 	Blockchain B: Blockchain to be freed
 *
 * Outputs:
 * 	none
 */
void freeBlockchain(Blockchain B){
	if (B == NULL) {
                fprintf(stderr , "Invalid Input (NULL) \n");
                return;
        }
	else{
		free(B);
		B = NULL;
	}
}

/*
 * append()
 * append a new block to the chain with the data specified in the new block
 * return the size of the block chain if successful and 0 otherwise
 *
 * Inputs:
 * 	Blockchain B: current Blockchain
 * 	char* data:string of information to be stored in the Block that will be added to the chain
 * 	Blockchain B or char* data can't be NULL to append to the Blockchain
 *
 * Outputs:
 * 	int B->size: the new size of the Blockchain after the new Block has been added
 */
int append(Blockchain B, char* data){
	if (B == NULL || data == NULL) {
		fprintf(stderr , "Invalid NULL Input\n");
		return (0);
	}

	long prev;
	int id;
	Block b;

	if ( B->size == 0){
		prev = 0;
	}

	else{
		prev = hash(B->chain[B->size-1]);
	}

	id = B->size;
	b = newBlock(data , id , prev);
	B->chain[B->size] = b;

	B->size = B->size + 1;
	return (B->size);
}

/*
 * size()
 * return the number of blocks in this chain
 *
 * Inputs:
 * 	Blockchain B: the blockchain whose size is to be returned
 *
 * Outputs:
 * 	int B->size: size of Blockchain B
 */
int size(Blockchain B){
	return B->size;
}

/*
 * get()
 * return the block at index idx in the chain
 *
 * Inputs:
 * 	Blockchain B: the blockchain to look for the element at the idxth index
 * 	int idx: index of the Block to be returned
 *
 * Outputs:
 * 	Block: returns the Block at index idx in Blockchain B, or a null Block if the Block is not found
 */
Block get(Blockchain B, int idx){
	if ( valid(B) == 1){
		
		int index = 0;
		while ( index != idx && index != BLOCKCHAIN_SIZE && B->chain[index] != NULL){
			index = index+1;
		}
		
		if ( index == idx){
			return B->chain[index];
		}
		else
			fprintf(stderr , "Block in Blockchain not found");
		//return;
	}
	fprintf(stderr , "Invalid Input");
	Block C = NULL;
	return C;
}

/*
 * valid()
 * check if this is a valid chain by checking the stored previousHash values in each block
 * return 1 if valid, 0 otherwise
 *
 * Inputs:
 * 	Blockchain B: blockchain to be checked if it is valid
 *
 * Outputs:
 * 	int: 1 if valid, 0 if not valid
 */
int valid(Blockchain B){
	if (B == NULL){
		return 0;
	}

	if ( (B->size) < 2){
		return 1;
	}
	
	int i;
	long prev_hash;
	long curr_hash;		
	Block b;

	for ( i = 0 ; i < (B->size)-1 ; i++){

		b = B->chain[i];
		prev_hash = hash(b);
		
		b = B->chain[i+1];
		curr_hash = previousHash(b);
		
		if ( prev_hash != curr_hash){
			return 0;
		}
	}
			
	return 1;
}

/*
 * removeLast()
 * shorten the chain by revmoing the last block
 * do nothing if the chain is already empty
 *
 * Inputs:
 * 	Blockchain B: Blockchain of which the last element is to be removed
 *
 * Outputs:
 * 	none
 */
void removeLast(Blockchain B){
	if ( B == NULL){
		fprintf(stderr, "Blockchain Error: removeLast() called on NULL Block reference\n");
	}
	else if (B->size == 0)
		fprintf(stderr, "Blockchain Error: removeLast() called on empty Block reference\n");
	else{
		freeBlock(B->chain[B->size -1]);
		B->size --;
	}
}

/*
 * printBlockchain()
 * print the Blockchain
 *
 * Inputs:
 * 	File* out: pointer to output file
 * 	Blocchain B: Blockchain to be printed
 * 
 * Outputs: none
 */
void printBlockchain(FILE* out, Blockchain B){
	if (B == NULL){
		fprintf(stderr, "Blockchain Error: printBlockchain() called on NULL Block reference\n");
		return;

	}
		
	int index;

	for (index = 0; index < B->size; index++) {
		printBlock(out, B->chain[index]);
	}
}
