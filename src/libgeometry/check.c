#include "check.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_str(char* a, char* b, int* error)
{
    int open_bracket = 0;
    for (int i = 0; i < 7; i++) {
        if (a[i] != b[i] && i < 6) {
            printf("Error at column %d: expected 'circle'\n", i);
            *error = 1;
            break;
            ;
        }
        open_bracket = i;
    }
    return open_bracket;
}

int check_find_close_bracket(char* a, int* l)
{
    int close_bracket = 0;
    for (int i = 0; i < *l; i++) {
        if (a[i] == ')') {
            close_bracket = i;
        }
    }
    return close_bracket;
}

int check_first_num(char* a, int* open_bracket, int* error)
{
    int first_num_elm = 0;
    for (int i = *open_bracket + 1; a[i] != ' '; i++) {
        if (*error == 0) {
            if (a[i] == ',') {
                *error = 1;
                printf("Error at column %d: expected '<space>' and "
                       "'<double>'\n",
                       i);
                break;
            }
            if (isdigit(a[i]) == 0 && a[i] != '.') {
                *error = 1;
                printf("Error at column %d: expected '<double>'\n", i);
                break;
            }
            first_num_elm = i;
        } else {
            break;
        }
    }
    return first_num_elm;
}

int check_second_num(char* a, int* first_num_elm, int* error)
{
    int second_num_elm = 0;
    for (int i = *first_num_elm + 2; a[i] != ','; i++) {
        if (*error == 0) {
            if (a[i] == ')') {
                *error = 1;
                printf("Error at column %d: expected ',' and '<double>'\n", i);
                break;
            }
            if (isdigit(a[i]) == 0 && a[i] != '.') {
                *error = 1;
                printf("Error at column %d: expected '<double>'\n", i);
                break;
            }
            second_num_elm = i;
        } else {
            break;
        }
    }
    return second_num_elm;
}

int check_last_num(char* a, int* second_num_elm, int* close_bracket, int* error)
{
    int last_num_elm = 0;
    for (int i = *second_num_elm + 3; i < *close_bracket; i++) {
        if (*error == 0) {
            if ((isdigit(a[i]) == 0 && a[i] != '.') || a[i] == '0') {
                if (a[i] == ')' || a[i] == '(' || a[i] == ' ') {
                    break;
                }
                *error = 1;
                printf("Error at column %d: expected '<double>'\n", i);
                break;
            }
            last_num_elm = i;
        } else {
            break;
        }
    }
    return last_num_elm;
}

int check_close_bracket(char* a, int* l, int* last_num_elm, int* error)
{
    int close_bracket = 0;
    for (int i = *last_num_elm + 1; i < *l; i++) {
        if (*error == 0) {
            if (a[i] != ')') {
                *error = 1;
                printf("Error at column %d: expected ')'\n", i);
                break;
            } else {
                close_bracket = i;
                break;
            }
        } else {
            break;
        }
    }
    return close_bracket;
}

int check_unexp_token(char* a, int* l, int* close_bracket, int* error)
{
    for (int i = *close_bracket + 1; i < *l; i++) {
        if (*error == 0) {
            if (a[i] == '\n') {
                break;
            }

            if (a[i] != ' ') {
                *error = 1;
                printf("Error at column %d: unexpected token\n", i);
                break;
            }
        } else {
            break;
        }
    }
    return *error;
}