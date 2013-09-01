/*******************************************************************************

 * (C) 2004 MOTOROLA INDIA ELECTRONICS LTD.
  ************************************************************************
  * Copyright 2005-2010 by Freescale Semiconductor, Inc.
  * All modifications are confidential and proprietary information
  * of Freescale Semiconductor, Inc.
  ************************************************************************

 *   CHANGE HISTORY
 *   dd/mm/yy   Code Ver     Description                        Author
 *   --------   -------      -----------                        ------
 *   08/04/2003 01           Created                            B.Venkatarao
 *   19/02/2004 02           Added global structure for         Vishala
 *                           relocatability
 *   12/07/2004 03           Added prototypes for swap
 *                           buffer function and removed
 *                           global structure and moved it
 *                           to other file                      Vishala
 *
 *   19/08/2004 04           Defined struct AACD_Block_Params,  S.Nachiappan
 *                           which is to be passed to the
 *                           decoder, along with the block to
 *                           be decoded. This struct has
 *                           parameters similar to ADIF/ADTS
 *                           header data.
 *
 *                           aacd_decode_frame() additionally
 *                           receives:
 *                           (1) a pointer to the buffer
 *                               containing the block to be
 *                               decoded
 *                           (2) Length of the buffer
 *                           (3) Pointer to AACD_Block_Params
 *
 *                           For MPEG-4 vectors, some encoders, put
 *                           in an 'emphasis' field in the ADTS Header
 *                           and don't perform a byte-alignment
 *                           after the header ends. So header is 58-bits
 *                           long instead of 56-bits. To handle
 *                           this situation, the decoder has to
 *                           flush LEN_EMPHASIS no.of bits from the
 *                           first-byte of the input-buffer.
 *                           to start off correctly.
 *
 *   23/08/2004 04           Moved BitCreditType to here        S.Nachiappan
 *                           from aac_common.h
 *
 *
 *   23/07/2004 04           Modified the prototype for
 *                           aacd_decode_frame for 24 bit
 *                           output                             Pradeep V
 *
 *   03/09/2004 06           Removed BitCreditType typedef      S.Nachiappan
 *   09/09/2004 07           App will write pointer to          S.Nachiappan
 *                           AACD_Block_Params data into
 *                           AACD_Decoder_config
 *
 *                           Moved structs ProgConfig, EleList
 *                           and MIXdown from aac_fix_types.h to
 *                           here
 *   09/09/2004 08           Added enum for pcm length and
 *                           memory type                        Pradeep V
 *
 *   15/09/2004 09           Modified proto-type of             S.Nachiappan
 *                           (*app_swap_buf)()
 *
 *   16/09/2004 10           Added new error code               S.Nachiappan
 *                           AACD_ERROR_PNS
 *
 *   16/09/2004 11           Added more error codes             S.Nachiappan
 *   25/04/2008 12       Add error concealment feature          Bing Song
 *   13/02/2009 13          support aacplus envoke aac lib      Lyon Wang
 *
 ******************************************************************************/
#ifndef _AACD_DEC_INTERFACE_H
#define _AACD_DEC_INTERFACE_H
#ifndef UNDER_CE
 #ifndef EXPORT_C
#define EXPORT_C __declspec(dllexport)
 #endif
 #ifndef IMPORT_C
#define IMPORT_C __declspec(dllimport)
 #endif
#else
 #ifndef EXPORT_C
#define EXPORT_C
 #endif
 #ifndef IMPORT_C
#define IMPORT_C
 #endif
#endif
#define AACD_TRUE               1
#define AACD_FALSE              0
#define AAC_FRAME_SIZE 1024
#define AACD_GLOBAL_STRUCT_SIZE 100000
#define AACD_FAST_MEMORY        0
#define AACD_SLOW_MEMORY        1
#define AACD_MAX_NUM_MEM_REQS   5+1+1+1 //5 note this should modified in case aac lib was used for aac+
#define AACD_DATA_SIZE          0
#define AACD_DATA_ALIGN_IN_BYTES 16
#define AACD_DATA_BEGIN         0       /* some known symbol */
#define AACD_MEM_TYPE           AACD_FAST_MEMORY /* can be changed */
#define AACD_INPUT_BUFFER_SIZE  6*768  /*size of input buffer*/
#define AACD_FRAME_SIZE          2*1024 /* size in bytes for one channel */

#define AACD_PATH_LEN           128
#define AACD_LEN_TAG            4

#define INTERNAL_BS_BUFSIZE 2048         //DSPhl28187
#define AACD_6CH_FRAME_MAXLEN  6*768

#ifndef AACD_UINT32
typedef unsigned int AACD_UINT32;
#endif
#ifndef AACD_INT32
typedef int AACD_INT32;
#endif
#ifndef AACD_UINT16
typedef unsigned short AACD_UINT16;
#endif
#ifndef AACD_INT16
typedef short AACD_INT16;
#endif
#ifndef AACD_UCHAR
typedef unsigned char AACD_UCHAR;
#endif
#ifndef AACD_UINT8
typedef unsigned char AACD_UINT8;
#endif
#ifndef AACD_INT8
typedef char AACD_INT8;
#endif
#ifndef AACD_CHAR
typedef char AACD_CHAR;
#endif
#ifndef AACD_Void
typedef void           AACD_Void;
#endif

typedef signed long int AACD_OutputFmtType;

#define AACPD_WARNING_BASE       11
#define AACPD_RECOVERROR_BASE    31
#define AACPD_FATALERROR_BASE    51

/* enum with error return */
typedef enum
{
    AACD_ERROR_NO_ERROR,
    AACD_ERROR_EOF,
    /* The output of decoder is produced by error concealment. It can be used as NO ERROR output */
    AACD_ERROR_START_BLOCK=AACPD_RECOVERROR_BASE,
    AACD_ERROR_HUFFDECODE,
    AACD_ERROR_GETCC,
    AACD_ERROR_DATA_CHN,
    AACD_ERROR_PROG_CONFIG,
    AACD_ERROR_MCINFO,
    AACD_ERROR_END_BLOCK,
    AACD_ERROR_HEADER_TYPES,
    AACD_ERROR_NOT_SUPPORTED_PCM_BITS,
    AACD_ERROR_NOT_SUPPORTED_CHANNEL_CONFIG,
    AACD_ERROR_NOT_SUPPORTED_CHANNEL_COUNT,
    AACD_ERROR_SEEKING,
    AACD_ERROR_PNS,
    AACD_ERROR_MS_STEREO,
    AACD_ERROR_IS_STEREO,
    AACD_ERROR_DEINTERLEAVE,
    AACD_ERROR_TNS_COEF_RES,
    AACD_ERROR_BLOCK_TYPE,
    AACPD_ERROR_SBRD_CONCEAL,
    AACPD_ERROR_SBRD_NOT_INITIALIZED,
    /* Fatal error base*/
    AACD_ERROR_INIT = AACPD_FATALERROR_BASE,
    AACD_ERROR_INVALID_HEADER,
    AACPD_ERROR_INVALID_PARAMETERS,
    AACPD_ERROR_MEMALLOC
}AACD_RET_TYPE;

typedef enum
{
    AACD_MEM_SCRATCH = 0,
    AACD_MEM_PERSISTENT
}AACD_MEM_DESC;
typedef enum
{
    AACD_MEM_PRIORITY_HIGH = 0,
    AACD_MEM_PRIORITY_LOW
}AACD_MEM_PRIORITY;

typedef enum
{
    AACD_16_BIT_OUTPUT = 16,
    AACD_24_BIT_OUTPUT = 24
}AACD_PCM_LENGTH;

typedef enum
{
    AACD_NO_PACKET_LOSS = 0,
    AACD_PACKET_LOSS
}AACD_ERROR_CONCEALMENT;

enum
{
    /*
     * channels for 5.1 main profile configuration
     * (modify for any desired decoder configuration)
     */
    FCHANS      = 3,    /* front channels: left, center, right */
    FCenter     = 1,    /* 1 if decoder has front center channel */
    SCHANS      = 0,    /* side channels: */
    BCHANS      = 2,    /* back channels: left surround, right surround */
    BCenter     = 0,    /* 1 if decoder has back center channel */
    LCHANS      = 1,    /* LFE channels */
    XCHANS      = 0,    /* scratch space for parsing unused channels */

    CHANS       = FCHANS + SCHANS + BCHANS + LCHANS + XCHANS
};

/* Structure definitions */
typedef  struct
{
    AACD_INT32              aacd_size;        /* Size in bytes */
    AACD_INT32              aacd_type;        /* Fast or Slow */
    AACD_MEM_DESC      aacd_mem_desc;    /* Static/Scratch memory*/
    AACD_MEM_PRIORITY  aacd_priority;    /* In case of fast Memory type, specify the
                                     * priority */

    void               *app_base_ptr;     /* Pointer to the base memory,
                           which will be allocated and
                                           * filled by the application*/
} AACD_Mem_Alloc_Info_Sub;


typedef struct
{
    AACD_INT32    aacd_num_reqs;    /*  Number of valid memory requests */
    AACD_Mem_Alloc_Info_Sub   mem_info_sub[AACD_MAX_NUM_MEM_REQS];
} AACD_Mem_Alloc_Info;



typedef struct
{
    AACD_UINT32 aacd_sampling_frequency;     /* Sampling frequency of the current frame in Khz */
    AACD_UINT32     aacd_num_channels;       /* Number of channels decoded in current frame */
    AACD_UINT32      aacd_bit_rate;
    AACD_UINT32      aacd_len;

    AACD_UINT32 aacd_frame_size;                /* Number of stereo samples being outputted for this
                                                                            frame */
    AACD_INT8    output_path[AACD_PATH_LEN];

    AACD_UINT32   BitsInBlock;
    AACD_INT8      ch_is_present[CHANS]; /* flag to indicate presence of each channel */
    AACD_UINT32    AACD_bno;         /* frame number, updated after each call to aacpd_decode_frame*/

    /* More parameters can be added here if required in the future
       .............................
       .............................
     */
} AACD_Decoder_info;

typedef struct
{
    AACD_INT32             num_ele;
    AACD_INT32             ele_is_cpe[(1 << AACD_LEN_TAG)];
    AACD_INT32             ele_tag[(1 << AACD_LEN_TAG)];
}   AACD_EleList;

typedef struct
{
    AACD_INT32             present;
    AACD_INT32             ele_tag;
    AACD_INT32             pseudo_enab;
}   AACD_MIXdown;

typedef struct
{
    AACD_INT32             profile;
    AACD_INT32             sampling_rate_idx;
    AACD_EleList         front;
    AACD_EleList         side;
    AACD_EleList         back;
    AACD_EleList         lfe;
    AACD_EleList         data;
    AACD_EleList         coupling;
    AACD_MIXdown         mono_mix;
    AACD_MIXdown         stereo_mix;
    AACD_MIXdown         matrix_mix;
    /* Ignore the comment field to minimize memory usage */
    AACD_INT8            comments[1];
    AACD_INT32            buffer_fullness;    /* put this transport level info here */

  /* Added the following the 'tag' field, to process ProgConfigElements outside
     of the header-parsing routines */

    AACD_INT32             tag;
}   AACD_ProgConfig;


typedef struct
{
    AACD_INT32        num_pce;
    AACD_ProgConfig *pce;

    AACD_INT32 ChannelConfig;
    AACD_INT32 SamplingFreqIndex;
    AACD_INT32 BitstreamType;
    AACD_INT32 BitRate;
    AACD_INT32 BufferFullness; /*No. of bits in encoder buffer after encoding first raw_data_block */
    AACD_INT32 ProtectionAbsent;
    AACD_INT32 CrcCheck;
    AACD_INT32 frame_length;
} AACD_Block_Params_Tmp;


typedef struct
{
    AACD_INT32        num_pce;
    AACD_ProgConfig *pce;

    AACD_INT32 ChannelConfig;
    AACD_INT32 SamplingFreqIndex;
    AACD_INT32 BitstreamType;
    AACD_INT32 BitRate;
    AACD_INT32 BufferFullness; /*No. of bits in encoder buffer after encoding first raw_data_block */
    AACD_INT32 ProtectionAbsent;
    AACD_INT32 CrcCheck;
    AACD_INT32 frame_length;

    AACD_INT32 scalOutObjectType;
    AACD_INT32 scalOutNumChannels;
    AACD_INT32 sampleRate;
    AACD_INT32 framelengthflag;
    AACD_INT32 iMulti_Channel_Support;
    AACD_INT32 bsacDecLayer;

    /* Please see FileHeader at the top for explanation */
#ifdef OLD_FORMAT_ADTS_HEADER
    AACD_INT32        Flush_LEN_EMPHASIS_Bits;
#endif
} AACD_Block_Params;

//DSPhl28187
typedef struct
{
    AACD_INT32    sbrd_down_sample;   /* flag to indicate SBR down sample mode */
    AACD_INT32    sbrd_stereo_downmix;    /* flag related to stereo down mix */
}SBRD_Decoder_Config;

#define MAX_FILE_EXTENSION_LEN 6

typedef struct
{
    AACD_INT32          *present;/* channel present */
    char                *fext;
    AACD_INT32          *file_opened; /* file is already open aacd_or not */
} AACD_Ch_Info;

typedef struct
{
    void *ps_aacd_ptr;      /* pointer to AACD_global_struct */
    void *psStreamSbr;      /* SBRBITSTREAM * psStreamSbr; */
    void *poutbuf;          /* int (*poutbuf)[2048]; */
    void *psStreamSbr_tmp;  /* for error_concealment use */
    void *psStreamSbr_restore; /* for error_concealment use */
} SBR_Temp_Info;

typedef struct AACD_decoder_config_struct
{
    AACD_Mem_Alloc_Info    aacd_mem_info;
    void                   *aacd_decode_info_struct_ptr;

    AACD_UINT8   num_pcm_bits;    /*Specifies number of Bits in the PCM.(16 or 24)*/

    long         *AACD_bno;     //DSPhl28187
    AACD_Block_Params *params;

    AACD_Ch_Info ch_info[CHANS];    //DSPhl28187
    AACD_INT32 adts_format;    /* Used for error concealment to indicate if the stream is adts format */
    AACD_INT32 packet_loss;    /* Used for error concealment. If the flag set as AACD_PACKET_LOSS,
                                          the decoder will output one frame data based on previous frame data */
    AACD_UINT8      *aacd_initialized_data_start;
    AACD_Void * sbrd_info_struct_ptr;
    SBRD_Decoder_Config sbrd_dec_config;
    void *pContext;
    SBR_Temp_Info sbr_temp_struct; //for pass information between aac and aac+
    AACD_INT32 aac_plus_enable;  //indicate codec used in aac+ decoder
} AACD_Decoder_Config;

//DSPhl28187
#define BIT_COUNTER_INIT            (24)
#define MIN_REQD_BITS               (24)
#define ADTS_FRAME_MAX_SIZE         (8192)
#define ADTS_FRAME_HEADER_SIZE      (7)

/* #define is required in order to use these args in #if () directive */
#define ICCHANS 0       /* independently switched coupling channels */
#define DCCHANS 0       /* dependently switched coupling channels */
#define XCCHANS 0       /* scratch space index for parsing unused coupling
                 * channels */
#define CCHANS  (ICCHANS + DCCHANS + XCCHANS)


enum
{
    LN = 2048,
    LN2 = LN / 2,

    LEN_ELE_IS_CPE = 1,
    LEN_PROFILE = 2,
    LEN_SAMP_IDX = 4,
    LEN_NUM_ELE = 4,
    LEN_NUM_LFE = 2,
    LEN_NUM_DAT = 3,
    LEN_NUM_CCE = 4,

    LEN_MIX_PRES = 1,
    LEN_MMIX_IDX = 2,
    LEN_PSUR_ENAB = 1,
    LEN_COMMENT_BYTES = 8,

    /*
    * audio data transport stream frame format header
    */
    /* fixed header */
    LEN_SYNCWORD        = 12,
    LEN_ID      = 1,
    LEN_LAYER   = 2,
    LEN_PROTECT_ABS = 1,
    LEN_PRIVTE_BIT  = 1,
    LEN_CHANNEL_CONF    = 3,

    /* variable header */
    LEN_COPYRT_START            = 1,
    LEN_FRAME_LEN               = 13,
    LEN_ADTS_BUF_FULLNESS   = 11,
    LEN_NUM_OF_RDB          =2,

    /* CRC */
    LEN_CRC = 16,

    /* Some encoders (PsyTEL) put an addtional field 'Emphasis'
       in MPEG-4 ADTS streams, though it a violation of the
       standard.
       But defining OLD_FORMAT_ADTS_HEADER will correctly decode
       such streams.
       */
#ifdef OLD_FORMAT_ADTS_HEADER
    LEN_EMPHASIS   =  2,
#endif

    /* audio data interchange format header */
    LEN_ADIF_ID = (32 / 8),
    LEN_COPYRT_ID = (72 / 8),
    LEN_COPYRT_ID_ADTS  = 1,

    LEN_COPYRT_PRES = 1,
    LEN_ORIG = 1,
    LEN_HOME = 1,
    LEN_BS_TYPE = 1,
    LEN_BIT_RATE = 23,
    LEN_NUM_PCE = 4,
    LEN_ADIF_BF = 20,


    LEN_TAG = 4,
    LEN_BYTE = 8
};

enum
{
    AAC_ERROR_EOF = 0,
    AAC_ERROR_USAGE,
    AAC_ERROR_ADTS_HEADER,
    AAC_ERROR_PROG_CONFIG,
    AAC_ERROR_ENTER_CHN,
    AAC_ERROR_DEFAULT_POSITION,
    AAC_ERROR_MCINFO,
    AAC_ERROR_GETCC,
    AAC_ERROR_DATA_CHN,
    AAC_ERROR_START_BLOCK,
    AAC_ERROR_END_BLOCK,
    AAC_ERROR_ICS_INFO,
    AAC_ERROR_GET_MASK,
    AAC_ERROR_GETICS,
    AAC_ERROR_INITIO,
    AAC_ERROR_COUPLING,
    AAC_ERROR_PREDICT,
    AAC_ERROR_MEMORY,
    AAC_ERROR_HUFFDECODE,
    AAC_ERROR_GAIN_CONTROL,
    AAC_ERROR_PULSE_NC,
    AAC_ERROR_FILEIO,
    AAC_ERROR_DRC,
    AAC_ERROR_BLOCK_TYPE,
    AAC_ERROR_HEADER_TYPES,
    AAC_ERROR_TNS_COEF_RES,
    AAC_ERROR_FFT_LENGTH
};

typedef struct
{
    char            adif_id[LEN_ADIF_ID + 1];
    int             copy_id_present;
    char            copy_id[LEN_COPYRT_ID + 1];
    int             original_copy;
    int             home;
    int             bitstream_type;
    long            bitrate;
    int             num_pce;
    int             prog_tags[(1 << LEN_TAG)];
}               ADIF_Header;

typedef struct
{
    int             syncword;
    int             id;
    int             layer;
    int             protection_abs;
    int             profile;
    int             sampling_freq_idx;
    int             private_bit;
    int             channel_config;
    int             original_copy;
    int             home;
    int             copyright_id_bit;
    int             copyright_id_start;
    int             frame_length;
    int             adts_buffer_fullness;
    int             num_of_rdb;
    int             crc_check;
}               ADTS_Header;

#ifdef __cplusplus
#define EXTERN
#else
#define EXTERN extern
#endif

#ifdef __cplusplus
extern "C"
{
#endif


/* Function prototypes */
 EXTERN const AACD_INT8 * aacd_decode_versionInfo();
 EXTERN AACD_RET_TYPE aacd_query_dec_mem (AACD_Decoder_Config *dec_config);
 EXTERN AACD_RET_TYPE aacd_decoder_init (AACD_Decoder_Config *dec_config);
 EXTERN AACD_RET_TYPE aacd_decode_frame (AACD_Decoder_Config *dec_config,
                                 AACD_Decoder_info *dec_info,
                                         AACD_OutputFmtType *out_buf,
                 AACD_INT8* buf, AACD_INT32 buf_len);


#ifdef __cplusplus
}
#endif
#endif
