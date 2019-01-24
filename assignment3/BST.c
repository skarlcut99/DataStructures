/*
 * Name: Sukhveer Karlcut
 * ID: skarlcut
 * Class: 12B/M
 * This file contains methods to insert nodes in a binary tree, traverse through a binary trees in multiple ways, find the leaves of a tree,
 * find a node in a tree,find the height of a tree, copy a tree, and clear a tree.
 */

#include "BST.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * insert()
 * add a new node to the BST with the new_data values, space must be allocated in the BST node
 *
 * Inputs:
 * 	char *new_data: the term of the node to be inserted, to be compared with the term of **pBST to determine where to insert the node
 * 	BSTObj **pBST: the node whose term is used to compare with new_data, to determine where to insert the new node with term new_data
 *
 * Outputs:
 * 	none
 */
void insert(char *new_data,  BSTObj **pBST){
        if(pBST == NULL){
                fprintf(stderr, "Invalid NULL pointer \n");
                return;
        }
        if(new_data == NULL){
                fprintf(stderr, "Invalid Input. Can't insert a NULL string\n");
                return;
        }
        BSTObj *T = *pBST;

        if(T == NULL){
                T = (BSTObj *) malloc(sizeof(BSTObj));
                char* newStr =   (char*)(calloc(strlen(new_data) , sizeof(char)));
                int i;
                for(i = 0; i < strlen(new_data); i++){
                        newStr[i] = new_data[i];
                }
                newStr[i+1] = '\0';
                T->term = newStr;
                *pBST = T;
        }

        else{
                if(T->leftChild == NULL && strcmp(new_data, T->term) < 0){

                        T->leftChild = (BSTObj *) malloc(sizeof(BSTObj));
                        char* newStr = (char*)(calloc(strlen(new_data), sizeof(char)));
                        int i;

                        for(i = 0; i < strlen(new_data); i++){
                                newStr[i] = new_data[i];
                        }

                        newStr[i+1] = '\0';
                        T->leftChild->term = newStr;
                        return;
                }

                if(T->rightChild == NULL && strcmp(new_data, T->term) > 0){
                        T->rightChild = (BSTObj *) malloc(sizeof(BSTObj));

                        char* newStr = (char*) calloc(strlen(new_data), sizeof(char));
                        int i;
                        for(i = 0; i < strlen(new_data); i++){
                                newStr[i] = new_data[i];
                        }
                        newStr[i+1] = '\0';
                        T->rightChild->term = newStr;
                        return;
                }

                if(strcmp(new_data, T->term) < 0){
                        insert(new_data, &(T->leftChild));
                }
                else{
                        insert(new_data, &(T->rightChild));
                }
        }
}

/*
 * inorderTraverse()
 * print to OUT the inorder traversal
 *
 * Inputs:
 * 	File *out: the file to output the traverse print
 * 	BSTObj *T: the starting node, printing the left child, then the node, and finally the right child
 *
 * Outputs:
 * 	none
 */
void inorderTraverse(FILE *out, BSTObj *T){
	if (T == NULL)    
                return; 
        inorderTraverse(out, T->leftChild); 
	fprintf(out,"%s ", T->term);
        inorderTraverse(out, T->rightChild); 
}

/*
 * preorderTraverse()
 * print to OUT the preorder traversal
 *
 * Inputs:
 * 	File *out: the file to output the traverse print
 * 	BSTObj *T: the starting node, printing the node, then the left child, and finally the right child
 *
 * Outputs:
 * 	none
 */
void preorderTraverse(FILE *out, BSTObj *T){
	if (T == NULL)
                return;
	fprintf(out,"%s ", T->term);
        preorderTraverse(out, T->leftChild);
        preorderTraverse(out, T->rightChild);
}

/*
 * postorderTraverse()
 * print to OUT the postoder traversal
 *
 * Inputs:
 * 	File *out: the file to output the traverse print
 * 	BSTObj *T: the starting node, printing the left child, then the right child, and finally the node
 *
 * Outputs:
 * 	none
 */
void postorderTraverse(FILE *out, BSTObj *T){
	if (T == NULL) 
        	return; 
	postorderTraverse(out, T->leftChild); 
	postorderTraverse(out, T->rightChild); 
	fprintf(out,"%s ", T->term);
}

/*
 * inorderLeaves()
 * print the leaves of the tree in inorder to OUT
 *
 * Inputs:
 * 	File *out: the file to output the traverse print
 * 	BSTObj *T: the starting node, traversing in an inorder fashion, printing the node if it is a leaf of the tree
 *
 * Outputs:
 * 	none
 */
void inorderLeaves(FILE *out, BSTObj *T){
	if (T == NULL)
                return;
        inorderLeaves(out, T->leftChild);  
        if(T->leftChild == NULL && T->rightChild == NULL)
		fprintf(out,"%s ", T->term);
        inorderLeaves(out, T->rightChild);
}

/*
 * find()
 * return TRUE if the item_to_find matches a string stored in the tree, FALSE otherwise
 *
 * Inputs:
 * 	char *term_to_find: looking for a node in the tree with term that is term_to_find
 * 	BSTObj *T: the node to check if its term is equal to term_to_find, if its not found, then T's left child and right child are checked
 *
 * Outputs:
 * 	int: returns TRUE, or 1, if the node is found in the tree, returns FALSE, or 0, if the node is not found in the tree
 */
int find(char *term_to_find, BSTObj *T){
	if(T == NULL)
		return FALSE;
	int temp = strcmp(T->term, term_to_find);
	if(temp == 0){
		return TRUE;
	}
	else if(temp < 0)
		return find(term_to_find, T->leftChild);
	else
		return find(term_to_find, T->rightChild);
}

/*
 * treeHeight()
 * compute the height of the tree
 * call with height = 0 and root of tree
 *
 * Inputs:
 * 	BSTObj *T: the node on the current level of the tree, checking if there are more levels to the tree
 * 	int height: the current height of the tree
 *
 * Outputs:
 * 	int: returns the height of the tree
 */
int treeHeight(BSTObj *T, int height){
	if (T == NULL)  
		return 0;
	else 
	{
		int lDepth = treeHeight(T->leftChild, height); 
		int rDepth = treeHeight(T->rightChild, height); 
		if (lDepth > rDepth)  
			return(lDepth+1); 
		else 
			return(rDepth+1); 
	} 
}

/*
 * copyTree()
 * create and return a complete memory independent copy of the tree
 *
 * Inputs:
 * 	BSTObj *T: the current node, which gets copied, and its children are then copied
 *
 * Outputs:
 * 	BSTObj *: returns the root of the copy of the tree
 */
BSTObj * copyTree(BSTObj *T){
	if(T == NULL)
		return T;
	BSTObj* temp = malloc(sizeof(BSTObj));
	temp->term = T->term;
	temp->leftChild = copyTree(T->leftChild);
	temp->rightChild  = copyTree(T->rightChild);
	return temp;
}

/*
 * makeEmpty()
 * remove all the nodes from the tree, deallocate space and reset Tree pointer
 *
 * Inputs:
 * 	BSTObj **pT: pointer to the pointer to node to be freed
 *
 * Outputs:
 * 	none
 */
void makeEmpty(BSTObj **pT){
	BSTObj *T = *pT;
	if(T != NULL){
		makeEmpty(&(T->leftChild));
		makeEmpty(&(T->rightChild));
		free(T->term);
		free(T);
	}
}
