/*
 * A simple string implementation in c
 *
 * The implementation of the string's methods
 *
 * File:   neostring.c
 * Author: Jackie Kuo <j.kuo2012@gmail.com>
 *
 * @license GNU AGPLv3
 */

#include <ctype.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>

#include "neostring.h"

#define INIT_CAPACITY      128
#define CAPACITY_INCREMENT 32
#define LINE_MAX           128

#define CHECK_CAPACITY(len)                                     \
    if (self->capacity <= len) {                                \
        self->capacity = len + CAPACITY_INCREMENT;              \
        char *tmpPtr = realloc(self->value, self->capacity);    \
        if (tmpPtr == NULL) {                                   \
            return -1;                                          \
        }                                                       \
        self->value = tmpPtr;                                   \
        tmpPtr = NULL;                                          \
    }                                                           \

#define CHECK_ARG_POS(retval)                                   \
    if (pos < 0) {                                              \
        fprintf(stderr, "%s\n", "Error: \n\t"                   \
                "The pos argument can't be less than 0");       \
        return retval;                                          \
    } else if (pos > self->size) {                              \
        fprintf(stderr, "%s\n", "Error: \n\t"                   \
                "The pos argument can't be greater than"        \
                " the size of the string");                     \
        return retval;                                          \
    }                                                           \

#define CHECK_ARG(arg, value, retval)                           \
    if (arg == value) {                                         \
        return retval;                                          \
    }                                                           \

/* Initializes members of a string */
static void str_init(str_t self);

static void str_init(str_t self) {
    self->value[0] = '\0';
    self->size = 0;
    self->capacity = INIT_CAPACITY;
}

str_t str_new(void) {
    str_t self = malloc(sizeof(struct str_s));
    if (self == NULL) {
        return NULL;
    }
    self->value = malloc(INIT_CAPACITY);
    if (self->value == NULL) {
        return NULL;
    }
    str_init(self);
    return self;
}

void str_destroy(str_t self) {
    if (self->value != NULL) {
        free(self->value);
    }
    if (self != NULL) {
        free(self);
    }
}

int str_append(str_t self, const char *str) {
    CHECK_ARG(self, NULL, -1);
    CHECK_ARG(str, NULL, -1);

    int len = self->size + strlen(str);
    CHECK_CAPACITY(len);
    strncpy(self->value + self->size, str, self->capacity - self->size);
    self->size = len;
    return 0;
}

char str_charAt(const str_t self, int pos) {
    CHECK_ARG(self, NULL, -1);
    CHECK_ARG_POS(-1);

    return self->value[pos];
}

void str_clear(str_t self) {
    CHECK_ARG(self, NULL, );

    str_init(self);
}

str_t str_clone(const str_t self) {
    CHECK_ARG(self, NULL, NULL);

    str_t clone = str_new();
    if (clone == NULL) {
        return NULL;
    }
    if (str_set(clone, self->value) < 0) {
        return NULL;
    }
    return clone;
}

int str_compare(const str_t str1, const str_t str2) {
    CHECK_ARG(str1, NULL, -1);
    CHECK_ARG(str2, NULL, -1);

    return strcmp(str1->value, str2->value);
}

const char *str_cstr(const str_t self) {
    CHECK_ARG(self, NULL, NULL);

    return self->value;
}

int str_erase(str_t self, const int pos, const int count) {
    CHECK_ARG(self, NULL, -1);
    CHECK_ARG_POS(-1);

    str_t tmp = str_new();
    if (tmp == NULL) {
        return -1;
    }
    if (str_set(tmp, self->value + pos + count) < 0) {
        return -1;
    }
    self->value[pos] = '\0';
    self->size = pos;
    if (str_append(self, tmp->value) == -1) {
        return -1;
    }
    str_destroy(tmp);
    return 0;
}

int str_findch(const str_t self, const char ch, const int pos) {
    CHECK_ARG(self, NULL, -1);
    CHECK_ARG_POS(-1);

    int i;
    for (i = 0; i < self->size; ++i) {
        if (self->value[pos + i] == ch) {
            return pos + i;
        }
    }
    return -1;
}

int str_findstr(const str_t self, const char *str, const int pos) {
    CHECK_ARG(self, NULL, -1);
    CHECK_ARG_POS(-1);

    char *p = strstr(self->value, str);
    if (p == NULL) {
        return -1;
    }
    return (int)p - (int)(self->value);
}

int str_hasPrefix(const str_t self, const char *str) {
    CHECK_ARG(self, NULL, -1);
    CHECK_ARG(str, NULL, -1);

    int index = str_findstr(self, str, 0);

    return index == 0;
}

int str_hasSuffix(const str_t self, const char *str) {
    CHECK_ARG(self, NULL, -1);
    CHECK_ARG(str, NULL, -1);

    int i, len = strlen(str);
    for (i = 0; i < len; ++i) {
        if (str[i] != self->value[self->size - len + i]) {
            return 0;
        }
    }
    return 1;
}

int str_insert(str_t self, const int offset, const char *str) {
    CHECK_ARG(self, NULL, -1);
    CHECK_ARG(str, NULL, -1);


    if (offset < 0) {
        fprintf(stderr, "%s\n", "Error: \n\t"
                "The offset argument can't be less than 0");
        return -1;
    } else if (offset > self->size) {
        fprintf(stderr, "%s\n", "Error: \n\t"
                "The offset argument can't be greater than"
                "the length of this sequence");
        return -1;
    }
    int len = self->size + strlen(str);
    CHECK_CAPACITY(len);
    str_t tmp = str_new();
    if (tmp == NULL) {
        return -1;
    }
    if (str_set(tmp, self->value + offset) < 0) {
        return -1;
    }
    self->value[offset] = '\0';
    self->size = offset;
    if (str_append(self, str) == -1) {
        return -1;
    }
    if (str_append(self, tmp->value) == -1) {
        return -1;
    }
    str_destroy(tmp);
    return 0;
}

int str_isempty(const str_t self) {
    CHECK_ARG(self, NULL, 1);

    return self->size == 0 ? 1 : 0;
}

size_t str_length(const str_t self) {
    CHECK_ARG(self, NULL, 0);

    return self->size;
}

void str_print(const str_t self) {
    CHECK_ARG(self, NULL, );

    printf("%s", self->value);
}

void str_println(const str_t self) {
    CHECK_ARG(self, NULL, );

    printf("%s\n", self->value);
}

int str_readFromFile(str_t self, const char *path) {
    CHECK_ARG(self, NULL, -1);
    CHECK_ARG(path, NULL, -1);

    str_clear(self);
    char line[LINE_MAX];
    FILE *fp = fopen(path, "r");
    if (fp == NULL) {
        return -1;
    }
    while (fgets(line, LINE_MAX - 1, fp) != NULL) {
        if (str_append(self, line) == -1) {
            return -1;
        }
    }
    fclose(fp);
    return 0;
}

int str_replace(str_t self, const int pos, const int count, const char *str) {
    CHECK_ARG(self, NULL, -1);
    CHECK_ARG(str, NULL, -1);
    CHECK_ARG_POS(-1);

    str_t tmp = str_new();
    if (tmp == NULL) {
        return -1;
    }
    if (str_set(tmp, str) < 0) {
        return -1;
    }
    if (tmp->size > count) {
        tmp->value[count] = '\0';
    }
    if (str_append(tmp, self->value + pos + count) == -1) {
        return -1;
    }
    self->value[pos] = '\0';
    self->size = pos;
    if (str_append(self, tmp->value) == -1) {
        return -1;
    }
    str_destroy(tmp);
    return 0;
}

void str_reverse(str_t self) {
    CHECK_ARG(self, NULL, );

    int i, len = self->size;
    for (i = 0; i < len / 2; ++i) {
        char tmp = self->value[i];
        self->value[i] = self->value[len - i - 1];
        self->value[len - i - 1] = tmp;
    }
}

int str_set(str_t self, const char *strformat, ... /* args */) {
    if (self == NULL || strformat == NULL) {
        return -1;
    }

    int len = strlen(strformat) + CAPACITY_INCREMENT;
    CHECK_CAPACITY(len);
    va_list arg;
    int done;
    /* this is not entirely safe */
    va_start (arg, strformat);
    while ((done = vsnprintf (self->value, self->capacity, strformat, arg)) < 0) {
        CHECK_CAPACITY(self->capacity + CAPACITY_INCREMENT);
    }
    va_end (arg);
    self->size = strlen(self->value);

    return done;
}

str_t str_substr(const str_t self, const int pos, const int count) {
    CHECK_ARG(self, NULL, NULL);
    CHECK_ARG_POS(NULL);

    str_t tmp = str_new();
    if (tmp == NULL) {
        return NULL;
    }
    if (str_set(tmp, self->value + pos) < 0) {
        return NULL;
    }
    tmp->value[count] = '\0';
    tmp->size = count;
    return tmp;
}

int str_swap(str_t str1, str_t str2) {
    CHECK_ARG(str1, NULL, -1);
    CHECK_ARG(str2, NULL, -1);

    str_t tmp = str_new();
    if (tmp == NULL) {
        return -1;
    }
    if (str_set(tmp, str1->value) < 0) {
        return -1;
    }
    if (str_set(str1, str2->value) < 0) {
        return -1;
    }
    if (str_set(str2, tmp->value) < 0) {
        return -1;
    }
    str_destroy(tmp);
    return 0;
}

void str_tolower(str_t self) {
    CHECK_ARG(self, NULL, );

    int i;
    for (i = 0; i < self->size; ++i) {
        self->value[i] = tolower(self->value[i]);
    }
}

void str_toupper(str_t self) {
    CHECK_ARG(self, NULL, );

    int i;
    for (i = 0; i < self->size; ++i) {
        self->value[i] = toupper(self->value[i]);
    }
}

void str_trim(str_t self) {
    CHECK_ARG(self, NULL, );

    int off = 0;
    while (self->value[off] == ' ') {
        ++off;
    }
    int i = self->size - 1;
    while (self->value[i] == ' ') {
        --i;
    }
    self->value[i + 1] = '\0';
    self->size = i + 1 - off;
    for (i = 0; i <= self->size; ++i) {
        self->value[i] = self->value[i + off];
    }
}

void str_trimToSize(str_t self) {
    CHECK_ARG(self, NULL, );

    self->capacity = self->size;
    char *tmpPtr = realloc(self->value, self->capacity);
    if (tmpPtr == NULL) {
        return;
    }
    self->value = tmpPtr;
    tmpPtr = NULL;
}

int str_writeToFile(const str_t self, const char *path) {
    CHECK_ARG(self, NULL, -1);
    CHECK_ARG(path, NULL, -1);

    FILE *fp = fopen(path, "w");
    if (fp == NULL) {
        return -1;
    }
    if (fputs(self->value, fp) == EOF) {
        fclose(fp);
        return -1;
    }
    fclose(fp);
    return 0;
}
