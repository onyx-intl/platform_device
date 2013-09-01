
/**********************************************************************
*
* Motorola Inc.
* (c) Copyright 2004 Motorola, Inc.
* ALL RIGHTS RESERVED.
*
***********************************************************************
*  Copyright (c) 2011, Freescale Semiconductor Inc.,
*  All Rights Reserved.
*
*  The following programs are the sole property of Freescale Semiconductor Inc.,
*  and contain its proprietary and confidential information.
*
************************************************************************
*
* File Name			: WBAMR_DEC_INTERFACE.H
*
* Description		: WBAMR Decoder interface.
*
* Functions Included: --NONE--
*
****************************** Change History**************************
*
*    DD/MM/YYYY     Code Ver     Description      Author
*    -----------     --------     -----------      ------
*	 03/11/2004		1.0			Initial version		Shashi/Naganna
**********************************************************************/

#ifndef _WBAMR_DEC_INTERFACE_H_
#define	_WBAMR_DEC_INTERFACE_H_

#include "wbamr_common_interface.h"
#include <stdio.h>
#include <stdlib.h>

/* this should be set to 0xF to enable all the debug level logs
 * value of 0x1 will enbale - log level 1 only
 * value of 0x2 will enable - log level 2 only
 * value of 0x3 will enable - level 1 and 2 logs
 * value of 0x4 will enable - level 3 logs
 * value of 0x8 will enabel - level 4 log
 */
#define WBAMRD_DEBUG_LVL 0x0

/* this is start of log message */
#define WBAMRD_BEGIN_DBG_MSGID  300
/* end of debug msg id */
#define WBAMRD_END_DBG_MSGID    600

#define BEGIN_WBAMRD_DATA		NULL		/* to be decided by
							application */
/***************** Data types ************************************/
#define WBAMRD_NUM_WARNING 20
#define WBAMRD_NUM_RECOVERROR 20
#define WBAMRD_WARNING_BASE 111
#define WBAMRD_RECOVERROR_BASE (WBAMRD_NUM_WARNING+WBAMRD_WARNING_BASE)
#define WBAMRD_FATALERROR_BASE (WBAMRD_RECOVERROR_BASE+WBAMRD_NUM_RECOVERROR)


/***** Decoder return type, other return value to be added ****/
/* Success is assigned to 0. As of now there can be 20 warnings, starting from 111 to 130.
Recoverable errors can be 20, starting from 131 to 150. Fatal errors can be 20, starting from 151 to 170. Later more error types can be added */

typedef enum
{
     WBAMRD_OK,
     WBAMRD_WARNING = WBAMRD_WARNING_BASE,			/* Warning */
     WBAMRD_INVALID_MODE = WBAMRD_RECOVERROR_BASE,	/* Recoverable error */
     WBAMRD_INIT_ERROR,								/* Recoverable error */
     WBAMRD_MEMALLOC_ERROR = WBAMRD_FATALERROR_BASE/* Fatal error */
} WBAMRD_RET_TYPE;

/* received speech frame enum */
typedef enum
{
	 WBAMRD_RX_SPEECH_GOOD = 0,
     WBAMRD_RX_SPEECH_PROBABLY_DEGRADED,
     WBAMRD_RX_SPEECH_LOST,
     WBAMRD_RX_SPEECH_BAD,
     WBAMRD_RX_SID_FIRST,
     WBAMRD_RX_SID_UPDATE,
     WBAMRD_RX_SID_BAD,
     WBAMRD_RX_NO_DATA,
     WBAMRD_RX_N_FRAMETYPES							/* number of frame types */
} WBAMRD_RXFrameType;

/******************** Structure/Union ***************************/
/* decoder sub-memory array */
typedef struct
{
	WBAMR_S32		wbamrd_size;				/* Size in bytes */
	WBAMRMemType 	wbamrd_mem_type;  			/* Static or scratch */
	WBAMR_S32 		wbamrd_type_fs;				/* Fast or Slow */
	WBAMR_U8 		wbamrd_priority;			/* Priority level */
	void			*wbappd_base_ptr;			/* Pointer to the base memory, which will be
												   allocated and filled by the application*/
}WBAMRD_Mem_Alloc_Info_Sub;

/* decoder memory info structure */
typedef struct
{
	WBAMR_S32					wbamrd_num_reqs;/* Number of valid memory requests */
	WBAMRD_Mem_Alloc_Info_Sub 	mem_info_sub[WBAMR_MAX_NUM_MEM_REQS];
}WBAMRD_Mem_Alloc_Info;

/* decoder parameter structure */
typedef struct
{
	WBAMRD_Mem_Alloc_Info     wbamrd_mem_info;
	void				      *wbamrd_decode_info_struct_ptr;
    WBAMR_U8                  *wbappd_initialized_data_start;
    WBAMR_U8                  bitstreamformat;
    WBAMR_U8                  watermarkFlag;
}WBAMRD_Decoder_Config;

#ifdef __cplusplus
extern "C"
{
#endif

 WBAMRD_RET_TYPE wbamrd_query_dec_mem(WBAMRD_Decoder_Config *dec_config);

 WBAMRD_RET_TYPE wbamrd_decode_init (WBAMRD_Decoder_Config *dec_config);

 WBAMRD_RET_TYPE wbamrd_decode_frame (WBAMRD_Decoder_Config *dec_config,
				WBAMR_S16 *in_buf,
				WBAMR_S16 *out_buf);
 const char *WBAMR_get_version_info(void);

#ifdef __cplusplus
}
#endif

#endif
