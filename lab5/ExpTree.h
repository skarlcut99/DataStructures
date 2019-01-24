//-----------------------------------------------------------------------------
// Sukhveer Karlcut
// ID: skarlcut
// Class: 12B/M
//
// ExpTree.h
// Header file for the ExpTree ADT
// Defines all methods in ExpTree.c
// 	Defines the enum tokenType, the stack object ExpT, and methods to traverse, evaluate, delete, and create new expression trees
//-----------------------------------------------------------------------------

#ifndef _EXPTREE_H_INCLUDE_
#define _EXPTREE_H_INCLUDE_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Stack.h"


#define MAX_INPUT_STR 80
#define MAX_TOKEN_LENGTH 80
#define MAX_OPERATOR_LENGTH 1

/*
 * Defines the enum tokenType, which is used to classify the inputted characters as operands or operators
 */
typedef enum {PLUS, MINUS, MUL, DIV, OPERAND, END} tokenType;

/*
 * Defines the StackObj ExpT
 */
typedef StackObj ExpT;

/*
 * Exported data type
 * Typedef for TNode
 */
typedef struct TNode{
	tokenType type;
	int value;
	struct TNode *leftOperand;
	struct TNode *rightOperand;
} TNode;

/*
 * expressionEval()
 * determines the value of an expression of an expression tree
 * should not be called with an empty tree
 */
int expressionEval( TNode *T);

/*
 * inorderTraverse()
 * traverses through the expression tree inorder and prints out the tree with parentheses
 */
void inorderTraverse(FILE *out, TNode  *T);

/*
 * outputExpression()
 * calls inorderTraverse() to print out the expression tree
 */
void outputExpressionTree(ExpT *T);

/*
 * inputExpressionTree()
 * reads in the values to be added into the expression tree
 * these values are inputted as a stack
 */
void inputExpressionTree(ExpT *T);

/*
 * deleteExpressionTree()
 * deletes each tree inside the stack
 */
void deleteExpressionTree(ExpT *T);

/*
 * *newExpressionTree()
 * creates a new expression tree
 */
ExpT *newExpressionTree();
#endif
