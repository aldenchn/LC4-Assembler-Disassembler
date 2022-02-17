/************************************************************************/
/* File Name : lc4_disassembler.c 										*/
/* Purpose   : This file implements the reverse assembler 				*/
/*             for LC4 assembly.  It will be called by main()			*/
/*             															*/
/* Author(s) : tjf and you												*/
/************************************************************************/

#include <stdio.h>
#include "lc4_memory.h"
#include <string.h>
#include <stdlib.h>
// helper function to get subsets of the contents (bianry instructions) 
short unsigned int getRd(row_of_memory* node){
    short unsigned int Rd = (node->contents & 0b0000111000000000);
    return Rd >> 9 ; // shift to the right end, let Rd ends with 1, otherwise sprintf(%d,Rd) will be misiterpreted
}

short unsigned int getRs(row_of_memory* node){
    short unsigned int Rs = (node->contents & 0b0000000111000000);
    return Rs >> 6; // shift to the right end, let Rs ends with 1, otherwise sprintf(%d,Rs) will be misiterpreted
}

short unsigned int getRt(row_of_memory* node){
    short unsigned int Rt = (node->contents & 0b0000000000000111);
    return Rt;
}

short unsigned int getIMM(row_of_memory* node){
    short unsigned int IMM = (node->contents & 0b0000000000011111);
    return IMM;
}

short unsigned int getSubOpcode(row_of_memory* node){
    short unsigned int sub = (node->contents & 0b0000000000111000);
    return sub;
}

int reverse_assemble (row_of_memory* memory)
{
    row_of_memory *p = memory; // make a copy of the momory, list head, for find opcode 0001
    row_of_memory *p2 = memory; // make a copy of the momory, list head, for find pure label with contents as 0x0000
    row_of_memory* node_to_reverse = NULL;
    while (p != NULL){
        node_to_reverse = search_opcode(p, 0001);
        if (node_to_reverse == NULL){
            break; // break the while loop when all nodes with opcode 0001 have been reversed
        }
        // firstly get all subsets might be useful(in each case, either Rt or imm will be needed)
        short unsigned int sub = getSubOpcode(node_to_reverse);
        short unsigned int Rd = getRd(node_to_reverse);
        short unsigned int Rs = getRs(node_to_reverse);
        short unsigned int Rt = getRt(node_to_reverse);
        short unsigned int imm = getIMM(node_to_reverse);
        
        char assembly_string[50];// allocate space to store the string temperarily
        int num_char = 0; // allocate to store the # of characters read in the a *str
        // branches of operations based on sub-opcode

        switch(sub){
            case 0b0000000000000000://ADD REG
                //sprinf will add the trailing '\0' after the fotmatted string
                // returns the number of characters stored in the array s, 
                // not including the terminating null character, thus num_char plus 1
                num_char= sprintf(assembly_string,"ADD R%d R%d R%d", Rd, Rs, Rt) + 1;
                // now make heap space for assembly
                node_to_reverse->assembly = (char*) malloc(num_char);
                if(node_to_reverse->assembly == NULL){ // check malloc
                    printf("malloc for assembly error\n");
                    return -1;
                }
                strcpy(node_to_reverse->assembly, assembly_string);
                break; // once a case is executed, jump out of switch and back to while loop
            
            case 0b0000000000001000: //MUL
                num_char = sprintf(assembly_string,"MUL R%d R%d R%d", Rd, Rs, Rt) + 1;
                // now make heap space for assembly
                node_to_reverse->assembly = (char*) malloc(num_char);
                if(node_to_reverse->assembly == NULL){ // check malloc
                    printf("malloc for assembly error\n");
                    return -1;
                }
                strcpy(node_to_reverse->assembly, assembly_string);
                break;
           
            case 0b0000000000010000: // SUB
                num_char = sprintf(assembly_string,"SUB R%d R%d R%d", Rd, Rs, Rt) + 1;
                // now make heap space for assembly
                node_to_reverse->assembly = (char*) malloc(num_char);
                if(node_to_reverse->assembly == NULL){ // check malloc
                    printf("malloc for assembly error\n");
                    return -1;
                }
                strcpy(node_to_reverse->assembly, assembly_string);
                break;
                
            case 0b0000000000011000://DIV
                num_char = sprintf(assembly_string,"DIV R%d R%d R%d", Rd, Rs, Rt) + 1;
                // now make heap space for assembly
                node_to_reverse->assembly = (char*) malloc(num_char);
                if(node_to_reverse->assembly == NULL){ // check malloc
                    printf("malloc for assembly error\n");
                    return -1;
                }
                strcpy(node_to_reverse->assembly, assembly_string);
                break;
                
            default :// ADD IMM
                if (imm <= 15){ // assume the 5 bits imm is signed, <= 15 indicats it's a positive number
                    num_char = sprintf(assembly_string,"ADD R%d R%d #%d", Rd, Rs, imm) + 1;
                    // now make heap space for assembly
                    node_to_reverse->assembly = (char*) malloc(num_char );
                    if(node_to_reverse->assembly == NULL){ // check malloc
                        printf("malloc for assembly error\n");
                        return -1;
                    }
                    strcpy(node_to_reverse->assembly, assembly_string);
                    break;
                } else { // the imm is a negative number
                    imm = (imm ^ 0b0000000000011111) + 0b1; // flip the bits and add 1, get positive counterpart
                    num_char = sprintf(assembly_string,"ADD R%d R%d #-%d", Rd, Rs, imm) + 1;
                    // now make heap space for assembly
                    node_to_reverse->assembly = (char*) malloc(num_char);
                    if(node_to_reverse->assembly == NULL){ // check malloc
                        printf("malloc for assembly error\n");
                        return -1;
                    }
                    strcpy(node_to_reverse->assembly, assembly_string);
                    break;
                    
                }   
        }
    }
    // if there is pure label node with contents as 0x0000, set assembly to NOP
	// according to piazza requirement update
    short unsigned int labelContents;
    int num_char_label;
    char assembly_string_label[50];
    while (p2 != NULL){
        labelContents = p2->contents;
        if (labelContents == 0){
            num_char_label = sprintf(assembly_string_label,"NOP") + 1;
            p2-> assembly = malloc(num_char_label);
            if (p2->assembly == NULL){     // check for malloc return
                printf("malloc for assembly error\n");
                return -1;
            }
            strcpy(p2->assembly, assembly_string_label);
        }
        p2 = p2->next;
    }
	return 0 ;
}
