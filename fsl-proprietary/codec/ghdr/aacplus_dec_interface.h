
/************************************************************************
 * Copyright 2005-2010 by Freescale Semiconductor, Inc.
 * All modifications are confidential and proprietary information
 * of Freescale Semiconductor, Inc. ALL RIGHTS RESERVED.
 ************************************************************************/

/*****************************************************************************
 *
 * File Name: aacpd_dec_interface.h
 *
 * Description: aacplus decoder interface.
 *
 ****************************** Change History********************************
 *
 *   DD/MMM/YYYY     Code Ver     Description                   Author
 *   -----------     --------     -----------                   ------
 *   08/Jun/2005     0.1          File created                  Tommy Tang
 *   08/Jun/2005     0.2          redefine macro                Webber Wang
 *                                AACPD_MAX_NUM_MEM_REQS
 *                                add enum type AACPD_MEMALIGN.
 *                                add element aacd_mem_align in
 *                                structure AACPD_Mem_Alloc_Info_Sub
 *  20/Aug/2005      0.3          AACPD_OutputFmtType made as   Ganesh Kumar C
 *                                short/long depending on flag
 *                                "OUTPUT_24BITS"
 *  29/Aug/2005      1.0          Increased MAX_NUM_MEM_REQS by 1   Ashok Kumar
 *                                to add SBR decoder scratch and
 *                                added SBR decoder related error
 *                                return
 *  29/Dec/2007      1.1          Merged AAC LC optimized code and
 *                                changed to interleave output      Bing Song
 *  13/Feb/2009      2.2          support envoke AAC LC lib         Lyon Wang
 ******************************************************************************/

#ifndef _AACPD_DEC_INTERFACE_H
#define _AACPD_DEC_INTERFACE_H

#include "aacd_dec_interface.h"

#define AACP_FRAME_SIZE          2048
#define AACPD_INPUT_BUFFER_SIZE  6*768

typedef struct
{
  long bit_counter;
  unsigned long bit_register;
  unsigned char *bs_curr;
  unsigned char *bs_end;
  unsigned char *bs_curr_ext;
  unsigned char *bs_end_ext;
  unsigned int bs_eof;
  unsigned int bs_seek_needed;
} BitstreamParam;


#ifdef __cplusplus
extern "C"
{
#endif
typedef enum
{
    NO_SBR_FRAME, /* indicate no sbr information */
    SBR_FRAME     /* indicate sbr information contained */
}SBR_FRAME_TYPE;

extern const char * AACPDCodecVersionInfo ();
EXTERN AACD_RET_TYPE aacpd_query_dec_mem ( AACD_Decoder_Config *dec_config);
EXTERN AACD_RET_TYPE SBRD_decoder_init(AACD_Decoder_Config *dec_config);

EXTERN AACD_RET_TYPE SBRD_decode_frame(
        AACD_Decoder_Config *dec_config,
        AACD_Decoder_info *dec_info,
        AACD_INT32 *out_buf,
        SBR_FRAME_TYPE * sbr_frame_type);

#ifdef __cplusplus
}
#endif
#endif

/**************************<END OF THE FILE>***********************************/

