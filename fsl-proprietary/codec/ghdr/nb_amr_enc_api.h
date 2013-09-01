/*******************************************************************************
*
* Motorola Inc.
* (c) Copyright 2004 Motorola, Inc.
* ALL RIGHTS RESERVED.
*
********************************************************************************
*
* File Name: nb_amr_enc_api.h
*
* Description: This is a header file corresponding to nb_amr_enc_api.c.
*/
/************************************************************************
 * Copyright (c) 2005-2011, Freescale Semiconductor Inc.,
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
*   01/Jul/2008     1.2          Added version API Tao Jun
*
*******************************************************************************/
#ifndef NB_AMR_ENC_API_H
#define NB_AMR_ENC_API_H
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

#define NBAMRE_DBGLOG_LVL 0x0

/* start val of debug log msg id, should be modified as per integration
 * requirement
 */
#define NBAMRE_BEGIN_DBGLOG_MSGID  200
/* end of debug log message */
#define NBAMRE_END_DBGLOG_MSGID  399

/******************************<DEFINES END>***********************************/

/******************************<ENUMS BEGIN>***********************************/
/***** Encoder return type, other return value to be added ****/
/* Success is assigned to 0. As of now there can be 20 warnings,
   starting from 11 to 30. Recoverable errors can be 20, starting
   from 31 to 50. Fatal errors can be 20, starting from 51 to 70.
   Later more error types can be added */
typedef enum
{
     E_NBAMRE_OK =0,
     E_NBAMRE_WARNING = NBAMR_WARNING_BASE,
     E_NBAMRE_INVALID_MODE = NBAMR_RECOVERROR_BASE,
     E_NBAMRE_INIT_ERROR,
     E_NBAMRE_INVALID_ENCODER_ARGS,
     E_NBAMRE_INPUT_READERROR,
     E_NBAMRE_MEMALLOC_ERROR = NBAMR_FATALERROR_BASE,
     E_NBAMRE_ERROR
} eAMREReturnType;
/******************************<ENUMS END>*************************************/

/****************************<STRUCTURES/UNIONS BEGIN>*************************/
typedef struct
 {
	NBAMR_S32	s32AMRESize;	    /* Size in bytes */
	NBAMR_S32 	s32AMREMemType;	    /* Memory is static or scratch */
	NBAMR_S32 	s32AMREMemTypeFs;	/* Memory type FAST or SLOW */
	NBAMR_Void	*pvAPPEBasePtr;	    /* Pointer to the base memory,
						               that will be allocated
						               and  filled by the application*/
	NBAMR_U8	u8AMREMemPriority;	/* Priority level */
} sAMREMemAllocInfoSubType;

/*Memory information structure array*/
typedef struct
{
	/* Number of valid memory requests */
	NBAMR_S32				    s32AMRENumMemReqs;
	sAMREMemAllocInfoSubType 	asMemInfoSub[NBAMR_MAX_NUM_MEM_REQS];
} sAMREMemAllocInfoType;

/* encoder parameter structure */
typedef struct
{
	sAMREMemAllocInfoType   sAMREMemInfo;
	NBAMR_Void			    *pvAMREEncodeInfoPtr;
    NBAMR_U8                *pu8APPEInitializedDataStart;
	NBAMR_S16			    s16APPEDtxFlag;
	NBAMR_S8			    **pps8APPEModeStr;
	NBAMR_S8		        **pps8AMREUsedModeStr;
	NBAMR_U32               *pu32AMREPackedSize; /* size of packed data in case of
                                                   MMS, IF1 and IF2 */
    NBAMR_U8                u8BitStreamFormat;
    NBAMR_U8                u8NumFrameToEncode;    /* number of frame to be encoded */
    NBAMR_U8                watermarkFlag;         /* watermark Flag for codec protection */
} sAMREEncoderConfigType;
/****************************<STRUCTURES/UNIONS END>***************************/

/***************************<GLOBAL_VARIABLES BEGIN>***************************/
                                    /* None */
/***************************<GLOBAL_VARIABLES END>*****************************/

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
 EXTERN eAMREReturnType eAMREEncodeInit (sAMREEncoderConfigType *psEncConfig);

 EXTERN eAMREReturnType eAMREEncodeFrame (
                sAMREEncoderConfigType *psEncConfig,
				NBAMR_S16 *ps16InBuf,NBAMR_S16 *ps16OutBuf);

 EXTERN eAMREReturnType eAMREQueryMem (
                sAMREEncoderConfigType *psEncConfig);
  const char * eAMREVersionInfo(void);
#ifdef __cplusplus
}
#endif
/**************************<FUNCTION_PROTOTYPES END>***************************/
#endif /* end of NB_AMR_ENC_API_H header file */
/**************************<END OF THE FILE>***********************************/
