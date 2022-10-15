#ifndef PARSER_DEBUG_H_INCLUDED
#define PARSER_DEBUG_H_INCLUDED
/*
author: plapacz6@gmail.com; date:  2020-09-22 ;version: 0.1
*/
#include "model_of_expresson.h"
#ifdef DEBUG_
  #include <stdio.h>
  #define PR(X) printf("%s == %x : %c : %i\n", #X, (X), (X), (X));
#else
  #define PR(X)
#endif


#ifdef DEBUG1
  #include <stdio.h>
  #define PRINTF1_DEBUG1(x) printf("[%c] - %s\n", c, (x))
#else
  #define PRINTF1_DEBUG1(x)
#endif // DEBUG1
#ifdef DEBUG2
  #include <stdio.h>
  #define PRINTF2_DEGUG2(X, Y) \
            print_expresion1_t(X, Y); \
            if(X->plarg != NULL) {\
              print_list_of_arguments_t(X->plarg, Y); \
              if(X->plarg->curr != NULL) \
                print_argument_t(X->plarg->curr->el, Y);  \
            } \

#else
  #define PRINTF2_DEGUG2(X,Y)
#endif // DEBUG2
#ifdef DEBUG3
  #include <stdio.h>
  #define PRINTF2_DEGUG3(X, Y) \
            if(X != NULL){ \
            print_expresion1_t(X, Y); \
            if(X->plarg != NULL) {\
              print_list_of_arguments_t(X->plarg, ""); \
              if(X->plarg->curr != NULL) \
                print_argument_t(X->plarg->curr->el, "");  \
            }} \

#else
  #define PRINTF2_DEGUG3(X,Y)
#endif // DEBUG3


void print_argument_t(argument_t* pa, char* comment);
void print_list_of_arguments_t(list_of_arguments_t* pla, char *comment);
void print_expresion1_t(expression1_t *pe, char *comment);

void display_a(argument_t *pa, int indent);
void display_e(expression1_t *pe, int indent);
void display_la(list_of_arguments_t *pla, int indent);

#endif // PARSER_DEBUG_H_INCLUDED
