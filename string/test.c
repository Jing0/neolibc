#include <stdio.h>
#include "neostring.h"
int main(int argc, char const *argv[]) {
    /* str_new */
    str_t string = str_new();
    /* str_set */
    str_set(string, "   %d%d%d", 1, 2, 3);
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
    str_trim(string);
    printf("size after trimming:\t%d\n", str_length(string));
    /* str_substr */
    str_t substr = str_substr(string, 0, 3);
    printf("substr before swap:\t");
    str_println(substr);
    printf("string before swap:\t");
    str_println(string);
    str_swap(substr, string);
    printf("substr after swap:\t");
    str_println(substr);
    printf("string after swap:\t");
    str_println(string);
    printf("is string empty?\t%s\n",
           str_isempty(string) ? "Yes" : "No");
    printf("is substr equal to string?\t%s\n",
           str_compare(substr, string) ? "No" : "Yes");

    /* str_readFromFile */
    str_readFromFile(string, "neostring.c");
    printf("string size: %d\t", str_length(string));
    printf("string capacity: %d\n", string->capacity);
    str_set(string, "ok");
    printf("Before trimToSize():\n");
    printf("string size: %d\t", str_length(string));
    printf("string capacity: %d\n", string->capacity);
    /* str_trimToSize */
    str_trimToSize(string);
    printf("After trimToSize():\n");
    printf("string size: %d\t", str_length(string));
    printf("string capacity: %d\n", string->capacity);
    str_set(string, "hello, world");
    printf("string has prefix ello?\t%s\n", str_hasPrefix(string, "ello") ? "Yes" : "No");
    printf("string has prefix orld?\t%s\n", str_hasSuffix(string, "orld") ? "Yes" : "No");
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
    return 0;
}