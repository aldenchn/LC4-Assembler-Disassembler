/**************************************************************
 * file name   : program1.c                                   *
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
	char my_string [100] = "Tom" ;

	// test of strlen() functions 
	printf ("Sample string: \"%s\" \n", my_string) ;
	printf (" string's length: strlen()     = %lu \n",   strlen  (my_string)) ;
	printf (" string's length: my_strlen()  = %lu \n", my_strlen (my_string)) ;
	printf (" string's length: my_strlen2() = %lu \n", my_strlen2(my_string)) ;

    /* CIT 593 students: TODO: add code to test your my_string.h functions */
    // test of my_strcpy() functions
    char src[40];
    char dest[40];
    my_strcpy(src, "This string is for test my_strcpy() function");
    my_strcpy(dest, src);
    printf("Final result in dest: %s\n", dest);
    
    char src2[30];
    char dest2[30];
    my_strcpy2(src2, "This string is for test my_strcpy2() function");
    my_strcpy2(dest2,src2);
    printf("Final result in dest2: %s\n", dest2);
    
    //test of my_strchr functions
    // test my_strchr
    const char *string_to_search = "Hello World";
    const char e = 'e';
    char *ret = my_strchr(string_to_search, e);
    printf("In '%s', string after |%c| is - |%s|\n",string_to_search, e,ret);
    // test my_strchr2
    const char *string_to_search2 = "Merry Christmas";
    const char k = 'k';
    char *ret2 = my_strchr2(string_to_search2,k);
    printf("If there is character '%c' in '%s', print it out: %s\n", k, string_to_search2,ret2);
   
    // test of my_strcat functions
    char srccat1[20] = "This is source";
    char destcat1[70] = "This is destination ";
    char srccat2[20] = "This is source2";
    char destcat2[70] = "This is destination2 ";
    char* retcat1 = my_strcat(destcat1, srccat1);
    char* retcat2 = my_strcat2(destcat2, srccat2);
    printf("Final result for my_strcat: %s\n", retcat1);
    printf("Final result for my_strcat2: %s\n", retcat2);
    
    // test of my_strcomp
    char strcmp1[20] = "ABCDEF";
    char strcmp2[20] = "abcdef";
    char strcmp3[10] = "Klaus";
    char strcmp4[10] = "Klaus";
    char strcmp5[10] = "CIT593";
    char strcmp6[10] = "CIS545";
    int comp_res1 = my_strcmp(strcmp1,strcmp2);
    if (comp_res1 ==0 ){
        printf("'%s' euquals '%s'\n", strcmp1, strcmp2);
    } else if (comp_res1 > 0){
       printf("'%s' is less than '%s'\n",strcmp2, strcmp1);
    } else {
        printf("'%s' is less than '%s'\n", strcmp1, strcmp2);
    }
    // test of my_strcmp2
    int comp_res2 = my_strcmp2(strcmp3,strcmp4);
    if (comp_res2 == 0 ){
        printf("'%s' euquals '%s'\n", strcmp3, strcmp4);
    } else if (comp_res1 > 0){
       printf("'%s' is less than '%s'\n",strcmp4, strcmp3);
    } else {
        printf("'%s' is less than '%s'\n", strcmp3, strcmp4);
    }
    // the first differed character "T">"S" by 1 in ascii code
    int comp_res3 = my_strcmp2(strcmp5,strcmp6);
    printf("expected result: 1; actual result: %d\n",comp_res3);
    
	return (0) ;

}
