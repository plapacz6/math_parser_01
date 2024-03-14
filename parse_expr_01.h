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
#ifndef PARSE_EXPR_01_H_INCLUDED
#define PARSE_EXPR_01_H_INCLUDED

#include "complex_expression.h"


typedef enum expr_read_state_tt {
    E_PARSE_BEGINING_OF_LEVEL = 1,
    E_PARSE_OPERATOR_NAME = 2,
    E_PARSE_ARGUMENT_LIST = 3,
    E_PARSE_NUMBER = 4,
    E_PARSE_SPACE_AFTER_ARGUMENT = 5
} expr_read_state_t;

expression1_t *expression_read(char *expr);

/** calulates value of expression.
  @param pexpr - pointer to object being 1st level of expression
  @return value of expression

  PL:
  przeszukuje drzewo reprezentujace strukturę wyrażenia. Jeśli wskaznik calc
  argumentu jest równy NULL, przyjmowana jest wartość VAL wyrażenia. Jelsi wskanik
  jest rożny od null, następuje zawieszenie evaluacji wyrażenia i przejście do
  ewaluacji wyrażenia przechowywanego pod adresem w tym wskaźniku (wskazniku calulation).
  Jeśli wszystkie argumenty takiego wyrżenia mają 'clculation' == NULL. Wyrażenie jest olbiczone.
  Tzn. do funkcji wskazywanej przez wskanik fn (wyrżenie jest typu expression1_t) przekazane sa
  wskaśniki do wartości VAL kadego argumentu. Wynik funkcji zapisany jest pod
  adresem (wskanik pval stuktury expression_t) wartości arguemntu w wyrażeniu niższego pozomu.
  /NIE TRZEBA TEGO ROBIC ...
  Następnie usuwana jest lista argumentów i samo wyrażenie jak już niepotrzebne.
  .../
  i kontynuowane jest zawieszone obliczanie wartości wyrżenia niższego rzędu
*/
#endif // PARSE_EXPR_01_H_INCLUDED
#endif //MODEL_OF_EXPRESSON_2
