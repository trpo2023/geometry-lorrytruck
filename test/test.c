#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../src/libgeometry/check.h"
#include "../thirdparty/ctest.h"

#define _USE_MATH_DEFINES

CTEST(input_check, str_correct)
{
    char* a = "circle(9 1, 2)";
    char* b = "circle";
    int error = 0;
    int expected = 0;
    check_str(a, b, &error);
    int real = error;

    ASSERT_EQUAL(expected, real);
}

CTEST(input_check, str_error)
{
    char* a = "cittcke(2 4, 7)";
    char* b = "circle";
    int error = 0;
    int expected = 1;
    check_str(a, b, &error);
    int real = error;

    ASSERT_EQUAL(expected, real);
}

CTEST(input_check, open_bracket_correct)
{
    char* a = "circle(9 1, 2)";
    char* b = "circle";
    int error = 0;
    int expected = 0;
    check_str(a, b, &error);
    int real = error;

    ASSERT_EQUAL(expected, real);
}

CTEST(input_check, open_bracket_error)
{
    char* a = "circle9 1, 2)";
    char* b = "circle";
    int error = 0;
    int expected = 0;
    check_str(a, b, &error);
    int real = error;

    ASSERT_EQUAL(expected, real);
}

CTEST(input_check, find_close_bracket_correct)
{
    char* a = "circle(9 1, 2)";
    int l = 14;
    int expected = 13;
    int real = check_find_close_bracket(a, &l);

    ASSERT_EQUAL(expected, real);
}

CTEST(input_check, find_close_bracket_error)
{
    char* a = "circle(9 1, 2 ";
    int l = 13;
    int expected = 0;
    int real = check_find_close_bracket(a, &l);

    ASSERT_EQUAL(expected, real);
}

CTEST(input_check, first_num_correct)
{
    char* a = "circle(9 1, 2)";
    int open_bracket = 6;
    int error = 0;
    int expected = 7;
    int real = check_first_num(a, &open_bracket, &error);

    ASSERT_EQUAL(expected, real);
}

CTEST(input_check, first_num_error)
{
    char* a = "circle(M 1, 2)";
    int open_bracket = 6;
    int error = 0;
    int expected = 1;
    check_first_num(a, &open_bracket, &error);
    int real = error;

    ASSERT_EQUAL(expected, real);
}

CTEST(input_check, second_num_correct)
{
    char* a = "circle(9 1, 2)";
    int first_num_elm = 7;
    int error = 0;
    int expected = 9;
    int real = check_second_num(a, &first_num_elm, &error);

    ASSERT_EQUAL(expected, real);
}

CTEST(input_check, second_num_error)
{
    char* a = "circle(9 w, 2)";
    int first_num_elm = 7;
    int error = 0;
    int expected = 1;
    check_second_num(a, &first_num_elm, &error);
    int real = error;

    ASSERT_EQUAL(expected, real);
}

CTEST(input_check, last_num_correct)
{
    char* a = "circle(9 1, 2)";
    int second_num_elm = 9;
    int close_bracket = 13;
    int error = 0;
    int expected = 12;
    int real = check_last_num(a, &second_num_elm, &close_bracket, &error);

    ASSERT_EQUAL(expected, real);
}

CTEST(input_check, last_num_error)
{
    char* a = "circle(9 1, s)";
    int second_num_elm = 9;
    int close_bracket = 13;
    int error = 0;
    int expected = 1;
    check_last_num(a, &second_num_elm, &close_bracket, &error);
    int real = error;

    ASSERT_EQUAL(expected, real);
}

CTEST(input_check, close_bracket_correct)
{
    char* a = "circle(9 1, 2)";
    int last_num_elm = 12;
    int l = 14;
    int error = 0;
    int expected = 13;
    int real = check_close_bracket(a, &l, &last_num_elm, &error);

    ASSERT_EQUAL(expected, real);
}

CTEST(input_check, close_bracket_error)
{
    char* a = "circle(9 1, 2l";
    int last_num_elm = 12;
    int l = 14;
    int error = 0;
    int expected = 1;
    check_close_bracket(a, &l, &last_num_elm, &error);
    int real = error;

    ASSERT_EQUAL(expected, real);
}

CTEST(input_check, unexp_token_correct)
{
    char* a = "circle(9 1, 2)";
    int l = 14;
    int close_bracket = 13;
    int error = 0;
    int expec = 0;
    int real = check_unexp_token(a, &l, &close_bracket, &error);

    ASSERT_EQUAL(expec, real);
}

CTEST(input_check, unexp_token_error)
{
    char* a = "circle(9 1, 2)hq";
    int l = 16;
    int close_bracket = 13;
    int error = 0;
    int expec = 1;
    check_unexp_token(a, &l, &close_bracket, &error);
    int real = error;

    ASSERT_EQUAL(expec, real);
}