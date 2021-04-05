#ifndef __BASIC_TYPES_H__
#define __BASIC_TYPES_H__

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> 

#define FALSE (bool)0U
#define TRUE (bool)!FALSE

#define VAL_ZERO (Cplr_val)0LU
#define VAL_MINUS_ONE (Cplr_val)-1L
#define VAL_TWO (Cplr_val)2L
#define VAL_ONE (Cplr_val)1L

#define ERROR_PRINT(msg)\
    do{\
        printf("Error: ");perror("");puts("");\
        printf("%s in FUNCTION: %s\n", msg, __func__);\
        printf("FILE: %s in LINE: %d\n", __FILE__, __LINE__);\
        exit(EXIT_FAILURE);\
    }while(FALSE)


#ifdef __SIZEOF_INT128__

typedef __int128 Cplr_index;
typedef __int128 Cplr_id;
typedef __int128 Cplr_val;
typedef char *Cplr_name;

#else

typedef int64_t Cplr_index;
typedef int64_t Cplr_id;
typedef int64_t Cplr_val;
typedef char *Cplr_name;

#endif


#endif /*__BASIC_TYPES_H__*/
