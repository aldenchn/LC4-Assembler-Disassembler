/***************************************************************************
 * file name   : assembler.c                                               *
 * author      : tjf & you                                                 *
 * description : This program will assemble a .ASM file into a .OBJ file   *
 *               This program will use the "asm_parser" library to achieve *
 *			     its functionality.										   * 
 *                                                                         *
 ***************************************************************************
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "asm_parser.h"

int main(int argc, char** argv) {

	char* filename = NULL ;					// name of ASM file
	char  program [ROWS][COLS] ; 			// ASM file line-by-line
	char  program_bin_str [ROWS][17] ; 		// instructions converted to a binary string
	unsigned short int program_bin [ROWS] ; // instructions in binary (HEX)
  
  if (argc == 2){
    filename = argv[1];
  } else { // if there is no argument for a filename, print error message and return
    printf("error1: usage: ./assembler <assembly_file.asm>\n");
    return 1;
  }
  
  read_asm_file(filename,program);

// for testing read_asm_file, print out what we read line by line:
//   for (int i = 0; program[i][0] != '\0'; i++ ){
//          printf("%s\n", program[i]);
//   }
  
  for (int i = 0; program[i][0] != '\0'; i++){
     parse_instruction(program[i],program_bin_str[i]);
//      printf("%s\n",program_bin_str[i]);
     program_bin[i] = str_to_bin(program_bin_str[i]);
//      printf("0x%X\n",program_bin[i]); just for testing when writing str_to_bin() 

  }
  
  write_obj_file (filename, program_bin);
  
  return (0);


}
