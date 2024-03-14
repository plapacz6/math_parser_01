/*
Copyright 2020-2024 plapacz6@gmail.com

This file is part of math_parser_01.

math_parser_01 is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

math_parser_01 is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with Foobar. If not, see <https://www.gnu.org/licenses/>.
*/

#ifdef MODEL_OF_EXPRESSON_2
#ifndef COMPLEX_EXPRESSION_H_INCLUDED
#define COMPLEX_EXPRESSION_H_INCLUDED

/* author: plapacz6@gmail.com; date: 2020-09-22 ;version: 0.1 */
/** @file complex_expression.h */
extern char* expression;  //string of expression

/** structure to represent the construction of an expression */

typedef double type_of_value_t;

/** 1 argument of operator
  may be specified value or operator of next level expression
*/
//extern argument_tt;
//extern expression1_tt;
//extern list_of_arguments_element_tt;

typedef enum type_of_token_tt {
    tot_digit,
    tot_name,
    tot_symbol,
    tot_name_of_operator
} type_of_token_t;

typedef struct argument_tt {
    struct expression1_tt *calc;  /**< Pointer to next level expression1_t.
                                      which calculates value of this argument.
                                      if NULL val is specified. */
    type_of_value_t val;          /**< value of argument */
    type_of_value_t *pval;        /**< pointer to value of argument */
    int i_start;  /**< index of first character of argument's string */
    int i_end;    /**< index of last character of argument's string */
    type_of_token_t token_type;
} argument_t;
void print_argument_t(argument_t* pa, char* comment);
/** element of list of arguments.
*/
typedef struct list_of_arguments_element_tt {
    argument_t *el;
    struct list_of_arguments_element_tt* next;
} list_of_arguments_element_t;

/** list of arguments
*/
typedef struct list_of_arguments_tt {
    int n_of_args;
    list_of_arguments_element_t* first;    /**< first element of list */
    list_of_arguments_element_t* curr;  /**< currly ponted element of list */
    list_of_arguments_element_t* last;     /**< last alement of list. New element will be added after this element */
} list_of_arguments_t;
void print_list_of_arguments_t(list_of_arguments_t* pla, char *comment);

/** elemental expression (1 level expression)
*/
typedef struct expression1_tt {
    struct expression1_tt *parent;  /**< poointer to parent expression */
    argument_t *pval; /**< pointer to place where value of expression will be placed */
    void *fn;  /**< pointer to function which calcualtes value of this expression */
    int n_of_args;   /**< how many arguments funciton has */
    list_of_arguments_t* plarg;  /**< list of arguments */
    int i_start; /**< index of beginning of name */
    int i_end;  /**< inde of last character of name */
} expression1_t;
void print_expresion1_t(expression1_t *pexpr, char *comment);

/** adds next argument to list of arguemnts.
  arguments for this list are created manually with malloc, and
  filled manually by =.
  @param pla - pointer to list to which argument will be added
  @param parg - pointer to obiect of type argument_t created and filled manually
  @return 0 : ok, -1 : error
*/
int list_of_arguments_add(list_of_arguments_t *pla, argument_t* parg);

/**
  free() all arguments stored on the list, and free() also the list.
  @param pla - pointer to released list
  @return 0 : ok, -1 : erorr
*/
int list_of_arguments_release(list_of_arguments_t *pla);

/** create empty list of arguments
  @return pointer to created list, or NULL if error occured.
*/
list_of_arguments_t *list_of_arguments_create(void);

/** return currly pointed element of list.
  @param pla - pointer ot list of arugments.
  @return pointer to currly pointed element of list
*/
argument_t *list_of_arguments_get(list_of_arguments_t *pla);

/** switch pointer from currly pointed to next element of list.
  @param pla - pointer to list of arguemnts
  @return 0 : ok, 1 : there is no next element, -1 : error
*/
int list_of_arguments_next(list_of_arguments_t *pla);

/** set currly poined element on first element
  @param pla - pointer to list of arguemnts
  @return 0 : ok, -1 : error0;
*/
int list_of_arguments_rewind(list_of_arguments_t *pla);



/** using the above structures to read and parse an expression */

/** reads character string representing expression in polish notation.
  @param expression - pointer to character string representing the expression
  @return pointer to object being 1 level of parsed expression

  PL:
  zapamietujemy index poczatku argumentu
  gdy napotkamy (
    - zapamietujemy poprzedni index jako koniec argumentu
    - ( oznacza ze stirng pomiedzy poczatkiem a koncem jest nazwa operatora
    Odszukujemy wskanzik do funkcji reazlisujacej opeator w tablicy opeatorow
    tworzymy expression1_t kolejnego poziomu i zapamietujemy wskaznik do funkcji w nim
    ustaiwamy licznik argumentow na 0
    zapamietujemy index poczatku
    jesli kolejny znak rozny od , ) ( to traktujemy jako czesc argumentu
    - jesli , to zapamietujemy indeks konca
    tworzymy nowy argument_t i zapisujemy indeksy poczatku i konca
    ustawiamy wskanik calc na NULL
    - jesli ) to koniec listy argumentow
    - jesli ( to znaczy, ze lancuch pomiedzy indeksami poaczatku i konca to nazwa
    operator wyrazenia nastepnego poziomu
    - jesli spacja to ignorujemy.

    UWAGA:
    moze nastapic kombinacja ,) - wtedy bedzie to koniec listy arguemtow, ale powyzszy
    algorytm to obsluży

    Zakładamy że każdy operator ma 0 lub więcej argumentów.
    Tzn. mozemy mieć operator PI() - np. zwracajacy wartość 3.14
*/

type_of_value_t expression_calculate(expression1_t *pexpr);

#endif // COMPLEX_EXPRESSION_H_INCLUDED
#endif // MODEL_OF_EXPRESSON_2
