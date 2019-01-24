#include "ExpTree.h"
/*
 * Name: Sukhveer Karlcut
 * ID: skarlcut
 * Class: 12B/M
 * 
 * This file contains methods to traverse, evaluate, delete, and create new expression trees
 *
 * Read input string with contains a post-fix expression and buid the corresponding expression evaluation
 *
 * handles input of one post-fix expression of integers n read from stdin. Examples:
 *   a b c + +    a b - c +   where a,b,c are integers
 * ignores all white space and uses C's sscanf to find acceptable integer formats. Input can flow over
 * multiple lines and is terminated with EOF. 
 *
 * This program only handles regular ints on your machine. So if you input very long int values they will be either
 * truncated or wrap around due to overflow, depening on what sscanf does will integer conversion from too long
 * string values.
 * 
 * Does not handle overflow in general, so if you have a resulting expression too large for an int, an overflow
 * generate unexpected results. 
 *
 */

/*
 * convertToken()
 * reads in the characters and determines what type of token (operator or operand) is in tokenStr
 */
tokenType convertToken( char *tokenStr, int *tokenVal);

/*
 * newTNode()
 * This method creates a new node to be inserted into the expression tree using the inputted values for inputTokena and tokenVal
 * This method is called with the previous two nodes in the stack. 
 * If the node to be created is an operand, the node is a leaf and is added to the bottom of the tree
 * If the node to be created is an operator, the node becomes the root of the tree with the previous two nodes in the stack as its children
 */
TNode * newTNode(tokenType inputToken, int tokenVal, TNode *op1, TNode *op2);

/*
 * tokenToStr()
 * returns the mathematical operator for the inputted token type
 */
const char *tokenToStr(tokenType tokenT);

/*
 * printNode()
 * prints the information about the inputted node
 */
void printNode( TNode * node);

/*
 * *newExpressionTree()
 * creates a new expression tree
 *
 * Inputs:
 * 	none
 *
 * Outputs:
 * 	returns the newly created expression tree
 */
ExpT * newExpressionTree() {
	StackObj *S;
	S = newStack();
	return S;
}

/*
 * deleteTree()
 * deletes a tree and frees each node
 *
 * Inputs:
 * 	TNode *T: the current node
 *
 * Outputs:
 * 	none
 */
void deleteTree(TNode *T) {
	if (T != NULL){ 
		T->value = 0;	// neurotic
		deleteTree(T->leftOperand);
		deleteTree(T->rightOperand);
		free(T);
	}
}

/*
 * deleteExpressionTree()
 * deletes each tree inside the stack
 *
 * Inputs:
 * 	ExpT *T: the stack of trees to be deleted
 *
 * Outputs:
 * 	none
 */
void deleteExpressionTree(ExpT *T) {
	TNode *node;
	StackObj *S = T;

	while ((node = (TNode *) pop(S)) != NULL){ 
		deleteTree(node);
	}
	deleteStack(S);
}

/*
 * printNode()
 * prints the information about the inputted node
 *
 * Inputs:
 * 	TNode * node: node whose information is to be printed
 *
 * Outputs:
 * 	none
 */
void printNode( TNode * node) {
	printf(" node addr = %p, type = %d, value = %d, leftOp = %p, rightOp = %p\n", node, node->type, 
			node->value, node->leftOperand, node->rightOperand);
}

/*
 * convertToken()
 * reads in the characters and determines what type of token (operator or operand) is in tokenStr
 *
 * Inputs:
 * 	char *tokenStr: the character for which the token is to be determined
 * 	int *tokenVal: contains the value of the token
 *
 * Outputs:
 * 	returns the token type of tokenStr
 * 		can be OPERAND, PLUS, MINUS, MUL, DIV, or END
 */
tokenType convertToken( char *tokenStr, int *tokenVal) {

	tokenType retVal;
	char      junkChars[MAX_TOKEN_LENGTH];
	int	      scanCount;

	// check what the token string might be
	scanCount = sscanf (tokenStr, "%d%s", tokenVal, junkChars);

	if (scanCount == 1) {
		//printf("token is an integer,str is %s, value = %d\n", tokenStr, *tokenVal);
		return OPERAND;
	}
	if (scanCount == 2) {  // check no trailing characters
		fprintf(stderr, "ERROR, unaccceptable format, had some extra characters in the integer %d\n", *tokenVal);
		exit(EXIT_FAILURE);
	}

	if (scanCount > 2 ) {
		fprintf(stderr, "something weird in input parsing, exiting with str = %s\n", tokenStr);
		exit(EXIT_FAILURE);
	}
	// maybe an operator, try and check the format
	else { 
		if (strlen(tokenStr) > MAX_OPERATOR_LENGTH) {
			printf("sorry, can't handle operators longer than 1 character\n");
			return END;
		}
		switch (tokenStr[0]) {
			case '+':
			retVal = PLUS;
			break;
			case '-': 
			retVal = MINUS; 
			break;
			case '*':
			retVal = MUL;
			break;
			case '/':
			retVal = DIV;
			break;
				default: 
			fprintf(stderr, "sorry, don't recognize this operator %c\n", tokenStr[0]);
				exit(EXIT_FAILURE);
		}
		//printf("got operator = %d\n", retVal);
		return retVal;
	}
}

/*
 * newTNode()
 * This method creates a new node to be inserted into the expression tree using the inputted values for inputTokena and tokenVal
 * This method is called with the previous two nodes in the stack. 
 * If the node to be created is an operand, the node is a leaf and is added to the bottom of the tree
 * If the node to be created is an operator, the node becomes the root of the tree with the previous two nodes in the stack as its children
 *
 * Inputs:
 * 	tokenType inputToken: the token type for the node to be created
 * 	int tokenVal: if the node to be created is for an operand , this is the number for the node to store
 * 	TNode *op1: set as the left child if the inputted token is an operand
 * 	TNode *op2: set as the right child if the inputted token is an operand
 *
 * Outputs:
 * 	return the newly created node
 */
TNode * newTNode(tokenType inputToken, int tokenVal, TNode *op1, TNode *op2)  {

	TNode *node;

	node = (TNode *) malloc ((size_t)(sizeof(TNode)));
	node->type = inputToken;
	if (inputToken == OPERAND ) { // this will be a leaf
		node->value = tokenVal;
		node->leftOperand = NULL;
		node->rightOperand = NULL;
	}
	else { // this will be an internal node 
		node->leftOperand = op1;
		node->rightOperand = op2;
	}
	//printf("tree node created\n");
	//printNode(node);
	return node;
}

/*
 * tokenToStr()
 * returns the mathematical operator for the inputted token type
 *
 * Inputs:
 * 	tokenType tokenT: the token for which the mathematical operator is to be determined
 *
 * Outputs:
 * 	the element of the constant char* which applies to the inputted token
 */
const char * tokenToStr(tokenType tokenT) {
	const static char *tokenChars[] = {"+", "-", "*",  "/", "^D"};
	return tokenChars[tokenT];
}

/*
 * expressionEval()
 * determines the value of an expression of an expression tree
 * should not be called with an empty tree
 * Error when divide by 0: error warning printed to stderr, 0 returned
 *
 * Inputs:
 * 	TNode *T: the node at which to evaluate the expression, called recursively if T holds an operator
 *
 * Outputs:
 * 	returns the value of the expression
 */
int expressionEval(TNode *T) {
	if(T==NULL){
                printf("ERROR: tree doesn't exist");
		return 0;
	}
	if(T->type == OPERAND && T->leftOperand == NULL &&T->rightOperand == NULL)
		return T->value;
	else if(T->type == PLUS)
		return expressionEval(T->leftOperand) + expressionEval(T->rightOperand);
	else if(T->type == MINUS)
		return expressionEval(T->leftOperand) - expressionEval(T->rightOperand);
	else if(T->type == MUL)
		return (expressionEval(T->leftOperand) * expressionEval(T->rightOperand));
	else if(T->type == DIV){
		if((T->rightOperand)->value == 0 || expressionEval(T->rightOperand) == 0){
			fprintf(stderr, "ERROR: Cannot divide by 0, answer will not be correct");
			return 0;
		}
		else
			return (expressionEval(T->leftOperand) / expressionEval(T->rightOperand));
	}
	return 0;
}

/*
 * inorderTraverse()
 * traverses through the expression tree inorder and prints out the tree with parentheses
 *
 * Inputs:
 * 	File *out: pointer to the file where the output is printed
 * 	TNode *T: the starting node, printing the left child, then the node, and finally the right child, inside parentheses
 *
 * Outputs:
 * 	none
 */
void inorderTraverse(FILE *out, TNode  *T) {
	if(out == NULL)
		fprintf(out, "ERROR: Output file doesn't exist");
	if(T==NULL)
		fprintf(out, "ERROR: tree doesn't exist");
	if(T->type == OPERAND)
		fprintf(out, "(%d)", T->value);
	else{
		fprintf(out, "(");
		inorderTraverse(out, T->leftOperand);
		fprintf(out, "%s", tokenToStr(T->type));
		inorderTraverse(out, T->rightOperand);
		fprintf(out, ")");
	}
}

/*
 * outputExpression()
 * calls inorderTraverse() to print out the expression tree
 *
 * Inputs:
 * 	ExpT *T: the stack to be printed through an inorder tree traversal
 *
 * Outputs:
 * 	none
 */
void outputExpressionTree(ExpT *T){
	TNode *node;
	StackObj *S = T;
	// check if the expression tree is correct for evaluation
	// check overflow or underflow of operands
	if (stackSize(S) > 1 ) {
		fprintf (stderr, "ERROR extra operands in expression\n");
	}
	else {
		node = (TNode *) pop(S);	// pop off the node to get access to it
		inorderTraverse(stdout, node);
		printf(" = %d\n", expressionEval(node));
		push(S, node);		// push the node back on so the stack retains the tree for deletion
	}
}

/*
 * inputExpressionTree()
 * reads in the values to be added into the expression tree
 * these values are inputted as a stack
 *
 * Inputs:
 * 	ExpT *T: the current stack, all inputted characters are added to this stack
 *
 * Outputs:
 * 	none
 */
void inputExpressionTree(ExpT *T){
	char  inputToken[MAX_TOKEN_LENGTH + 1];
	tokenType token;
	TNode  *node, *op1, *op2;
	int   tokenVal;
	StackObj *S;

	S = T;
	while (scanf( "%s", inputToken) > 0) {
		//printf("input token = %s\n", inputToken);
		token = convertToken (inputToken, &tokenVal);
		//printf( "converted token %d \n", token);
		if (token == OPERAND ) {
			if ((node = newTNode(OPERAND, tokenVal, NULL, NULL)) == NULL) 
				fprintf(stderr, "problem creating node\n");
			else
				push(S, (void *)node);
		}
		else {
			if ((op2 = pop(S)) == NULL) {
				fprintf(stderr, "sorry, out of operands for operators\n");
				exit(EXIT_FAILURE);
			}
			if ((op1 = pop(S)) == NULL) {
				fprintf(stderr, "sorry, out of operands for operator\n");
				exit(EXIT_FAILURE);
			}
			node = newTNode(token, 0, op1, op2);
			push(S, node);
		}
	}
}
