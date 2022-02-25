#ifndef SEMANTIC_PROCESSOR_01_H_INCLUDED
#define SEMANTIC_PROCESSOR_01_H_INCLUDED
/*
author: plapacz1@gmail.com; date: 2021-02-16 ;version: 0.1
*/
#include "semantic_processor_01.h"
#include "model_of_expresson.h"

typedef struct function_db_tt {
  char *name;
  int n_of_args;
  type_of_value_t (*pf)(argument_t** tbl_args, int n_of_args);
} function_db_t;

#define FUNCTION_DB_SIZE (8)

extern function_db_t function_db[];

void interpret_num(argument_t *parg, char *formula);
void interpret_op(expression1_t *pex, char* formula);

#endif // SEMANTIC_PROCESSOR_01_H_INCLUDED
