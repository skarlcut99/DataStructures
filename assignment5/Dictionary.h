//-----------------------------------------------------------------------------
// Sukhveer Karlcut
// ID: skarlcut
// Class: 12B/M
// 
// Dictionary.h
// Header file for the HashTable ADT
// Array implmentation with  bucket heads that point to linked list of items
// that hash to this bucket
//
// Note that the hash table size is decided by the client and passed to
// the new function that creates the hash table.
//
//-----------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#ifndef _DICTIONARY_H_INCLUDE_
#define _DICTIONARY_H_INCLUDE_


typedef struct bucketListObj  *bucketList;

/*
 * Exported reference type
 * constructor for bucketListObj, which contains a linked list of strings
 */
typedef struct bucketListObj {
    bucketList 	next;
    char 	item[];
} bucketListObj;

/*
 * this item will be dynamically allocated newHash,
 * must manage the index to stay in allocated array range
 *
 * Exported reference type
 * constructor for HashTableObj, which contains an array of bucketLists
 */
typedef struct HashTableObj {
    int		size;		// MUST COME FIRST!!!
    bucketList bucket[];
} HashTableObj;

/*
 * *newHashTable()
 * Constructor for the hash table object
 */
HashTableObj 	*newHashTable(int size);
/*
 * deleteHashTable()
 * deletes all  of the data inside a hash table, and frees all the memory allocated for the hash table
 */
void 		deleteHashTable(HashTableObj * H);
/*
 * member()
 * Checks to see if the string is a member of the hashtable or not
 */
bool		member(HashTableObj *H, char *str);
/*
 * insert()
 * inserts a string into a hash table
 */
void 		insert(HashTableObj *H, char *str);
/*
 * delete()
 * deletes the bucketList holding the string str from the hash table
 */
bool		delete(HashTableObj *H, char *str);
/*
 * printHashTable()
 * prints the hash table and all its values to file out
 */
void		printHashTable(FILE *out, HashTableObj *H);
/*
 * new_bucket_node()
 * Helper function to create a new bucketList node that contains term
 */
bucketList new_bucket_node(char * term);

/*
 * rotate_left()
 * Helper function to shift the bits in an unsigned int by a specified amount
 */
unsigned int rotate_left(unsigned int value, int shift);
/*
 * pre_hash()
 * Helper function to convert a string to an unsigned int
 */
unsigned int pre_hash(char* input);
/*
 * hash()
 * Helper function to hash a string, returning an integer in the range 0 to tableSize-1
 */
int hash(char* key, int tableSize);
#endif

