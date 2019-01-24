//-----------------------------------------------------------------------------
// Stack.h
// Header file for the Stack ADT
// Array implmentation with stack size limitation
// Array of points to arbitrary structures, users will have to cast the pointer
// to set pointer type and keep track of their own logical use of pointers
//
//-----------------------------------------------------------------------------
#ifndef _STACK_H_INCLUDE_
#define _STACK_H_INCLUDE_

#define MAX_STACK 100

/*
 * Typedef for StackObj
 * Exported reference type
 */
typedef struct StackObj {
	void *items[MAX_STACK];
	int  top;
} StackObj;

/*
 * *newStack()
 * creates a new stckObj, and uses -1 as top index to show the stack is empty
 */
StackObj 	*newStack();

/*
 * deleteStack()
 * sets the top of the stack to NULL, and frees the stack
 */
void 		deleteStack(StackObj * S);

/*
 * stackSize()
 * returns the number of elements in the stack
 */
int 		stackSize( StackObj * S);

/*
 * *pop()
 * removes the top element of the stack
 */
void 		*pop(StackObj *S);

/*
 * push()
 * adds an element to the top of the stack that refers to *ref
 */
void 		push(StackObj *S,  void *ref);

/*
 * printStack()
 * prints all the elements of the stack, from the bottom to the top
 */
void		printStack(StackObj *S);
#endif
