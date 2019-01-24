//-----------------------------------------------------------------------------
//// BlockchainClient.c
//// Test client for Blockchain ADT
////-----------------------------------------------------------------------------
//
/*
 * Name: Sukhveer Karlcut
 * ID: skarlcut
 * Class: 12B/M
 * This file contains tests for Blockchain.c
 */

#include<stdio.h>
#include<stdlib.h>
#include "Blockchain.h"

////////// add your own tests here /////////////
void myTest(Blockchain B){
	freeBlockchain(B);
	B = NULL;
	B = newBlockchain();
	printf("My own tests\n");
	char hackArr2[] = "one";
	append(B, hackArr2);
	append(B, "two");
	append(B, "three");
	append(B, "four");
	printBlockchain(stdout, B);
	printf("Size: %d\n", size(B));
	printf("Is it valid? Valid: %d\n", valid(B));
	removeLast(B);
	printf("Removing last block\n");
	printBlockchain(stdout, B);
	//break the chain
	Block firstOne = get(B, 0);
	char *value = data(firstOne);
	*value = (*value) + 1;
	printf("Print blockchain after breaking it.\n");
	printBlockchain(stdout, B);
	printf("Is it valid? Valid: %d\n", valid(B));
	//freeBlockchain(B);
	B = NULL;
	//recreate the blockchain
	B = newBlockchain();
	printf("Restart\n");
 	append(B, "one");
 	append(B, "two");
	append(B, "three");
	append(B, "four");
	append(B, "five");
	printBlockchain(stdout, B);
	printf("Size: %d\n", size(B));
	removeLast(B);
	removeLast(B);
	printBlockchain(stdout, B);
	printf("Size: %d\n", size(B));
	//test for corner cases
	printf("Corner tests: \n");
	//freeBlockchain(B);
	B = NULL; 
	append(B, "one"); //should give error message: B is null
	B = newBlockchain();
	removeLast(B);//should give error message:removing last from null chain
	freeBlockchain(B);
	B = NULL;
}

int main(int argc, char* argv[]){
	Blockchain chain = newBlockchain();
	char hackable[] = "one";
	printf("putting in first block = %d\n", append(chain, hackable));
	printBlockchain(stdout, chain);
	printf("putting in second block = %d\n", append(chain, "two"));
	printBlockchain(stdout, chain);
	printf("putting in third block %d\n", append(chain, "three"));
	printf("how many total blocks now? = %d\n", size(chain));
	printBlockchain(stdout, chain);
	//freeBlockchain(chain);
	//chain = NULL;
	printf("find block 2\n");
	Block b =  get(chain, 2);
	printBlock(stdout,b);
	//printf("remove last block and print out\n");
	//removeLast(chain);
	//printBlockchain(stdout, chain);
	printf("valid = %d\n", valid(chain));
	//could use printBlockChain() here but want to explicitly test printBlock()
	printf("printing each block through block print calls \n");
	for (int i = 0; i < size(chain); i++) {
		printBlock(stdout,get(chain, i));
	}
	printf("about to remove the last block\n");
	removeLast(chain);
	printf("removed last block\n");
	printBlockchain(stdout, chain);
	// now break the chain
	b = get(chain, 0);
	char* value =  data(b);
	*value = (*value)+1; // change a value in the first block
	//attempt to append to an invalid chain
	printf("putting in block should have 3 in the chain, %d\n", append(chain, "five"));
	printf("after appending a 3rd element with name five\n");
	// just won't be able to invalidate it
	printf("after append and bad chain valid = %d\n", valid(chain));
	printBlockchain(stdout, chain);
	//myTest(chain);
	return 0;
}
