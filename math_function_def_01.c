#include <math.h>
#include "math_function_def_01.h"
/*
author: plapacz1@gmail.com; date: 2020- ;version: 0.1
*/
type_of_value_t sum2(argument_t** tbl_args, int n_of_args){
  type_of_value_t value = 0;
  int i;
  for(i = 0; i < n_of_args; i++){
    value += tbl_args[i]->val;
  }
  return value;
}
type_of_value_t sum3(argument_t** tbl_args, int n_of_args){
  type_of_value_t value = 0;
  int i;
  for(i = 0; i < n_of_args; i++){
    value += tbl_args[i]->val;
  }
  return value;
}
type_of_value_t sum4(argument_t** tbl_args, int n_of_args){
  type_of_value_t value = 0;
  int i;
  for(i = 0; i < n_of_args; i++){
    value += tbl_args[i]->val;
  }
  return value;
}
type_of_value_t sub2(argument_t** tbl_args, int n_of_args){
  type_of_value_t value = 0;
  value += tbl_args[0]->val - tbl_args[1]->val;
  return value;
}
type_of_value_t mul2(argument_t** tbl_args, int n_of_args){
  type_of_value_t value = 0;
  value += tbl_args[0]->val * tbl_args[1]->val;
  return value;
}
type_of_value_t div2(argument_t** tbl_args, int n_of_args){
  type_of_value_t value = 0;
  if(tbl_args[1]->val != 0){
    value += tbl_args[0]->val / tbl_args[1]->val;
    return value;
  }
  else {
    return 0; //TODO
  }
}
type_of_value_t pow2(argument_t** tbl_args, int n_of_args){
  type_of_value_t value = 0;
  value += tbl_args[0]->val * tbl_args[1]->val;
  return value;
}
type_of_value_t sqrt2(argument_t** tbl_args, int n_of_args){
  type_of_value_t value = 0;
  value += tbl_args[0]->val * tbl_args[1]->val;
  return value;
}

