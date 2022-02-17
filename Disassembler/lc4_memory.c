/************************************************************************/
/* File Name : lc4_memory.c		 										*/
/* Purpose   : This file implements the linked_list helper functions	*/
/* 			   to manage the LC4 memory									*/
/*             															*/
/* Author(s) : tjf and you												*/
/************************************************************************/

#include <stdio.h>
#include "lc4_memory.h"
#include <stdlib.h>

/*
 * adds a new node to linked list pointed to by head - should keep list in order by address
 */
int add_to_list (row_of_memory** head,
		 short unsigned int address,
		 short unsigned int contents)
{
	/* allocate memory for a single node */
    row_of_memory* new_node = malloc( sizeof(row_of_memory) );
    if (new_node == NULL){ //if malloc fails, return -1;
        printf("create new_node in heap failed\n");
        return -1;
    }
	/* populate fields in newly allocated node w/ address&contents */
    new_node -> address = address;
    new_node -> contents = contents;
    new_node -> label = NULL;
    new_node -> assembly = NULL;
    new_node -> next = NULL;
	/* if head==NULL, node created is the new head of the list! */
    if (*head == NULL){
        *head = new_node;
        return 0;
    }
	/* otherwise, traverse linked list until you reach an address before the address passed in */
    row_of_memory* temp1 = NULL;
    row_of_memory* temp2 = *head;// start address of the first node
    
    // if the new node has a smaller address than the start node, update the new node to be the first node
    if (temp2->address > new_node->address){
        *head = new_node;
        new_node->next = temp2;
        return 0;
    }
    
    while(temp2->next != NULL && temp2->next->address <= address){
        temp2 = temp2->next;
        if (temp2->address == address){ // if there is already a node of the same address update the content 
            temp2->contents = contents;
            return 0;
        }
    }
    /* insert node into the list - perform necessary "surgery" on this list */
    // reaching this line means temp2 is the node we need to append the new node after
    //    temp2 = temp1->next;
    temp1 = temp2->next;
    temp2->next = new_node;
    new_node->next = temp1;
	/* return 0 for success, -1 if malloc fails */
	return 0 ;
}


/*
 * search linked list by address field, returns node if found
 */
row_of_memory* search_address (row_of_memory* head,
			       short unsigned int address )
{
	/* traverse linked list, searching each node for "address"  */
    row_of_memory *ptr_head = head; // make a copy of head
    while((ptr_head->address != address) && (ptr_head->next != NULL)){
        ptr_head = ptr_head->next;
    }
	/* return pointer to node in the list if item is found */
    if ((ptr_head->address) == address){
        return ptr_head;
    }
	/* return NULL if list is empty or if "address" isn't found */
	return NULL ;
}

/*
 * search linked list by opcode field, returns node if found
 */
row_of_memory* search_opcode  (row_of_memory* head,
				      short unsigned int opcode  )
{
	/* traverse linked list until node is found with matching opcode
	   AND "assembly" field of node is empty */
    row_of_memory *p = head; // make a copy of the head
    while(p-> next != NULL){
        short unsigned int oc = p->contents;
        // shift to get the most significant 4 bits
        if ((oc >> 12) == opcode && p->assembly == NULL) {
            return p;
        }
        p = p->next;
    }/* return pointer to node in the list if item is found */
	/* return NULL if list is empty or if no matching nodes */
	return NULL ; // if head itself is NULL, it won't enter the while loop
    // reaching here means either it is empty or there is no matching node found
}


void print_list (row_of_memory* head )
{
	/* make sure head isn't NULL */
    row_of_memory *p = head; // make a copy of head for print_list
    
    if (head == NULL){
        printf("Print_list error, the head is NULL\n");
        return;
    }
    /* print out a header */                       
    printf("The followings are details of the list:\n");
    printf("%-16s %-16s %-16s %-16s\n", "<label>", "<address>", "<contents>", "<assembly>");
    // left align, take at least 16 spaces

	/* traverse linked list, print contents of each node */
    while (p != NULL){ 
        // leave enough spaces beteewn different columns since we use %04X to specify padding
        // thus cannot use 0x%-16X to control spacing
        printf("%-16s %04X             %04X             %-16s\n", p->label, p->address, p->contents, p->assembly);
        p = p->next;
    }
	return ;
}


/*
 * delete entire linked list
 */
int delete_list  (row_of_memory** head )
{
	/* delete entire list node by node */
    if (*head == NULL){
        printf("The list to delete is already cleaned\n");
        return -1;
    }
    row_of_memory *p = *head; // make a copy of the address head points to 
    while(p != NULL){
        row_of_memory *node_to_free =p;
        p = p->next;// p jump to the next so not affect freeing node_to_free
        if (node_to_free-> label != NULL){
            free(node_to_free->label);
        }
        if (node_to_free-> assembly != NULL){
            free( node_to_free->assembly);
        }
        free(node_to_free);
    }
	/* if no errors, set head = NULL upon deletion */
    *head = NULL;
	/* return 0 if no error, -1 for any errors that may arise */
	return 0 ;
}


