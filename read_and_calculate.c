/* author: plapacz6@gmail.com; date: 2020-10-04 ;version: 0.1 */
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "model_of_expresson.h"
#include "read_and_calculate.h"

typedef struct wyrazzenie_i_wartosc_tt {
  void *fn; //wskaznik do funkcji realizujacej operator
  int il_arg; //ilosc argumentow do cofnieca na stosie argtumentow : lub
  int i_a;  //indeks wartosci na stosie argumentow
} wyrazzenie_i_wartosc_t;

type_of_value_t read_and_calulate(char *expr){
  type_of_value_t wynik = 0;
  //int n = 0;  //indeks znaku w expr
  int j = 0; //indeks stosu argumenty
  //type_of_value_t argumenty[1000];
  int i = 0; //indeks stosu poziomy
  wyrazzenie_i_wartosc_t poziomy[1000];

  //i = 0 //pozoiom
  //odczytaj_sekwencje znakow
  //jesli operator:
    //odczytaj nazwe operatora
    //odnajdz fukcje go realizujaca
    //zapisz adres funkcji w i-tej komorce stosu poziomy
    j++;
    //zpissz tez w tej i-tej komorce indeks komorki argumentow (j):
    poziomy[i].i_a = j;
    //++; lub nastepna sensowna sekwencja
  //jesli liczba
    j++;
    //dopisz ja do stosu argumentow
    //n++ lub nastepna sensowna sekwencja
  //jesli koniec listy argumentow
    //blicz operator
    //zapisz wartosc w zapisanym przy nim w komorce i stosu poziomy indeksie j stosu argumenty
    //ustaw globalne j na ten zapisany indeksj j (czyli usun niepotrzene juz argumenty ):
    j = poziomy[i].i_a;
    //n++ lub oczytaj kolejna sensowna sekwencje




  return wynik;

}

#define INDENT_MAX (100)
static void make_indent(char *s, int indent){
  int i = 0;
  for(i = 0; i < indent && i < INDENT_MAX - 1; i++){
    s[i] = '.';
  }
  s[i] = 0;
}


/**
 * @brief read value of argument (in recursive way)
 * 
 * @param pa 
 * @param formula 
 * @param indent  - for print debug info
 * @return type_of_value_t 
 */
type_of_value_t read_a(argument_t *pa, char *formula, int indent){
  type_of_value_t val;

  #ifdef DEBUG_PRINT_READ
  char s[INDENT_MAX];  
  make_indent(s, indent);
  printf("%slevel: %i, val: %f\n",s, pa->level, pa->val);
  printf("%s_____________________A|\n", s);
  #endif // DEBUG_PRINT_READ

  if(pa->calc != NULL) {
    val = read_e(pa->calc, formula, indent + 1);
  }
  else {
    val = pa->val;
  }
  return val;
}



/**
 * @brief  calculate value of arguemnt being complex expression
 * during that alocates memory for value orgument of function realizes operation
 * and release that memory after calculations
 * 
 * @param pe        - pointer to expression struct
 * @param formula   - analyzed formula
 * @param indent    - indentation of the message printout (debug info)
 * @return type_of_value_t   - calculated value of formula
 */
type_of_value_t read_e(expression1_t *pe, char* formula,  int indent){

  #ifdef DEBUG_PRINT_READ
    char s[INDENT_MAX];
    char n[INDENT_MAX];
    strncpy(n, formula + (pe->i_start), pe->i_end - pe->i_start);
    n[pe->i_end - pe->i_start] = 0;
    make_indent(s, indent);
    //printf("%spIasArg->level: %i  %s\n", s, pe->pIasArg->level, n);
  #endif // DEBUG_PRINT_READ

  if(pe->plarg != NULL) {
    argument_t** tbl_args = malloc(sizeof(argument_t*) * pe->n_of_args); //pe->n_of_args is generated in perse_express4()  //TODO: IT SHOUD BE IN ONE PLACE ONLY FOR EXPAMPLE IN pe->la REDUNDANCY INTORUCES ERROS
    if(tbl_args == NULL) exit(1);
    read_la(pe->plarg, formula, indent + 1, tbl_args, pe->n_of_args);
    pe->pIasArg->val = (pe->fn)(tbl_args, pe->n_of_args);
    free(tbl_args);
  }
  
  #ifdef DEBUG_PRINT_READ
    printf("%spIasArg->level: %i  %s == %f\n", s, pe->pIasArg->level, n, (double) (pe->pIasArg->val));
  #endif // DEBUG_PRINT_READ

  return pe->pIasArg->val;
}


/**
 * @brief  reads values of argument being on list of arguments 
 * (in recursive way (by read_a() function) ia any of arguments is complex expression)
 * 
 * @param pla 
 * @param formula 
 * @param indent    - for print debug info 
 * @param tbl_args 
 * @param n_of_args 
 */
void read_la(list_of_arguments_t *pla, char* formula, int indent, argument_t** tbl_args, int n_of_args){
  int i = 0;
  list_of_arguments_rewind(pla);
  do {
    assert(i < n_of_args);    //na_of_arg is generated in perse_express4()
    if(list_of_arguments_get(pla) != NULL){
      tbl_args[i] = list_of_arguments_get(pla);
      read_a(list_of_arguments_get(pla), formula, indent);
      i++;
    }
    else 
      return;
  } while(list_of_arguments_next(pla) == 0);  //0 - still there are arguments
  return;
}





















