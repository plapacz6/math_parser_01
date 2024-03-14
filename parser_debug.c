/*
Copyright 2020-2024 plapacz6@gmail.com

This file is part of math_parser_01.

math_parser_01 is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

math_parser_01 is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with Foobar. If not, see <https://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "model_of_expresson.h"
#include "parser_debug.h"
extern char *expression_test;
#define INDENT_MAX (100)
static void make_indent(char *s, int indent) {
    int i = 0;
    for(i = 0; i < indent && i < INDENT_MAX - 1; i++) {
        s[i] = '.';
    }
    s[i] = 0;
}
void display_a(argument_t *pa, int indent) {
    char s[INDENT_MAX];
    char n[INDENT_MAX];
    //for(int i = 0; i < )
    strncpy(n, expression_test + (pa->i_start), pa->i_end - pa->i_start);
    n[pa->i_end - pa->i_start] = 0;
    make_indent(s, indent);
    printf("%s___                 \n", s);
    printf("%s           %p: A\n", s, pa);
    printf("%sA_name: %s\n", s, n);
    printf("%scalc: %p\n", s, pa->calc);
    printf("%sval: %f\n", s, pa->val);
    printf("%spval: %p\n", s, pa->pval);
    printf("%si_start: %i\n", s, pa->i_start);
    printf("%si_end: %i\n", s, pa->i_end);
    printf("%stoken_type: %i\n", s, pa->token_type);
    printf("%slevel: %i\n",s, pa->level);
    printf("%s_____________________A|\n", s);
    if(pa->calc != NULL) {
        display_e(pa->calc, indent + 1);
    }
    //printf("%s________:\n", s);
    return;
}
void display_e(expression1_t *pe, int indent) {
    char s[INDENT_MAX];
    char n[INDENT_MAX];
    strncpy(n, expression_test + (pe->i_start), pe->i_end - pe->i_start);
    n[pe->i_end - pe->i_start] = 0;
    make_indent(s, indent);
    printf("%s___                 \n", s);
    printf("%s           %p: E\n", s, pe);
    printf("%sE_name: %s\n", s, n);
    printf("%sparent: %p\n", s, pe->parent);
    printf("%spIsArg: %p\n", s, pe->ptr_this_as_arg_in_parent);
    printf("%sptr_this_as_arg_in_parent->level: %i\n", s, pe->ptr_this_as_arg_in_parent->level);
    printf("%sfn: %p\n", s, pe->fn);
    printf("%snum_of_arg: %i\n", s, pe->plarg->n_of_args);
    printf("%splarg: %p\n", s, pe->plarg);
    printf("%si_start: %i\n", s, pe->i_start);
    printf("%si_end: %i\n", s, pe->i_end);
    printf("%s_____________________E|\n", s);
    if(pe->plarg != NULL) {
        display_la(pe->plarg, indent + 1);
    }
    //printf("%s________:\n", s);
    return;
}
void display_la(list_of_arguments_t *pla, int indent) {
    list_of_arguments_rewind(pla);
    do {
        if(list_of_arguments_get(pla) != NULL) {
            display_a(list_of_arguments_get(pla), indent);
        }
        else return;
    } while(list_of_arguments_next(pla) == 0);  //0 - still there are arguments
    return;
}


/* ------------------------------------------------------------------ */
void print_argument_t(argument_t* pa, char* comment) {
    char substring[1000];
    printf("%s\n", "-------------------------------------------------");
    printf("argument__: adres : %p  - %s\n", pa, comment);
    if(pa != NULL) {
        printf("adres wyrazenia wyliczajacego ten argument: %p\n", pa->calc);
        printf("val: %f, pval: %p\n", pa->val, pa->pval);
        printf("i_start: %d, i_end %d\n", pa->i_start, pa->i_end);
        strncpy(substring, expression_test + (pa->i_start), pa->i_end - pa->i_start);
        substring[pa->i_end - pa->i_start] = 0;
        printf("i_start: %i, i_end: %i, substring: %s\n", pa->i_start, pa->i_end, substring);
    }
    printf("%s\n", "-------------------------------------------------");
}
void print_list_of_arguments_t(list_of_arguments_t* pla, char *comment) {
    //char substring[1000];
    printf("%s\n", "++++++++++++++++++++++++++++++++++++++++++++++++++");
    printf("lista_argumentow__: adres: %p\n, %s\n", pla, comment);
    if(pla != NULL) {
        if(pla->curr != NULL) {
            printf("->curr__: adres: %p\n, %s\n", pla->curr, comment);
            printf("adres wartosci (argument) : %p\n", pla->curr->el);
            printf("adres nastepnego elementu(next): %p\n", pla->curr->next);
        }
        else {
            printf("%p->curr == NULL : %s\n", pla, comment);
        }
    }
    printf("%s\n", "++++++++++++++++++++++++++++++++++++++++++++++++++");
}
void print_expresion1_t(expression1_t *pe, char *comment) {
    //char substring[1000];
    printf("%s\n", "####################################################");
    printf("operator__: adres: %p\n, %s\n", pe, comment);
    if(pe != NULL) {
        printf("parent: %p\n", pe->parent);  /**< poointer to parent expression */
        printf("adres gdzie wartosc tego wyrzenia zapisac: %p\n", pe->ptr_this_as_arg_in_parent); /**< pointer to place where value of expression will be placed */
        printf("pointer funkcji realizujacej: %p: \n", pe->fn);  /**< pointer to function which calcualtes value of this expression */
        printf("liczba argumentow: %i\n", pe->plarg->n_of_args);   /**< how many arguments funciton has */
        printf("adres listy argumentow: %p\n", pe->plarg);  /**< list of arguments */
    }
    printf("%s\n", "####################################################");

}
