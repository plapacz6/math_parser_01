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