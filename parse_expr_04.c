/*
author: plapacz1@gmail.com; date: 2020- ;version: 0.1
*/

/*
author: plapacz1@gmail.com; date: 2020- ;version: 0.1
*/
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include "model_of_expresson.h"
#include "parse_expr_04.h"
#include "parser_debug.h"
#include "semantic_processor_01.h"

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
  char *formula;
  int i_start;
  int i_end;
  syntax_state_t curr_state;
  int i_curr;
  bool syntax_error;

/* -------------- logic of expression tree ----------------- */
  int level;
  //expression1_t *first_op;
  expression1_t *curr_op;
  list_of_arguments_t *curr_al;
  argument_t *curr_arg;
  bool curr_arg_closed;
  //type_of_token_t token_type;
  bool expr_tree_complete;
} parser04_state_t;

parser04_state_t st, *pst = &st;

#ifdef DEBUG_PRN
#define PR_N(P,W,S,E) \
  {char prn_buff[100]; \
  strncpy(prn_buff, W + S, (E - S)); \
  prn_buff[E - S] = 0; \
  printf("level %d: %s\n", P->curr_op->pIasArg->level, prn_buff);}
  //printf("level %d: %s\n", P->level, prn_buff);}
#else
  #define PR_N(P,W,S,E)
#endif // DEBUG_PRN


#define PR_2(P,W,S,E) \
  {char prn_buff[100]; \
  strncpy(prn_buff, W + S, (E - S)); \
  prn_buff[E - S] = 0; \
  printf("level %d: %s\n", P->curr_op->pIasArg->level, prn_buff);}

void o_s(){
  pst->i_start = pst->i_curr;
}
void c_s(){
  pst->i_end = pst->i_curr;
}
void o_arg(){
  argument_t *arg = malloc(sizeof(argument_t));
  if(arg == NULL) exit(1);
  arg->pval = &arg->val;
  arg->i_start = pst->i_curr;
  list_of_arguments_add(pst->curr_al, arg);

  pst->curr_arg = arg;
  assert(pst->curr_arg == pst->curr_al->last->el);
  assert(pst->curr_arg == pst->curr_al->curr->el);
  pst->curr_arg_closed = false;
}
void c_arg(){
  //pst->curr_arg->i_start = pst->i_start;
  pst->curr_arg->i_end = pst->i_curr;;
  //pst->i_start = pst->i_end = 0;
  if(pst->curr_arg->token_type == tot_digit){
    interpret_num(pst->curr_arg, pst->formula);
  }
  pst->curr_arg_closed = true;
  return;
}
void s_arg(type_of_token_t t){
  assert(pst->curr_arg != NULL);
  pst->curr_arg->token_type = t;
}

void o_al(int level){
/*
   !!! level is incremented (if neccecary) outside (before call) this function
*/
  list_of_arguments_t* new_al = list_of_arguments_create(level);
  if(new_al == NULL) exit(1);
  pst->curr_al = new_al;
  if(level > 0)  {
    pst->curr_op->plarg = new_al;
  }
}
void c_al(){

  return;
}
void o_exp(){
  expression1_t *new_op = malloc(sizeof(expression1_t));
  if(new_op == NULL) exit(1);
  new_op->parent = pst->curr_op;

  assert(pst->curr_arg != NULL);
  pst->curr_arg->calc = new_op;
  new_op->pIasArg = pst->curr_arg;

  new_op->i_start = pst->i_start;
  new_op->i_end = pst->i_end;
  pst->i_start = pst->i_end = 0;

  pst->curr_op = new_op;
  pst->level++; //level++ gdy otwiera sie nawias (level tylko do debugu i analizy)
}
void c_exp(){
  pst->curr_op->n_of_args = pst->curr_op->plarg->n_of_args;
  interpret_op(pst->curr_op, pst->formula);
  //znajdz funkcje realizujaca operator (nazwa + liczba arg)
  //pst->curr_op->fn = funkcja((pst->curr_op->i_start, pst->curr_op->i_end), pst->curr_op->n_of_args)
  pst->level--; //level-- gdy zamyka sie nawias (level tylko do debugu i analizy)
  if(pst->curr_op->parent != NULL){
    pst->curr_op = pst->curr_op->parent;
    pst->curr_al = pst->curr_op->plarg;   //lista parenta juz
    pst->curr_arg = pst->curr_op->plarg->last->el; //ostatni przetwarzany element z tej listy

  }
  else { //zamykamy pierwszy element ktory nie ma parenta
    assert(pst->curr_op->pIasArg->level == 0); //1 bo nie mozna nijak dosiegnac 0wej listy arg, na ktorej jest pierwszy operator
    assert(pst->level == 0);
    pst->expr_tree_complete = true;
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

expression1_t *parse_expr4(char *expr){

  pst->formula = expr;
  pst->level = 0;
  pst->curr_op = NULL;
  pst->curr_al = NULL;
  pst->curr_arg = NULL;

  syntax_state_t sstate = st3_la;
  char c;
  int i;
  puts(expr);



  o_al(0);


  //PR(pst->level)
  for(i = 0; (c = expr[i]) != '\0'; i++){
    //PR(pst->curr_op->pIasArg->level);
    //R_2(pst, expr, pst->curr_arg->i_start, pst->curr_arg->i_end);
    //PR(pst->level);
    //PR(c)
    //PR(sstate)
    pst->curr_state = sstate;
    pst->i_curr = i;
    switch(sstate){

       case st3_la:
        switch(c){
          case ' ':
            break;
          case_09: case '+': case '-':
            o_s();
            o_arg();
            s_arg(tot_digit);
            sstate = st4_digit;
            break;
          case_AZ:
            o_s();
            o_arg();
            s_arg(tot_name);
            sstate = st2_name;
            break;
          case ',':
            //c_arg(); //nie ma czego zamykac, bo otwierane tylko w st3_la
            break;
          case ')':
            if(pst->curr_arg_closed != false){
              c_arg();
            }
            c_al();
            c_exp();
            c_arg();
            PR_N(pst, expr, pst->curr_arg->i_start, pst->curr_arg->i_end);
            if(pst->expr_tree_complete == true){
              return pst->curr_op;
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
            s_arg(tot_symbol);
            c_arg();
            PR_N(pst, expr, pst->curr_arg->i_start, pst->curr_arg->i_end);
            sstate = st3_la;
            break;
          case ')':  //CHECK
            c_s();
            s_arg(tot_symbol);
            //if(pst->curr_arg_closed != false){
              c_arg();
            //}
            c_al();
            c_exp(); //zmiana pst->curr_arg
            c_arg(); //IasArg
            PR_N(pst, expr, pst->curr_arg->i_start, pst->curr_arg->i_end);

            if(pst->expr_tree_complete == true){
              return pst->curr_op;
              sstate = st6_end;
            }
            sstate = st3_la;
            break;
          case ' ':
            c_s();
            s_arg(tot_symbol);
            c_arg();
            sstate = st5_sp_afer_sp;
            break;
          case '(':
            c_s();
            s_arg(tot_name_of_operator);
            o_exp();

            o_al((pst->curr_op->pIasArg->level + 1));

            PR_N(pst, expr, pst->curr_op->i_start, pst->curr_op->i_end);

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
            PR_N(pst, expr, pst->curr_arg->i_start, pst->curr_arg->i_end);
            sstate = st3_la;
            break;
          case ')':
            c_s();
            s_arg(tot_digit);
            //if(pst->curr_arg_closed != false){
              c_arg();
            //}
            c_al();
            c_exp(); //zmiana pst->curr_arg
            c_arg(); //IasArg
            PR_N(pst, expr, pst->curr_arg->i_start, pst->curr_arg->i_end);

            if(pst->expr_tree_complete == true){
              return pst->curr_op;
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
            PR_N(pst, expr, pst->curr_arg->i_start, pst->curr_arg->i_end);
            sstate = st3_la;
            break;
          default:
            exit(2);  //syntax error
            break;
        }
        break;
      case st6_end:  //poniewaz kzda petla to kolejny znak formuly to nie mozna tak konczyc, trzeba od razu
        if(pst->expr_tree_complete) return pst->curr_op;
        break;
    }//case
  }//for

  //return pst->curr_op;
  return NULL;
}
