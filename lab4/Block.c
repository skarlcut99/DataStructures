/*
 * Name: Sukhveer Karlcut
 * ID: skarlcut
 * Class: 12B/M 
 * This file contains methods to construct, destruct, and edit Blocks, and also methods to give information about a Block
 */

#include "Block.h"
#include "assert.h"
#include "string.h"

/*
 * Typedef for BlockObj
 * Exported reference type
 */
typedef struct BlockObj{
	char* data;
	int id;
	long hash;
} BlockObj;

/*
 * newBlock()
 * constructor for the Block type
 *
 * Inputs;
 * 	char* data: a string that is the information stored in the block
 * 	int id: indicates the blocks position in the chain
 * 	long hash: the hash value for the previous block in the chain
 *
 * Outputs:
 * 	Block B: newly created Block using inputs
 */
Block newBlock(char* data, int id, long hash){
	Block B = malloc(sizeof(BlockObj));
	assert(B!=NULL);
	B->data = data;
	B->id = id;
	B->hash = hash;
	return B;
}

/*
 * freeBlock()
 * destructor for the Block type
 *
 * Inputs:
 * 	Block B: Block to be removed
 *
 * Outputs:
 * 	none
 */
void freeBlock(Block B){
	if(B!=NULL){
		free(B);
		B=NULL;
	}
	fprintf(stderr, "Error: Block doesn't exist \n");
}

/*
 * data()
 * return a pointer to this block's data
 * return a copy to avoid, easy erroneous manipulation of blocks,
 *
 * Inputs:
 * 	Block B: Block whose data is to be returned
 *
 * Outputs:
 * 	char* temp: Copy of B's data
 */
char* data(Block B){
	if(B==NULL){
		fprintf(stderr, "Error: Block doesn't exist\n");
		exit(EXIT_FAILURE);
	}
	char* temp;
	temp = B->data;
	return temp;
}

/*
 * previousHash()
 * return the stored previousHash from this block
 *
 * Inputs:
 * 	Block B: Block whose hash is to be returned
 *
 * Outputs:
 * 	long temp: copy of B's hash
 */
long previousHash (Block B){
	if(B==NULL){
                fprintf(stderr, "Error: Block doesn't exist\n");
                exit(EXIT_FAILURE);
        }
	long temp;
	temp = B->hash;
	return temp;
}

/*
 * hash()
 * recomute the hash value for this block
 *
 * Inputs:
 * 	Block B: Block whose id, hash, and data are used to calculate the new hash value for this Block
 *
 * Outputs:
 * 	long value: new hash value for the Block
 */
long hash(Block B){

	long value = -1;
	int i;
	
	if ( B != NULL){
		value = (B -> id) + (B -> hash);

		for ( i = 0 ; i < strlen(B->data) ; i++){
			value += (int) (B->data)[i] ;
		}
		
		return value;
	}

	else {
		fprintf(stderr , "Invalid Input\n");
		return value;	
	}
}

/*
 * printBlock()
 * print the block id and data
 *
 * Inputs:
 * 	File* out: pointer to output file
 * 	Block B: Block to be printed
 *
 * Outputs: none
 */
void printBlock(FILE* out, Block B){

	if (B != NULL){
		fprintf(out , "Block: Data = %s , ID = %i , Hash = %ld\n" , B->data , B->id , B->hash);
		return;
	}
	
	fprintf(stderr, "Invalid Input\n");
}
