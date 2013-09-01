
 /************************************************************************
  * Copyright 2005-2011 by Freescale Semiconductor, Inc.
  * All modifications are confidential and proprietary information
  * of Freescale Semiconductor, Inc. ALL RIGHTS RESERVED.
  ************************************************************************/

/***************************************************************************
*
* ANSI C source code
*
* Project Name : MP3 Decoder
*
***************************************************************************/
/***************************************************************************
 *
 *   CHANGE HISTORY
 *   dd/mm/yy   Code Ver     Description                   Author
 *   --------   -------      -----------                   ------
 *   16 APR 04    0.1 		created file                   Mahesh D.S
 *   17 AUG 04    0.2       Changes for ARM11 release      Mahesh D.S
 *   24 AUG 04    0.3       Changes for seperate scratch   mahesh D.S
 **************************************************************************/
/*********************************************************************************************
 *
 *		=============================
 *   CHANGE HISTORY
 *   dd/mm/yy   Code Ver     Description						  			Author
 *   --------   -------      -----------									------
 *   05 Apr 07	1.0			Added Layer info and modified size of			Madhav Varma
 *							Global Structure to support MPEG1-Layer2
 *   19-12-2007    1.4     OpenMax synthesis filter porting  Katherine Lu
 *   17-01-2008    1.5     Update total buffer size for
 *                         synthesis opt.                    Katherine Lu
 *   31-01-2008    1.6     Code clean up                     Katherine Lu
 *   18-03-2008    1.7     COde clean up                     Zhongsong Lin
 *   18-07-2008    1.8     Add error code for Layer1 and Layer2 Zhongsong Lin
 *   14-01-2009    1.9     code clean up                     Baofeng Tian
 *   30-Aug-2010   2.7     Add mp3 version info in API       Lyon Wang
 *********************************************************************************************/
#ifndef __MP3D_DEC_INTERFACE_H_
#define __MP3D_DEC_INTERFACE_H_

#ifdef __cplusplus
#define EXTERN extern "C"
#else
#define EXTERN
#endif

#define MP3D_MAX_NUM_MEM_REQS             2 /* presently we need seperate chunk
											   of memory for scratch_lf */
#define MP3D_TRUE	                       1


#define MP3D_INPUT_BUF_SIZE               2048
#define MP3D_INPUT_BUF_PUSH_SIZE         (2048*4)

#define MP3D_FAST_MEMORY                  1
#define MP3D_SLOW_MEMORY                  2
#define MP3D_DATA_SIZE                    /* presently not used */
#define MP3D_DATA_ALIGN_IN_BYTES          4
#define MP3D_MEM_TYPE                     FAST_MEMORY /* can be changed */
#define MP3D_INPUT_BUFFER_SIZE            2048
#define MP3D_FRAME_SIZE                   576


#define MAX_FRAME_SIZE                    2881   //Mpeg2.5 LayerII, 8KHz, 160kbps, padding slot
#define BS_PROTECT                        8
#define SIZE_THRESHOLD                   (MAX_FRAME_SIZE+BS_PROTECT)



/* Data type */
typedef unsigned char     MP3D_UINT8;
typedef char              MP3D_INT8;
typedef unsigned short    MP3D_UINT16;
typedef short             MP3D_INT16;
typedef unsigned int      MP3D_UINT32;
typedef int               MP3D_INT32;

#define LAYER2OFFSET 100
#define LAYER1OFFSET 200
/* Error types */
typedef enum
{
  /* Sucess */
  MP3D_OK = 0,			   /* no error 						*/
  /* Warning : End of bitstream */
  MP3D_END_OF_STREAM,      /* end of bit stream 			*/
  /* Recoverable Errors */
  MP3D_ERROR_LAYER = 31,   /* invalid layer 				*/
  MP3D_ERROR_SAMP_FREQ,    /* invalid sampling frequency 	*/
  MP3D_ERROR_BIT_RATE,     /* invalid bit rate 				*/
  MP3D_ERROR_BLOCK_TYPE,   /* invalid block type 			*/
  MP3D_ERROR_CRC,          /* CRC error 					*/
  MP3D_ERROR_STREAM,
  MP3D_ERROR_DATA,         /* not enough main data 			*/
  MP3D_ERROR_WRAP,         /* bit error detected in hwrapbuf*/
  MP3D_ERROR_FREE_BIT_RATE,/* error computing free bit rate	*/
  MP3D_ERROR_HUFFMAN_TABLE,/* Selection of wronge huffman table */
  MP3D_ERROR_VERSION,      /* Wrong version */
  MP3D_ERROR_EMPHASIS,      /* reserved emphsis */
  MP3D_ERROR_SCALEFACTOR,   /*  this error is specified for lay1 & lay2 scalefactor if == 63 this error will occur */
  MP3D_ERROR_BIGVALUE,      /*  while big value > 288 error occurs  */
  MP3D_ERROR_SCFSI,         /*  scale factor side information error */
  MP3D_ERROR_PART3LEN,      /* if no bits left for part3 length, error occurs */
  MP3D_ERROR_STEREO,        /* if two channel does not have the same stereo mode, error occurs */
  MP3D_ERROR_HEADER,        /* if current sync word positon + main data slot offset is not next frame*/

  /* Invalid Parameters to decode frame */
  MP3D_LAYER2_E_NO_ERROR = LAYER2OFFSET,
  MP3D_LAYER2_E_VERSION_ERROR,           /* Version Error */
  MP3D_LAYER2_E_LAYER_ERROR,             /* invalid layer */
  MP3D_LAYER2_E_SAMP_FREQ_ERROR,         /* invalid sampling frequency */
  MP3D_LAYER2_E_BIT_RATE_ERROR,          /* invalid bit rate */
  MP3D_LAYER2_E_FREE_BIT_RATE_ERROR,     /* error computing free bit rate */
  MP3D_LAYER2_E_CRC_ERROR,               /* CRC error */
  MP3D_LAYER2_E_DATA_ERROR,              /* Error in the data */
  MP3D_LAYER2_E_STREAM_ERROR,            /* end of bit stream */
  MP3D_LAYER2_E_NUM_ERRORS,              /* Number of error types, should be at the end */

  MP3D_LAYER1_E_NO_ERROR = LAYER1OFFSET,
  MP3D_LAYER1_E_VERSION_ERROR,           /* Version Error */
  MP3D_LAYER1_E_LAYER_ERROR,             /* invalid layer */
  MP3D_LAYER1_E_SAMP_FREQ_ERROR,         /* invalid sampling frequency */
  MP3D_LAYER1_E_BIT_RATE_ERROR,          /* invalid bit rate */
  MP3D_LAYER1_E_FREE_BIT_RATE_ERROR,     /* error computing free bit rate */
  MP3D_LAYER1_E_CRC_ERROR,               /* CRC error */
  MP3D_LAYER1_E_DATA_ERROR,              /* Error in the data */
  MP3D_LAYER1_E_STREAM_ERROR,            /* end of bit stream */
  MP3D_LAYER1_E_NUM_ERRORS,              /* Number of error types, should be at the end */
  MP3D_LAYER1_E_NO_OUTPUT,               /* No output in this frame */

    /* Fatal Error */
  MP3D_ERROR_INIT = 250,    /* initialization error 			*/
  MP3D_ERROR_INVALID_PARAM = 251,
} MP3D_RET_TYPE;

typedef enum
{
    MP3D_STATIC_MEM,        /* 0 for static memory */
    MP3D_SCRATCH_MEM        /* 1 for scratch memory */
} MP3D_MEM_DESC;

typedef enum
{
    MPEG_VERSION2 = 0,       /* MPEG_PHASE2_LSF */
    MPEG_VERSION1 = 1,       /* MPEG_AUDIO_ID 1 */
    MPEG_VERSION25 = 2,      /* MPEG_25_LSF */
} MP3D_VERSION;


typedef struct {
	MP3D_INT32		mp3d_size;     /* Size in bytes */
	MP3D_INT32 	    mp3d_type;	   /* Memory type Fast or Slow */
	MP3D_MEM_DESC   mp3d_mem_desc; /* to indicate if it is scratch memory */
	MP3D_INT32      mp3d_priority; /* In case of fast memory, specify the priority */
	void 	        *app_base_ptr; /* Pointer to the base memory , which will be allocated and
                                    * filled by the  application */
} MP3D_Mem_Alloc_Info_Sub;

typedef struct {
	MP3D_INT32 	mp3d_sampling_freq; /* Sampling frequency of the current frame in Khz */
	MP3D_INT32 	mp3d_num_channels;  /* Number of channels decoded in current frame */
	MP3D_INT32 	mp3d_frame_size;    /* Number of stereo samples being outputted for this
                                     * frame */
	MP3D_INT32 mp3d_bit_rate;		/* tlsbo79740 - bit-rate information*/
	MP3D_INT32 layer;				/* engr30582 - MPEG layer of the current stream
									 * 1 for layer-I,2 for layer-II and 3 for layer-III */
	MP3D_INT32 mp3d_remain_bytes;    /*bytes remainded after decoding one frame*/
    MP3D_VERSION version;            /*for return mp3 stream version  */
} MP3D_Decode_Params;

typedef struct {
	MP3D_INT32 				mp3d_num_reqs;
	MP3D_Mem_Alloc_Info_Sub	mem_info_sub [MP3D_MAX_NUM_MEM_REQS];
} MP3D_Mem_Alloc_Info;


struct MP3D_Dec_Config;
typedef struct MP3D_Dec_Config {
	MP3D_Mem_Alloc_Info		mp3d_mem_info;
	void					*mp3d_decode_info_struct_ptr; // Global_struct

  MP3D_INT8              (*app_swap_buf) (MP3D_UINT8 ** new_buf_ptr,
                                            MP3D_INT32 * new_buf_len,
                                            struct MP3D_Dec_Config *dec_config);
  MP3D_INT8*               pInBuf;
  MP3D_INT16               inBufLen;
  MP3D_INT16               consumedBufLen;
                            /* Pointer to swap buffer function */
} MP3D_Decode_Config;

#ifdef __SYMBIAN32__
#define IMPORT_C __declspec(dllimport)
#define EXPORT_C __declspec(dllexport)
#define EXTERN
#else
#define EXPORT_C
#define IMPORT_C
#endif

IMPORT_C EXTERN const MP3D_INT8 * mp3d_decode_versionInfo(void);
IMPORT_C EXTERN MP3D_RET_TYPE mp3d_query_dec_mem (MP3D_Decode_Config *dec_config);


IMPORT_C EXTERN MP3D_RET_TYPE mp3d_decode_init (MP3D_Decode_Config *dec_config, MP3D_UINT8 *input_buffer,
                                MP3D_INT32 input_buffer_length);
IMPORT_C EXTERN MP3D_RET_TYPE mp3d_decode_frame  (MP3D_Decode_Config *dec_config,
                                  MP3D_Decode_Params *dec_param, MP3D_INT32 *out_buf);
IMPORT_C MP3D_INT8 app_swap_buffers_mp3_dec(MP3D_UINT8 **new_buf_ptr, MP3D_INT32 *new_buf_size,
                                    MP3D_Decode_Config *dec_config);
#endif
