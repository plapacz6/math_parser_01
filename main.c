#include <stdio.h>
#include <stdlib.h>
#include "model_of_expresson.h"
//#include "parse_expr_01.h"
//#include "parse_expr_02.h"
#include "parse_expr_04.h"
#include "parser_debug.h"
#include "read_and_calculate.h"
#include "semantic_processor_01.h"



char* expression_test = "sum(mul( -1,sum(2 ,3.98)), sum(4 ,sum(5,6) ))";  //string of expression in polish notation
char * expression_test_math = "((-1 * (2 + 3.98)) + (4 + (5 + 6)))";  //odpowiedbnik

char* expression_error1 = "4 sum(sum4(-1,sum(23 4 ,3)), 5sum(4 ,sum(5,6) ))";  //wrong string of expression in polish notation

int main(int argc, char** argv)
{
  char bufor[1000];
  char *formula;
  char *formula_math;
  int i;
    if(argc > 1) {
      printf("formula musi byc w postaci: \n%s\n", expression_test);
      for(i = 0; i < FUNCTION_DB_SIZE; i++) {
        printf("%s\n", function_db[i].name);
      }
      puts(":\n");
      fgets(bufor, 999, stdin);
      formula = bufor;
      formula_math = "";
    }
    else {
      formula = expression_test;
      formula_math = expression_test_math;
    }
    type_of_value_t val;
    //expression1_t *pexpr = expression_read(expression_test);
    expression1_t *pexpr = parse_expr4(formula);
    //expression_read(expression_error1);
    //printf("Hello world! %p\n", pexpr);
    puts("---------------------");
    display_e(pexpr, 0);

    val = read_e(pexpr, expression_test, 0);
    printf("wartosc == %f\n", val);

    puts("---------------------");
    printf("%s\n", "TO BYLO OBLICZANIE:");
    printf("%s\n", "notacja polska:");
    printf("%s\n", formula);
    printf("%s\n", "zapis tradycyjny:");
    printf("%s\n", formula_math);
    puts("---------------------");

    return 0;
}
