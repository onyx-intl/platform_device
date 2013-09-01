/*******************************************************************************
*
* Motorola Inc.
* (c) Copyright 2004 Motorola, Inc.
* ALL RIGHTS RESERVED.
*
********************************************************************************
* File Name: nb_amr_dec_api.h
*
* Description: This is a header file for nb_amr_dec_api.c.
*/
/************************************************************************
 * Copyright 2005-2010 by Freescale Semiconductor, Inc.
 * All modifications are confidential and proprietary information
 * of Freescale Semiconductor, Inc.
 ************************************************************************/
/****************************** Change History***********************************
*
*   DD/MMM/YYYY     Code Ver     Description      Author
*   -----------     --------     -----------      ------
*   20/May/2004     0.1          File created     Ashok
*   03/Jun/2004     1.0          Review rework    Ashok
*   22/Jul/2004     1.1          Clened up code    Ashok
*   01/Jul/2008     1.2          Added version    Tao Jun
*                                API
*******************************************************************************/
#ifndef NB_AMR_DEC_API_H
#define NB_AMR_DEC_API_H

/*****************************<INCLUDE_FILES BEGIN>****************************/
#ifndef _OS_VRTX
#include <stdio.h>
#endif
#include "nb_amr_common_api.h"
/*******************************<INCLUDE_FILES END>****************************/

/******************************<DEFINES BEGIN>*********************************/

/* this define should be set to non-zero val to enable debug log
 * Following are the value and corresponding enabling
 * 0x0 -> log disbale
 * 0x1 -> log level 0 enable
 * 0x2 -> log level 1 will get enabled
 * 0x3 -> 0 and 1 both will get enabled
 * 0x4 -> log level 2 will be enabled
 * 0xf -> all log level will be enabled
 */

#define NBAMRD_DBGLOG_LVL 0x0

/* start val of debug log msg id */
#define NBAMRD_BEGIN_DBGLOG_MSGID  400
/* end of debug log message */
#define NBAMRD_END_DBGLOG_MSGID  499
/******************************<DEFINES END>***********************************/

/******************************<ENUMS BEGIN>***********************************/
/* Success is assigned to 0. As of now there can be 20 warnings,
   starting from 11 to 30. Recoverable errors can be 20,
   starting from 31 to 50. Fatal errors can be 20, starting
   from 51 to 70. Later more error types can be added */

/***** Decoder return type, other return value to be added ****/
typedef enum
{
     E_NBAMRD_OK =0,
     E_NBAMRD_WARNING = NBAMR_WARNING_BASE,
     E_NBAMRD_INVALID_MODE = NBAMR_RECOVERROR_BASE,
     E_NBAMRD_INIT_ERROR,
     E_NBAMRD_INVALID_DECODER_ARGS,
     E_NBAMRD_INVALID_BITSTREAM,
     E_NBAMRD_INPUT_READERROR,
     E_NBAMRD_MEMALLOC_ERROR = NBAMR_FATALERROR_BASE,
     E_NBAMRD_ERROR
} eAMRDReturnType;

/******************************<ENUMS END>*************************************/

/****************************<STRUCTURES/UNIONS BEGIN>*************************/
/* decoder sub-memory array */
typedef struct
{
	NBAMR_S32	s32AMRDSize;	  /* Size in bytes */
	NBAMR_S32 	s32AMRDMemType;	  /* Memory is STATIC or SCRATCH */
	NBAMR_S32 	s32AMRDMemTypeFs; /* Memory type FAST or SLOW */
	NBAMR_Void	*pvAPPDBasePtr;	  /* Pointer to the base memory,
	                               which will be allocated
 						           and filled by the application*/
	NBAMR_U8	u8AMRDMemPriority; /* Priority level */

} sAMRDMemAllocInfoSubType;

/* decoder memory info structure */
typedef struct
{
	/* Number of valid memory requests */
	NBAMR_S32				s32AMRDNumMemReqs;
	sAMRDMemAllocInfoSubType 	asMemInfoSub[NBAMR_MAX_NUM_MEM_REQS];
}sAMRMemAllocInfoType;

/* decoder parameter structure */
typedef struct
{
	sAMRMemAllocInfoType  sAMRDMemInfo;
	NBAMR_Void           *pvAMRDDecodeInfoPtr;
    NBAMR_U8             *pu8APPDInitializedDataStart;
    NBAMR_U8             u8RXFrameType;        /* whether frame is contains RX frame */
    NBAMR_U8             u8BitStreamFormat;    /* Requested file format */
    NBAMR_U8             u8NumFrameToDecode;    /* number of frame to be decoded */
    NBAMR_U8             watermarkFlag;         /* watermark Flag for codec protection */
}sAMRDDecoderConfigType;
/****************************<STRUCTURES/UNIONS END>***************************/

/***************************<GLOBAL_VARIABLES BEGIN>***************************/
                                   /* None */
/***************************<GLOBAL_VARIABLES END>*****************************/
                                   /* None */
/**************************<STATIC_VARIABLES BEGIN>****************************/
                                    /* None */
/**************************<STATIC_VARIABLES END>******************************/

/**************************<FUNCTION_PROTOTYPES BEGIN>*************************/
#ifdef __SYMBIAN32__
#define EXTERN
#define EXPORT_C __declspec(dllexport)
#else
#define EXTERN
#define EXPORT_C
#endif
#ifdef __cplusplus
extern "C"
{
#endif
  eAMRDReturnType eAMRDDecodeInit (sAMRDDecoderConfigType *psDecConfig);

  eAMRDReturnType eAMRDDecodeFrame (sAMRDDecoderConfigType *psDecConfig,
			NBAMR_S16 *ps32InBuf, NBAMR_S16 *ps32OutBuf);

  eAMRDReturnType eAMRDQueryMem (sAMRDDecoderConfigType *psDecConfig);

  const char * eAMRDVersionInfo(void);
#ifdef __cplusplus
}
#endif
/**************************<FUNCTION_PROTOTYPES END>***************************/

#endif /* end of NB_AMR_DEC_API_H header file */
/**************************<END OF THE FILE>***********************************/
