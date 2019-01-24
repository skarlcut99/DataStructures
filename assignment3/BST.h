//--------------------------------------------------
// Sukhveer Karlcut
// ID: skarlcut
// Class: 12B/M
//
// BST.h
// A header file for the BST ADT 
// Defines all of the methods in BST.c
// 	Defines methods to insert nodes in a binary tree, traverse through a binary trees in multiple ways, find the leaves of a tree,
// 	find a node in a tree,find the height of a tree, copy a tree, and clear a tree.
//--------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#ifndef _BST_H_INCLUDE_
#define _BST_H_INCLUDE_
#define TRUE 1
#define FALSE 0

// Exported reference type
// Tree node to store strings, space must be allocated for the strings
typedef struct BSTObj {
	char               *term;           /* string data in each block */
	struct BSTObj      *leftChild;      /* ptr to left child */
	struct BSTObj      *rightChild;     /* ptr to right child */
} BSTObj;


// add a new node to the BST with the new_data values, space must be allocated in the BST node
void insert(char *new_data,  BSTObj **pBST);

// print to OUT the inorder traversal
void inorderTraverse(FILE *out, BSTObj *T);

// print to OUT the preorder traversal
void preorderTraverse(FILE *out, BSTObj *T);

// print to OUT the postorder traversal
void postorderTraverse(FILE *out, BSTObj *T);

// print the leaves of the tree in inorder to OUT
void inorderLeaves(FILE *out, BSTObj *T);


// return TRUE if the item_to_find matches a string stored in the tree
int  find(char *term_to_find, BSTObj *T);
               
// compute the height of the tree
// call with height = 0 and root of tree
int treeHeight(BSTObj *T, int height);

// create and return a complete memory independent copy of the tree 
BSTObj * copyTree(BSTObj *T);

// remove all the nodes from the tree, deallocate space and reset Tree pointer
void makeEmpty(BSTObj **pT);

#endif
