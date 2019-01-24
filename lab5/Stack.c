#include <stdlib.h>
#include <stdio.h>
#include "Stack.h"

/*
 * *newStack()
 * creates a new stackObj, uses -1 as top index to show stack is empty
 *
 * Inputs:
 *      none
 *
 * Outputs:
 *      the newly created StackObj
 */
StackObj * newStack() {
	StackObj *S;
	S = (StackObj *) malloc ((size_t) sizeof(StackObj));
	S->top = -1;	//nothing in the stack
	return S;
}

/*
 * printStack()
 * prints all the elements of the stack, from the bottom to the top
 *
 * Inputs:
 * 	StackObj * S: pointer to the stack to be printed
 *
 * Outputs:
 * 	none
 */
void printStack (StackObj *S) {
	int i;
	printf("going to print stack contents %d element \n", S->top +1);
	for (i=0; i<= S->top; i++) {
		printf("stack index %d = %p\n", i, S->items[i]);
	}
}
/*
 * deleteStack()
 * sets the top of the stack to NULL, and frees the stack
 * 
 * Inputs:
 * 	StackObj * S: pointer to the stack whose top is set to -1 (NULL)
 *
 * Outputs:
 * 	none
 */
void deleteStack(StackObj * S) {
	S->top = -1;		// being neurotic
	free(S);
}
/*
 * stackSize()
 * returns the number of elements in the stack
 *
 * Inputs:
 * 	StackObj * S: pointer to the stack of which the size is returned
 *
 * Outputs:
 * 	returns the number of elements in the stack
 */
// return the number of elements in the stack
int stackSize( StackObj * S) {
	return (S->top + 1);
}
/*
 * *pop()
 * removes the top element of the stack
 *
 * Inputs:
 * 	StackObj * S: pointer to stack from which to remove the top element
 *
 * Outputs:
 * 	none
 */
void *pop(StackObj *S){
	if (S->top < 0 ) {  // out of stack items
		//printf("returning nothing, stack empty\n");
		return NULL;
	}
	else {
		//printf("pop returning node");
		return (S->items[S->top--]);
	}
}

/*
 * push()
 * adds an element to the top of the stack that refers to *ref
 *
 * Inputs:
 * 	StackObj * S: pointer to the stack
 * 	*ref: what is to be added to the top of the stack
 */
void push(StackObj *S,  void *ref){
	//printf("pushing token ");
	if (S->top <  MAX_STACK - 1) {  // out of stack items
		S->items[++(S->top)] = ref;
	}
	else {
		fprintf(stderr, "sorry out of stack space\n");
	}
}
