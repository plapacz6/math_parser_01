#ifdef MODEL_OF_EXPRESSON_2
/*
author: plapacz1@gmail.com; date: 2020-11-26 ;version: 0.1
*/
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "parse_expr_02.h"
#include "complex_expression.h"
#include "parser_debug.h"
/* -------------- logic of syntax ----------------- */
typedef enum syntax_state_tt {
  st1_begining,
  st2_name,
  st3_la,
  st4_digit,
  st5_sp_afer_sp,
  st6_end,
} syntax_state_t;


typedef struct parser02_state_tt{
  int i_start;
  int i_end;
  syntax_state_t curr_state;
  int i_curr;
  bool syntax_error;

/* -------------- logic of expression tree ----------------- */
  int level;
  expression1_t *first_expr;
  expression1_t *curr_expr;
  list_of_arguments_t *curr_al;
  argument_t *curr_arg;
  //type_of_token_t token_type;
  bool expr_tree_complete;
} parser02_state_t;

parser02_state_t p2st;

#define DEBUG_PRN
#ifdef DEBUG_PRN
#define PR_N(P,W,S,E) \
  {char prn_buff[100]; \
  strncpy(prn_buff, W + S, (E - S)+1); \
  prn_buff[E - S + 1] = 0; \
  printf("level %d: %s\n", P.level, prn_buff);}
#else
  #define PR_N(W,S,E)
#endif // DEBUG_PRN

/** start tracking name of operator or digit
*/
static void strN_start(){
  p2st.i_start = p2st.i_curr;
}
/** stop tracking name or digit and store information of it
*/
void strN_stop(){
  p2st.i_end = p2st.i_curr - 1;
}
/** start tracking name of operator or digit
*/
static void strD_start(){
  p2st.i_start = p2st.i_curr;
}
/** stop tracking name or digit and store information of it
*/
static void strD_stop(){
  p2st.i_end = p2st.i_curr - 1;
  //inne przetworzenia nazwy/liczby
}

/** create and switch to new level of expression
*/
static void open_new_expr(){
  expression1_t *tmp = p2st.curr_expr;
  p2st.level++;
  p2st.curr_expr = malloc(sizeof(expression1_t));
  p2st.curr_expr->parent = tmp;
  if(p2st.curr_arg != NULL){
    p2st.curr_arg->calc = p2st.curr_expr;
  }
  p2st.curr_expr->i_start = p2st.i_start;
  p2st.curr_expr->i_end = p2st.i_end;
}
/** create and open new arg list
*/
static void open_new_arg_list(){
  p2st.curr_expr->plarg = list_of_arguments_create();
  p2st.curr_al = p2st.curr_expr->plarg;
}
/** create new argument, and set it as curr
*/
static void open_new_arg(){
  argument_t *arg = malloc(sizeof(argument_t));
  arg->pval = &arg->val;
  p2st.curr_arg = arg;
  list_of_arguments_add(p2st.curr_al, arg);
}
static void open_digit(){
}
static void close_digit(){
  p2st.curr_arg->calc = NULL;
}
static void open_symbol(){
}
static void close_symbol(){
}
/** processes closeing argument procedure
*/
static void close_arg(){
  p2st.curr_arg->i_start = p2st.i_start;
  p2st.curr_arg->i_end = p2st.i_end;
  //PR(p2st.curr_arg->i_start);
  //PR(p2st.curr_arg->i_end);

}
/** processes closing argument list procedure
*/
static void close_arg_list(){
  //number of arguments is final
}
/** close expression and return to lower level's expression
*/
static expression1_t* close_expr() {
  expression1_t *tmp;
  p2st.curr_expr->n_of_args = p2st.curr_al->n_of_args;
  //znajdz funkcje realizujaca operator (nazwa + liczba arg)
  //p2st.curr_expr->fn = funkcja((p2st.curr_expr->i_start, p2st.curr_expr->i_end), p2st.curr_expr->n_of_args)
  tmp = p2st.curr_expr->parent;
  p2st.curr_expr = p2st.curr_expr->parent;
  p2st.level--;
  p2st.curr_al = p2st.curr_expr->plarg;
  p2st.curr_arg = p2st.curr_al->last->el;
  return tmp;
}
#define case_AZ  \
case'a': case 'b': case 'c': case 'd': case 'e': case 'f': case 'g': \
case 'h': case 'i': case 'j': case 'k': case 'l': case 'm': case 'n': \
case 'o': case 'p': case 'r': case 'q': case 's': case 't': case 'u': \
case 'w': case 'x': case 'y': case 'z'
#define case_09 \
case '0': case '1': case '2': case '3': case '4': case '5': \
case '6': case '7': case '8': case '9'

expression1_t *parse_expr_02(char *expr){
  p2st.level = 0;
  p2st.curr_expr = NULL;
  p2st.curr_al = NULL;
  p2st.curr_arg = NULL;

  syntax_state_t sstate = st1_begining;
  char c;
  int i;
  puts(expr);
  for(i = 0; (c = expr[i]) != '\0'; i++){
    //PR(c)
    //PR(sstate)
    p2st.curr_state = sstate;
    p2st.i_curr = i;
    switch(sstate){
      case st1_begining:
        switch(c){
          case ' ':
            break;
          case_AZ:
            if(p2st.curr_arg != NULL){
              p2st.curr_arg->token_type = tot_name;
            }
            strN_start();
            //open_new_expr();
            sstate = st2_name;
            break;
        }
        break;
      case st2_name:
        switch(c){
          case_AZ:
            break;
          case ',':
            p2st.curr_arg->token_type = tot_symbol;
            strN_stop();
            close_symbol();
            close_arg();
            PR_N(p2st, expr, p2st.curr_arg->i_start, p2st.curr_arg->i_end);
            sstate = st3_la;
            break;
          case ' ':
            p2st.curr_arg->token_type = tot_symbol;
            strN_stop();
            close_symbol();
            sstate = st5_sp_afer_sp;
          case '(':
            if(p2st.curr_arg != NULL){
              p2st.curr_arg->token_type = tot_name_of_operator;
            }
            strN_stop();
            open_new_expr();
            PR_N(p2st, expr, p2st.curr_expr->i_start, p2st.curr_expr->i_end);
            open_new_arg_list();
            sstate = st3_la;
            break;
        }
        break;
      case st3_la:
        switch(c){
          case ' ':
            break;
          case_09: case '+': case '-':
            open_new_arg();
            p2st.curr_arg->token_type = tot_digit;
            strD_start();
            open_digit();
            sstate = st4_digit;
            break;
          case_AZ:
            open_new_arg();
            p2st.curr_arg->token_type = tot_name;
            strN_start();
            sstate = st2_name;
            break;
          case ',':
            //empty arg
            break;
          case ')':
            switch(p2st.curr_arg->token_type) {
              case tot_digit:
                strD_stop();
                close_digit();
                break;
              case tot_name:
                strN_stop();
                //TODO
                break;
              case tot_symbol:
                strN_stop();
                //TODO
                break;
              case tot_name_of_operator:
                //processing during closing whole expression of curr level
                break;
            }
            /*
            typ argumentu musi być zapisany w argumencie, bo  po zamknieciu
            poziomu nie wiadomo jakoego typu jest ostatni argument poziomu
            niższego.
            Może to rozwiaże właczanie dwóch nawiasów do wyrązenia (liczby).
            */
            close_arg();
            PR_N(p2st, expr, p2st.curr_arg->i_start, p2st.curr_arg->i_end);
            close_arg_list();
            close_expr();
            if(p2st.level == 0) p2st.expr_tree_complete = true;
            sstate = st6_end;
            break;
        }
        break;
      case st4_digit:
        switch(c){
          case_09: case '.':
            break;
          case ' ':
            strD_stop();
            close_digit();
            sstate = st5_sp_afer_sp;
            break;
          case ',':
            strD_stop();
            close_digit();
            close_arg();
            PR_N(p2st, expr, p2st.curr_arg->i_start, p2st.curr_arg->i_end);
            sstate = st3_la;
            break;
        }
        break;
      case st5_sp_afer_sp:
        switch(c){
          case ' ':
            break;
          case ',':
            close_arg();
            PR_N(p2st, expr, p2st.curr_arg->i_start, p2st.curr_arg->i_end);
            sstate = st3_la;
            break;
        }
        break;
      case st6_end:
        if(p2st.expr_tree_complete) return p2st.curr_expr;
        break;
    }//case
  }//for
  return p2st.curr_expr;
}




#endif // MODEL_OF_EXPRESSON_2
