/*
author: plapacz6@gmail.com; date: 2021-02-16 ;version: 0.1
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
void interpret_num(argument_t *parg, const char *formula){
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
void interpret_op(expression1_t *pex, const char* formula){
  char buf[MAX_SIZE_OF_DIGIT + 1];
  strncpy(buf, formula + (pex->i_start), pex->i_end - pex->i_start);
  buf[pex->i_end - pex->i_start] = 0;

  //znajdz funkcje o tej nazwie w tabeli znanych funkcji
  int i;
  for(i = 0; i < FUNCTION_DB_SIZE; i++){
    if( !strncmp(function_db[i].name, buf, strlen(buf)) &&
        function_db[i].n_of_args == pex->n_of_args){
      //znaleziona
      pex->fn = function_db[i].pf;
      break;
    }
  }
  //utworzenie tablicy arg dla wywolania tej funkcji
  //utworz dynamiczn atablice o rozmiarze n_of_args
  //przeszuaj liste arg i zapisz  argument_t*
  //(lepiej w pzzyszlosci od razu pval zapisywac)
}


