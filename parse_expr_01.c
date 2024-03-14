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
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "parse_expr_01.h"
#include "parser_debug.h"

expression1_t *expression_read(char *expr) {
    int i_start;
    int i_end;
    int i;
    expr_read_state_t stage = E_PARSE_BEGINING_OF_LEVEL;
    bool syntax_error = false;
    bool memory_allocation_error = false;
    expression1_t *pwhole_expression = NULL;
    expression1_t *pcurr_level_expr = NULL;
    expression1_t *new_level_expr = NULL;
    argument_t *pcurr_arg = NULL;
    char operator_name[1000];
    int n_of_args = 0;
    char c;

    puts(expr);
    for(i = 0; (c = expr[i]) != '\0'; i++) {
        /** nawiasy i składnia notacji polskiej.
        nawiasy nie oznaczają tu grupowania wyrażeń (okreslania priorytetu), ale
        otaczają liste argumentów operatora.

        parentes and syntax of polish notation.
        the parentheses here do not mean grouping expressions (determining priority), but
        surround the list of operator arguments.
        */
        switch(stage) {
        case E_PARSE_BEGINING_OF_LEVEL: //parisng begining of one evel of expression
            PRINTF1_DEBUG1("E_PARSE_BEGINING_OF_LEVEL");
            switch(c) {
            case 'a':
            case 'b':
            case 'c':
            case 'd':
            case 'e':
            case 'f':
            case 'g':
            case 'h':
            case 'i':
            case 'j':
            case 'k':
            case 'l':
            case 'm':
            case 'n':
            case 'o':
            case 'p':
            case 'q':
            case 'r':
            case 's':
            case 't':
            case 'u':
            case 'w':
            case 'x':
            case 'y':
            case 'z':
                i_start = i;
                i_end = i;
                stage = E_PARSE_OPERATOR_NAME;
                break;
            default:
                syntax_error = true;
                break;
            };
            break;

        case E_PARSE_ARGUMENT_LIST: //parsing arguments list
            PRINTF1_DEBUG1("E_PARSE_ARGUMENT_LIST");
            switch(c) {
            case ' ': //przeskakiwanie spacji pomiedzy  argumentami a przecinkami
                break;

            //poczatek liczby
            case '+':
            case '-':
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                //case '.':  //liczba nie zaczyna sie od kropki ale moze od + i -
                i_start = i;
                i_end = i;
                stage = E_PARSE_NUMBER; //wczytywanie liczby
                break;

            //poczatek nazwy operatora
            case 'a':
            case 'b':
            case 'c':
            case 'd':
            case 'e':
            case 'f':
            case 'g':
            case 'h':
            case 'i':
            case 'j':
            case 'k':
            case 'l':
            case 'm':
            case 'n':
            case 'o':
            case 'p':
            case 'q':
            case 'r':
            case 's':
            case 't':
            case 'u':
            case 'w':
            case 'x':
            case 'y':
            case 'z':
                i_start = i;
                i_end = i;
                stage = E_PARSE_OPERATOR_NAME; //wczytywanie nazwy opearatora
                break;

            case ')':  //zamkniecie pustej listy argumentów (liczba argumentów == 0)
                PRINTF1_DEBUG1("  E_PARSE_ARGUMENT_LIST: )");
                //zamknij liste argumentow
                //uzupelnij liczbe argumentow operatora
                pcurr_level_expr->n_of_args = n_of_args;
                n_of_args = 0;
                //powrot do nizszego poziomu wyrazenia
                pcurr_level_expr = pcurr_level_expr->parent;
                stage = E_PARSE_ARGUMENT_LIST;

                PRINTF2_DEGUG2(pcurr_level_expr, "E_PARSE_ARGUMENT_LIST: nawias/)");

                break;
            };
            break;

        case E_PARSE_NUMBER: //parsing a number
            PRINTF1_DEBUG1("E_PARSE_NUMBER");
            switch(c) {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
            case '.':
                //case '+': //na tym etapie nie ma + i -, ale jest kropka
                //case '-':
                i_end = i;
                break;
            case ' ':
                stage = E_PARSE_SPACE_AFTER_ARGUMENT; //spacja po liczbie
                break;
            case ',':
            case ')':
                //utworz nowy argument
                pcurr_arg = malloc(sizeof(argument_t));
                if(pcurr_arg == NULL) {
                    memory_allocation_error = true;
                    goto clean;
                }
                //dopisz go do listy argumentow
                list_of_arguments_add(pcurr_level_expr->plarg, pcurr_arg);
                assert(pcurr_arg == pcurr_level_expr->plarg->curr->el);
                //zapisz odczytany argument (liczbe)
                pcurr_level_expr->plarg->curr->el->i_start = i_start;
                pcurr_level_expr->plarg->curr->el->i_end = i_end;
                pcurr_level_expr->plarg->curr->el->calc = NULL; //to konkretna liczba
                //TODO: SEGMENTATION FAULT: - jakies przesuniecie o jeden poziom za duzo w doł
                n_of_args++;
                pcurr_level_expr->n_of_args = n_of_args;
                PRINTF2_DEGUG2(pcurr_level_expr, "E_PARSE_NUMBER:");

                //koniec listy argumentow operatora i samego operatora
                if(c == ')') {
                    PRINTF1_DEBUG1("  E_PARSE_NUMBER: /)");
                    pcurr_level_expr->n_of_args = n_of_args;
                    n_of_args = 0;
                    //powrot do nizszego poziomu wyrazenia
                    pcurr_level_expr = pcurr_level_expr->parent;

                    PRINTF2_DEGUG2(pcurr_level_expr, "E_PARSE_NUMBER:");
                }
                stage = E_PARSE_ARGUMENT_LIST;
                break;
            default:  //tu mozna jeszcze wydzielic alfanumeryczne nazwy - dla zmiennych algebraicznych
                syntax_error = true;
                break;
            };
            break;

        case E_PARSE_SPACE_AFTER_ARGUMENT: //spacja po liczbie
            PRINTF1_DEBUG1("E_PARSE_SPACE_AFTER_ARGUMENT");
            switch(c) {
            case ' ':
                break;
            case ',': //kopiuj wklej z sekcji E_PARSE_NUMBER
            case ')':
                //utworz nowy argument
                pcurr_arg = malloc(sizeof(argument_t));
                if(pcurr_arg == NULL) {
                    memory_allocation_error = true;
                    goto clean;
                }
                //dopisz go do listy argumentow
                list_of_arguments_add(pcurr_level_expr->plarg, pcurr_arg);
                //zapisz odczytany argument (liczbe)
                pcurr_level_expr->plarg->curr->el->i_start = i_start;
                pcurr_level_expr->plarg->curr->el->i_end = i_end;
                pcurr_level_expr->plarg->curr->el->calc = NULL; //to konkretna liczba
                //TODO: SEGMENTATION FAULT:
                n_of_args++;
                pcurr_level_expr->n_of_args = n_of_args;

                PRINTF2_DEGUG2(pcurr_level_expr, "E_PARSE_SPACE_AFTER_ARGUMENT:");

                //koniec listy argumentow operatora i samego operatora
                if(c == ')') {
                    PRINTF1_DEBUG1("  E_PARSE_SPACE_AFTER_ARGUMENT: )");
                    pcurr_level_expr->n_of_args = n_of_args;
                    n_of_args = 0;
                    //powrot do nizszego poziomu wyrazenia
                    pcurr_level_expr = pcurr_level_expr->parent;

                    PRINTF2_DEGUG2(pcurr_level_expr, "E_PARSE_SPACE_AFTER_ARGUMENT:");
                }
                stage = E_PARSE_ARGUMENT_LIST;
                break;
            default:
                syntax_error = true;
                break;
            }
            break;


        case E_PARSE_OPERATOR_NAME: //parsing alphanumeric name of operator
            PRINTF1_DEBUG1("E_PARSE_OPERATOR_NAME");
            switch(c) {
            //kolejne listery nazwy operatora
            case 'a':
            case 'b':
            case 'c':
            case 'd':
            case 'e':
            case 'f':
            case 'g':
            case 'h':
            case 'i':
            case 'j':
            case 'k':
            case 'l':
            case 'm':
            case 'n':
            case 'o':
            case 'p':
            case 'q':
            case 'r':
            case 's':
            case 't':
            case 'u':
            case 'w':
            case 'x':
            case 'y':
            case 'z':
                //odczytywanie kolejnych liter nazwy operatora
                i_end = i;
                break;
            case '(':   //nowa lista argumentow
                //wyciecie nazwy operatora (indeksy) z wyrazenia
                strncpy(operator_name, &(expr[i_start]), i_end - i_start);
                //odszukaj wskaznik do funkcj realizujacej operator
                /*
                ...
                */
                //utworz nowy poziom wyrazenia i zapisz wskaznik do tego poziomu
                //w wartosci artguemntu ostatnio czytanego poziomu nizszego : expression1_tt *calc;
                new_level_expr = malloc(sizeof(expression1_t));
                if(new_level_expr == NULL) {
                    memory_allocation_error = true;
                    goto clean;
                }

                if(pwhole_expression == NULL) {
                    pwhole_expression = new_level_expr;
                    pwhole_expression->parent = NULL;
                    pwhole_expression->pval = NULL;
                    pcurr_level_expr = pwhole_expression;
                }
                else {
                    new_level_expr->parent = pcurr_level_expr;
                    /*w momencie tworzenia nowego poziomu tworzymy
                      nowy element(argument) w liscie argumentow poporzedniego
                    */
                    //utworz nowy argument
                    pcurr_arg = malloc(sizeof(argument_t));
                    if(pcurr_arg == NULL) {
                        memory_allocation_error = true;
                        goto clean;
                    }
                    //dopisz go do listy argumentow
                    list_of_arguments_add(pcurr_level_expr->plarg, pcurr_arg);
                    //zapisz odczytany argument (liczbe)
                    pcurr_level_expr->plarg->curr->el->i_start = i_start;
                    pcurr_level_expr->plarg->curr->el->i_end = i_end;
                    pcurr_level_expr->plarg->curr->el->calc = new_level_expr; //to konkretna liczba

                    n_of_args++;
                    pcurr_level_expr->n_of_args = n_of_args;

                    //TODO: TU JEST SEGMENTATION FAULT
                    //new_level_expr->pval = pcurr_level_expr->plarg->curr->el;
                    //pcurr_level_expr->plarg->curr->el->calc = new_level_expr;
                    pcurr_level_expr = new_level_expr;
                }

                //nowa lista argumentow i zapisz adres tej listy w list_of_arguments_t larg
                pcurr_level_expr->plarg = list_of_arguments_create();
                //malloc(sizeof list_of_arguments_t);
                if(pcurr_level_expr->plarg == NULL) {
                    memory_allocation_error = true;
                    goto clean;
                }
                pcurr_level_expr->n_of_args = 0;
                stage = E_PARSE_ARGUMENT_LIST;

                PRINTF2_DEGUG2(pcurr_level_expr, "E_PARSE_OPERATOR_NAME: nawias\(");

                break;
            default:
                syntax_error = true;
                break;
            }
            break;
        } //switch
        PRINTF2_DEGUG3(pcurr_level_expr, "___kolejna_petla_dla_c___\n");
    } //for

    if(syntax_error == true) {
        goto clean;
    }
clean:
    if(memory_allocation_error == true) {
        puts("brak pamieci: clean");
        //free(wszystkie_utworzone dotad elementy);
        //pwhole_expression;
    }

    return pwhole_expression;
}
#endif // MODEL_OF_EXPRESSON_2
