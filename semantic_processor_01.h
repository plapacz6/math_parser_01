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

#ifndef SEMANTIC_PROCESSOR_01_H_INCLUDED
#define SEMANTIC_PROCESSOR_01_H_INCLUDED

#include "semantic_processor_01.h"
#include "model_of_expresson.h"

typedef struct function_db_tt {
    char *name;
    int n_of_args;
    type_of_value_t (*pf)(argument_t** tbl_args, int n_of_args);
} function_db_t;

#define FUNCTION_DB_SIZE (8)

extern function_db_t function_db[];

void interpret_num(argument_t *parg, const char *formula);
void interpret_op(expression1_t *pex, const char* formula);

#endif // SEMANTIC_PROCESSOR_01_H_INCLUDED
