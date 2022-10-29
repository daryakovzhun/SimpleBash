#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_

#define  _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

struct list {
    char* find;
    struct list *ptr;
    int file;
};

typedef struct {
    int i;
    int v;
    int c;
    int l;
    int n;
    int h;
    int s;
    int o;
} option;

void define_struct(char* flag, option* op, size_t* count);
void check_struct(option op, char** buffer, struct list* temp_list, size_t* len);
void op_c(int count_file_flag, char* name, int count_match, int l, int h);
void find(char** buffer, char* find, option op);
void add_name_file(char** buffer, char* name_file, size_t* len);
void *s21_insert(const char *src, const char *str, size_t start_index);
struct list* init(char* find);
struct list* add(struct list* lst, char* find, int flag);
void delete_list(struct list* start);
#endif  //  SRC_GREP_S21_GREP_H_
