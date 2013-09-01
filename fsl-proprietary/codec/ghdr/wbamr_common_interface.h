
/**********************************************************************
*
* Motorola Inc.
* (c) Copyright 2004 Motorola, Inc.
* ALL RIGHTS RESERVED.
*
***********************************************************************
*
*  Copyright (c) 2011, Freescale Semiconductor Inc.,
*  All Rights Reserved.
*
*  The following programs are the sole property of Freescale Semiconductor Inc.,
*  and contain its proprietary and confidential information.
*
***********************************************************************
* File Name			: WBAMR_COMMON_INTERFACE.H
*
* Description		: Common macros for WBAMR Decoder and Encoder.
*
* Functions Included: --NONE--
*
****************************** Change History**************************
*
*    DD/MM/YYYY     Code Ver     Description      Author
*    -----------     --------     -----------      ------
*	 03/11/2004		1.0			Initial version		Shashi/Naganna
**********************************************************************/

#ifndef _WBAMR_COMMON_INTERFACE_H_
#define	_WBAMR_COMMON_INTERFACE_H_

#ifdef TGT_OS_VRTX
#define alloc_fast(x)	MALLOC(x)
#define alloc_slow(x)	MALLOC(x)
#else
#define alloc_fast(x)	malloc(x)
#define alloc_slow(x)	malloc(x)
#endif

#ifdef __SYMBIAN32__
#define EXPORT_C __declspec(dllexport)
#else
#define EXPORT_C
#endif

#define WBAMR_TRUE	         	1
#define WBAMR_FALSE				0
#define WBAMR_SUCCESS			0
#define WBAMR_FAILURE 			1
#define WBAMR_FAST_MEMORY       0
#define WBAMR_SLOW_MEMORY       1
#define WBAMR_MAX_NUM_MEM_REQS	2
#define WBAMR_MEM_TYPE			WBAMR_FAST_MEMORY
#define WBAMR_MAX_SERIAL_SIZE	477
#define WBAMR_SERIAL_FRAMESIZE 	(1+WBAMR_MAX_SERIAL_SIZE+2)
#define WBAMR_L_FRAME      		320

/* this is start of log message */
#define WBAMRC_BEGIN_DBG_MSGID  200
/* end of debug msg id */
#define WBAMRC_END_DBG_MSGID    299

/* mode 6.60 kbps */
#define WBAMR_MODE_6_60		0

/* mode 8.85 kbps */
#define WBAMR_MODE_8_85		1
/* mode 12.65 kbps */
#define WBAMR_MODE_12_65	2
/* mode 14.25 kbps */
#define WBAMR_MODE_14_25	3
/* mode 15.85 kbps */
#define WBAMR_MODE_15_85	4
/* mode 18.25 kbps */
#define WBAMR_MODE_18_25	5
/* mode 19.85 kbps */
#define WBAMR_MODE_19_85	6
/* mode 23.05 kbps */
#define WBAMR_MODE_23_05	7
/* mode 23.85 kbps */
#define WBAMR_MODE_23_85	8


/********************** Data types ******************************/

/******** define 8 bit signed/unsigned types & constants ********/

typedef signed char WBAMR_S8;
typedef unsigned char WBAMR_U8;


/******** define 16 bit signed/unsigned types & constants *********/

typedef short WBAMR_S16;
typedef unsigned short WBAMR_U16;


/********define 32 bit signed/unsigned types & constants *********/

typedef int WBAMR_S32;
typedef unsigned int WBAMR_U32;

typedef enum {
	WBAMR_STATIC,
	WBAMR_SCRATCH
}WBAMRMemType;

#endif

