# Copyright 2020-2024 plapacz6@gmail.com

# This file is part of math_parser_01.

# math_parser_01 is free software: you can redistribute it and/or modify it under
# the terms of the GNU Lesser General Public License as published by the Free
# Software Foundation, either version 3 of the License, or (at your option) any
# later version.

# math_parser_01 is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
# FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more
# details.

# You should have received a copy of the GNU Lesser General Public License along
#  with math_parser_01. If not, see <https://www.gnu.org/licenses/>.

cmake_minimum_required (VERSION 3.6)
project(math_parser VERSION 0.0.1)
set (CMAKE_C_STANDARD 90)
#set (CMAKE_BUILD_TYPE Release)
set (CMAKE_BUILD_TYPE Debug)

set (PROJECT_SRC_DIR ./)
add_executable(math_parser /
  complex_expression.c /
  main.c /
  math2polnot.c /
  math_function_def_01.c /
  model_of_expression.c / 
  parse_expr_04.c /
  parser_debug.c /
  read_and_calculate.c /
  semantic_processor_01.c /
  tests_db.c /
  )
#parse_expr_01.c  #parse_expr_02.c #parse_expr_03.c /
  
target_compile_optIons(math_parser PRIVATE  -g -Wall /
-DEBUG_PRINT_READ / #print some info in calulating phase
#-DDEBUG -DDEBUG_ /
-DDEBUG_LEVEL / #TODO: 
#-DDEBUG2 /
#-DDEBUG1 /
#-DDEBUG3 /
#-DDEBUG_PRINT_READ /
-DPRINT_INFO / #print some info at parser phase
)

target_include_directories(math_parser PUBLIC ${PROJECT_SRC_DIR})


