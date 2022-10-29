//  Copyright rosanabr 2022
#include "s21_cat.h"

int main(int argc, char *argv[]) {
    FILE* fd_in;
    option op = {0};
    int flag = 0;

    for (int i = 1; i < argc; i++) {
        int count = 0;
        if (flag == 0) {
            count = define_struct(argv[i], &op);
        }
        char *buffer = NULL;
        size_t len = 0;
        if (count == 0) {
            fd_in = fopen(argv[i], "r");
            if (fd_in) {
                int count_line = 0;
                int count_read = 1;
                while (!feof(fd_in) && count_read > 0) {
                    count_read = getline(&buffer, &len, fd_in);
                    if (count_read != -1) {
                        check_struct(op, &buffer, fd_in,
                                     &count_line, &len, &count_read);
                    }

                    for (int j = 0; j < count_read; j++) {
                        printf("%c", buffer[j]);
                    }
                }
                free(buffer);
                fclose(fd_in);
            } else {
                fprintf(stderr, "cat: %s: No such file or directory\n", argv[i]);
            }
            flag = 1;
        }
    }
    return 0;
}

int define_struct(char* flag, option* op) {
    int count = 0;
    if (flag && flag[0] == '-' && flag[1] == '-') {
        if (strcmp(flag, "--number-nonblank") == 0) {
            op->b = 1;
        } else if (strcmp(flag, "--number") == 0) {
            op->n = 1;
        } else if (strcmp(flag, "--squeeze-blank") == 0) {
            op->s = 1;
        }
        count++;
    } else if (flag && flag[0] == '-') {
        for (size_t i = 0; i < strlen(flag); i++) {
            if (flag[i] == 'b') {
                op->b = 1;
            } else if (flag[i] == 'e' || flag[i] == 'E') {
                op->e = (flag[i] == 'e') ? 1 : 2;
            } else if (flag[i] == 'n') {
                op->n = 1;
            } else if (flag[i] == 's') {
                op->s = 1;
            } else if (flag[i] == 't' || flag[i] == 'T') {
                op->t = (flag[i] == 't') ? 1 : 2;
            } else if (flag[i] == 'v') {
                op->v = 1;
            }
        }
        count++;
    }

    return count;
}

void numeration_line(int count_lines, char** buffer,
                        size_t* len, int count_read) {
    char str_count[100];
    sprintf(str_count, "%6d\t", count_lines);
    *len += (count_read + 7);
    *buffer = realloc(*buffer, *len * sizeof(char));

    char* temp = (char*)malloc(sizeof(char) * count_read + 1);
    for (int j = 0; j < count_read; j++) {
        temp[j] = (*buffer)[j];
    }

    for (int j = 0; j < (count_read + 7); j++) {
        if (j < 7) {
            (*buffer)[j] = str_count[j];
        } else {
            (*buffer)[j] = temp[j - 7];
        }
    }
    free(temp);
}

void op_v(char** buffer, size_t* len, int* count_read) {
    size_t i = 0, j = 0;

    char* temp = (char*)malloc(sizeof(char) * (*count_read) * 2 + 1);
    while ((int) i < *count_read) {
        if ((*buffer)[i] != '\n' && (*buffer)[i] >= 0 && (*buffer)[i] <= 31
                                                && (*buffer)[i] != '\t') {
            temp[j] = '^';
            temp[j + 1] = (*buffer)[i] + 64;
            j += 2;
        } else if ((*buffer)[i] == 127) {
            temp[j] = '^';
            temp[j + 1] = 63;
            j += 2;
        } else {
            temp[j] = (*buffer)[i];
            j++;
        }
        i++;
    }

    temp[j] = '\0';
    *count_read = j;
    *len += strlen(temp);
    *buffer = realloc(*buffer, *len * sizeof(char));
    strcpy(*buffer, temp);
    free(temp);
}

void op_b(char** buffer, int* i, size_t* len, int* count_read) {
    if (strcmp(*buffer, "\n") != 0) {
        (*i)++;
        numeration_line(*i, buffer, len, *count_read);
        *count_read += 7;
    }
}

void op_n(char** buffer, int* i, size_t* len, int* count_read) {
    (*i)++;
    numeration_line(*i, buffer, len, *count_read);
    *count_read += 7;
}

void op_e(char** buffer, size_t* len, option op, int* count_read) {
    char* temp = (char*)malloc(sizeof(char) * (*count_read) + 2);
    if ((*buffer)[*count_read - 1] == '\n') {
        int j;
        for (j = 0; j < *count_read - 1; j++) {
            temp[j] = (*buffer)[j];
        }
        temp[j] = '$';
        temp[j + 1] = '\n';
        temp[j + 2] = '\0';
        if (*len < (size_t)*count_read + 1) {
            *len = *count_read + 1;
            *buffer = realloc(*buffer, *len * sizeof(char));
        }
        for (int i = 0; i < *count_read + 2; i++) {
            (*buffer)[i] = temp[i];
        }
        *count_read += 1;
    }
    free(temp);

    if (op.e == 1) {
        op_v(buffer, len, count_read);
    }
}

void op_t(char** buffer, size_t* len, option op, int* count_read) {
    size_t i = 0, j = 0;
    char* temp = (char*)malloc(sizeof(char) * (*count_read) * 2 + 1);
    while ((int)i < *count_read) {
        if ((*buffer)[i] == '\t') {
            temp[j] = '^';
            temp[j + 1] = 'I';
            j += 2;
        } else {
            temp[j] = (*buffer)[i];
            j++;
        }
        i++;
    }

    if ((int)i == *count_read) {
        temp[j] = '\0';
    }

    *len += j;
    *buffer = realloc(*buffer, *len * sizeof(char));
    for (size_t k = 0; k < j; k++) {
        (*buffer)[k] = temp[k];
    }
    *count_read = j;
    if (op.t == 1) {
        op_v(buffer, len, count_read);
    }
    free(temp);
}

void op_s(char** buffer, FILE* fd_in, size_t* len, int* count_read) {
    if (strcmp(*buffer, "\n") == 0) {
        while (!feof(fd_in) && strcmp(*buffer, "\n") == 0) {
            *count_read = getline(buffer, len, fd_in);
        }
        fseek(fd_in, -(*count_read) - 1, SEEK_CUR);
        *count_read = getline(buffer, len, fd_in);
        if (*count_read < 0) {
            strcpy(*buffer, "\n");
            *count_read = 1;
        }
    }
}

void check_struct(option op, char** buffer, FILE* fd_in, int* count_line,
                            size_t* len, int* count_read) {
    if (op.s == 1)
        op_s(buffer, fd_in, len, count_read);
    if (op.t >= 1)
        op_t(buffer, len, op, count_read);

    if (op.b == 1) {
        op_b(buffer, count_line, len, count_read);
    } else if (op.n == 1) {
         op_n(buffer, count_line, len, count_read);
    }

    if (op.e >= 1)
        op_e(buffer, len, op, count_read);

    if (op.v >= 1)
        op_v(buffer, len, count_read);
}
