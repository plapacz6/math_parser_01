/*
Copyright 2020-2024 plapacz6@gmail.com

This file is part of math_parser_01.

math_parser_01 is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

math_parser_01 is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with Foobar. If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef ERROR_HANDLING_H
#define ERROR_HANDLING_H
#include <stdio.h>

#define PERROR_MALLOC(X) { fprintf(stderr, "%s\n", X); exit(1); }


#ifndef INFO_HANDLING_H
#define INFO_HANDLING_H
/* separate into a separate file   info_handling.h  */
#ifdef PRINT_INFO
#define PRINT_INFO_1(X) { printf("%s\n", X);}
#else
#define PRINT_INFO_1(X) ;
#endif //PRINT_INFO
#endif //INFO_HANDLING_H


#endif // ERROR_HANDLING_H