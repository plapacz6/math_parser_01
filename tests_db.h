/*
Copyright 2020-2024 plapacz6@gmail.com

This file is part of math_parser_01.

math_parser_01 is free software: you can redistribute it and/or modify it under
the terms of the GNU Lesser General Public License as published by the Free
Software Foundation, either version 3 of the License, or (at your option) any
later version.

math_parser_01 is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more
details.

You should have received a copy of the GNU Lesser General Public License along
 with math_parser_01. If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef TESTS_DB_H
#define TESTS_DB_H
#include "model_of_expresson.h"

typedef struct test_expr_tt {
    char *f;
    char *a;
    type_of_value_t val;
    int test_result;
} test_expr_t;

extern int tests_number;
extern const test_expr_t *test_expr;


extern char* expression_test;
extern char* expression_test_math;
extern char* expression_error1;

typedef struct test_result_tt {
    int pass;
    int fail;
    int count;
} test_result_t;

extern test_result_t test_result;

#endif // TESTS_DB_H
