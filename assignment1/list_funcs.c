//Sukhveer Karlcut
//skarlcut@ucsc.edu
//CMPS 12M
//Methods that create and manipulate a linked list of riders.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list.h"

/* create_new_rider
 *      Create a new rider node. Allocate space and initialize the values.
 *      No space is allocated for strings, the strings must be allocated by
 *      caller.
 *
 * inputs:
 *
 *      id              - The ID of the rider
 *      first_name      - first name string * (space allocated elsewhere)
 *      last_name       - last name string * (space allocated elsewhere)
 *      ave_rating      - overall average rating of this rider across all rides taken
 *
 *
 * return value:
 *      rider_st *      - a pointer to the new rider_st node created.
 */
rider_st* 
create_new_rider(id, first_name, last_name, ave_rating, distance)
	int id;
	char *first_name;
	char *last_name;
        double ave_rating;
	double distance;
{
	rider_st *new_rider_node;	
	new_rider_node = (rider_st *) malloc (sizeof(rider_st));

	/* we have space, now initalize with the field values passed into this function */
	new_rider_node->ID = id;
	new_rider_node->first_name = first_name;	/* string space was created elsewhere */
	new_rider_node->last_name = last_name;		/* string space was created elsewhere */
	new_rider_node->ave_rating = ave_rating;
	new_rider_node->distance = distance;
	new_rider_node->next = NULL;			/* set next ptr to NULL, end of list */

	return (new_rider_node);
}

/*
 *
 * insert
 *      Insert a node at the head of the list
 *
 * inputs:
 *
 *
 *	ptr_to_list_head 	- pointer to pointer of the list head (should be non-null)
 *	to_be_inserted  	- pointer to new node to be inserted (should be non-null)
 *      id              	- The ID of the rider
 *      first_name      	- first name string * (space allocated elsewhere)
 *      last_name       	- last name string * (space allocated elsewhere)
 *      ave_rating      	- overall average rating of this rider across all rides taken
 *
 * return value:
 *     none
 *
 * side effects:
 *	head of list will be modified via ptr_list_head 
 * 
 */
void 
front_insert(ptr_to_list_head, to_be_inserted)
	rider_st **ptr_to_list_head;
	rider_st *to_be_inserted;

{
	/* this should not happen but check anyway */
	if (ptr_to_list_head == NULL)
		return; 

	if (*ptr_to_list_head == NULL) {
		/* empty list, this node will be the only one in the list */
		*ptr_to_list_head = to_be_inserted;
		to_be_inserted->next = NULL; /* never hurts to be careful, set it yourself */
	}
	/* non_empty list */
	else { 
		/* insert at the head of the list, be lazy */
        	to_be_inserted->next = *ptr_to_list_head;
		*ptr_to_list_head = to_be_inserted;
       }
}


/*
 *
 * insert
 *      Insert a node at the _end_ of the list
 *
 * inputs:
 *
 *
 *	ptr_to_list_head 	- pointer to pointer of the list head (should be non-null)
 *	to_be_inserted  	- pointer to new node to be inserted (should be non-null)
 *      id              	- The ID of the rider
 *      first_name      	- first name string * (space allocated elsewhere)
 *      last_name       	- last name string * (space allocated elsewhere)
 *      ave_rating      	- overall average rating of this rider across all rides taken
 *
 * return value:
 *     none
 *
 * side effects:
 *	head of list will be modified via ptr_list_head 
 */
void 
end_insert(ptr_to_list_head, to_be_inserted)
	rider_st **ptr_to_list_head;
	rider_st *to_be_inserted;

{
	rider_st *ptr=NULL;

	/* should not be the case, but check anyway */
	if (ptr_to_list_head == NULL ) 
		return;			/* could be a warning message printf */

        if (*ptr_to_list_head == NULL) {
                /* empty list, this node will be the only one in the list */
                *ptr_to_list_head = to_be_inserted;
                to_be_inserted->next = NULL; /* never hurts to be careful, set it yourself */
        }
        /* non_empty list */
        else {
                ptr = *ptr_to_list_head;
                while ( ptr->next != NULL) {
                        ptr = ptr->next;
                }
                /* we are at the end of the list! */
                ptr->next = to_be_inserted;
       }


}

/*
 * ordered_insert
 * inserts the given node into the list based on the “distance” field ordering, least to greatest
 * inputs: 
 * 	rider_st **ptr_to_list_head
 * 	rider_st *to_be_inserted
 * outputs:
 * 	none
 *
 * Precondition: The list is already sorted when passed as a parameter
 */
void
ordered_insert(rider_st **ptr_to_list_head, rider_st *to_be_inserted)
{
	rider_st* current;
        if (ptr_to_list_head == NULL )
                return;

	if (*ptr_to_list_head == NULL || (*ptr_to_list_head)->distance >= to_be_inserted->distance)
	{
        	to_be_inserted->next = *ptr_to_list_head;
        	*ptr_to_list_head = to_be_inserted;
	}
	
	else {
		current = *ptr_to_list_head;
		while(current->next!= NULL && current->next->distance < to_be_inserted->distance)
                        current = current->next;
		to_be_inserted->next = current->next;
		current->next = to_be_inserted;
	}
}

/*
 * empty
 * removes all of the nodes in the list and deallocates the space
 * inputs:
 * 	rider_st *list_head
 * outputs:
 * 	none
 */
void
empty(rider_st *list_head)
{
	rider_st *current = list_head; 
	rider_st *next; 
	while (current != NULL) 
	{ 
		next = current->next; 
		free(current); 
		current = next; 
	} 
	list_head = NULL;
}

/*
 * delete
 * removes the given node from the list and deallocates the space
 * inputs:
 * 	rider_st **ptr_to_list_head
 * 	rider_st *to_be_deleted
 * outputs:
 * 	none
 */
void 
delete(rider_st **ptr_to_list_head, rider_st *to_be_deleted)
{
	rider_st *ptr = NULL;
        rider_st *pointer;
        if(ptr_to_list_head == NULL)
                return;
        if(*ptr_to_list_head == NULL || to_be_deleted == NULL)
                return;
        else{
                ptr = *ptr_to_list_head;
                if(ptr == to_be_deleted){
                        pointer = ptr->next;
                        free(ptr);
                        *ptr_to_list_head = pointer;
                }
                else{
                        while(ptr->next != NULL && to_be_deleted != ptr->next)
                                ptr = ptr->next;
                        pointer = ptr->next;
                        free(ptr->next);
                        if(pointer->next != NULL)
                                ptr->next = pointer->next;

                        else
                                ptr->next = NULL;
                }
        }
}

/*
 * find_next_distance_rider
 * returns the node that has the next greater distance value than the min_distance value passed
 * 
 * inputs:
 * 	rider_st *list_head
 * 	double min_distance
 * outputs:
 * 	rider_st, which has to be freed in main or there will be a memory leak
 */
rider_st
find_next_distance_rider( rider_st *list_head, double min_distance)
{
	rider_st *ptr = list_head;
	double max = -1;
	if(list_head == NULL)
	{
		ptr = create_new_rider(-1, "Invalid", "Invalid", -1, -1);
		return *ptr;
	}
	while(ptr != NULL)
	{
		if((ptr->distance > min_distance && max == -1) || (ptr->distance < max && ptr->distance >= min_distance))
			max = ptr->distance;
		ptr = ptr->next;
	}
	ptr = list_head;
	while(ptr != NULL && max != ptr->distance)
		ptr = ptr->next;
	if(ptr == NULL)
		ptr = create_new_rider(-1, "Invalid", "Invalid", -1, -1);
	return *ptr;
}
