/**************************************************************
 * file name   : program2.c                                   *
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

int main() {

	// a string we will test with
	char my_string_test [100] = "CIT593" ;

	// test of my_strrev() function
    my_strrev(my_string_test);
    printf("Content in 'CIT593' after reversion: %s\n", my_string_test);
    
    // test with my_strccase() 
    char case_test [10] = "Tom";
    my_strccase(case_test);
    printf("Content in 'Tom' after case conversion is: %s\n", case_test);
	
    // test with my_strccase() 
    char case_test2 [10] = "Age21";
    my_strccase(case_test2);
    printf("Content in 'Age21' after case conversion is: %s\n", case_test2);
    return (0) ;

}
