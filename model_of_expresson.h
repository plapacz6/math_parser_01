/*
Copyright 2020-2024 plapacz6@gmail.com

This file is part of math_parser_01.

math_parser_01 is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

math_parser_01 is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with Foobar. If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef MODEL_OF_EXPRESSON_H_INCLUDED
#define MODEL_OF_EXPRESSON_H_INCLUDED

//#ifndef COMPLEX_EXPRESSION_H_INCLUDED
//#define COMPLEX_EXPRESSION_H_INCLUDED
/* author: plapacz6@gmail.com; date: 2020-09-22 ;version: 0.1 */
/** @file complex_expression.h */
extern char *expression; //string of expression

/** structure to represent the construction of an expression */

typedef double type_of_value_t;

/** 1 argument of operator
  may be specified value or operator of next level expression
*/
//extern argument_tt;
//extern expression1_tt;
//extern list_of_arguments_element_tt;

typedef enum type_of_token_tt
{
    tot_digit,
    tot_name,
    tot_symbol,
    tot_name_of_operator
} type_of_token_t;


typedef struct argument_tt
{

    int level; /**< nesting level */

    struct expression1_tt *calc; /**< Pointer to next level expression1_t.
                                     which calculates value of this argument.
                                     if NULL val is specified. */
    type_of_value_t val;         /**< value of argument */
    type_of_value_t *pval;       /**< pointer to value of argument */

    int i_start; /**< index of first character of argument's string */
    int i_end;   /**< index of last character of argument's string */

    type_of_token_t token_type; /**< for distinguish between digit, operator name, etc */
} argument_t;



/** element of list of arguments.
*/
typedef struct list_of_arguments_element_tt
{
    argument_t *el;
    struct list_of_arguments_element_tt *next;
} list_of_arguments_element_t;



/** list of arguments
*/
typedef struct list_of_arguments_tt
{
#ifdef DEBUG_LEVEL
    int level; /**< nesting level */
#endif       //DEBUG_LEVEL

    int n_of_args;                      //TODO: this is right place for that information
    list_of_arguments_element_t *first; /**< first element of list */
    list_of_arguments_element_t *curr;  /**< currly ponted element of list */
    list_of_arguments_element_t *last;  /**< last alement of list. New element will be added after this element */
} list_of_arguments_t;



/** elemental expression (1 level expression)
*/
typedef struct expression1_tt
{
    struct expression1_tt *parent;           /**< pointer to parent expression */
    argument_t *ptr_this_as_arg_in_parent;   /**< pointer to parent's argument that will contain the value of the expression*/

    type_of_value_t (*fn)(argument_t **, int); /**< pointer to function which calcualtes value of this expression */

    //int n_of_args;   /**< how many arguments funciton has */ //TODO: unneccesary copy of that information (shoud be only in plarg)

    list_of_arguments_t *plarg; /**< list of arguments */

    //TODO: maybe this shoud be in struct
    int i_start; /**< index of beginning of name */
    int i_end;   /**< inde of last character of name */
} expression1_t;



/** adds next argument to list of arguemnts.
  arguments for this list are created manually with malloc, and
  filled manually by =.
  @param pla - pointer to list to which argument will be added
  @param parg - pointer to obiect of type argument_t created and filled manually
  @return 0 : ok, -1 : error
*/
int list_of_arguments_add(list_of_arguments_t *pla, argument_t *parg);

/**
  free() all arguments stored on the list, and free() also the list.
  @param pla - pointer to released list
  @return 0 : ok, -1 : erorr
*/
//int list_of_arguments_destruct(list_of_arguments_t *pla);
int list_of_arguments_release(list_of_arguments_t *pla);

/** create empty list of arguments
  @return pointer to created list, or NULL if error occured.
*/
#ifdef DEBUG_LEVEL
list_of_arguments_t *list_of_arguments_create(int level);
#else
list_of_arguments_t *list_of_arguments_create(void);
#endif // DEBUG_LEVEL

/** return currently pointed element of list.
  @param pla - pointer to list of arugments.
  @return pointer to currly pointed element of list
*/
argument_t *list_of_arguments_get(list_of_arguments_t *pla);

/** switch pointer from currently pointed to next element of list.
  @param pla - pointer to list of arguemnts
  @return 0 : ok, 1 : there is no next element, -1 : error
*/
int list_of_arguments_next(list_of_arguments_t *pla);

/** set currently poined element on first element
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

//DEBUG
void print_argument_t(argument_t *pa, char *comment);
void print_list_of_arguments_t(list_of_arguments_t *pla, char *comment);
void print_expresion1_t(expression1_t *pexpr, char *comment);

//#endif // COMPLEX_EXPRESSION_H_INCLUDED

#endif // MODEL_OF_EXPRESSON_H_INCLUDED
