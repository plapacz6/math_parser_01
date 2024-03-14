/*
Copyright 2020-2024 plapacz6@gmail.com

This file is part of math_parser_01.

math_parser_01 is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

math_parser_01 is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with Foobar. If not, see <https://www.gnu.org/licenses/>.
*/

#include "complex_expression.h"
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>


#ifdef COMPLEX_EXPRESSION_H_INCLUDED

list_of_arguments_t *list_of_arguments_create(void) {
    list_of_arguments_t *pla = malloc(sizeof(list_of_arguments_t));
    if(pla != NULL) {
        pla->first = NULL;
        pla->curr = pla->first;
        pla->last = pla->first;
    }
    pla->n_of_args = 0;
    return pla;
}

int list_of_arguments_add(list_of_arguments_t *pla, argument_t* parg) {
    pla->curr = malloc(sizeof(list_of_arguments_element_t));
    if(pla->curr == NULL) return -1;
    //linking elements of list
    pla->curr->next = NULL;
    if(pla->first == NULL) {
        pla->first = pla->curr;
    }
    pla->last = pla->curr;
    //adding value of list's element
    pla->curr->el = parg;
    pla->n_of_args++;
    return 0;
}

int list_of_arguments_release(list_of_arguments_t *pla) {
    if(pla == NULL) return -2; //wrong call
    //usun wszystkie obiekty wskazwywane przez elementy listy i same ementy listy
    while(pla->first != NULL) {
        pla->curr = pla->first;
        pla->first = pla->first->next;
        assert(pla->curr->el != NULL);
        free(pla->curr->el);
        free(pla->curr);
    };
    //usun sama liste
    free(pla);
    return 0;
}

argument_t *list_of_arguments_get(list_of_arguments_t *pla) {
    if(pla->curr == NULL) return NULL;
    else return pla->curr->el;
}

int list_of_arguments_next(list_of_arguments_t *pla) {
    if(pla->curr->next == NULL) return 1;
    else {
        pla->curr = pla->curr->next;
    }
    return 0;
}

int list_of_arguments_rewind(list_of_arguments_t *pla) {
    pla->curr = pla->first;
    return 0;
}


type_of_value_t expression_calculate(expression1_t *pexpr) {
    return 0.0;
}

#endif // COMPLEX_EXPRESSION_H_INCLUDED
