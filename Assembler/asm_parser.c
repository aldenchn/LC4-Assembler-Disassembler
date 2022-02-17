/***************************************************************************
 * file name   : asm_parser.c                                              *
 * author      : tjf & you                                                 *
 * description : the functions are declared in asm_parser.h                *
 *               The intention of this library is to parse a .ASM file     *
 *			        										               * 
 *                                                                         *
 ***************************************************************************
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "asm_parser.h"

/* to do - implement all the functions in asm_parser.h */

int read_asm_file (char* filename, char program [ROWS][COLS] ){
  int line_index = 0;
  int letter_index  = 0;
  char line[COLS];
  
  FILE* src_file = fopen(filename, "r"); // open the file
  if (src_file == NULL) {
    printf("error2: read_asm_file() failed\n");
    return 2; // test if the is valid 
  }
  
  // read the file line by line
  while (fgets (line, COLS, src_file)) {
    letter_index = 0; // read success, return a pointer to the string
     // iterate each character until hits new line character or comment symbol ";" (EC Q1) 
    while(line[letter_index] != '\n' && line[letter_index] != ';'){ 
      program[line_index][letter_index] = line[letter_index];
      letter_index++;
    }
    line_index ++; // increase the rows by 1 each time finish reading a row
  }
  
  if (feof(src_file)) { 
    // successfully read the entire file
    fclose(src_file);
    return 0;
  } else { // error ecountered
    printf("error2: read_asm_file() failed\n");
    fclose(src_file);
    return 2;
  }   
}


int parse_instruction (char* instr, char* instr_bin_str){
  char *token;
  char *firsttoken;
  char delimiter[2] = ", "; // delimters: space and comma
  char add[5];
  char mul[5];
  char div[5];
  char sub[5];
  char xor[5];
  char and[5];
  char or[5];
  int result;
  
  strcpy(add,"ADD");
  strcpy(mul,"MUL");
  strcpy(div,"DIV");
  strcpy(sub,"SUB");
  strcpy(xor,"XOR");
  strcpy(and,"AND");
  strcpy(or,"OR");
    
  token  = strtok(instr,delimiter);
  firsttoken = token;
//   printf("%s\n",firsttoken);
  if (strcmp(firsttoken,add)==0){  // decide which parse method to use based on firsttoken
    result = parse_add(token, instr_bin_str);
  } else if (strcmp(firsttoken,mul)==0){
    result = parse_mul(token, instr_bin_str);
  } else if (strcmp(firsttoken,div)==0){
    result = parse_div(token, instr_bin_str);
  } else if (strcmp(firsttoken,sub)==0){
    result = parse_sub(token, instr_bin_str);
  } else if (strcmp(firsttoken,xor)==0){
    result = parse_xor(token, instr_bin_str);
  } else if (strcmp(firsttoken,and) == 0){
    result = parse_and(token, instr_bin_str);
  } else if (strcmp(firsttoken,or) == 0) {
    result = parse_or(token, instr_bin_str);
  } else {
    // if there are other operations, return 3
    printf("error3: parse_instruction() failed.\n");
    return 3;
  }
    // return 3 if any sub_parse function failed
  if (result != 0){
      printf("error3: parse_instruction() failed.\n");
      return 3;
  } 
  return 0;
}

int parse_add(char* instr,char* instr_bin_str){
  char *Rd;
  char *Rs;
  char *Rt;
  
  Rd = strtok(NULL,", ");
  Rs = strtok(NULL,", ");
  Rt = strtok(NULL,", ");
  
  //deal with add immediate, assume we only need to deal with 
  //immediate in decimal format like #32 
  if (Rt[0] == '#'){
    instr_bin_str[0] = '0';
    instr_bin_str[1] = '0';
    instr_bin_str[2] = '0';
    instr_bin_str[3] = '1';
    instr_bin_str[10] = '1'; // opcode for ADD IMM5
    
    if(Rd ==NULL || Rs == NULL ){
      printf("error4: parse_add() failed.\n");
      return 4;
    }
    if (parse_reg(Rd[1], instr_bin_str + 4) != 0){
      printf("error4: parse_add() failed.\n");
      return 4;
    }
    if (parse_reg(Rs[1], instr_bin_str + 7) != 0){
      printf("error4: parse_add() failed.\n");
      return 4;
    }
    if (parse_reg_immediate(Rt+1, instr_bin_str +11) != 0){
      printf("error4: parse_add() failed.\n");
      return 4;
    }
    return 0;
    
  } else { // deal with normal add operatin specifying 3 regiaters
    // fill in opcode adn sub-opcode
    
    instr_bin_str[0] = '0';
    instr_bin_str[1] = '0';
    instr_bin_str[2] = '0';
    instr_bin_str[3] = '1';
    instr_bin_str[10] = '0';
    instr_bin_str[11] = '0';
    instr_bin_str[12] = '0';

    if(Rd ==NULL || Rs == NULL ||Rt == NULL){
      printf("error4: parse_add() failed.\n");
      return 4;
    }
    if (parse_reg(Rd[1], instr_bin_str + 4) != 0){
      printf("error4: parse_add() failed.\n");
      return 4;
    }
    if (parse_reg(Rs[1], instr_bin_str + 7) != 0){
      printf("error4: parse_add() failed.\n");
      return 4;
    }
    if (parse_reg(Rt[1], instr_bin_str + 13) != 0) {
      printf("error4: parse_add() failed.\n");
      return 4;
    }
    return 0;
  }
  return 0;
}

int parse_mul(char* instr,char* instr_bin_str){
  char *Rd;
  char *Rs;
  char *Rt;
  // fill in opcode adn sub-opcode
  instr_bin_str[0] = '0';
  instr_bin_str[1] = '0';
  instr_bin_str[2] = '0';
  instr_bin_str[3] = '1';
  instr_bin_str[10] = '0';
  instr_bin_str[11] = '0';
  instr_bin_str[12] = '1';
 
  Rd = strtok(NULL,", ");
  Rs = strtok(NULL,", ");
  Rt = strtok(NULL,", ");

  if(Rd ==NULL || Rs == NULL ||Rt == NULL){
    printf("error4: parse_mul() failed.\n");
    return 4;
  }

  if (parse_reg(Rd[1], instr_bin_str + 4) != 0){
    printf("error4: parse_mul() failed.\n");
    return 4;
  };
  if (parse_reg(Rs[1], instr_bin_str + 7) != 0){
    printf("error4: parse_mul() failed.\n");
    return 4;
  };
  if (parse_reg(Rt[1], instr_bin_str + 13) != 0) {
    printf("error4: parse_mul() failed.\n");
    return 4;
  };
  return 0;
}

int parse_div(char* instr,char* instr_bin_str){
  char *Rd;
  char *Rs;
  char *Rt;

  // fill in opcode adn sub-opcode
  instr_bin_str[0] = '0';
  instr_bin_str[1] = '0';
  instr_bin_str[2] = '0';
  instr_bin_str[3] = '1';
  instr_bin_str[10] = '0';
  instr_bin_str[11] = '1';
  instr_bin_str[12] = '1';
 
  Rd = strtok(NULL,", ");
  Rs = strtok(NULL,", ");
  Rt = strtok(NULL,", ");

  if(Rd ==NULL || Rs == NULL ||Rt == NULL){
    printf("error4: parse_div() failed.\n");
    return 4;
  }

  if (parse_reg(Rd[1], instr_bin_str + 4) != 0){
    printf("error4: parse_div() failed.\n");
    return 4;
  };
  if (parse_reg(Rs[1], instr_bin_str + 7) != 0){
    printf("error4: parse_div() failed.\n");
    return 4;
  };
  if (parse_reg(Rt[1], instr_bin_str + 13) != 0) {
    printf("error4: parse_div() failed.\n");
    return 4;
  };
  return 0;
}

int parse_sub(char* instr,char* instr_bin_str){
  char *Rd;
  char *Rs;
  char *Rt;

  // fill in opcode adn sub-opcode
  instr_bin_str[0] = '0';
  instr_bin_str[1] = '0';
  instr_bin_str[2] = '0';
  instr_bin_str[3] = '1';
  instr_bin_str[10] = '0';
  instr_bin_str[11] = '1';
  instr_bin_str[12] = '0';
 
  Rd = strtok(NULL,", ");
  Rs = strtok(NULL,", ");
  Rt = strtok(NULL,", ");

  if(Rd ==NULL || Rs == NULL || Rt == NULL){
    printf("error4: parse_sub() failed.\n");
    return 4;
  }

  if (parse_reg(Rd[1], instr_bin_str + 4) != 0){
    printf("error4: parse_sub() failed.\n");
    return 4;
  };
  if (parse_reg(Rs[1], instr_bin_str + 7) != 0){
    printf("error4: parse_sub() failed.\n");
    return 4;
  };
  if (parse_reg(Rt[1], instr_bin_str + 13) != 0) {
    printf("error4: parse_sub() failed.\n");
    return 4;
  };
  return 0;
}

int parse_xor(char* instr,char* instr_bin_str){
  char *Rd;
  char *Rs;
  char *Rt;

  // fill in opcode adn sub-opcode
  instr_bin_str[0] = '0';
  instr_bin_str[1] = '1';
  instr_bin_str[2] = '0';
  instr_bin_str[3] = '1';
  instr_bin_str[10] = '0';
  instr_bin_str[11] = '1';
  instr_bin_str[12] = '1';
 
  Rd = strtok(NULL,", ");
  Rs = strtok(NULL,", ");
  Rt = strtok(NULL,", ");

  if(Rd ==NULL || Rs == NULL ||Rt == NULL){
    printf("error4: parse_xor() failed.\n");
    return 4;
  }

  if (parse_reg(Rd[1], instr_bin_str + 4) != 0){
    printf("error4: parse_xor() failed.\n");
    return 4;
  };
  if (parse_reg(Rs[1], instr_bin_str + 7) != 0){
    printf("error4: parse_xor() failed.\n");
    return 4;
  };
  if (parse_reg(Rt[1], instr_bin_str + 13) != 0) {
    printf("error4: parse_xor() failed.\n");
    return 4;
  };
  return 0;
}

int parse_and(char* instr,char* instr_bin_str){
  char *Rd;
  char *Rs;
  char *Rt;

  // fill in opcode adn sub-opcode
  instr_bin_str[0] = '0';
  instr_bin_str[1] = '1';
  instr_bin_str[2] = '0';
  instr_bin_str[3] = '1';
  instr_bin_str[10] = '0';
  instr_bin_str[11] = '0';
  instr_bin_str[12] = '0';
 
  Rd = strtok(NULL,", ");
  Rs = strtok(NULL,", ");
  Rt = strtok(NULL,", ");

  if(Rd ==NULL || Rs == NULL ||Rt == NULL){
    printf("error4: parse_and() failed.\n");
    return 4;
  }

  if (parse_reg(Rd[1], instr_bin_str + 4) != 0){
    printf("error4: parse_and() failed.\n");
    return 4;
  };
  if (parse_reg(Rs[1], instr_bin_str + 7) != 0){
    printf("error4: parse_and() failed.\n");
    return 4;
  };
  if (parse_reg(Rt[1], instr_bin_str + 13) != 0) {
    printf("error4: parse_and() failed.\n");
    return 4;
  };
  return 0;
}

int parse_or(char* instr,char* instr_bin_str){
  char *Rd;
  char *Rs;
  char *Rt;

  // fill in opcode adn sub-opcode
  instr_bin_str[0] = '0';
  instr_bin_str[1] = '1';
  instr_bin_str[2] = '0';
  instr_bin_str[3] = '1';
  instr_bin_str[10] = '0';
  instr_bin_str[11] = '1';
  instr_bin_str[12] = '0';
 
 
  Rd = strtok(NULL,", ");
  Rs = strtok(NULL,", ");
  Rt = strtok(NULL,", ");

  if(Rd ==NULL || Rs == NULL ||Rt == NULL){
    printf("error4: parse_or() failed.\n");
    return 4;
  }

  if (parse_reg(Rd[1], instr_bin_str + 4) != 0){
    printf("error4: parse_or() failed.\n");
    return 4;
  };
  if (parse_reg(Rs[1], instr_bin_str + 7) != 0){
    printf("error4: parse_or() failed.\n");
    return 4;
  };
  if (parse_reg(Rt[1], instr_bin_str + 13) != 0) {
    printf("error4: parse_or() failed.\n");
    return 4;
  };
  return 0;
}


int parse_reg (char reg_num, char* instr_bin_str) {
  switch(reg_num){
    case '0':
      instr_bin_str[0] = '0';
      instr_bin_str[1] = '0';
      instr_bin_str[2] = '0';
      break;
    case '1':
      instr_bin_str[0] = '0';
      instr_bin_str[1] = '0';
      instr_bin_str[2] = '1';
      break;
    case '2':
      instr_bin_str[0] = '0';
      instr_bin_str[1] = '1';
      instr_bin_str[2] = '0';
      break;
    case '3':
      instr_bin_str[0] = '0';
      instr_bin_str[1] = '1';
      instr_bin_str[2] = '1';
      break;
    case '4':
      instr_bin_str[0] = '1';
      instr_bin_str[1] = '0';
      instr_bin_str[2] = '0';
      break;
    case '5':
      instr_bin_str[0] = '1';
      instr_bin_str[1] = '0';
      instr_bin_str[2] = '1';
      break;
    case '6':
      instr_bin_str[0] = '1';
      instr_bin_str[1] = '1';
      instr_bin_str[2] = '0';
      break;
    case '7':
      instr_bin_str[0] = '1';
      instr_bin_str[1] = '1';
      instr_bin_str[2] = '1';
      break;
    default: // if the register number goes beyond 0-7, it's illegal
      printf("error5: parse_reg() failed.\n");
      return 5;
  }
  return 0;
}

int parse_reg_immediate (char* imme, char* instr_bin_str) {
  // assume the input immediate number are within valid range of 5 bits (signed) -16 -- 15
  unsigned short int res;
  int remainder;
  if (imme[0] != '-'){ // deal with non-negative number
    res = strtol(imme,NULL,10);
    if (res > 15){ // out of the valid immediate number range
      printf("error8: parse_reg_immediate() failed.\n");
      return 8;
    }
    int i = 4;// start from the end of instr_bin_str
    while (res != 0 && i >= 0){
      remainder = res % 2;
      if (remainder == 0){
        instr_bin_str[i] = '0';
      } else {
        instr_bin_str[i] = '1';
      }
      i--;
      res = res/2;
    }
    while (i >= 0){
    instr_bin_str[i] = '0';
    i--;
    }
    
    return 0;
  } else { // deal with negative number liek #-1
    res = strtol(imme+1,NULL,10);
    printf("%X",res);
    if (res > 16){
      printf("error8: parse_reg_immediate() failed.\n"); // out of valid nagetive number range
      return 8;
    }
    // convert it to binary and 2c complement
    char binary[5];
    char onesComp[5];
    char twosComp[5];
    int i = 4;
    while (res != 0 && i >= 0){
      remainder = res %2;
      if (remainder == 1){
        binary[i] = '1';
      } else {
        binary[i] ='0';
      }
      i--;
      res = res/2;
    }
    while (i >= 0){
    binary[i] = '0';
    i--;
    }
    
    for(int j = 0; j < 5; j++){
      if(binary[i] == '1'){
        onesComp[i] = '0';
      } else if(binary[i] == '0'){
        onesComp[i] = '1';
      }
    }
    
    int carry =1;
    int x;
    for(x=4; x>=0; x--) {
      if(onesComp[x] == '1' && carry == 1){
        twosComp[x] = '0';
      } else if(onesComp[x] == '0' && carry == 1){
        twosComp[x] = '1';
        carry = 0;
      } else {
        twosComp[x] = onesComp[x];
      }
    }
    
    for (i= 0; i <= 5; i++){
      instr_bin_str[i] = twosComp[i];
    }
    return 0;
  }
}
  

unsigned short int str_to_bin (char* instr_bin_str){
  unsigned short int ret; // 2 bytes
  ret = strtol(instr_bin_str,NULL,2); // 2 is the base of the number in the string
  if (ret == 0){
    printf("error6: str_to_bin() failed.\n");
    return 6;
  } 
  
  return ret;
}

int write_obj_file  (char* filename, unsigned short int program_bin[ROWS]){
  char *outputfilename = filename;
  FILE *file;
  int len = strlen(outputfilename);
  outputfilename[len-3] = 'o';
  outputfilename[len-2] = 'b';
  outputfilename[len-1] = 'j';
  file = fopen(outputfilename,"wb");
  // check file open
  if (file == NULL){
    printf("error7: cannot open output file.\n");
    return 7;
  }
  
  unsigned short int num = 0xDECA;
  unsigned short int add = 0x0000;
  unsigned short int n = 0; // to count row number
  
  unsigned short int first_part;
  unsigned short int sec_part;

  for (int j =0; j < ROWS; j++){
    if (program_bin[j] == '\0'){
      break;
    }
    // change to litte endian
    first_part = program_bin[j] & 0x00FF;
    sec_part = program_bin[j] & 0xFF00;
    first_part =  first_part << 8;
    sec_part = sec_part >>8;
    program_bin[j] = first_part | sec_part;
    n++;
  }
  
  int rows_count = n; // store n's value before conversion
  // convert n to little endian as well
  first_part = n & 0x00FF;
  sec_part = n & 0xFF00;
  first_part =  first_part << 8;
  sec_part = sec_part >> 8;
  n = first_part | sec_part;
  
  // write .CODE , address, number of rows to file
  if (fwrite (&num, sizeof(unsigned short int), 1, file) != 1) {
    printf("error7: fail to write to output file.\n");
    return 7;
  };
  if (fwrite (&add, sizeof(unsigned short int), 1, file) != 1) {
    printf("error7: fail to write to output file.\n");
    return 7;
  };
  if (fwrite (&n, sizeof(unsigned short int), 1, file) != 1) {
    printf("error7: fail to write to output file.\n");
    return 7;
  };

  for (int i = 0; i < rows_count ; i++){
    if (fwrite(&program_bin[i], sizeof(program_bin[i]), 1, file) != 1){
      printf("error7: fail to write to output file.\n");
      return 7;
    }
  }
  
  fclose(file);
  
  return 0;
}