/*
 * A simple string implementation in c
 *
 * The definition of the string and it's methods
 *
 * File:   neostring.h
 * Author: Jackie Kuo <j.kuo2012@gmail.com>
 *
 * @license GNU AGPLv3
 */

#ifndef _NEOSTRING_H
#define _NEOSTRING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

#define INIT_CAPACITY      256
#define CAPACITY_INCREMENT 64
#define LINE_MAX           128

typedef struct str_s * str_t;

typedef struct str_s {
    char *value;
    uint16_t size;
    uint16_t capacity;
} str_s;

/* ==== Constructor and Destructor ==== */

/*
 * Calls the constructor
 * allocates a new string
 */
str_t str_new(void);

/*
 * Calls the destructor
 * destructs a stirng stored in the allocated storage
 */
void str_destroy(str_t self);

/* ========== Methods Summary ========== */

/*
 * Appends the string representation of the char array argument to this string
 *
 * @return
 * 0 if successful, -1 otherwise
 */
int str_append(str_t self, const char *str);

/*
 * Returns the char value at the specified pos
 *
 * @return
 * the char value at the specified pos if not successful,
 * -1 otherwise
 * The first char value is at index 0.
 *
 */
char str_charAt(const str_t self, int pos);

/*
 * Clears the contents
 *
 */
void str_clear(str_t self);

/*
 * Returns a clone of this instance
 *
 * @return
 * A clone of the string if successful, NULL otherwise
 */
str_t str_clone(const str_t self);

/*
 * Compares two strings
 *
 * @return
 * An integer greater than, equal to, or less than 0,
 * according as the string str1 is greater than, equal to, or less than the string str2
 */
int str_compare(const str_t str1, str_t str2);

/*
 * Returns a pointer to a null-terminated character array
 * with data equivalent to those stored in the string
 *
 * @return
 * A pointer point to a character array with data equivalent to those stored in the string
 */
const char *str_cstr(const str_t self);

/*
 * Removes specified characters [pos, pos + count) from the string
 *
 * @return
 * 0 if characters removed successfully, -1 otherwise
 */
int str_erase(str_t self, const int pos, const int count);

/*
 * Finds the first character ch, starting the search at pos
 *
 * @return
 * Position of the first occurance of the found character,
 * or -1 if no such character is found
 */
int str_findch(const str_t self, const char ch, const int pos);

/*
 * Find the first string str, starting the search at pos
 *
 * @return
 * Position of the first occurance of the found substring,
 * or -1 if no such substring is found
 */
int str_findstr(const str_t self, const char *str, const int pos);

/*
 * Checks if the string has the str as prefix
 *
 * @return
 * 1 if the string has the str as prefix, 0 if not, -1 otherwise
 */
int str_hasPrefix(const str_t self, const char *str);

/*
 * Checks if the string has the str as prefix
 *
 * @return
 * 1 if the string has the str as suffix, 0 if not, -1 otherwise
 */
int str_hasSuffix(const str_t self, const char *str);

/*
 * Inserts characters into the string
 *
 * @return
 * 0 if characters inserted successfully, -1 otherwise
 */
int str_insert(str_t self, const int offset, const char *str);

/*
 * Checks if the string has no characters
 *
 * @return
 * 1 if the string is empty, 0 otherwise
 */
int str_isempty(const str_t self);

/*
 * Returns the length of this string
 *
 * @return
 * The length of the sequence of characters represented by this string
 */
uint16_t str_length(const str_t self);

/*
 * Prints the string
 *
 */
void str_print(const str_t self);

/*
 * Prints the string and then terminates the line
 *
 */
void str_println(const str_t self);

/*
 * Set the string value as the content of the file at the given path
 *
 * @return
 * 0 if file content loaded successfully, -1 otherwise
 */
int str_readFromFile(str_t self, const char *path);

/*
 * Replaces the part of the string indicated by [pos, pos + count) with a new string
 *
 * @return
 * 0 if characters inserted successfully, -1 otherwise
 */
int str_replace(str_t self, const int pos, const int count, const char *str);

/*
 * Causes this character sequence to be replaced by the reverse of the sequence
 *
 */
void str_reverse(str_t self);

/*
 * Exchanges the contents of the str1 with those of str2
 *
 */
void str_swap(str_t str1, str_t str2);

/*
 * Sets the string value as the formated character array argument
 *
 * @return
 * 0 if successful, -1 otherwise
 */
int str_set(str_t self, const char *strformat, ... /* args */);

/*
 * Returns a substring [pos, pos + count).
 *
 * @return
 * If the requested substring extends past the end of the string, or if count == npos,
 * the returned substring is [pos, self->size).
 */
str_t str_substr(const str_t self, const int pos, const int count);

/*
 * Changes each character to its corresponding lowercase value
 *
 */
void str_tolower(str_t self);

/*
 * Changes each character to its corresponding uppercase value
 *
 */
void str_toupper(str_t self);

/*
 * Returns a copy of the string, with leading and trailing whitespace omitted
 *
 */
void str_trim(str_t self);

/*
 * Attempts to reduce storage used for the character sequence
 *
 */

void str_trimToSize(str_t self);

/*
 * Writes the string's value to the file named by path
 *
 * @return
 * 0 if successful, -1 otherwise
 */
int str_writeToFile(const str_t self, const char *path);

#endif /* _NEOSTRING_H_ */