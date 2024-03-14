/*
Copyright 2020-2024 plapacz6@gmail.com

This file is part of math_parser_01.

math_parser_01 is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

math_parser_01 is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with Foobar. If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef READ_AND_CALCULATE_H_INCLUDED
#define READ_AND_CALCULATE_H_INCLUDED

#include "model_of_expresson.h"

type_of_value_t read_a(argument_t *pa, char *formula, int indent);
type_of_value_t read_e(expression1_t *pe, char* formula,  int indent);
void read_la(list_of_arguments_t *pla, char* formula, int indent, argument_t** tbl_args, int n_of_args);
#endif // READ_AND_CALCULATE_H_INCLUDED
