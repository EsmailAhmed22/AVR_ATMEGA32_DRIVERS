/******************************************************************************
 *
 * [FILE NAME]:		<Standard - Types.h>
 *
 * [AUTHOR]:		<Esmail Ahmed>
 *
 * [DATE CREATED]:	<11/3/2020>
 *
 * [DESCRIPTION]:	<Make portable types and define new ones>
 *
 *******************************************************************************/
#ifndef STD_TYPES_H_
#define STD_TYPES_H_

/* Define Boolean  Data Type */
typedef unsigned char bool;

/* Boolean FALSE Value */
#ifndef FALSE
#define FALSE	(0u)
#endif

/* Boolean TRUE Value */
#ifndef TRUE
#define TRUE	(1u)
#endif

/* Define HIGH for high output */
#ifndef HIGH
#define HIGH	(1u)
#endif

/* Define LOW for low output */
#ifndef LOW
#define LOW		(0u)
#endif

#define NULL_PTR    ((void*)0)

/* Define portable types */
typedef unsigned char		uint8;
typedef signed 	 char		sint8;
typedef unsigned short		uint16;
typedef signed   short		sint16;
typedef unsigned long		uint32;
typedef signed   long		sint32;
typedef unsigned long long	uint64;
typedef signed   long long	sint64;
typedef float				float32;
typedef double				float64;

#endif /* STD_TYPES_H_ */
