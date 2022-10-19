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

  #parse_expr_01.c  #parse_expr_02.c #parse_expr_03.c \

target_compile_optIons(math_parser PRIVATE  -g -Wall -DDEBUG -DDEBUG_ -DDEBUG_LEVEL -DDEBUG2 -DDEBUG1 -DDEBUG3 -DDEBUG_PRINT_READ -DPRINT_INFO)
#target_compile_optIons(math_parser PRIVATE  -g -Wall -DDEBUG -DDEBUG_ -DDEBUG2 -DDEBUG1 -DDEBUG3 -DDEBUG_PRINT_READ -DPRINT_INFO)
target_include_directories(math_parser PUBLIC ${PROJECT_SRC_DIR})


