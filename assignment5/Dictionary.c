/*
 * File: Dictionary.c
 * Name: Sukhveer Karlcut
 * Class: CMPS 12B
 * CruzID: skarlcut
 * 
 * Description: implementations of Hash Table and all associated helper functions specified in Dictionary.h
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "Dictionary.h"

/*
 * new_bucket_node()
 * Helper function to create a new bucketList node that contains term
 *
 * Inputs:
 *      char * term: the string that the node will have as its term
 *
 * Outputs:
 *      returns the newly created bucketList node
 */
bucketList new_bucket_node(char * term) {
	bucketList node = malloc(sizeof(bucketListObj) + strlen(term)+ 1);// (bucketList) malloc(sizeof(bucketListObj) + (strlen(term) + 1) * sizeof(char));
	assert(node != NULL);
	node -> next = NULL;
	strcpy(node -> item, term);
	return node;
}

/*
 * *newHashTable()
 * Constructor for the hash table object
 *
 * Inputs:
 * 	int size: the size of the hash table
 * Outputs:
 * 	returns the newly created hash table object
 */
HashTableObj 	*newHashTable(int size){
	if(size<1){
		fprintf(stderr, "ERROR: cannot create a hashtable with negative or no size");
		return NULL;
	}
	int i;
	HashTableObj * table = (HashTableObj *) malloc(sizeof(HashTableObj) + sizeof(bucketListObj) * size);
	assert(table != NULL);
	table -> size = size;
	for ( i = 0; i < size; i++ ) {
		table -> bucket[i] = NULL;
	}
	return table;
}

/*
 * deleteHashTable()
 * deletes all  of the data inside a hash table, and frees all the memory allocated for the hash table
 *
 * Inputs:
 * 	HashTableObj *H: the has table to be deleted and freed
 * Outputs:
 * 	none
 */
void 		deleteHashTable(HashTableObj * H){
	bucketList temp = NULL;
	bucketList curr = NULL;
	for ( int i = 0; i < H -> size; i++ ) {
		if((H -> bucket)[i] -> item != NULL) {
			curr = H -> bucket[i];
			while(curr != NULL) {
				temp = curr;
				curr = curr -> next;
				free(temp);
			}
		}
	}
	free(H);
	//H = NULL;
}

/*
 * member()
 * Checks to see if the string is a member of the hashtable or not
 *
 * Inputs:
 * 	HashTableObj *H: the hash table used to find char * str
 * 	char * str: thr string to find in the hash table
 * Outputs:
 * 	returns true if the string is found in the hash table, false if it is not found in the hash table
 */
bool		member(HashTableObj *H, char *str){
	if ( H == NULL ) {
		fprintf(stderr, "ERROR: passed hash table is a NULL reference\n");
		return false;
	}
	if ( str == NULL ) {
		fprintf(stderr, "ERROR: string passed is a NULL reference\n");
		return false;
	}
	int i = hash(str, H->size);
	bucketList temp = (H -> bucket)[i];
	while ( temp != NULL ) {
		if ( ( strcmp(temp -> item, str) == 0 ) )
			return true;
		temp = temp -> next;
	}
	return false;
}

/*
 * insert()
 * inserts a string into a hash table
 *
 * Inputs:
 * 	HashTableObj *H: the hash table to add str to
 * 	char * str: the string to be added to the hash table
 * Outputs:
 * 	none
 */
void 		insert(HashTableObj *H, char *str){
	int index;
	if ( H == NULL ) {
		fprintf(stderr, "ERROR: passed hash table is a NULL reference\n");
		return;
	}
	if ( str == NULL ) {
		fprintf(stderr, "ERROR: string passed is a NULL reference\n");
		return;
	}
	if(H->size <= 0){
		fprintf(stderr, "ERROR: cannot insert into a hash table with size <= 0");
		return;
	}
	index = hash(str, H -> size);
	if ( (H -> bucket)[index] == NULL )
		(H -> bucket)[index] = new_bucket_node(str);
	else {
		bucketList temp = new_bucket_node(str);
		temp -> next = (H -> bucket)[index];
		(H -> bucket)[index] = temp;
	}
}

/*
 * delete()
 * deletes the bucketList holding the string str from the hash table
 *
 * Inputs:
 * 	HashTableObj *H: the hash table from which the bucketList containing str is to be deleted
 * 	char * str: the bucketList with str is deleted
 * Outputs:
 * 	returns true if the bucketList is deleted, false if not found ot not deleted
 */
bool		delete(HashTableObj *H, char *str){
	int index;
	bucketList temp = NULL;
	bucketList delete_temp = NULL;
	if ( H == NULL ) {
		fprintf(stderr, "ERROR: passed hash table is a NULL reference\n");
		return false;
	}
	if ( str == NULL ) {
		fprintf(stderr, "ERROR: string passed is a NULL reference\n");
		return false;
	}
	if ( !member( H, str ) ) {
		fprintf(stderr, "ERROR: term is not in the hash table\n");
		return false;
	}
	index = hash(str, H -> size);
	temp = (H -> bucket)[index];
	if ( temp == NULL )
        return false;
	// case 2: head needs to be deleted
	if ( ( strcmp(temp -> item, str) == 0 ) ) {
		// set 'delete_temp' to the list head so it can be freed
		delete_temp = temp;
		// set the list head pointer to the next node, since the head is going to be freed
		(H -> bucket)[index] = temp -> next;
		// now that the structure is preserved and the list head pointer has been moved, free the original first node
		free(delete_temp);
		return true;
	}
	// case 3: if the node is anywhere else
	// ensure that the next node is not NULL to prevent illegal memory access
	while ( temp -> next != NULL ) {
        if ( ( strcmp((temp -> next) -> item, str) == 0 ) ) {
            delete_temp = temp -> next;
            temp -> next = temp -> next -> next;
            free(delete_temp);
            return true;
        }
        temp = temp -> next;
    }
	return false;
}

/*
 * printHashTable()
 * prints the hash table and all its values to file out
 *
* Inputs:
 * 	FILE *out: where the contents of the hash table are printed
 *	Hashtable Obj *H: the hash table to be printed
 * Outputs:
 * 	none
 */
void		printHashTable(FILE *out, HashTableObj *H){
	bucketList list;
	int i;
	if (H == NULL) {
		fprintf(stderr, "ERROR: Hashtable does not exist, so can't print it.\n");
		return;
	}
	if(out == NULL){
		fprintf(stderr, "ERROR: null output file");
		return;
	}
	list = NULL;
	fprintf(out, "Hash table contents\n");
	for ( i = 0; i < H -> size; i++ ) {
		list = H -> bucket[i];
		fprintf(out, "bucket %d\n", i);
		while (list != NULL) {
			fprintf(out, "    bucket list item = %s\n", list->item);
			list = list -> next;
		}
	}
}

/*
 * rotate_left()
 * Helper function to shift the bits in an unsigned int by a specified amount
 * 
 * Inputs:
 *      unsigned int value: the value to be shifted
 *      int shift: the amount to shift the specified value
 * Outputs:
 *      The new shifted int
 */
unsigned int rotate_left(unsigned int value, int shift) {
	int sizeInBits = 8*sizeof(unsigned int);
	shift = shift & (sizeInBits - 1);
	if ( shift == 0 )
	return value;
	return (value << shift) | (value >> (sizeInBits - shift));
}

/*
 * Function: pre_hash()
 * Helper function to convert a string to an unsigned int
 * 
 * Inputs:
 *      char* input: the string to be converted into an unsigned int
 * Outputs:
 *      result: the newly calculated unsigned int, the prehash value for the char* input
 */
unsigned int pre_hash(char* input) {
	unsigned int result = 0xBAE86554;
	while (*input) {
		result ^= *input++;
		result = rotate_left(result, 5);
	}
	return result;
}

/*
 * hash()
 * Helper function to hash a string, returning an integer in the range 0 to tableSize-1
 *
 * Inputs:
 * 	char * key: the string to hash and generate an index for
 * 	int tableSize: the size of the hash table, used to generate the hash index
 * Outputs:
 *      the calculated index value for the specified string
 */
int hash(char* key, int tableSize) {
	return pre_hash(key)%tableSize;
}
