# Copyright 2020-2024 plapacz6@gmail.com

# This file is part of math_parser_01.

# math_parser_01 is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

# math_parser_01 is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

# You should have received a copy of the GNU Lesser General Public License along with Foobar. If not, see <https://www.gnu.org/licenses/>.

CC=gcc
FLAGS=-g -Wall -DDEBUG -DDEBUG_ -DDEBUG_LEVEL -DDEBUG2 -DDEBUG1 -DDEBUG3
OBJECTS=main.o math2polnot.o read_and_calculate.o \
model_of_expression.o parse_expr_04.o math_function_def_01.o \
semantic_processor_01.o \
parser_debug.o \
#complex_expression.o

math_parser_01: $(OBJECTS)
	 $(CC) -g -Wall $(OBJECTS) -lm -o $@

main.o: main.c model_of_expresson.h parse_expr_04.h parser_debug.h read_and_calculate.h semantic_processor_01.h 	
	 $(CC) $(FLAGS)  main.c -c

math2polnot.o: math2polnot.c math2polnot.h 
	 $(CC) $(FLAGS)  math2polnot.c -c

#math2polnot.h

#complex_expression.o: complex_expression.c complex_expression.h 
#	 $(CC) $(FLAGS)  complex_expression.c -c

#complex_expression.h

read_and_calculate.o: read_and_calculate.c model_of_expresson.h read_and_calculate.h 
	 $(CC) $(FLAGS)  read_and_calculate.c -c

#parse_expr_01.h: complex_expression.h 
#parse_expr_02.h: complex_expression.h 

#parse_expr_01.o: parse_expr_01.c parse_expr_01.h parser_debug.h complex_expression.h
#	 $(CC) $(FLAGS)  parse_expr_01.c -c

#parse_expr_02.o: parse_expr_02.c parse_expr_02.h complex_expression.h parser_debug.h model_of_expresson.h 

#parse_expr_03.h: complex_expression.h 
#parse_expr_03.o: complex_expression.h parse_expr_03.h parser_debug.h model_of_expresson.h

#model_of_expresson.h
#parse_expr_04.h: model_of_expresson.h 

model_of_expression.o: model_of_expression.c model_of_expresson.h model_of_expresson.h
	 $(CC) $(FLAGS)  model_of_expression.c -c

parse_expr_04.o: parse_expr_04.c model_of_expresson.h parse_expr_04.h parser_debug.h semantic_processor_01.h 
	 $(CC) $(FLAGS)  parse_expr_04.c -c

#semantic_processor_01.h: semantic_processor_01.h model_of_expresson.h 

math_function_def_01.o: math_function_def_01.c math_function_def_01.h model_of_expresson.h
	 $(CC) $(FLAGS)  math_function_def_01.c -c

#math_function_def_01.h: model_of_expresson.h 

semantic_processor_01.o: semantic_processor_01.c semantic_processor_01.h model_of_expresson.h math_function_def_01.h 
	 $(CC) $(FLAGS)  semantic_processor_01.c -c

#read_and_calculate.h

#parser_debug.h: model_of_expresson.h 
parser_debug.o: parser_debug.c model_of_expresson.h parser_debug.h 
	 $(CC) $(FLAGS) parser_debug.c -c

.PHONY: clean

clean:
	- rm *.o math_parser_01
