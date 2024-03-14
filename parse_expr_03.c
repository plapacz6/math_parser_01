/*
Copyright 2020-2024 plapacz6@gmail.com

This file is part of math_parser_01.

math_parser_01 is free software: you can redistribute it and/or modify it under
the terms of the GNU Lesser General Public License as published by the Free
Software Foundation, either version 3 of the License, or (at your option) any
later version.

math_parser_01 is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more
details.

You should have received a copy of the GNU Lesser General Public License along
 with math_parser_01. If not, see <https://www.gnu.org/licenses/>.
*/

#ifdef MODEL_OF_EXPRESSON_2

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include "complex_expression.h"
#include "parse_expr_03.h"
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


typedef struct parser03_state_tt {
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
    bool curr_arg_closed;
    //type_of_token_t token_type;
    bool expr_tree_complete;
} parser03_state_t;

parser03_state_t st, *pst = &st;

#ifdef DEBUG_PRN
#define PR_N(P,W,S,E) \
  {char prn_buff[100]; \
  strncpy(prn_buff, W + S, (E - S)); \
  prn_buff[E - S] = 0; \
  printf("level %d: %s\n", P->level, prn_buff);}
#else
#define PR_N(W,S,E)
#endif // DEBUG_PRN

void o_s() {
    pst->i_start = pst->i_curr;
}
void c_s() {
    pst->i_end = pst->i_curr;
}
void o_arg() {
    argument_t *arg = malloc(sizeof(argument_t));
    arg->pval = &arg->val;
    pst->curr_arg = arg;
    pst->curr_arg_closed = false;
    list_of_arguments_add(pst->curr_al, arg);
}
void c_arg() {
    pst->curr_arg->i_start = pst->i_start;
    pst->curr_arg->i_end = pst->i_end;
    pst->i_start = pst->i_end = 0;
    pst->curr_arg_closed = true;
    return;
}
void s_arg(type_of_token_t t) {
    assert(pst->curr_arg != NULL);
    pst->curr_arg->token_type = t;
}
void o_al() {
    pst->curr_expr->plarg = list_of_arguments_create();
    pst->curr_al = pst->curr_expr->plarg;
    pst->level++;
}
void c_al() {
    pst->level--;
    return;
}
void o_exp() {
    expression1_t *tmp = pst->curr_expr;
    //pst->level++; //na liscie argumento to powinno byc
    pst->curr_expr = malloc(sizeof(expression1_t));
    pst->curr_expr->parent = tmp;
    if(pst->curr_arg != NULL) {
        pst->curr_arg->calc = pst->curr_expr;
    }
    pst->curr_expr->i_start = pst->i_start;
    pst->curr_expr->i_end = pst->i_end;
}
void c_exp() {
    //expression1_t *tmp;
    pst->curr_expr->n_of_args = pst->curr_al->n_of_args;
    //znajdz funkcje realizujaca operator (nazwa + liczba arg)
    //p2st.curr_expr->fn = funkcja((p2st.curr_expr->i_start, p2st.curr_expr->i_end), p2st.curr_expr->n_of_args)
    //tmp = pst->curr_expr->parent;
    pst->curr_expr = pst->curr_expr->parent;
    //pst->level--; NA LISCIE ARGUMENTOW TO POWINNO BYC
    pst->curr_al = pst->curr_expr->plarg;
    pst->curr_arg = pst->curr_al->last->el;
    if(pst->level == 0) pst->expr_tree_complete = true;
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

expression1_t *parse_expr(char *expr) {
    expression1_t *tmp;
    pst->level = -1;
    pst->curr_expr = NULL;
    pst->curr_al = NULL;
    pst->curr_arg = NULL;

    syntax_state_t sstate = st3_la;
    char c;
    int i;
    puts(expr);
    o_exp();
    o_al();
    tmp = pst->curr_expr;
    //PR(pst->level)
    for(i = 0; (c = expr[i]) != '\0'; i++) {
        PR(pst->level)
        //PR(c)
        //PR(sstate)
        pst->curr_state = sstate;
        pst->i_curr = i;
        switch(sstate) {
        case st1_begining:
//        switch(c){
//          case ' ':
//            break;
//          case_AZ:
//            o_s();
//            s_arg(tot_name);
//            sstate = st2_name;
//            break;
//        }
            break;
        case st2_name:
            switch(c) {
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
                if(pst->curr_arg_closed != false) {
                    c_arg();
                }
                c_al();
                c_exp();
                c_arg();
                PR_N(pst, expr, pst->curr_arg->i_start, pst->curr_arg->i_end);
                if(pst->level == 0) {
                    pst->expr_tree_complete = true;
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
                o_al();
                PR_N(pst, expr, pst->curr_expr->i_start, pst->curr_expr->i_end);
                sstate = st3_la;
                break;
            }
            break;
        case st3_la:
            switch(c) {
            case ' ':
                break;
case_09:
            case '+':
            case '-':
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
                if(pst->curr_arg_closed != false) {
                    c_arg();
                }
                c_al();
                c_exp();
                c_arg();
                PR_N(pst, expr, pst->curr_arg->i_start, pst->curr_arg->i_end);
                if(pst->level == 0) {
                    pst->expr_tree_complete = true;
                    sstate = st6_end;
                }
                break;
            }
            break;
        case st4_digit:
            switch(c) {
case_09:
            case '.':
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
                if(pst->curr_arg_closed != false) {
                    c_arg();
                }
                c_al();
                c_exp();
                c_arg();
                PR_N(pst, expr, pst->curr_arg->i_start, pst->curr_arg->i_end);
                if(pst->level == 0) {
                    pst->expr_tree_complete = true;
                    sstate = st6_end;
                }
                sstate = st3_la;
                break;
            }
            break;
        case st5_sp_afer_sp:
            switch(c) {
            case ' ':
                break;
            case ',':
                PR_N(pst, expr, pst->curr_arg->i_start, pst->curr_arg->i_end);
                sstate = st3_la;
                break;
            }
            break;
        case st6_end:
            if(pst->expr_tree_complete) return pst->curr_expr;
            break;
        }//case
    }//for
    //return pst->curr_expr;
    return tmp;
}
#endif // MODEL_OF_EXPRESSON_2
