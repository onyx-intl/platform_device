/**
 *  Copyright (c) 2010-2012, Freescale Semiconductors, Inc.
 *  All Rights Reserved.
 *
 *  The following programs are the sole property of Freescale Semiconductors Inc.,
 *  and contain its proprietary and confidential information.
 *
 */

/**
 *  @file AacCoreParser.h
 *  @brief AAC core parser.
 *  @ingroup AacCoreParser
 */


#ifndef AacCoreParser_h
#define AacCoreParser_h

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "AudioCoreParser.h"
//#include "aacd_dec_interface.h"

typedef enum {
    FILETYPEADTS,
    FILETYPEADIF,
    FILETYPERAW
}AAC_FILETYPE;

typedef enum {
    AAC_PARSERRETURNSUCESS,
    AAC_PARSERRETURNFAIL
}AAC_PARSERRETURNTYPE;

enum {
  FLAG_SUCCESS,
  FLAG_NEEDMORE_DATA
};

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

#define AAC_FRAME_SIZE 		1024
#define AACD_LEN_TAG            4

#define BIT_COUNTER_INIT        (24)
#define MIN_REQD_BITS           (24)
#define ADTS_FRAME_MAX_SIZE     (8192)
#define ADTS_FRAME_HEADER_SIZE  (7)

/* #define is required in order to use these args in #if () directive */
#define ICCHANS 		0       /* independently switched coupling channels */
#define DCCHANS 		0       /* dependently switched coupling channels */
#define XCCHANS 		0       /* scratch space index for parsing unused coupling
                 * channels */
#define CCHANS  (ICCHANS + DCCHANS + XCCHANS)

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
}  ADIF_Header;

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
}  ADTS_Header;

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
    AACD_INT32           profile;
    AACD_INT32           sampling_rate_idx;
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
    AACD_INT32           buffer_fullness;    /* put this transport level info here */

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

AAC_FILETYPE Aac_FindFileType(uint8 *pBuffer, int32 nBufferLen);
FRAME_INFO ParserADTS(AACD_Block_Params *params, uint8 *pBuffer, uint32 nBufferLen, FRAME_INFO *in_info);
FRAME_INFO ParserADIF(AACD_Block_Params *params, uint8 *pBuffer, int32 nBufferLen);
AAC_PARSERRETURNTYPE AacDec_InitRaw(AACD_Block_Params *params, int32 nChannels, int32 nSamplingFreq);

AUDIO_PARSERRETURNTYPE AacParserFileHeader(AUDIO_FILE_INFO *pFileInfo, uint8 *pBuffer, \
 										uint32 nBufferLen);
AUDIO_PARSERRETURNTYPE AacParserFrame(AUDIO_FRAME_INFO *pFrameInfo, uint8 *pBuffer, \
										uint32 nBufferLen);
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
/* File EOF */
