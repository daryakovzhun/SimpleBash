//  Copyright rosanabr 2022

#include "s21_grep.h"

int find_e_or_f(char *argv[], int argc) {
    int search = 0;
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-' && (strchr(argv[i], 'e') || strchr(argv[i], 'f'))) {
            search = 1;
            break;
        }
    }
    return search;
}

void reg_from_file(struct list* list_find, char* file_name) {
    struct list* list_f = list_find;
    FILE* file;
    char *buffer = NULL;
    size_t len_buffer = 0;
    file = fopen(file_name, "r");
    if (file) {
        int count_read;
        while (!feof(file) && (count_read = getline(&buffer, &len_buffer, file)) > 0) {
                size_t len = strlen(buffer);
                if (len > 1 && buffer[len - 1] == '\n') {
                    buffer[len - 1] = '\0';
                }
                list_f = add(list_f, buffer, 1);
        }
    } else {
        fprintf(stderr, "grep: %s: No such file or directory\n", file_name);
    }
    free(buffer);
}

void define_list(char *argv[], int argc, struct list* list_find, int* j, int* index, option* op) {
    int flag = 0;
    for (int i = 1; i < argc; i++) {
        size_t is_e_or_f = 0;
        define_struct(argv[i], op, &is_e_or_f);
        if (is_e_or_f > 0) {
            if (strlen(argv[i]) == is_e_or_f) {
                if (argv[i][is_e_or_f - 1] == 'e') {
                    list_find = add(list_find, argv[i + 1], 0);
                } else {
                    reg_from_file(list_find, argv[i + 1]);
                }
                i++;
            } else {
                if (argv[i][is_e_or_f - 1] == 'e') {
                    list_find = add(list_find, argv[i] + is_e_or_f, 0);
                } else {
                    reg_from_file(list_find, argv[i] + is_e_or_f);
                }
            }
        } else if (argv[i][0] != '-') {
            if (flag == 0 && (list_find)->find == NULL && find_e_or_f(argv, argc) == 0) {
                list_find = add(list_find, argv[i], 0);
                flag = 1;
            } else {
                index[*j] = i;
                (*j)++;
            }
        }
    }
}

void check_printf_op_v(struct list* start, char** buffer, option op) {
    struct list* list_find = start;
    do {
        find(buffer, list_find->find, op);
        if (strcmp(*buffer, "\0") == 0) {
            break;
        }
        list_find = list_find->ptr;
    } while (list_find != NULL);
}

void check_line_in_file(FILE* fd_in, struct list* start_list_find, option op,
                        int count_file_flag, char *argv[], int i, int* count_match, int* index) {
    char *buffer = NULL;
    size_t len = 0;
    int count_read = 1, count_line = 0;
    while (!feof(fd_in) && count_read > 0) {
        count_line++;
        count_read = getline(&buffer, &len, fd_in);
        struct list* temp = start_list_find->ptr;
        int flag_dublicate = 0;

        if (count_read != -1 && strlen(buffer) > 0 && buffer[strlen(buffer) - 1] != '\n') {
            len += 2;
            char* buffer_temp = realloc(buffer, len * sizeof(char));
            if (buffer_temp == NULL) {
                free(buffer);
            } else {
                buffer = buffer_temp;
            }
            strcat(buffer, "\n");
        }
        char* buf_buffer = (char*) malloc(sizeof(char) * (strlen(buffer) + 1));
        strcpy(buf_buffer, buffer);

        if (op.v == 1)
            check_printf_op_v(temp, &buffer, op);

        while (temp != NULL && strcmp(buffer, "\0") != 0) {
            if (count_read != -1) check_struct(op, &buffer, temp, &len);

            if (op.n == 1 && strlen(buffer) > 0) {
                char number[1000];
                sprintf(number, "%d", count_line);
                add_name_file(&buffer, number, &len);
            }

            if (op.h != 1 && count_file_flag != 0 && strlen(buffer) > 0)
                add_name_file(&buffer, argv[index[i]], &len);

            if (strlen(buffer) > 0 && (op.c == 1 || op.l == 1) && flag_dublicate == 0) {
                (*count_match)++;
                flag_dublicate = 1;
            } else if (strlen(buffer) > 0 && flag_dublicate == 0) {
                printf("%s", buffer);
                flag_dublicate = 1;
                break;
            }
            temp = temp->ptr;
            len = strlen(buf_buffer) + 1;
            buffer = realloc(buffer, len * sizeof(char));
            strcpy(buffer, buf_buffer);
        }
        free(buf_buffer);
    }
    free(buffer);
}

int main(int argc, char *argv[]) {
    option op = {0};
    struct list* list_find = init(NULL);
    struct list* start_list_find = list_find;
    int count_file_flag = 0, index[argc], j = 0;

    define_list(argv, argc, list_find, &j, index, &op);

    for (int i = 0; i < j; i++) {
        FILE* fd_in;

        if (j > 1) count_file_flag++;
        fd_in = fopen(argv[index[i]], "r");
        if (fd_in) {
            int count_match = 0;

            check_line_in_file(fd_in, start_list_find, op,
                                count_file_flag, argv, i, &count_match, index);

            if (op.c == 1)
                op_c(count_file_flag, argv[index[i]], count_match, op.l, op.h);

            if (op.l == 1 && count_match > 0)
                printf("%s\n", argv[index[i]]);

            fclose(fd_in);
        } else if (op.s != 1) {
            fprintf(stderr, "grep: %s: No such file or directory\n", argv[index[i]]);
        }
    }

    delete_list(start_list_find);

    return 0;
}

struct list* init(char* find) {
    struct list* temp;
    temp = (struct list*)malloc(sizeof(struct list));
    temp->file = 0;
    temp->find = find;
    temp->ptr = NULL;
    return(temp);
}

struct list* add(struct list* lst, char* find, int flag) {
    struct list *temp, *p;
    temp = malloc(sizeof(struct list));
    p = lst->ptr;;
    lst->ptr = temp;
    if (flag == 1) {
        temp->find = malloc(sizeof(char) * (strlen(find) + 1));
        strcpy(temp->find, find);
    } else {
        temp->find = find;
    }
    temp->file = flag;
    temp->ptr = p;
    return(temp);
}

void delete_list(struct list* start) {
    while (start != NULL) {
        struct list* temp = start->ptr;
        if (start->file == 1) {
            free(start->find);
        }
        free(start);
        start = temp;
    }
}

void define_struct(char* flag, option* op, size_t* count) {
    if (flag[0] == '-') {
        for (size_t i = 1; i < strlen(flag); i++) {
            if (flag[i] == 'e' || flag[i] == 'f') {
                *count = i + 1;
                break;
            } else if (flag[i] == 'i') {
                op->i = 1;
            } else if (flag[i] == 'v') {
                op->v = 1;
            } else if (flag[i] == 'c') {
                op->c = 1;
            } else if (flag[i] == 'l') {
                op->l = 1;
            } else if (flag[i] == 'n') {
                op->n = 1;
            } else if (flag[i] == 'h') {
                op->h = 1;
            } else if (flag[i] == 's') {
                op->s = 1;
            } else if (flag[i] == 'o') {
                op->o = 1;
            } else {
                fprintf(stderr, "grep: unknown --directories option\n");
                exit(1);
            }
        }
    }
}

void op_c(int count_file_flag, char* name, int count_match, int l, int h) {
    if (count_file_flag != 0 && h != 1) {
        printf("%s:", name);
    }
    if (l == 1 && count_match > 0) {
        count_match = 1;
    }
    printf("%d\n", count_match);
}

void find(char** buffer, char* find, option op) {
    if (strcmp(find, ".") == 0 && strcmp(*buffer, "\n") == 0 && op.v != 1) {
        strcpy(*buffer, "\0");
    }

    if (strcmp(find, "\\n") == 0) {
        strcpy(*buffer, "\0");
    }

    regex_t reg;
    int status = (op.i == 1) ? regcomp(&reg, find, REG_ICASE) : regcomp(&reg, find, 0);
    if (!status) {
        int status_find = regexec(&reg, *buffer, 0, NULL, 0);
        if (strcmp(*buffer, "\n") == 0 && strcmp(find, ".") == 0) {;
        } else if ((status_find == REG_NOMATCH && op.v == 0) || (!status_find && op.v == 1)) {
            strcpy(*buffer, "\0");
        }
    }
    regfree(&reg);
}


void patert_in_patern(char* buffer, char* search, option op, char** result, size_t* len) {
    regmatch_t math = {0};
    regex_t reg;

    int status = (op.i == 1) ? regcomp(&reg, search, REG_ICASE) : regcomp(&reg, search, 0);
    if (!status) {
        int status_find = 0;
        size_t i = 0;
        while (!status_find && i < strlen(buffer)) {
            status_find = regexec(&reg, buffer + i, 1, &math, 0);
            if (!status_find) {
                *result = realloc(*result, (*len + strlen(buffer) + 2) * sizeof(char));
                for (int j = math.rm_so; j < math.rm_eo; j++) {
                    (*result)[*len] = *(buffer + i + j);
                    *len += 1;
                }
                (*result)[*len] = '\n';
                *len += 1;
                i += math.rm_eo;
            }
        }
    }

    regfree(&reg);
}

void find_o(char** buffer, struct list* temp_list, option op, char** result, size_t* len) {
    regmatch_t math = {0};
    regex_t reg;

    int status = (op.i == 1) ? regcomp(&reg, temp_list->find, REG_ICASE) : regcomp(&reg, temp_list->find, 0);
    if (!status) {
        int status_find = 0, flag = 0;
        size_t i = 0;
        while (!status_find && i < strlen(*buffer)) {
            status_find = regexec(&reg, *buffer + i, 1, &math, 0);
            if (!status_find) {
                *result = realloc(*result, (*len + strlen(*buffer) + 2) * sizeof(char));
                for (int j = math.rm_so; j < math.rm_eo; j++) {
                    (*result)[*len] = *(*buffer + i + j);
                    *len += 1;
                }
                (*result)[*len] = '\n';
                *len += 1;
                i += math.rm_eo;
                flag = 1;

                struct list* start = temp_list->ptr;
                while (start != NULL) {
                    patert_in_patern(temp_list->find, start->find, op, result, len);
                    start = start->ptr;
                }
            } else if (flag == 1) {
                temp_list = temp_list->ptr;
                *buffer = *buffer + i;
                while (temp_list != NULL) {
                    (*result)[*len] = '\0';
                    size_t len_res = strlen(*result);
                    find_o(buffer, temp_list, op, result, len);
                    (*result)[*len] = '\0';
                    *buffer = *buffer + (strlen(*result) - len_res);
                    temp_list = temp_list->ptr;
                }
            }
        }
    }

    regfree(&reg);
}

int count_in_list_n(struct list* temp_list) {
    int count = 0;
    struct list* list = temp_list;
    while (list != NULL) {
        if (strcmp(list->find, "\n") == 0 || strcmp(list->find, ".") == 0) {
            count++;
            break;
        }
        list = list->ptr;
    }
    return count;
}

void check_struct(option op, char** buffer, struct list* temp_list, size_t* len_buf) {
    int count = 0;
    if (op.o == 1) {
        size_t len = 0;

        if (op.v == 0 && count_in_list_n(temp_list) == 0) {
            char* temp_buff = *buffer;
            char* result = (char*) malloc(sizeof(char) + 1);
            find_o(buffer, temp_list, op, &result, &len);
            result[len] = '\0';
            *len_buf = strlen(result) + 1;
            *buffer = realloc(temp_buff, (*len_buf) * sizeof(char));
            strcpy(*buffer, result);
            free(result);
        }
        count++;
    }

    if (op.v == 1 && count == 0) {
        find(buffer, temp_list->find, op);
        count++;
    }

    if (count == 0) {
        find(buffer, temp_list->find, op);
    }
}

void add_name_file(char** buffer, char* name, size_t* len) {
    char* name_file = (char*) malloc((sizeof(char) * strlen(name) + 2));
    strcpy(name_file, name);
    strcat(name_file, ":");

    char* temp_memory = NULL;
    temp_memory = s21_insert(*buffer, name_file, 0);

    *len += strlen(temp_memory);
    *buffer = realloc(*buffer, *len * sizeof(char));
    strcpy(*buffer, temp_memory);

    free(name_file);
    free(temp_memory);
}

void *s21_insert(const char *src, const char *str, size_t start_index) {
    char *buff = NULL;
    if (src != NULL && str != NULL && start_index <= strlen(src)) {
        buff = (char *) malloc((sizeof(char) * strlen(src) + strlen(str) + 1));
        if (buff != NULL) {
            strncpy(buff, src, start_index);
            strcpy(buff + start_index, str);
            strcpy(buff + start_index + strlen(str), src + start_index);
        }
    }
    return buff;
}
