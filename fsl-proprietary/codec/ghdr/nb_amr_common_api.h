/*******************************************************************************
*
* Motorola Inc.
* (c) Copyright 2004 Motorola, Inc.
* ALL RIGHTS RESERVED.
*
********************************************************************************
* File Name: nb_amr_common_api.h
*
* Description: This is common header file included by encoder and decoder both
*************************************************************************
  * Copyright 2005-2010 by Freescale Semiconductor, Inc.
  * All modifications are confidential and proprietary information
  * of Freescale Semiconductor, Inc.
  ************************************************************************/
/****************************** Change History***********************************
*   DD/MMM/YYYY     Code Ver     Description      Author
*   -----------     --------     -----------      ------
*   20/May/2004     0.1          File created     Ashok
*   02/Jun/2004     1.0          Review rework    Ashok
*   20/Jul/2004     1.1          Implemented        Ashok
*                                API based on the
*                                doc
*******************************************************************************/
#ifndef NB_AMR_COMMON_API_H
#define NB_AMR_COMMON_API_H
/*****************************<INCLUDE_FILES BEGIN>****************************/
#ifndef _OS_VRTX
#include <stdio.h>
#endif
/*******************************<INCLUDE_FILES END>****************************/
/******************************<DEFINES BEGIN>*********************************/
#define     NBAMR_TRUE     1
#define     NBAMR_FALSE    0
#define     NBAMR_SUCCESS  0
#define     NBAMR_FAILURE  1
#define     NBAMR_MEM_STATIC      0
#define     NBAMR_MEM_SCRATCH     1
#define     NBAMR_FAST_MEMORY     0
#define     NBAMR_SLOW_MEMORY     1
#define     NBAMR_MAX_NUM_MEM_REQS	20
#define     NBAMR_PRIORITY_LOWEST  255
#define     NBAMR_PRIORITY_NORMAL  128
#define     NBAMR_PRIORITY_HIGHEST 0

/* for future use */
#define     NBAMR_BEGIN_DATA TBD /* to be decided by application */
#define     NBAMR_MEM_TYPE        FAST_MEMORY

#define     MAX_SERIAL_SIZE 244
#define     SERIAL_FRAMESIZE    (1+MAX_SERIAL_SIZE+5)
#define     L_FRAME         160

#define     NBAMR_WARNING_BASE	    11
#define     NBAMR_RECOVERROR_BASE	31
#define     NBAMR_FATALERROR_BASE	51

#define    NBAMR_MAX_NUM_MODES      16

/********************** Data types ******************************/

/********define 8 bit signed/unsigned types & constants *********/
typedef void	NBAMR_Void;
typedef signed char NBAMR_S8;
typedef unsigned char NBAMR_U8;

/********define 16 bit signed/unsigned types & constants *********/

typedef short NBAMR_S16;
typedef unsigned short NBAMR_U16;

/********define 32 bit signed/unsigned types & constants *********/
typedef long NBAMR_S32;
typedef unsigned long NBAMR_U32;

#define NBAMR_MAGIC_NUMBER           "#!AMR\n"
/* for MMS and IF2 file format MAX_PACKED_SIZE = MAX_SERIAL_SIZE/8 +2
 * whereas for IF1 it should be MAX_SERIAL_SIZE/8+4.
 * but to make allocation same for all the three file format
 * it is defined MAX_PACKED_SIZE/8+4 = 34 bytes
 */
#define NBAMR_MAX_PACKED_SIZE     (MAX_SERIAL_SIZE/8 + 4)

/* define used to check Non DTX configuration */
#define NBAMR_NONDTX        0
/* define used to check VAD1 configuration */
#define NBAMR_VAD1          1
/* define used to check VAD2 configuration */
#define NBAMR_VAD2          2

/* NB-AMR file format */
#define NBAMR_ETSI      0
/* MMS format */
#define NBAMR_MMSIO     1
/* IF1 format */
#define NBAMR_IF1IO     2
/* IF2 format */
#define NBAMR_IF2IO     3
/******************************<DEFINES END>***********************************/

/******************************<ENUMS BEGIN>***********************************/
                                /* NONE */
/******************************<ENUMS END>*************************************/

/****************************<STRUCTURES/UNIONS BEGIN>*************************/
                                /* NONE */
/****************************<STRUCTURES/UNIONS END>***************************/

/***************************<GLOBAL_VARIABLES BEGIN>***************************/
                                    /* None */
/***************************<GLOBAL_VARIABLES END>*****************************/

/**************************<STATIC_VARIABLES BEGIN>****************************/
                                    /* None */
/**************************<STATIC_VARIABLES END>******************************/

/**************************<FUNCTION_PROTOTYPES BEGIN>*************************/
                                   /* None */
/**************************<FUNCTION_PROTOTYPES END>***************************/
#endif /* end of NBAMR_COMMON_API_H header file */
/**************************<END OF THE FILE>***********************************/
