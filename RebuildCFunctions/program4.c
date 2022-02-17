/**************************************************************
 * file name   : program4.c                                   *
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
#define null ((char *)0)

int main () {
    char tokens[1000] = "I love CIT593";
    char s[2] = " ";
    char *token;
    printf("Print each token in '%s':\n", tokens);
    /* get the first token */
    token = my_strtok(tokens, s);
    while (token != null){
        printf( "%s\n", token );
        token = my_strtok(null, s);
    }
    
    return (0) ;
}
