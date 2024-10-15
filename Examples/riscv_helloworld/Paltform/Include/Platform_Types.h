#ifndef PLATFORM_TYPES_H
#define PLATFORM_TYPES_H

#ifndef TRUE
#define TRUE (1u)
#endif
#ifndef FALSE
#define FALSE (0u)
#endif

typedef unsigned char boolean;
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long uint64;
typedef signed char sint8;
typedef signed short sint16;
typedef signed int sint32;
typedef signed long long sint64;

typedef unsigned int uint8_least;
typedef unsigned int uint16_least;
typedef unsigned int uint32_least;

typedef signed int sint8_least;
typedef signed int sint16_least;
typedef signed int sint32_least;

typedef float float32;
typedef double float64;

typedef boolean bool;

#endif /* #ifndef PLATFORM_TYPES_H */
