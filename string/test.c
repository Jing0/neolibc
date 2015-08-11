#include <stdio.h>
#include "neostring.h"
int main(int argc, char const *argv[]) {
    /* str_new */
    str_t string = str_new();
    /* str_setf */
    str_setf(string, "   %d%d%d", 1, 2, 3);
    /* str_append */
    str_append(string, "appending   end");
    /* str_println */
    str_println(string);
    /* str_reverse */
    str_reverse(string);
    str_println(string);
    /* str_length */
    printf("size before trimming:\t%d\n", str_length(string));
    /* str_trim */
    str_t trim = str_trim(string);
    printf("size after trimming:\t%d\n", str_length(trim));
    /* str_substr */
    str_t substr = str_substr(string, 0, 3);
    printf("substr before swap:\t");
    str_println(substr);
    printf("trim before swap:\t");
    str_println(trim);
    str_swap(substr, trim);
    printf("substr after swap:\t");
    str_println(substr);
    printf("trim after swap:\t");
    str_println(trim);
    printf("is string empty?:\t%s\n", 
        str_isempty(string) ? "Yes" : "No");
    printf("is substr equal to string?:\t%s\n", 
        str_compare(substr, string) ? "No" : "Yes");
    
    /* str_readFromFile */
    str_readFromFile(string, "Makefile");
    /* str_clone */
    str_t clone = str_clone(string);
    /* str_toupper */
    str_toupper(clone);
    /* str_writeToFile */
    str_writeToFile(clone, "./test.txt");
    /* str_destroy */
    str_destroy(string);
    str_destroy(clone);
    str_destroy(substr);
    str_destroy(trim);
    return 0;
}