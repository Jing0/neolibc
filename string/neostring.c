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

#include "neostring.h"

str_t str_new(void) {
    str_t self = malloc(sizeof(str_s));
    if (self == NULL) {
        return NULL;
    }
    self->capacity = INITSIZE;
    self->value = malloc(self->capacity);
    if (self->value == NULL) {
        return NULL;
    }
    self->value[0] = '\0';
    self->size = 0;
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

int str_set(str_t self, const char *str) {
    if (self == NULL || str == NULL) {
        return -1;
    }

    int len = strlen(str);
    if (self->capacity <= len) {
        self->capacity *= 2;
        if (self->capacity <= len) {
            self->capacity = len + 16;
        }
        char *tmpPtr = realloc(self->value, self->capacity);
        if (tmpPtr == NULL) {
            return -1;
        }
        self->value = tmpPtr;
    }
    strcpy(self->value, str);
    self->size = len;
    return 0;
}

int str_setf(str_t self, const char *strformat, ... /* args */) {
    if (self == NULL || strformat == NULL) {
        return -1;
    }

    int len = strlen(strformat) + 16;
    if (self->capacity <= len) {
        self->capacity *= 2;
        if (self->capacity <= len) {
            self->capacity = len + 16;
        }
        char *tmpPtr = realloc(self->value, self->capacity);
        if (tmpPtr == NULL) {
            return -1;
        }
        self->value = tmpPtr;
    }
    va_list arg;
    int done;
    /* this is not entirely safe */
    va_start (arg, strformat);
    done = vsprintf (self->value, strformat, arg);
    va_end (arg);
    self->size = strlen(self->value);

    return done;
}

void str_print(const str_t self) {
    if (self == NULL) {
        return;
    }

    printf("%s", self->value);
}

void str_println(const str_t self) {
    if (self == NULL) {
        return;
    }

    printf("%s\n", self->value);
}

/* TODO: deal with capacity */
int str_append(str_t self, const char *str) {
    if (self == NULL || str == NULL) {
        return -1;
    }

    int len = self->size + strlen(str);
    if (self->capacity <= len) {
        self->capacity *= 2;
        if (self->capacity <= len) {
            self->capacity = len + 1;
        }
        char *tmpPtr = realloc(self->value, self->capacity);
        if (tmpPtr == NULL) {
            return -1;
        }
        self->value = tmpPtr;
    }
    strcpy(self->value + self->size, str);
    self->size = len;
    return 0;
}

int str_replace(str_t self, const int pos, const int count, const char *str) {
    if (self == NULL || str == NULL) {
        return -1;
    }

    if (pos < 0) {
        fprintf(stderr, "%s\n", "Error: \n\t"
                "The pos argument can't be less than 0");
        return -1;
    } else if (pos > self->size) {
        fprintf(stderr, "%s\n", "Error: \n\t"
                "The pos argument can't be greater than the length of this sequence");
        return -1;
    }
    str_t replace = str_new();
    if (replace == NULL) {
        return -1;
    }
    str_set(replace, str);
    int len = replace->size;
    if (len > count) {
        replace->value[count] = '\0';
    }
    str_t tmp = str_new();
    if (replace == NULL) {
        return -1;
    }
    str_set(tmp, self->value + pos + count);
    self->value[pos] = '\0';
    self->size = pos;
    str_append(self, replace->value);
    str_append(self, tmp->value);

    str_destroy(replace);
    str_destroy(tmp);
    return 0;
}

int str_erase(str_t self, const int pos, const int count) {
    if (self == NULL) {
        return -1;
    }

    if (pos > self->size) {
        fprintf(stderr, "%s\n", "Error: \n\t"
                "The pos argument can't be greater than the length of this sequence");
        return -1;
    }
    str_t tmp = str_new();
    if (tmp == NULL) {
        return -1;
    }
    str_set(tmp, self->value + pos + count);
    self->value[pos] = '\0';
    self->size = pos;
    str_append(self, tmp->value);

    str_destroy(tmp);
    return 0;
}

void str_reverse(str_t self) {
    if (self == NULL) {
        return;
    }

    int len = self->size;
    int i;
    char tmp;
    for (i = 0; i < len / 2; ++i) {
        tmp = self->value[i];
        self->value[i] = self->value[len - i - 1];
        self->value[len - i - 1] = tmp;
    }
}

/* TODO: deal with capacity */
int str_insert(str_t self, const int offset, const char *str) {
    if (self == NULL || str == NULL) {
        return -1;
    }

    if (offset < 0) {
        fprintf(stderr, "%s\n", "Error: \n\t"
                "The offset argument can't be less than 0");
        return -1;
    } else if (offset > self->size) {
        fprintf(stderr, "%s\n", "Error: \n\t"
                "The offset argument can't be greater than the length of this sequence");
        return -1;
    }
    int len = self->size + strlen(str);
    if (self->capacity <= len) {
        self->capacity *= 2;
        if (self->capacity <= len) {
            self->capacity = len + 1;
        }
        char *tmpPtr = realloc(self->value, self->capacity);
        if (tmpPtr == NULL) {
            return -1;
        }
        self->value = tmpPtr;
    }
    str_t lastpart = str_new();
    if (lastpart == NULL) {
        return -1;
    }
    str_set(lastpart, self->value + offset);
    self->value[offset] = '\0';
    self->size = offset;
    str_append(self, str);
    str_append(self, lastpart->value);

    str_destroy(lastpart);
    return 0;
}

uint16_t str_length(const str_t self) {
    if (self == NULL) {
        return -1;
    }

    return self->size;
}

int str_compare(const str_t str1, const str_t str2) {
    if (str1 == NULL || str2 == NULL) {
        return -1;
    }

    return strcmp(str1->value, str2->value);
}

void str_clear(str_t self) {
    if (self == NULL) {
        return;
    }

    self->value[0] = '\0';
    self->size = 0;
    self->capacity = INITSIZE;
}

void str_swap(str_t str1, str_t str2) {
    if (str1 == NULL || str2 == NULL) {
        return;
    }

    str_t tmp = str_new();
    if (tmp == NULL) {
        return;
    }
    str_set(tmp, str1->value);
    str_set(str1, str2->value);
    str_set(str2, tmp->value);
    str_destroy(tmp);
}

int str_isempty(const str_t self) {
    if (self == NULL) {
        return 1;
    }

    return self->size == 0 ? 1 : 0;
}

int str_findstr(const str_t self, const char *str, const int pos) {
    if (self == NULL) {
        return -1;
    }

    int index;
    if (pos > self->size) {
        fprintf(stderr, "%s\n", "Error: \n\t"
                "The pos argument can't be greater than the length of this sequence");
        return -1;
    }
    char *p = strstr(self->value, str);
    if (p != NULL) {
        index = (int)p - (int)(self->value);
    } else {
        index = -1;
    }
    free(p);
    return index;
}

int str_findch(const str_t self, const char ch, const int pos) {
    if (self == NULL) {
        return -1;
    }

    if (pos > self->size) {
        fprintf(stderr, "%s\n", "Error: \n\t"
                "The pos argument can't be greater than the length of this sequence");
        return -1;
    }
    int i;
    for (i = 0; i < self->size; ++i) {
        if (self->value[pos + i] == ch) {
            return pos + i;
        }
    }
    return -1;
}

str_t str_clone(const str_t self) {
    if (self == NULL) {
        return NULL;
    }

    str_t clone = str_new();
    if (clone == NULL) {
        return NULL;
    }
    str_set(clone, self->value);
    return clone;
}

str_t str_trim(const str_t self) {
    if (self == NULL) {
        return NULL;
    }

    int i = 0;
    while (self->value[i] == ' ') {
        ++i;
    }
    str_t tmp = str_new();
    if (tmp == NULL) {
        return NULL;
    }
    str_set(tmp, self->value + i);
    i = tmp->size - 1;
    while (tmp->value[i] == ' ') {
        --i;
    }
    tmp->value[i + 1] = '\0';
    tmp->size = i + 1;
    return tmp;
}

str_t str_substr(const str_t self, const int pos, const int count) {
    if (self == NULL) {
        return NULL;
    }

    if (pos > self->size) {
        fprintf(stderr, "%s\n", "Error: \n\t"
                "The pos argument can't be greater than the length of this sequence");
        return NULL;
    }
    str_t tmp = str_new();
    if (tmp == NULL) {
        return NULL;
    }
    str_set(tmp, self->value + pos);
    tmp->value[count] = '\0';
    tmp->size = count;
    return tmp;
}

char *str_cstr(const str_t self) {
    if (self == NULL) {
        return NULL;
    }

    return self->value;
}

int str_readFromFile(str_t self, const char *path) {
    if (self == NULL || path == NULL) {
        return -1;
    }

    str_clear(self);
    char line[LINE_MAX];
    FILE *fp = fopen(path, "r");
    if (fp == NULL) {
        return -1;
    }
    while (fgets(line, LINE_MAX - 1, fp) != NULL) {
        str_append(self, line);
    }
    fclose(fp);
    return 0;
}

int str_writeToFile(const str_t self, const char *path) {
    if (self == NULL || path == NULL) {
        return -1;
    }

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

void str_toupper(str_t self) {
    if (self == NULL) {
        return;
    }

    int i;
    for (i = 0; i < self->size; ++i) {
        self->value[i] = toupper(self->value[i]);
    }
}

void str_tolower(str_t self) {
    if (self == NULL) {
        return;
    }

    int i;
    for (i = 0; i < self->size; ++i) {
        self->value[i] = tolower(self->value[i]);
    }
}

char str_charAt(str_t self, int pos) {
    if (self == NULL) {
        return -1;
    }

    if (pos < 0) {
        fprintf(stderr, "%s\n", "Error: \n\t"
                "The pos argument can't be less than 0");
        return -1;
    } else if (pos > self->size) {
        fprintf(stderr, "%s\n", "Error: \n\t"
                "The pos argument can't be greater than the length of this sequence");
        return -1;
    }
    return self->value[pos];
}
