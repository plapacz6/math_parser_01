/*
Copyright 2020-2024 plapacz6@gmail.com

This file is part of math_parser_01.

math_parser_01 is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

math_parser_01 is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with Foobar. If not, see <https://www.gnu.org/licenses/>.
*/

#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "semantic_processor_01.h"
#include "model_of_expresson.h"
#include "math_function_def_01.h"

#define MAX_SIZE_OF_DIGIT  (1000)
#define MAX_SIZE_OF_SYMBOL  (1000)
#define MAX_SIZE_OF_OPERATOR_NAME (1000)

//typedef struct function_db_tt {
//  char *name;
//  int n_of_args;
//  type_of_value_t (*pf)(argument_t** tbl_args, int n_of_args);
//} function_db_t;
//#define FUNCTION_DB_SIZE (8)
function_db_t function_db [FUNCTION_DB_SIZE] = {
    {"sum", 2, sum2},
    {"sum", 3, sum3},
    {"sum", 4, sum4},
    {"sub", 2, sub2},
    {"mul", 2, mul2},
    {"div", 2, div2},
    {"pow", 2, pow2},
    {"sqrt", 2, sqrt2}
};

/**
 * @brief fill in valu of number
 *
 * @param parg
 * @param formula
 */
void interpret_num(argument_t *parg, const char *formula) {
    double value_d = 0;
    char buf[MAX_SIZE_OF_DIGIT + 1];
    strncpy(buf, formula + (parg->i_start), parg->i_end - parg->i_start);
    buf[parg->i_end - parg->i_start] = 0;

    value_d = atof(buf);

    parg->val = (type_of_value_t)value_d;
}

/**
 * @brief find and fill in pointer to function which perform operation asociatted with operator
 *
 * @param pex
 * @param formula
 */
void interpret_op(expression1_t *pex, const char* formula) {
    char buf[MAX_SIZE_OF_DIGIT + 1];
    strncpy(buf, formula + (pex->i_start), pex->i_end - pex->i_start);
    buf[pex->i_end - pex->i_start] = 0;

    //find function with specified name in database of known functions
    int i;
    for(i = 0; i < FUNCTION_DB_SIZE; i++) {
        if( !strncmp(function_db[i].name, buf, strlen(buf)) &&
                function_db[i].n_of_args == pex->plarg->n_of_args) {
            //found
            pex->fn = function_db[i].pf;
            break;
        }
    }
}


