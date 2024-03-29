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

#ifndef MATH_FUNCTION_DEF_01_H_INCLUDED
#define MATH_FUNCTION_DEF_01_H_INCLUDED

#include "model_of_expresson.h"

type_of_value_t sum2(argument_t** tbl_args, int n_of_args);
type_of_value_t sum3(argument_t** tbl_args, int n_of_args);
type_of_value_t sum4(argument_t** tbl_args, int n_of_args);
type_of_value_t sub2(argument_t** tbl_args, int n_of_args);
type_of_value_t mul2(argument_t** tbl_args, int n_of_args);
type_of_value_t div2(argument_t** tbl_args, int n_of_args);
type_of_value_t pow2(argument_t** tbl_args, int n_of_args);
type_of_value_t sqrt2(argument_t** tbl_args, int n_of_args);

#endif // MATH_FUNCTION_DEF_01_H_INCLUDED
