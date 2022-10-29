#ifndef SRC_CAT_S21_CAT_H_
#define SRC_CAT_S21_CAT_H_

#define  _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct {
    int b;
    int e;
    int n;
    int s;
    int t;
    int v;
} option;

int define_struct(char* flag, option* op);
void check_struct(option op, char** buffer, FILE* fd_in, int* count_line, size_t* len, int* count_read);
void *s21_insert(const char *src, const char *str, size_t start_index);
#endif  //  SRC_CAT_S21_CAT_H_
