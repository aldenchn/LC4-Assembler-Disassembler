/**************************************************************
 * file name   : program3.c                                   *
 * author      : tjf & you                                    *
 * description : this C-file tests the functions of the       *
 *               "my_string" library                          *
 *                                                            *
 *                                                            *
 **************************************************************
 *
 */

#include <stdio.h>
#include <string.h>
#include "my_string.h"

int main (int argc, char** argv) {
    
    printf ("# of arguments passed: %d\n", argc) ;
    
    for (int i=0; i< argc ; i++) {
        
        printf ( "argv[%d] = %s\n", i, argv[i] ) ;
}
    
    int int_arr[10];
    int int_arr_index = 0;
    char large_str[250];
    int large_str_index = 0;
    for (int i=0; i < argc; i++){
        if (sscanf(argv[i], "%d", int_arr + int_arr_index)){ // if matches an integer successfully, increade the index by 1
            int_arr_index++;
        } else {
            // store non-integer to large_str
            if (sprintf(large_str_index + large_str, "%s", argv[i])){
                large_str_index += my_strlen(argv[i]);// move the length of buffer/inputs
                sprintf(large_str + large_str_index, "%s", " "); // add space
                large_str_index++;
            }
            
        }
    }
    // print out integer arguments passed in
    puts("Integer arguments:");
    for (int j = 0; j< int_arr_index; j++){
        printf("%d\n", int_arr[j]);
    }
    
    char* final_large_str = large_str ; // may + 2 here if want to skip the first 2 places storing"./", but according to piazza post, including "./
    // is desired 
    // print out the large string
    puts("The large string:");
    printf("%s\n", final_large_str);
    return (0) ;
}
