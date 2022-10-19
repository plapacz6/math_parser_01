/*
author: plapacz6@gmail.com; date: 2020- ;version: 0.1
*/
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include "model_of_expresson.h"
#include "parse_expr_04.h"
#include "parser_debug.h"
#include "semantic_processor_01.h"
#include "error_handling.h"



/* -------------- logic of syntax ----------------- */
typedef enum syntax_state_tt {
  //st1_begining,
  st2_name,
  st3_la,
  st4_digit,
  st5_sp_afer_sp,
  st6_end,
} syntax_state_t;



typedef struct parser04_state_tt{
  const char *formula;  /**<  stringZ  analyzed formula */  
  int i_start;    /**<  index of currently analyzed part of formula */
  int i_end;
  int i_curr;     /**<   ???  */  

  syntax_state_t curr_state;    /**<  state machine   current state */
  bool syntax_error;            /**< flag if error occured */
/* -------------- logic of expression tree ----------------- */
  
  int level;  /**<TODO:    DEBUG, NECCESSARY, OR INFO ONLY ??? */
  
  list_of_arguments_t *first_al; /**<  pointer to first arg list on which expression is mounted in 1st arg */
  expression1_t *curr_op;       /**<   pointer to expression being currenly analyzed */
  list_of_arguments_t *curr_al; /**<   pointer to list of arguments  currently  analyzed expression */
  argument_t *curr_arg;         /**<   pointer to currently reading argument */
  bool curr_arg_closed;         /**<   flag if analyze of currently reading argument is done */
  bool expr_tree_complete;      /**<   tree growing from current expression is already processed */
} parser04_state_t;



parser04_state_t parser_state, *ptr_parser_state = &parser_state;


/**
 * @brief free() all created object (expression, armgument, arguments' list)
 * 
 */
void parser04_free(){
  if(ptr_parser_state->curr_al != NULL){
    list_of_arguments_release(ptr_parser_state->first_al);
  }
}
void parser04_state_reset(){
  parser04_state_t* ps = ptr_parser_state;
  parser04_free();
  ps->formula = NULL;
  ps->i_start = 0;
  ps->i_end = 0;
  ps->i_curr = 0;
  ps->curr_state = st3_la;     
  ps->syntax_error = false;
  ps->level = 0;  
  ps->curr_op = NULL;   
  ps->first_al = NULL;  
  ps->curr_al = NULL;
  ps->curr_arg = NULL;
  ps->curr_arg_closed = NULL;
  ps->expr_tree_complete = false;
}




#ifdef DEBUG_PRN
#define PR_N(P,W,S,E) \
  {char prn_buff[100]; \
  strncpy(prn_buff, W + S, (E - S)); \
  prn_buff[E - S] = 0; \
  printf("level %d: %s\n", P->curr_op->ptr_this_as_arg_in_parent->level, prn_buff);}
  //printf("level %d: %s\n", P->level, prn_buff);}
#else
  #define PR_N(P,W,S,E)
#endif // DEBUG_PRN




#define PR_2(P,W,S,E) \
  {char prn_buff[100]; \
  strncpy(prn_buff, W + S, (E - S)); \
  prn_buff[E - S] = 0; \
  printf("level %d: %s\n", P->curr_op->ptr_this_as_arg_in_parent->level, prn_buff);}



/**
 * @brief open/close of analyze current letter of formula
 * 
 */
void o_s(){
  ptr_parser_state->i_start = ptr_parser_state->i_curr;
}
void c_s(){
  ptr_parser_state->i_end = ptr_parser_state->i_curr;
}



void o_arg(){
  argument_t *arg = malloc(sizeof(argument_t));
  if(arg == NULL) PERROR_MALLOC("o_arg() - can't open new argument");

  arg->pval = &arg->val;
  arg->i_start = ptr_parser_state->i_curr;
  list_of_arguments_add(ptr_parser_state->curr_al, arg);

  ptr_parser_state->curr_arg = arg;
  assert(ptr_parser_state->curr_arg == ptr_parser_state->curr_al->last->el);
  assert(ptr_parser_state->curr_arg == ptr_parser_state->curr_al->curr->el);
  ptr_parser_state->curr_arg_closed = false;
}
void c_arg(){
  //ptr_parser_state->curr_arg->i_start = ptr_parser_state->i_start;
  ptr_parser_state->curr_arg->i_end = ptr_parser_state->i_curr;;
  //ptr_parser_state->i_start = ptr_parser_state->i_end = 0;
  if(ptr_parser_state->curr_arg->token_type == tot_digit){
    interpret_num(ptr_parser_state->curr_arg, ptr_parser_state->formula);
  }
  ptr_parser_state->curr_arg_closed = true;
  return;
}
void s_arg_type(type_of_token_t t){
  assert(ptr_parser_state->curr_arg != NULL);
  ptr_parser_state->curr_arg->token_type = t;
}



#ifdef DEBUG_LEVEL
void o_al(int level){
#else 
void o_al(){
#endif // DEBUG_LEVEL  

  #ifdef DEBUG_LEVEL
    /*!!! level is incremented (if neccecary) outside (before call) this function*/
    list_of_arguments_t* new_al = list_of_arguments_create(level);
  #else 
    list_of_arguments_t* new_al = list_of_arguments_create();
  #endif // DEBUG_LEVEL  
  if(new_al == NULL) PERROR_MALLOC("o_al - can't create new arguents list");

  new_al->n_of_args = 0;
  new_al->curr = NULL;
  new_al->first = NULL;
  new_al->last = NULL;
  
  ptr_parser_state->curr_al = new_al;  
  if(ptr_parser_state->first_al == NULL)
    ptr_parser_state->first_al = ptr_parser_state->curr_al;

  if(ptr_parser_state->curr_op != NULL){
    ptr_parser_state->curr_op->plarg = new_al;  
  }
}
void c_al(){
  return;
}




void o_exp(){
  expression1_t *new_op = malloc(sizeof(expression1_t));
  if(new_op == NULL) PERROR_MALLOC("o_exp() - can't open next level expression");
  
  new_op->plarg = NULL;  
  new_op->parent = ptr_parser_state->curr_op;
  
  /* expression is created always in place of complex argument on some arguments list */
  assert(ptr_parser_state->curr_arg != NULL);

  new_op->ptr_this_as_arg_in_parent = ptr_parser_state->curr_arg;
  
  new_op->i_start = ptr_parser_state->i_start;
  new_op->i_end = ptr_parser_state->i_end;
  ptr_parser_state->i_start = ptr_parser_state->i_end = 0;

  ptr_parser_state->curr_op = new_op;  
  ptr_parser_state->curr_arg->calc = new_op;

  #ifdef DEBUG_LEVEL
    ptr_parser_state->level++; //level++ gdy otwiera sie nawias (level tylko do debugu i analizy)
  #endif //DEBUG_LEVEL
}
void c_exp(){

  interpret_op(ptr_parser_state->curr_op, ptr_parser_state->formula);  
  
  #ifdef DEBUG_LEVEL
    ptr_parser_state->level--; //level-- gdy zamyka sie nawias (level tylko do debugu i analizy)
  #endif //DEBUG_LEVEL

  if(ptr_parser_state->curr_op->parent != NULL){
    ptr_parser_state->curr_op = ptr_parser_state->curr_op->parent;
    ptr_parser_state->curr_al = ptr_parser_state->curr_op->plarg;   //lista parenta juz
    ptr_parser_state->curr_arg = ptr_parser_state->curr_op->plarg->last->el; //ostatni przetwarzany element z tej listy
  }
  else { //closing first element without parent
    assert(ptr_parser_state->curr_op->ptr_this_as_arg_in_parent->level == 0); //1 bo nie mozna nijak dosiegnac 0wej listy arg, na ktorej jest pierwszy operator
    
    #ifdef DEBUG_LEVEL
      assert(ptr_parser_state->level == 0);
    #endif //DEBUG_LEVEL

    ptr_parser_state->expr_tree_complete = true;
  }
  return;
}




#define case_AZ  \
case'a': case 'b': case 'c': case 'd': case 'e': case 'f': case 'g': \
case 'h': case 'i': case 'j': case 'k': case 'l': case 'm': case 'n': \
case 'o': case 'p': case 'r': case 'q': case 's': case 't': case 'u': \
case 'w': case 'x': case 'y': case 'z'
#define case_09 \
case '0': case '1': case '2': case '3': case '4': case '5': \
case '6': case '7': case '8': case '9'




expression1_t *parse_expr4(const char *formula){
  parser04_state_reset();
  ptr_parser_state->formula = formula;
  // ptr_parser_state->level = 0;
  // ptr_parser_state->curr_op = NULL;
  // ptr_parser_state->curr_al = NULL;
  // ptr_parser_state->curr_arg = NULL;

  syntax_state_t sstate = ptr_parser_state->curr_state; // st3_la;
  char c;
  int i;
  PRINT_INFO_1(formula);  

  #ifdef DEBUG_LEVEL
    o_al(0);
  #else
    o_al();
  #endif // DEBUG_LEVEL


  //PR(ptr_parser_state->level)
  for(i = 0; (c = formula[i]) != '\0'; i++){
    //PR(ptr_parser_state->curr_op->ptr_this_as_arg_in_parent->level);
    //R_2(ptr_parser_state, formula, ptr_parser_state->curr_arg->i_start, ptr_parser_state->curr_arg->i_end);
    //PR(ptr_parser_state->level);
    //PR(c)
    //PR(sstate)
    ptr_parser_state->curr_state = sstate;
    ptr_parser_state->i_curr = i;
    switch(sstate){

      case st3_la:
        switch(c){
          case ' ':
            break;
          case_09: case '+': case '-':
            o_s();
            o_arg();
            s_arg_type(tot_digit);
            sstate = st4_digit;
            break;
          case_AZ:
            o_s();
            o_arg();
            s_arg_type(tot_name);
            sstate = st2_name;
            break;
          case ',':
            //c_arg(); //nie ma czego zamykac, bo otwierane tylko w st3_la
            break;
          case ')':
            if(ptr_parser_state->curr_arg_closed != false){
              c_arg();
            }
            c_al();
            c_exp();
            c_arg();
            PR_N(ptr_parser_state, formula, ptr_parser_state->curr_arg->i_start, ptr_parser_state->curr_arg->i_end);
            if(ptr_parser_state->expr_tree_complete == true){
              return ptr_parser_state->curr_op;
              sstate = st6_end;
            }
            break;
        }
        break;

      case st2_name:
        switch(c){
          case_AZ:
            break;
          case ',':
            c_s();
            s_arg_type(tot_symbol);
            c_arg();
            PR_N(ptr_parser_state, formula, ptr_parser_state->curr_arg->i_start, ptr_parser_state->curr_arg->i_end);
            sstate = st3_la;
            break;
          case ')':  //CHECK
            c_s();
            s_arg_type(tot_symbol);
            //if(ptr_parser_state->curr_arg_closed != false){
              c_arg();
            //}
            c_al();
            c_exp(); //zmiana ptr_parser_state->curr_arg
            c_arg(); //IasArg
            PR_N(ptr_parser_state, formula, ptr_parser_state->curr_arg->i_start, ptr_parser_state->curr_arg->i_end);

            if(ptr_parser_state->expr_tree_complete == true){
              return ptr_parser_state->curr_op;
              sstate = st6_end;
            }
            sstate = st3_la;
            break;
          case ' ':
            c_s();
            s_arg_type(tot_symbol);
            c_arg();
            sstate = st5_sp_afer_sp;
            break;
          case '(':
            c_s();
            s_arg_type(tot_name_of_operator);
            o_exp();

            #ifdef DEBUG_LEVEL
              o_al((ptr_parser_state->curr_op->ptr_this_as_arg_in_parent->level + 1));
            #else
              o_al();
            #endif // DEBUG_LEVEL

            PR_N(ptr_parser_state, formula, ptr_parser_state->curr_op->i_start, ptr_parser_state->curr_op->i_end);

            sstate = st3_la;
            break;
        }
        break;

      case st4_digit:
        switch(c){
          case_09: case '.':
            break;
          case ' ':
            c_s();
            c_arg();
            sstate = st5_sp_afer_sp;
            break;
          case ',':
            c_s();
            c_arg();
            PR_N(ptr_parser_state, formula, ptr_parser_state->curr_arg->i_start, ptr_parser_state->curr_arg->i_end);
            sstate = st3_la;
            break;
          case ')':
            c_s();
            s_arg_type(tot_digit);
            //if(ptr_parser_state->curr_arg_closed != false){
              c_arg();
            //}
            c_al();
            c_exp(); //zmiana ptr_parser_state->curr_arg
            c_arg(); //IasArg
            PR_N(ptr_parser_state, formula, ptr_parser_state->curr_arg->i_start, ptr_parser_state->curr_arg->i_end);

            if(ptr_parser_state->expr_tree_complete == true){
              return ptr_parser_state->curr_op;
              sstate = st6_end;
            }

            sstate = st3_la;
            break;
        }
        break;
      case st5_sp_afer_sp:
        switch(c){
          case ' ':
            break;
          case ',':
            PR_N(ptr_parser_state, formula, ptr_parser_state->curr_arg->i_start, ptr_parser_state->curr_arg->i_end);
            sstate = st3_la;
            break;
          default:
            exit(2);  //syntax error
            break;
        }
        break;
      case st6_end:  //poniewaz kzda petla to kolejny znak formuly to nie mozna tak konczyc, trzeba od razu
        if(ptr_parser_state->expr_tree_complete) return ptr_parser_state->curr_op;
        break;
    }//case
  }//for

  //return ptr_parser_state->curr_op;
  return NULL;
}
