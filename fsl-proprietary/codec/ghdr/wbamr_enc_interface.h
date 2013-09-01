
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
* File Name			: WBAMR_ENC_INTERFACE.H
*
* Description		: WBAMR Encoder interface header.
*
* Functions Included: --NONE--
*
****************************** Change History**************************
*
*    DD/MM/YYYY     Code Ver     Description      Author
*    -----------     --------     -----------      ------
*	 27/10/2004		1.0			Initial version		Shashi/Naganna
**********************************************************************/


#ifndef _WBAMR_ENC_INTERFACE_H_
#define	_WBAMR_ENC_INTERFACE_H_

#include "wbamr_common_interface.h"

/* this should be set to 0xF to enable all the debug level logs
 * value of 0x1 will enbale - log level 1 only
 * value of 0x2 will enable - log level 2 only
 * value of 0x3 will enable - level 1 and 2 logs
 * value of 0x4 will enable - level 3 logs
 * value of 0x8 will enabel - level 4 log
 */
#define WBAMRE_DEBUG_LVL 0x0

/* this is start of log message */
#define WBAMRE_BEGIN_DBG_MSGID   0
/* end of debug msg id */
#define WBAMRE_END_DBG_MSGID     199

/* for future use */
#define BEGIN_WBAMRE_DATA		NULL /* to be decided by application */

#define WBAMRE_NUM_WARNING	  20
#define WBAMRE_NUM_RECOVERROR 20
#define WBAMRE_WARNING_BASE   11
#define WBAMRE_RECOVERROR_BASE (WBAMRE_NUM_WARNING+WBAMRE_WARNING_BASE)
#define WBAMRE_FATALERROR_BASE (WBAMRE_RECOVERROR_BASE+WBAMRE_NUM_RECOVERROR)


/***** Encoder return type, other return value to be added ****/
/* Success is assigned to 0. As of now there can be 20 warnings, starting from 11 to 30.
Recoverable errors can be 20, starting from 31 to 50. Fatal errors can be 20, starting from 51 to 70. Later more error types can be added */

typedef enum
{
     WBAMRE_OK,
     WBAMRE_WARNING = WBAMRE_WARNING_BASE,			/* Warning */
     WBAMRE_INVALID_MODE = WBAMRE_RECOVERROR_BASE,	/* Recoverable error */
     WBAMRE_INIT_ERROR,								/* Recoverable error */
     WBAMRE_MEMALLOC_ERROR = WBAMRE_FATALERROR_BASE/* Fatal error */

} WBAMRE_RET_TYPE;

													/* transmitted speech frame enum */
typedef enum
{
	 WBAMRE_TX_SPEECH = 0,
     WBAMRE_TX_SID_FIRST,
     WBAMRE_TX_SID_UPDATE,
     WBAMRE_TX_NO_DATA,
     WBAMRE_TX_N_FRAMETYPES							/* number of frame types */
} WBAMRE_TXFrameType;

/****************** Structure/Union ******************/

typedef struct
{
	WBAMR_S32		wbamre_size;					/* Size in bytes */
	WBAMRMemType	wbamre_mem_type;				/* Static or scratch */
	WBAMR_S32 		wbamre_type_fs;					/* Fast or Slow */
	WBAMR_U8		wbamre_priority;				/* Priority level */
	void			*wbappe_base_ptr;				/* Pointer to the base memory, which will be
														allocated and filled by the application*/
} WBAMRE_Mem_Alloc_Info_Sub;

													/*Memory information structure array*/
typedef struct
{
	WBAMR_S32					wbamre_num_reqs;	/* Number of valid memory requests */
	WBAMRE_Mem_Alloc_Info_Sub 	mem_info_sub[WBAMR_MAX_NUM_MEM_REQS];
} WBAMRE_Mem_Alloc_Info;


													/* encoder parameter structure */
typedef struct
{
	WBAMRE_Mem_Alloc_Info	wbamre_mem_info;
	void				    *wbamre_encode_info_struct_ptr;
    WBAMR_U8                *wbappe_initialized_data_start;
	WBAMR_S32				wbappe_dtx_flag;
	WBAMR_S16				*wbappe_mode;
	WBAMR_U16				*wbamre_output_size;
	WBAMR_U8				wbamre_output_format;
	WBAMR_U8               watermarkFlag;
} WBAMRE_Encoder_Config;


/* c prototypes */

#ifdef __cplusplus
extern "C"
{
#endif

 WBAMRE_RET_TYPE wbamre_query_enc_mem(
				WBAMRE_Encoder_Config *enc_config);

 WBAMRE_RET_TYPE wbamre_encode_init(
				WBAMRE_Encoder_Config *enc_config);

 WBAMRE_RET_TYPE wbamre_encode_frame (
				WBAMRE_Encoder_Config *enc_config,
				WBAMR_S16 *in_buf,
				WBAMR_S16 *out_buf);
 const char *WBAMR_get_version_info(void);

#ifdef __cplusplus
}
#endif

#endif

