/*
 ***********************************************************************
 * Copyright 2005-2010 by Freescale Semiconductor, Inc.
 * All modifications are confidential and proprietary information
 * of Freescale Semiconductor, Inc. ALL RIGHTS RESERVED.
 ***********************************************************************
 */
 /***************************************************************************
 *   CHANGE HISTORY
 *   dd/mm/yy        Code Ver     Description             Author
 *   --------        -------      -----------             ------
 *   07/07/08         0.1 	      created file            Guo Yue
 **************************************************************************/
#ifndef __FLACD_DEC_INTERFACE_H_
#define __FLACD_DEC_INTERFACE_H_

#ifdef __cplusplus
#define EXTERN extern "C"
#else
#define EXTERN
#endif

//#include <stdio.h>
//#include "ordinals.h"
//#include "../src/flac/hdr/private/global_structure.h"
//#include "global_structure.h"
//#include "../../../src/flac_dec/hdr/global_structure.h"
//#include "flac/stream_decoder.h"

//#define FLACD_TRUE                  1
//#define FLACD_FALSE                 0
//***********************************************************************
//   Data type
//***********************************************************************

//#if !(defined(_MSC_VER) || defined(__BORLANDC__) || defined(__EMX__))
//#include <inttypes.h>
//#endif

typedef signed char FLAC__int8;
typedef unsigned char FLAC__uint8;
typedef short FLAC__int16;
typedef unsigned short FLAC__uint16;
typedef int FLAC__int32;
typedef unsigned int FLAC__uint32;
#if _WIN32
typedef __int64                 FLAC__int64;
typedef unsigned __int64        FLAC__uint64;
#else
typedef long long               FLAC__int64;
typedef unsigned long long      FLAC__uint64;
#endif

#if 0
#if defined(_MSC_VER) || defined(__BORLANDC__)
typedef __int16 FLAC__int16;
typedef __int32 FLAC__int32;
typedef __int64 FLAC__int64;
typedef unsigned __int16 FLAC__uint16;
typedef unsigned __int32 FLAC__uint32;
typedef unsigned __int64 FLAC__uint64;
#elif defined(__EMX__)
typedef short FLAC__int16;
typedef long FLAC__int32;
typedef long long FLAC__int64;
typedef unsigned short FLAC__uint16;
typedef unsigned long FLAC__uint32;
typedef unsigned long long FLAC__uint64;
#else
typedef int16_t FLAC__int16;
typedef int32_t FLAC__int32;
typedef int64_t FLAC__int64;
typedef uint16_t FLAC__uint16;
typedef uint32_t FLAC__uint32;
typedef uint64_t FLAC__uint64;
#endif
#endif

typedef int FLAC__bool;
typedef FLAC__uint8 FLAC__byte;

#define true 1
#define false 0

//#define NULL 0

#define FLAC_MAX_NUM_MEM_REQS             1 /* presently we need seperate chunk of memory for scratch_lf */
#define FLAC_FAST_MEMORY                  1
#define FLAC_SLOW_MEMORY                  2

/** The maximum number of channels permitted by the format. */
#define FLAC__MAX_CHANNELS (8u)

#define FLAC_INPUT_PULL_BUFFER_SIZE       (2048*sizeof(FLAC__uint32) * 8)
#define FLAC_OUTPUT_RESIDUAL              32

#define MAX_BLOCK_SIZE                    32768   // refer to format document of FLAC decoder.
#define BS_PROTECT                        8
#define SIZE_THRESHOLD                   (MAX_BLOCK_SIZE+BS_PROTECT)

#define FLAC_INPUT_BUF_PUSH_SIZE         (MAX_BLOCK_SIZE*FLAC__MAX_CHANNELS*sizeof(FLAC__uint32))

//***********************************************************************
//  struct definition
//***********************************************************************
typedef enum
{
    FLAC_STATIC_MEM,        /* 0 for static memory */
    FLAC_SCRATCH_MEM        /* 1 for scratch memory */
} FLAC_MEM_DESC;

typedef struct {
	FLAC__int32		flacd_size;     /* Size in bytes */
	FLAC__int32 	    flacd_type;	   /* Memory type Fast or Slow */
	FLAC_MEM_DESC   flacd_mem_desc; /* to indicate if it is scratch memory */
	FLAC__int32      flacd_priority; /* In case of fast memory, specify the priority */
	void 	        *app_base_ptr; /* Pointer to the base memory , which will be allocated and filled by the  application */
} FLAC_Mem_Alloc_Info_Sub;

typedef struct {
	FLAC__int32             flacd_num_reqs;
	FLAC_Mem_Alloc_Info_Sub	mem_info_sub[FLAC_MAX_NUM_MEM_REQS];
} FLAC_Mem_Alloc_Info;
#if 0
typedef enum {

	FLAC__STREAM_DECODER_READ_STATUS_CONTINUE,
	/**< The read was OK and decoding can continue. */

	FLAC__STREAM_DECODER_READ_STATUS_END_OF_STREAM,
	/**< The read was attempted while at the end of the stream.  Note that
	 * the client must only return this value when the read callback was
	 * called when already at the end of the stream.  Otherwise, if the read
	 * itself moves to the end of the stream, the client should still return
	 * the data and \c FLAC__STREAM_DECODER_READ_STATUS_CONTINUE, and then on
	 * the next read callback it should return
	 * \c FLAC__STREAM_DECODER_READ_STATUS_END_OF_STREAM with a byte count
	 * of \c 0.
	 */

	FLAC__STREAM_DECODER_READ_STATUS_ABORT
	/**< An unrecoverable error occurred.  The decoder will return from the process call. */

} FLAC__StreamDecoderReadStatus;
typedef FLAC__StreamDecoderReadStatus (*FLAC__StreamDecoderReadCallback)(const FLAC__StreamDecoder *decoder, FLAC__byte buffer[], size_t *bytes, void *client_data);
#endif
typedef struct FLACD_Dec_Config {
	FLAC_Mem_Alloc_Info      flacd_mem_info;
	void                     *flacd_decode_info_struct_ptr; // Global_struct

		//FLAC__StreamDecoderReadCallback read_callback;
		//int (*read_callback)(const void *decoder, FLAC__byte buffer[], FLAC__int32 *bytes, void *client_data);
		//int (*read_callback)(const void *decoder, FLAC__byte** buffer, FLAC__int32 *bytes, void *client_data);
		FLAC__int32 (*read_callback)(FLAC__byte** buffer, FLAC__uint32 *bytes, void *context);
//		int (*seek_callback)(const void *decoder, FLAC__uint64 absolute_byte_offset, void *client_data);
//		int (*tell_callback)(const void *decoder, FLAC__uint64 *absolute_byte_offset, void *client_data);
//		int (*length_callback)(const void *decoder, FLAC__uint64 *stream_length, void *client_data);
//		FLAC__bool (*eof_callback)(const void *decoder, void *client_data);

//		int (*write_callback)(const void *decoder, const void *frame, const FLAC__int32 * const buffer[], void *client_data);
//		void (*metadata_callback)(const void *decoder, const void *metadata, void *client_data);
//		void (*error_callback)(const void *decoder, int status, void *client_data);

        FLAC__uint32 channel_no;
		FLAC__uint32 bit_per_sample;
		FLAC__uint32 sampling_rate;
		FLAC__uint64 total_sample;
        FLAC__uint32 block_size;
		FLAC__bool bparser_support;

		void* context;

        //FLAC__int8*              pInBuf;
        //FLAC__int16              inBufLen;
        //FLAC__int16              consumedBufLen;
} FLACD_Decode_Config;

/* Error types */
typedef enum
{
  /* Sucess */
  FLACD_OK = 0,			   /* no error 						*/
  FLACD_CONTINUE_DECODING, 		   /* no error						*/
  FLACD_COMPLETE_DECODING,		   /* no error						*/
  /* Warning : End of bitstream */
  FLACD_END_OF_STREAM,      /* end of bit stream 			*/
  /* Recoverable Errors */
  FLACD_ERROR_LAYER = 31,   /* invalid layer 				*/
  FLACD_ERROR_SAMP_FREQ,    /* invalid sampling frequency 	*/
  FLACD_ERROR_BIT_RATE,     /* invalid bit rate 				*/
  FLACD_ERROR_BLOCK_TYPE,   /* invalid block type 			*/
  FLACD_ERROR_CRC,          /* CRC error 					*/
  FLACD_ERROR_STREAM,
  FLACD_ERROR_DATA,         /* not enough main data 			*/
  FLACD_ERROR_WRAP,         /* bit error detected in hwrapbuf*/
  FLACD_ERROR_FREE_BIT_RATE,/* error computing free bit rate	*/
  FLACD_ERROR_HUFFMAN_TABLE,/* Selection of wronge huffman table */
  FLACD_ERROR_VERSION,      /* Wrong version */
  /* Fatal Error */
  FLACD_ERROR_INIT = 51,    /* initialization error 			*/
  FLACD_ERROR_INVALID_PARAM = 52,
  /* Invalid Parameters to decode frame */
} FLACD_RET_TYPE;

EXTERN FLACD_RET_TYPE FSL_FLACD_query_memory( FLACD_Decode_Config *pDecoder_Config );

//FLACD_RET_TYPE FSL_FLACD_initiate_decoder( FLACD_Decode_Config *pDecoder_Config, FLAC__uint8 *input_buffer );
EXTERN FLACD_RET_TYPE FSL_FLACD_initiate_decoder( FLACD_Decode_Config *pDecoder_Config, FLAC__uint8 *inbuf/*, FLAC__uint8 *outbuf*//*, FLAC__uint8 *inputfilename, FILE* fout*/ );
//FLACD_RET_TYPE FSL_FLACD_initiate_decoder( FLACD_Decode_Config *pDecoder_Config, FLAC__uint8 *input_buffer, FLAC__uint8 *inputfilename, FILE* fout );
EXTERN FLACD_RET_TYPE FSL_FLACD_decode_frame( FLACD_Decode_Config *pDecoder_Config, FLAC__uint32* poutlength, FLAC__uint8* outbuf/*,
				FLAC__int16 *pInputBuffer,
                                FLAC__int8 *pOutputBuffer*/);

EXTERN const FLAC__int8 * FSL_FLACD_decoder_version_info();

#endif
