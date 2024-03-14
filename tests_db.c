/*
Copyright 2020-2024 plapacz6@gmail.com

This file is part of math_parser_01.

math_parser_01 is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

math_parser_01 is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with Foobar. If not, see <https://www.gnu.org/licenses/>.
*/

#include "tests_db.h"

char* expression_test = "sum(mul( -1,sum(2 ,3.98)), sum(4 ,sum(5,6) ))";  //string of expression in polish notation
char * expression_test_math = "((-1 * (2 + 3.98)) + (4 + (5 + 6)))";  //odpowiednik

char* expression_error1 = "4 sum(sum4(-1,sum(23 4 ,3)), 5sum(4 ,sum(5,6) ))";  //wrong string of expression in polish notation


// typedef struct test_expr_tt {
//   char *f;
//   char *(a;
//   type_of_value_t val;
//   int test_result;
// } test_expr_t;

#define TESTS_NUMBER (5)

int tests_number = TESTS_NUMBER;

test_result_t test_result;
test_expr_t test_expr_array[TESTS_NUMBER] = {
    {
        "sum(mul( -1,sum(2 ,3.99)), sum(4 ,sum(5,6) ))",
        "((-1 * (2 + 3.99)) + (4 + (5 + 6)))",
        9.01,
        1 //test pass
    }
    ,
    {
        "sum(mul( -1,sum(2 ,3.98)), sum(4 ,sum(5,6) ))",  //string of expression in polish notation
        "((-1 * (2 + 3.98)) + (4 + (5 + 6)))",            //odpowiedbnik
        9.02,
        1
    }
    ,
    {
        "sum(mul( -1,sum(2 ,3.97)), sum(4 ,sum(5,6) ))",
        "((-1 * (2 + 3.97)) + (4 + (5 + 6)))",
        9.03,
        1
    }
    ,
    {
        "sum(mul( -1,sum(2 ,4)), sum(4 ,sum(5,6) ))",
        "((-1 * (2 + 4)) + (4 + (5 + 6)))",
        9.00,
        1
    }
    ,
    {
        "sum(mul( -1,sum(2 ,4.01)), sum(4 ,sum(5,6) ))",
        "((-1 * (2 + 4.01)) + (4 + (5 + 6)))",
        9.01,
        0 //fail
    }
    ,
// {
// "4 sum(sum4(-1,sum(23 4 ,3)), 5sum(4 ,sum(5,6) ))",  //wrong string of expression in polish notation
// "incorrect syntax",
// 0.0,
// 0  //fail
// }
// ,
};
const test_expr_t *test_expr = test_expr_array;

