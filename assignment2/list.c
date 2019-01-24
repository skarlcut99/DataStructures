// Name: Sukhveer Karlcut
// ID: skarlcut
// Class: 12B/M
// This file contains all the general methods to manipulate doubly linked lists such as creating a node, inserting a node, deleting a node, and emptying the list. 

#include <stdlib.h>
#include <stdio.h>
#include "list.h" 

/*
 * create_new_node
 * 	Allocates the space for a new node and initializes the value field. Returns a pointer the node or NULL if memory allocation failed
 *
 * Input:
 * 	int id: the value of the node to be created
 *
 * Output:
 * 	A pointer to the newly created node, or NULL if memory allocation fails
 */

NodeObj * create_new_node (int id)
{
	NodeObj* new_node;
	new_node = (NodeObj *) malloc (sizeof(NodeObj));
	new_node -> value = id;
	new_node -> prev = NULL;
	new_node -> next = NULL;
	return (new_node);
}

/*
 * insert
 * 	Inserts the node at the end of the list.
 *
 * Input:
 * 	NodeObj **list_head: pointer to the pointer to head of the list
 * 	NodeObj *to_be_inserted: pointer to the node to be inserted
 *
 * Output:
 * 	None
 */

void insert(NodeObj **list_head, NodeObj *to_be_inserted)
{
	if(list_head == NULL || to_be_inserted == NULL)
        {
                fprintf(stderr, "Invalid Input\n");
                return;
        }
	NodeObj *curr = *list_head;
	to_be_inserted -> next = NULL;
	if(*list_head == NULL)
	{
		to_be_inserted -> prev = NULL;
		*list_head = to_be_inserted;
		return;
	}
	else
	{
		while(curr -> next != NULL)
		{
			if(curr == to_be_inserted)
        		{
                		fprintf(stderr, "Inputted node already exists in list\n");
                		return;
        		}
			curr = curr -> next; 
		}
		if(curr == to_be_inserted)
                {
                        fprintf(stderr, "Inputted node already exists in list\n");
                        return;
                }
		curr -> next = to_be_inserted;
		to_be_inserted -> prev = curr;
		return;
	}
}

/*
 * ordered_insert
 * 	Inserts a node into the increasing value ordered linked list
 * 
 * Precondition:
 * 	The list is already sorted
 *
 * Input:
 * 	NodeObj **list_head: pointer to the pointer to head of the list
 * 	NodeObj *to_be_inserted: pointer to the node to be inserted
 *
 * Output:
 * 	None
 *
 * Side Effect:
 * 	The head of the list will be changed by list_head
 */
void ordered_insert(NodeObj **list_head, NodeObj *to_be_inserted)
{
	NodeObj *curr;
	if(list_head == NULL || to_be_inserted == NULL) //bad input check
	{
		fprintf(stderr, "Invalid input\n");
		return;
	}
	if(*list_head == NULL)
	{
		*list_head = to_be_inserted;
	}
	else if((*list_head) -> value >= to_be_inserted -> value)
	{
		to_be_inserted -> next = *list_head;
		to_be_inserted -> next -> prev = to_be_inserted;
		*list_head = to_be_inserted;
	}
	else
	{
		curr = *list_head;
		while(curr -> next != NULL && curr -> next -> value < to_be_inserted -> value)
		{
			curr = curr -> next;
		}
		to_be_inserted -> next = curr -> next;
		if(curr -> next != NULL)
		{
			to_be_inserted -> next -> prev = to_be_inserted;
		}
		curr -> next = to_be_inserted;
		to_be_inserted -> prev = curr;
	}
}

/*
 * delete_all
 * 	Removes all the nodes from the list and deallocates the memory allocated to the list.
 *
 * Input:
 * 	NodeObj *list_head: pointer to the head of the list
 *
 * Output:
 * 	None
 */
void delete_all(NodeObj *list_head)
{
	/* checks if it is an empty list*/
	if(list_head == NULL)
	{
		fprintf(stderr, "Invalid Input\n");
		return;
	}
	NodeObj *curr = NULL;
	curr = list_head;
	NodeObj *next = NULL;
	while(curr -> next != NULL)
	{
		next = curr -> next;
		next -> prev = NULL;
		free(curr);
		curr = next;
	}
	free(curr);
	curr = NULL;
}

/*
 * delete
 * 	Deleted the node from the list and set the list head to null if the resulting list is empty.
 * 
 * Input:
 * 	NodeObj **list_head: pointer to the pointer to head of the list
 * 	NodeObj *to_be_inserted: pointer to the node to be inserted
 *
 * Output:
 * 	None
 *
 */
void delete(NodeObj **list_head, NodeObj *to_be_deleted)
{
	if(list_head == NULL)
        {
                fprintf(stderr, "Invalid Input\n");
                return;
        }
	if(*list_head == NULL || to_be_deleted == NULL)
		return;
	if(*list_head == to_be_deleted)
		*list_head = to_be_deleted -> next;
	if(to_be_deleted -> next != NULL)
		to_be_deleted -> next -> prev = to_be_deleted -> prev;
	if(to_be_deleted -> prev != NULL)
		to_be_deleted -> prev -> next = to_be_deleted -> next;
	free(to_be_deleted);
	return;
}
