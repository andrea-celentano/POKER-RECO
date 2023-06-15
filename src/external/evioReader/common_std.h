/**
 * Definitions of integers. ROOT CINT has problems parsing stdint.h file.
 * this file defines commonly used integers to avoid problems with CINT.
 */

#ifndef __COMMON_STD__
#define __COMMON_STD__

#include <stdio.h>
#include <stdlib.h>
//#include <stdint.h>
//#include <sys/types.h>

/*#if (defined(__APPLE__))

#ifndef uint8_t
typedef unsigned char uint8_t;
#endif

//#ifndef int8_t
//typedef char int8_t;
//#endif

#ifndef uint32_t
typedef unsigned __INT32_TYPE__ uint32_t;
#endif

#ifndef int32_t
typedef __INT32_TYPE__ int32_t;
#endif

#ifndef uint16_t
typedef unsigned __INT16_TYPE__ uint16_t;
#endif

#ifndef int16_t
typedef __INT16_TYPE__ int16_t;
#endif

#ifndef int64_t
typedef long long int64_t;
#endif

#else 
*/
#include <stdint.h>
#include <string.h>

//#endif

#endif
/**
 * End 
 */
