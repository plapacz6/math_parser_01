#ifndef READ_AND_CALCULATE_H_INCLUDED
#define READ_AND_CALCULATE_H_INCLUDED

/*
author: plapacz1@gmail.com; date: 2020-02-22 ;version: 0.1
*/


type_of_value_t read_a(argument_t *pa, char *formula, int indent);
type_of_value_t read_e(expression1_t *pe, char* formula,  int indent);
void read_la(list_of_arguments_t *pla, char* formula, int indent, argument_t** tbl_args, int n_of_args);
#endif // READ_AND_CALCULATE_H_INCLUDED
