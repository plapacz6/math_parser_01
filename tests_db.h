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
