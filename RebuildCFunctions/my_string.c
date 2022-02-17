/**************************************************************
 * file name   : my_string.c                                  *
 * author      : tjf & you                                    *
 * description : this C-file defines the functions previously *
 *               declared in the my_string.h header file      *
 *                                                            *
 *                                                            *
 **************************************************************
 *
 */

#include "my_string.h"
#define null ((char *)0)
// strlen functions takes in a pointer to a string and return its length
//
size_t2 my_strlen  (const char *str) {

	size_t2 len = 0 ;
	while (str[len] != '\0') {  // count up to the first NULL
		len++ ; 
	}
	return (len) ;

}

size_t2 my_strlen2 (const char *str) {

	const char* s;
	for (s = str; *s; ++s) ;
	return (s - str);

}


/* CIT 593 students: TODO: implement the remaining string functions
   that were declared in my_string.h */
// char* my_strcpy(char *dest, const char *src){
//    int pos = 0;
//    while (1){
//        dest[pos] = src[pos];
//        if (src[pos] == '\0'){
//            break;
//        }
//        pos++;
//    }
//    return dest;   
// }

char* my_strcpy  (char *dest, const char *src) {
    int i = 0;
    while(1){
        dest[i] = src[i];
        if (src[i] == '\0'){
            break;
        }
        i++;
    }
    return dest;// since dest (the address it contains) is not changed, return directly
} 

char* my_strcpy2 (char *dest, const char *src) {
    char* d ; // store dest (pointer) it in char* d, will needed in return
    d = dest;

    while(1){
        *dest = *src;
        dest++;
        src++;
        if (*src == '\0'){
            *dest = *src;   // when comes to the end of the string, copy paste the last null, then break
            break;
        }
    }
    return d; // returns a pointer to the destination string dest.
}

/* functions to search a string */
// returns a pointer to the first occurrence of the character c in the string str, or NULL if the character is not found.
char* my_strchr (const char *str, int c) {
    int length = 0;
    while (str[length] != (char) c && str[length] != '\0'){
        length++;
    } // break out of the loop once hits c or '\0'
    
    if (str[length] == '\0'){
        return null;
    } else{
        str = str + length;
        return (char *) str ; 
    }
    
}

char* my_strchr2 (const char *str, int c) {
    while (*str != (char) c && *str != '\0') {
        str++;
    }
    // directly deference the char pointer *str
    if (*str == '\0'){
        return null;
    } else{
        return (char *) str;
    }
}


/* functions to concatenate string */
// char* my_strcat  (char *dest, const char *src) {
//     des_start = my_strlen(dest);
//     int i = 0;
//     while (src[i] != '\0'){
//         dest[des_start] = src[i];
//         des_start++;
//         i++;
//     }
//     dest[des_start] = '\0';
//     return dest;
// }
char* my_strcat  (char *dest, const char *src) {
    size_t2 dest_len = my_strlen(dest);
    int src_len = 0;
    while (src[src_len] != '\0'){
        dest[dest_len] = src[src_len];
        dest_len++;
        src_len++;
    }
    dest[dest_len] = '\0';
    return dest;
}
char* my_strcat2 (char *dest, const char *src) {
    char *ptr = dest + my_strlen(dest);
    while (*src != '\0'){
        *ptr = *src;
        ptr++;
        src++;
    }
    *ptr = '\0';
    return dest;
}


/* functions to compare two strings */
int my_strcmp  (const char *str1, const char *str2) {
    int len = 0;
    while (str1[len]){
        if(str1[len] != str2[len]){
            break;
        }
        len++;
    }
    // if str2 is the same as str1, res will equal 0
    // if str2 is partially same as str1 (within str1's length), then res will be negative
    int res = str1[len] - str2[len];
    return res;
}

int my_strcmp2 (const char *str1, const char *str2) {
    // while *str1 == *str2 and either of them come to the string end
    while (*str1 == *str2 && *str1 != '\0'){
        str1++;
        str2++;
    }
    int res = *str1 - *str2;
    return res;
}

// function my_strrev() to reverse a string
char* my_strrev(char *string){
    int str_len = my_strlen(string);
    int j = str_len - 1;
    char temp [100];
    int i = 0;
    while (j >=0){
        temp[i] = string[j];
        i++;
        j--;
        
    }
    temp[i] = '\0';
    string = my_strcpy(string, temp);
    return string;
}

// function char* my_strccase (char *str) to convert character case to the opposite
char* my_strccase (char *str){
    int str_len = my_strlen(str);
    while(*str != '\0'){
        if (*str >= 97 && *str <= 122){ // if it's lowercase, decreade ascii number by 32 to uppercase
            *str = *str - 32;
        } else if ( *str >=65 && *str <=90){ // vice versa
            *str = *str + 32;
        }
        str++;
    }
    return str - str_len;
}

//function my_strtok()//
// firstly write a helper function my_cmp to help compare string when length is given
// my_cmp return 1 when des and src's first len characters are the same, otherwise return 0
int my_cmp(char *des, char *src, int len){
    int i;
    for (i = 0; i< len; i++){
        if (des[i] != src[i]){
            return 0;
        }
    }
    // step here means two des and src in certian len are the same
    return 1;
}


char* my_strtok(char *str, char *delim){
    int i = 0;
    static int valid = 1; // for read the last token
    static int last_len; // to store the length of the whole str when str is not null
    static char* end; // mark the end of the string at the beginning when str is not null
    int len = my_strlen(delim); // len stores the length of delimiter
    char *ret_position; // ret_position stores the pointer (an address )to be returned 
    char *temp;  // for read str
    static char *last;  //global variable to save the returned pointer of last time
    if (str == null) { // if first argument == NULL, start from the address in 'last'        
        temp = last;
        
    } else {
        temp = str;
        last_len = my_strlen(temp);
        end = temp + last_len;
    }
    last_len = my_strlen(temp);
    ret_position = temp; //upfdate to be returned pointer
    // when the delimiter is 1 in length
    if (len == 1){
         while (*temp != '\0'){
             if (*temp == *delim){
                 *temp = '\0'; // terminate str here
                 last = temp + 1; // update the addres to start search next time
                 return(ret_position);
             }
             temp++; // keep ierating until reach the string end
        }
        if (temp == end && valid){ // can only return once for the last token
            valid = 0;
            return ret_position;
        }
        return null ;// no delim found in str
    }
    // when the delim is more than 1 in length
    else {
        while(*temp != '\0'){
            if (my_cmp(temp, delim, len)){
                *temp = '\0';
                last = temp + len;
                return ret_position;
            }
            temp++;
        }
         if (temp == end && valid){
             valid = 0;
            return ret_position;
        }
    return null;
    }
}