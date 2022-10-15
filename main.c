#include <stdio.h>
#include <stdlib.h>
#include "model_of_expresson.h"
//#include "parse_expr_01.h"
//#include "parse_expr_02.h"
#include "parse_expr_04.h"
#include "parser_debug.h"
#include "read_and_calculate.h"
#include "semantic_processor_01.h"

#include "tests_db.h"

#define TEST_AUTO_ON


#define CLI_ARG_BUFF_SIZE (999)
typedef enum auto_test_switch_tt{
  AUTO_TEST_OFF,
  AUTO_TEST_ON,
} auto_test_switch_t;


int main(int argc, char** argv)
{
  auto_test_switch_t test = AUTO_TEST_OFF;
  char bufor[1000];
  char *formula;
  char *formula_math;
  int i;

    if(argc > 1) {
      printf("formula must be in form: \n%s\n", expression_test);
      for(i = 0; i < FUNCTION_DB_SIZE; i++) {
        printf("%s\n", function_db[i].name);
      }
      puts(":\n");
      fgets(bufor, CLI_ARG_BUFF_SIZE, stdin);
      formula = bufor;
      formula_math = "";
    }
    else {
      #ifdef TEST_AUTO_ON
      test = AUTO_TEST_ON;    
      #elif
      test = AUTO_TEST_OFF;    
      #endif
    }


    type_of_value_t val;
    //expression1_t *pexpr = expression_read(expression_test);
        
    if(test == AUTO_TEST_OFF){
      formula = expression_test;
      formula_math = expression_test_math;

      
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
    }
    else {  //AUTO_TEST_ON
      
      int j = 0;
      for(j = 0; j < tests_number; j++){
      
        
        expression1_t *pexpr = parse_expr4(test_expr[j].f);
        val = read_e(pexpr, test_expr[j].a, 0);

        test_result.count++;
        if( val == test_expr[j].val) {
          test_result.pass++;
        }
        else{
          test_result.fail++;
          printf("%s:\n","TEST FAIL");
          printf("formula:\n%s\n", test_expr[j].f);
          printf("algebraic:\n%s\n", test_expr[j].a);          
          printf("value:\n%f\n", (double)val);          
        }
        

      }
      printf("test pass: %i\n", test_result.pass);
      printf("test fail: %i\n", test_result.fail);
      printf("%s\n", "");
    }    
     
    return 0;
}
