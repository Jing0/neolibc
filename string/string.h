/*
 * A simple string implementation in c
 *
 * The definition of the string and it's methods
 *
 * File:   string.h
 * Author: Jackie Kuo <j.kuo2012@gmail.com>
 *
 * @license GNU AGPLv3
 */

#ifndef _STRING_H
#define _STRING_H

#include <stdio.h>
#include <stdlib.h>

#define INITSIZE 512

typedef struct str_s * str_t;

typedef struct str_s {
    char *value;
    uint16_t size;
    uint16_t capacity;
} str_s;

/*
 * The "Constructor" allocates a new stack
 */
str_t str_new(const char *string);
/* 
 * Returns a clone of this instance
 */
str_t str_clone(str_t self);
/*
 * Returns a copy of the string, with leading and trailing whitespace omitted 
 */
str_t str_trim(str_t self);
str_t str_substr(str_t self, const int pos, const int count);

void str_destroy(str_t self);
void str_clear(str_t self);
void str_println(str_t self);
void str_reverse(str_t self);
void str_swap(str_t str1, str_t str2);
void str_append(str_t self, const char *suffix);

int str_length(str_t self);
int str_isempty(str_t self);
int str_compare(str_t str1, str_t str2);
int str_findch(str_t self, const char ch, const int pos);
int str_findstr(str_t self, const char *str, const int pos);
int str_erase(str_t self, const int index, const int count);
int str_insert(str_t self, const int offset, const char *insert);
int str_replace(str_t self, const int pos, const int count, const char *replacement);

#endif