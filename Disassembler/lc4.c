/************************************************************************/
/* File Name : lc4.c 													*/
/* Purpose   : This file contains the main() for this project			*/
/*             main() will call the loader and disassembler functions	*/
/*             															*/
/* Author(s) : tjf and you												*/
/************************************************************************/

#include <stdio.h>
#include "lc4_memory.h"
#include "lc4_loader.h"
#include "lc4_disassembler.h"

/* program to mimic pennsim loader and disassemble object files */

int main (int argc, char** argv) {

	/**
	 * main() holds the linked list &
	 * only calls functions in other files
	 */

	/* step 1: create head pointer to linked list: memory 	*/
	row_of_memory* memory = NULL ;
    row_of_memory** memory_ptr = &memory; // a pointer to pointer memory

	/* step 2: determine filename, then open it		*/
	/*   TODO: extract filename from argv, pass it to open_file() */
    char *filename;
    FILE *file_to_parse; // intialize variable of filename and returned *file type from open_file() 
    if (argc == 2){
        filename = argv[1];
    } else { // if no file is specified, print error
        printf("error1: usage: ./lc4 <object_file.obj>\n");
        return 1;
    }
    file_to_parse = open_file(filename); // if fail to open file, print error
    if (file_to_parse == NULL){
        printf("error1: usage: ./lc4 <object_file.obj>\n");
        return 1;
    }

	/* step 3: call function: parse_file() in lc4_loader.c 	*/
	/*   TODO: call function & check for errors		*/
	if (parse_file (file_to_parse, memory_ptr) != 0){
        printf("parse_file error\n");
        return 1;
    };
    

	/* step 4: call function: reverse_assemble() in lc4_disassembler.c */
	/*   TODO: call function & check for errors		*/
    if (reverse_assemble(memory) != 0){
        printf("reverse_assemble error\n");
        return 1;
    };

	/* step 5: call function: print_list() in lc4_memory.c 	*/
	/*   TODO: call function 				*/
    print_list(memory);

	/* step 6: call function: delete_list() in lc4_memory.c */
	/*   TODO: call function & check for errors		*/
    if (delete_list (memory_ptr) != 0){
        printf("delete_list error\n");
        return 1;
    }
    
	/* only return 0 if everything works properly */
	return 0 ;
}
