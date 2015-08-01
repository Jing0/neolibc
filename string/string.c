/*
 * A simple string implementation in c
 *
 * The implementation of the string's methods
 *
 * File:   string.c
 * Author: Jackie Kuo <j.kuo2012@gmail.com>
 *
 * @license GNU AGPLv3
 */

#include <stdio.h>
#include <string.h>
#include "string.h"

void str_println(str_t self) {
    printf("%s\n", self->value);
}

/* TODO: deal with capacity */
void str_append(str_t self, const char *str) {
    int len = self->size + strlen(str);
    if (self->capacity <= len) {
        self->capacity *= 2;
        if (self->capacity <= len) {
            self->capacity = len + 1;
        }
        realloc(self->value, self->capacity);
    }
    strcpy(self->value + self->size, str);
    self->size = len;
}

int str_replace(str_t self, const int pos, const int count, const char *replacement) {
    if (pos < 0) {
        fprintf(stderr, "%s\n", "Error: \n\t"
            "The pos argument can't be less than 0");
        return -1;
    } else if (pos > self->size) {
        fprintf(stderr, "%s\n", "Error: \n\t"
            "The pos argument can't be greater than the length of this sequence");
        return -1;
    }
    str_t replace = str_new(replacement);
    int len = replace->size;
    if (len > count) {
        replace->value[count] = '\0';
    }
    str_t tmp = str_new(self->value + pos + count);
    self->value[pos] = '\0';
    self->size = pos;
    str_append(self, replace->value);
    str_append(self, tmp->value);

    str_free(replace);
    str_free(tmp);
    return 0;
}

int str_erase(str_t self, const int index, const int count) {
    if (index > self->size) {
        fprintf(stderr, "%s\n", "Error: \n\t"
            "The index argument can't be greater than the length of this sequence");
        return -1;
    }
    str_t tmp = str_new(self->value + index + count);
    self->value[index] = '\0';
    self->size = index;
    str_append(self, tmp->value);

    str_free(tmp);
    return 0;
}

void str_reverse(str_t self) {
    int len = self->size;
    int i;
    char tmp;
    for (i = 0; i < len/2; ++i) {
        tmp = self->value[i];
        self->value[i] = self->value[len-i-1];
        self->value[len-i-1] = tmp;
    }
}

/* TODO: deal with capacity */
int str_insert(str_t self, const int offset, const char *insert) {
    if (offset < 0) {
        fprintf(stderr, "%s\n", "Error: \n\t"
            "The offset argument can't be less than 0");
        return -1;
    } else if (offset > self->size) {
        fprintf(stderr, "%s\n", "Error: \n\t"
            "The offset argument can't be greater than the length of this sequence");
        return -1;
    }
    int len = self->size + strlen(insert);
    if (self->capacity <= len) {
        self->capacity *= 2;
        if (self->capacity <= len) {
            self->capacity = len + 1;
        }
        realloc(self->value, self->capacity);
    }
    str_t lastpart = str_new(self->value + offset);
    self->value[offset] = '\0';
    self->size = offset;
    str_append(self, insert);
    str_append(self, lastpart->value);

    str_free(lastpart);
    return 0;
}

int str_length(str_t self) {
    return self->size;
}

int str_compare(str_t str1, str_t str2) {
    return strcmp(str1->value, str2->value);
}

void str_clear(str_t self) {
    self->value[0] = '\0';
    self->size = 0;
    self->capacity = INITSIZE;
}

void str_swap(str_t str1, str_t str2) {
    str_t tmp = str_new(str1->value);
    str_clear(str1);
    str_append(str1, str2->value);
    str_clear(str2);
    str_append(str2, tmp->value);
    str_free(tmp);
}

int str_isempty(str_t self) {
    return self->size == 0? 1 : 0;
}

void str_destroy(str_t self) {
    if (self->value != NULL) {
        free(self->value);
    }
    if (self != NULL) {
        free(self);
    }
}

int str_findstr(str_t self, const char *substr, const int pos) {
    if (pos > self->size) {
        fprintf(stderr, "%s\n", "Error: \n\t"
            "The pos argument can't be greater than the length of this sequence");
        return -1;
    }
    char *p = strstr(self->value, substr);
    if (p != NULL) {
        return (int)p-(int)(self->value);
    }
    return -1;
}

int str_findch(str_t self, const char ch, const int pos) {
    if (pos > self->size) {
        fprintf(stderr, "%s\n", "Error: \n\t"
            "The pos argument can't be greater than the length of this sequence");
        return -1;
    }
    int i;
    for (i = 0; i < self->size; ++i) {
        if (self->value[pos+i] == ch) {
            return pos + i;
        }
    }
    return -1;
}

str_t str_clone(str_t self) {
    str_t clone = str_new(self->value);
    return clone;
}

str_t str_trim(str_t self) {
    int i = 0;
    while (self->value[i] == ' ') {
        ++i;
    }
    str_t tmp = str_new(self->value + i);
    i = tmp->size - 1;
    while (tmp->value[i] == ' ') {
        --i;
    }
    tmp->value[i+1] = '\0';
    tmp->size = i + 1;
    return tmp;
}

str_t str_substr(str_t self, const int pos, const int count) {
    if (pos > self->size) {
        fprintf(stderr, "%s\n", "Error: \n\t"
            "The pos argument can't be greater than the length of this sequence");
        return NULL;
    }
    str_t tmp = str_new(self->value + pos);
    tmp->value[count] = '\0';
    tmp->size = count;
    return tmp;
}

str_t str_new(const char *string) {
    /* TODO: check str */
    str_t self = malloc(sizeof(str_s));
    int len = strlen(string);
    self->capacity = INITSIZE;

    if (self->capacity <= len) {
        self->capacity *= 2;
        if (self->capacity <= len) {
            self->capacity = len + 1;
        }
        realloc(self->value, self->capacity);
    }

    self->value = malloc(self->capacity);
    strcpy(self->value, string);
    self->size = strlen(string);
    return self;
}