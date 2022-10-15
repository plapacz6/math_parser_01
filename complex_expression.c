/* author: plapacz6@gmail.com; date: 2020-09-22 ;version: 0.1 */

#include "complex_expression.h"
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>


#ifdef COMPLEX_EXPRESSION_H_INCLUDED

list_of_arguments_t *list_of_arguments_create(void){
  list_of_arguments_t *pla = malloc(sizeof(list_of_arguments_t));
  if(pla != NULL) {
    pla->first = NULL;
    pla->curr = pla->first;
    pla->last = pla->first;
  }
  pla->n_of_args = 0;
  return pla;
}

int list_of_arguments_add(list_of_arguments_t *pla, argument_t* parg){
  pla->curr = malloc(sizeof(list_of_arguments_element_t));
  if(pla->curr == NULL) return -1;
  //linking elements of list
  pla->curr->next = NULL;
  if(pla->first == NULL){
    pla->first = pla->curr;
  }
  pla->last = pla->curr;
  //adding value of list's element
  pla->curr->el = parg;
  pla->n_of_args++;
  return 0;
}

int list_of_arguments_release(list_of_arguments_t *pla){
  if(pla == NULL) return -2; //wrong call
  //usun wszystkie obiekty wskazwywane przez elementy listy i same ementy listy
  while(pla->first != NULL){
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

argument_t *list_of_arguments_get(list_of_arguments_t *pla){
  if(pla->curr == NULL) return NULL;
  else return pla->curr->el;
}

int list_of_arguments_next(list_of_arguments_t *pla){
  if(pla->curr->next == NULL) return 1;
  else {
    pla->curr = pla->curr->next;
  }
  return 0;
}

int list_of_arguments_rewind(list_of_arguments_t *pla){
  pla->curr = pla->first;
  return 0;
}


type_of_value_t expression_calculate(expression1_t *pexpr){
  return 0.0;
}

#endif // COMPLEX_EXPRESSION_H_INCLUDED
