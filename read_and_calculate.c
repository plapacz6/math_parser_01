/* author: plapacz1@gmail.com; date: 2020-10-04 ;version: 0.1 */
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

type_of_value_t read_a(argument_t *pa, char *formula, int indent){
  char s[INDENT_MAX];
  type_of_value_t val;
  make_indent(s, indent);
  printf("%slevel: %i, val: %f\n",s, pa->level, pa->val);
  printf("%s_____________________A|\n", s);
  if(pa->calc != NULL) {
    val = read_e(pa->calc, formula, indent + 1);
  }
  else {
    val = pa->val;
  }
  return val;
}

type_of_value_t read_e(expression1_t *pe, char* formula,  int indent){
  char s[INDENT_MAX];
  char n[INDENT_MAX];
  strncpy(n, formula + (pe->i_start), pe->i_end - pe->i_start);
  n[pe->i_end - pe->i_start] = 0;
  make_indent(s, indent);

  //printf("%spIasArg->level: %i  %s\n", s, pe->pIasArg->level, n);
  if(pe->plarg != NULL) {
    argument_t** tbl_args = malloc(sizeof(argument_t*) * pe->n_of_args);
    if(tbl_args == NULL) exit(1);
    read_la(pe->plarg, formula, indent + 1, tbl_args, pe->n_of_args);
    pe->pIasArg->val = (pe->fn)(tbl_args, pe->n_of_args);
    free(tbl_args);
  }
  printf("%spIasArg->level: %i  %s == %f\n", s, pe->pIasArg->level, n, (double) (pe->pIasArg->val));
  return pe->pIasArg->val;
}

void read_la(list_of_arguments_t *pla, char* formula, int indent, argument_t** tbl_args, int n_of_args){
  int i = 0;
  list_of_arguments_rewind(pla);
  do {
    assert(i<n_of_args);
    if(list_of_arguments_get(pla) != NULL){
      tbl_args[i] = list_of_arguments_get(pla);
      read_a(list_of_arguments_get(pla), formula, indent);
      i++;
    }
    else return;
  } while(list_of_arguments_next(pla) == 0);  //0 - still there are arguments
  return;
}





















