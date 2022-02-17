/************************************************************************/
/* File Name : lc4_loader.c		 										*/
/* Purpose   : This file implements the loader (ld) from PennSim		*/
/*             It will be called by main()								*/
/*             															*/
/* Author(s) : tjf and you												*/
/************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "lc4_memory.h"

/* declarations of functions that must defined in lc4_loader.c */

FILE* open_file(char* file_name)
{ 
    FILE* src_file = NULL;
    src_file = fopen(file_name,"rb");
    if (src_file != NULL){ // check if file opened without error
        return src_file;
    } else {
        return NULL ;
    }
}

int parse_file (FILE* my_obj_file, row_of_memory** memory)
{
    unsigned char header[2];
    unsigned char n[2];
    short unsigned int address;
    
    while (feof(my_obj_file) == 0 && fread(header, sizeof(char),2, my_obj_file) == 2 ){
//   if (fread(header, sizeof(char),2, my_obj_file) != 2) or file reaches end, break the loop
        
        fread(&address,2,1,my_obj_file); // since read 2 bytes together, has to manually convert to big endianess
        short unsigned int first_byte = address & 0xFF00;
        short unsigned int sec_byte = address & 0x00FF;
        address = (first_byte >> 8) | (sec_byte << 8);

        // all address and n and header requires to be in big Endianness 
        // read n below
        fread(n, 1, 2, my_obj_file); // n is now 0002, when read byte by byte, fread change to large endianess automatically
        // header comparison
        if ((header[0] == 0xCA && header[1] == 0xDE) || (header[0] == 0xDA && header[1] ==0xDA)){
            int counts = ((n[0] << 8) + n[1]); // convert to integer (16 bits)
            // read instructions
            for (int i = 0; i< counts; i++){
                short unsigned int oneContent;
                if (fread(&oneContent,2,1,my_obj_file) != 1){
                    printf("read content error\n");
                    return -1;
                }
                // convert to big endianess
                short unsigned int oneContent_first_byte = oneContent & 0xFF00;
                short unsigned int oneContent_second_byte = oneContent & 0x00FF; 
                oneContent = (oneContent_first_byte >> 8) | (oneContent_second_byte <<8);
                if (add_to_list(memory, address, oneContent)!=0){
                    printf("add_to_list error\n");
                    return -1;
                }
                address += 1; // increase the address by 1 to the next node
            }
        } else if (header[0] == 0xC3 && header[1] == 0xB7){
            int label_counts = ((n[0] << 8) + n[1]); // # of chars in a label
            char *label = (char*) malloc(label_counts + 1); // + 1: a extra space for '\0'
            if (label == NULL){ // check malloc
                printf("malloc for label error\n");
                return -1;
            }
            if (fread(label, 1, label_counts, my_obj_file) != label_counts){
                printf("label_read error\n");
                return -1;
            };
            label[label_counts] = '\0'; // end with null
            
            // search node needs labelling
            row_of_memory* node_to_label = search_address (*memory, address);
            if (node_to_label == NULL){ // there is no existant node to label, so add this node with the specified address to list
                if( add_to_list(memory, address, 0) != 0){
                    printf("add label node to list error\n");
                    return -1;
                }
                node_to_label = search_address(*memory, address); //  added to list, update node_to_label
            }
            node_to_label->label = label;
            }
        }
    
    // if at the end of file, close it and return 0 if no error occurs;
    if (fclose(my_obj_file) != 0){
        fprintf(stderr, "fclose_error\n");
        return -1;
        }
    return 0;
}

