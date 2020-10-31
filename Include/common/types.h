/******************************************************************************
FileName: 		types.h
Description:   	data type definition
Author:   		Round Bridge
Date: 			2020.1.1
Modification History:
					2020.1.1 create file
Version: 		0.0.1
******************************************************************************/
#ifndef _TYPES_H_
#define _TYPES_H_

#include <platform.h>

#define NULL		0
#define TRUE		1
#define FALSE		0


enum state_code{OK=0, FAILED, NULL_PTR, PARAM_ERR=4, DATA_NOTENOUGH=8};

#ifdef PLATEFORM_X86_32

#define INT_MINI     (-2147483648)
#define INT_MAXI     (2147483647)

typedef unsigned int		state;

typedef unsigned char		uint8;
typedef unsigned short		uint16;
typedef unsigned int		uint32;
typedef unsigned int		uint;
typedef unsigned long long 	uint64;
typedef unsigned char*		puint8;
typedef unsigned char**		ppuint8;
typedef unsigned short*		puint16;
typedef unsigned int*		puint32;
typedef unsigned int*		puint;
typedef unsigned long long*	puint64;
typedef signed char			sint8;
typedef short				sint16;
typedef int					sint32;
typedef int					sint;
typedef long long 			sint64;
typedef signed char*		psint8;
typedef short*				psint16;
typedef int*				psint;
typedef int*				psint32;
typedef long long*		 	psint64;
typedef void*				pvoid;
typedef float				sf4;
typedef double				sf8;
typedef float*				psf4;
typedef double*				psf8;


typedef volatile unsigned char			uint8v;
typedef volatile unsigned char*			puint8v;
typedef volatile unsigned short			uint16v;
typedef volatile unsigned short*		puint16v;
typedef volatile unsigned int			uint32v;
typedef volatile unsigned int*			puint32v;
typedef volatile unsigned long long		uint64v;
typedef volatile unsigned long long*	puint64v;

typedef volatile signed char			sint8v;
typedef volatile signed char*			psint8v;
typedef volatile short					sint16v;
typedef volatile short*					psint16v;
typedef volatile int					sint32v;
typedef volatile int*					psint32v;
typedef volatile long long				sint64v;
typedef volatile long long*				psint64v;
typedef volatile float					sf4v;
typedef volatile double					sf8v;
typedef volatile float*					psf4v;
typedef volatile double*				psf8v;


#elif defined PLATEFORM_X86_64

#define INT_MINI     (-2147483648)
#define INT_MAXI     (2147483647)

typedef unsigned int		state;

typedef unsigned char		uint8;
typedef unsigned short		uint16;
typedef unsigned int		uint32;
typedef unsigned int		uint;
typedef unsigned long long 	uint64;
typedef unsigned char*		puint8;
typedef unsigned char**		ppuint8;
typedef unsigned short*		puint16;
typedef unsigned int*		puint32;
typedef unsigned int*		puint;
typedef unsigned long long* puint64;
typedef signed char			sint8;
typedef short				sint16;
typedef int					sint32;
typedef int					sint;
typedef long long 			sint64;
typedef signed char*		psint8;
typedef short*				psint16;
typedef int*				psint;
typedef int*				psint32;
typedef long long*			psint64;
typedef void*				pvoid;
typedef float				sf4;
typedef double				sf8;
typedef float*				psf4;
typedef double*				psf8;


typedef volatile unsigned char			uint8v;
typedef volatile unsigned char*			puint8v;
typedef volatile unsigned short			uint16v;
typedef volatile unsigned short*		puint16v;
typedef volatile unsigned int			uint32v;
typedef volatile unsigned int*			puint32v;
typedef volatile unsigned long long		uint64v;
typedef volatile unsigned long long*	puint64v;

typedef volatile signed char			sint8v;
typedef volatile signed char*			psint8v;
typedef volatile short					sint16v;
typedef volatile short*					psint16v;
typedef volatile int					sint32v;
typedef volatile int*					psint32v;
typedef volatile long long				sint64v;
typedef volatile long long*				psint64v;
typedef volatile float					sf4v;
typedef volatile double					sf8v;
typedef volatile float*					psf4v;
typedef volatile double*				psf8v;

#endif

#endif

