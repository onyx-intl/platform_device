/*
 ***********************************************************************
 * Copyright (c) 2005-2012, Freescale Semiconductor, Inc.
 * All modifications are confidential and proprietary information
 * of Freescale Semiconductor, Inc. ALL RIGHTS RESERVED.
 ***********************************************************************
 */

/*
****************************************************************************
* ANSI C source code
*
* Project Name : WMA Decoder
*
***************************************************************************/
/***************************************************************************
 *
 *
 *   CHANGE HISTORY
 *   dd/mm/yy        Code Ver     Description             Author
 *   --------        -------      -----------             ------
 *   18th May 04     0.1 	  created file            Murali.
 *   5th  Feb 07     0.2	  TLSbo87089              Sukruth.
 *                            Raw file decode support
 **************************************************************************/

#ifndef __WMAD_DEC_INTERFACE_H_
#define __WMAD_DEC_INTERFACE_H_

#ifdef __cplusplus
extern "C"
{
#endif

//***********************************************************************
//   Data type
//***********************************************************************
typedef unsigned char		WMAD_UINT8;
typedef char			WMAD_INT8;
typedef unsigned short		WMAD_UINT16;
typedef short			WMAD_INT16;
typedef unsigned int		WMAD_UINT32;
typedef int			WMAD_INT32;
typedef WMAD_UINT32             WMAD_Bool;
#define WMAD_TRUE               1
#define WMAD_FALSE              0

#if _WIN32
typedef unsigned __int64        WMAD_UINT64;
typedef __int64                 WMAD_INT64;
#else
typedef unsigned long long      WMAD_UINT64;
typedef long long               WMAD_INT64;
#endif

//***********************************************************************
//  memory definition
//***********************************************************************
#define WMAD_FAST_MEMORY                  1
#define WMAD_SLOW_MEMORY                  0
#define WMAD_MAX_NUM_MEM_REQS             1 // (Temporary)
#define WMAD_MEM_TYPE                     WMAD_FAST_MEMORY /* can be changed */

#define WMA_MAX_DATA_REQUESTED            128
#define WMA_MAX_METADATA_LEN              512     // Max length (in bytes) of any metadata field - note that metadata is WCHAR, so use even numbers
                                                  // We will truncate incoming metadata to this length (and skip past the remaining data).
                                                  // If you want to support max allowable size, set this to 65535 (0xFFFF).

//***********************************************************************
//  enum definition
//***********************************************************************

/* status */
#ifndef _WMAFILESTATUS_DEFINED
#define _WMAFILESTATUS_DEFINED
typedef enum tagWMAFileStatus
{
    cWMA_NoErr,                 /* -> always first entry */
                                /* remaining entry order is not guaranteed */
    cWMA_Failed,
    cWMA_BadArgument,
    cWMA_BadAsfHeader,
    cWMA_BadPacketHeader,
    cWMA_BrokenFrame,
    cWMA_NoMoreFrames,
    cWMA_BadSamplingRate,
    cWMA_BadNumberOfChannels,
    cWMA_BadVersionNumber,
    cWMA_BadWeightingMode,
    cWMA_BadPacketization,

    cWMA_BadDRMType,
    cWMA_DRMFailed,
    cWMA_DRMUnsupported,

    cWMA_DemoExpired,

    cWMA_BadState,
    cWMA_Internal,               /* really bad */
    cWMA_NoMoreDataThisTime
}tWMAFileStatus;
#endif /* _WMAFILESTATUS_DEFINED */

typedef enum
{
    WMAD_STATIC_MEM,        /* 0 for static memory */
    WMAD_SCRATCH_MEM        /* 1 for scratch memory */
} WMAD_MEM_DESC;


//***********************************************************************
// Exercising Rapier Special Modes, not everything available all the time
//***********************************************************************
#define DECOPT_CHANNEL_DOWNMIXING      0x00000001
#define DECOPT_DRC                     0x00000002
#define DECOPT_INTERPOLATED_DOWNSAMPLE 0x00000004
#define DECOPT_HALF_TRANSFORM          0x00000008
#define DECOPT_HALF_UP_TRANSFORM       0x00000010
#define DECOPT_2X_TRANSFORM            0x00000020
#define DECOPT_REQUANTTO16             0x00000040
#define DECOPT_DOWNSAMPLETO44OR48      0x00000080
#define DECOPT_LTRTDOWNMIX             0x00000100
#define DECOPT_FLOAT_OUT               0x00000200
#define DECOPT_PCM24_OUT               0x00000400
#define DECOPT_PCM32_OUT               0x00000800
#define DECOPT_IGNOREFREQEX            0x00001000
#define DECOPT_IGNORECX                0x00002000



//***********************************************************************
//  struct definition
//***********************************************************************

#ifndef GUID_DEFINED
#define GUID_DEFINED
typedef struct {          // size is 16
    unsigned long  Data1;
    unsigned short Data2;
    unsigned short Data3;
    unsigned char  Data4[8];
} GUID;
#endif

#ifndef COMPILER_PACKALIGN
#ifndef PLATFORM_SPECIFIC_COMPILER_PACKALIGN
#define COMPILER_PACKALIGN(x)       pack(x)
#endif
#endif

#ifdef __arm
//#define EMBARM_PACK __packed
#define EMBARM_PACK 
#else
#define EMBARM_PACK
#endif

#if !defined(_Embedded_x86) && !defined(__arm)
#pragma COMPILER_PACKALIGN(1)
#endif

#ifndef _WAVEFORMATEX_
#define _WAVEFORMATEX_
#pragma pack(push,1)
#ifdef _LINUX_BUILD_
typedef struct
#else
typedef EMBARM_PACK struct
#endif
{
    WMAD_UINT16     wFormatTag;        /* format type */
    WMAD_UINT16     nChannels;         /* number of channels (i.e. mono, stereo...) */
    WMAD_UINT32     nSamplesPerSec;    /* sample rate */
    WMAD_UINT32     nAvgBytesPerSec;   /* for buffer estimation */
    WMAD_UINT16     nBlockAlign;       /* block size of data */
    WMAD_UINT16     wBitsPerSample;    /* Number of bits per sample of mono data */
    WMAD_UINT16     cbSize;            /* The count in bytes of the size of
                                * extra information (after cbSize) */
} WAVEFORMATEX, *PWAVEFORMATEX, *LPWAVEFORMATEX;
#pragma pack(pop)
#endif

#ifndef _WAVEFORMATEXTENSIBLE_
#define _WAVEFORMATEXTENSIBLE_
typedef struct
{
    WAVEFORMATEX Format;       /* The traditional wave file header */
    union {
        unsigned short wValidBitsPerSample; /* bits of precision */
        unsigned short wSamplesPerBlock;    /* valid if wBitsPerSample==0 */
        unsigned short wReserved;           /* If neither applies, set to zero */
    } Samples;
    unsigned long    dwChannelMask;        /* which channels are present in stream */
    GUID SubFormat;           /* specialization */
} WAVEFORMATEXTENSIBLE, *PWAVEFORMATEXTENSIBLE;

#endif

typedef struct {
    WMAD_INT32	    s32WMADSize;   /* Size in bytes */
    WMAD_INT32 	    s32WMADType;   /* Memory type Fast or Slow */
    WMAD_MEM_DESC   s32WMADMemDesc; /* to indicate if it is scratch memory */
    WMAD_INT32      s32WMADPriority; /* In case of fast memory, specify the priority */
    void 	    *app_base_ptr; /* Pointer to the base memory , which will be allocated and
                                    * filled by the  application */
} WMADMemAllocInfoSub;

typedef struct {
    WMAD_Bool   bIsRawDecoder;
    WMAD_UINT16 us16Reentrant;
    WMAD_UINT8 *pus8input_file;
    WMAD_UINT8 *pus8output_file;

    WMAD_UINT16 us16Version;
    WMAD_UINT16 us16wFormatTag;
    WMAD_UINT16 us16Channels;       /* Number of channels (0 or 1) */
    WMAD_UINT32 us32SamplesPerSec;  /* Sampling frequency of the current frame in Khz */
    WMAD_UINT32 us32AvgBytesPerSec; /* Average bit rate */
    WMAD_UINT32 us32nBlockAlign;
    WMAD_UINT32 us32ValidBitsPerSample;
    WMAD_UINT32 us32ChannelMask;
    WMAD_UINT32 us32AdvancedEncodeOpt2;
    WMAD_UINT16 us16EncodeOpt;
    WMAD_UINT16 us16AdvancedEncodeOpt;
    WMAD_UINT32 us32Duration;       // bitstream duration
    WMAD_Bool   bHas_DRM;

    WMAD_Bool    bDropPacket;
    WMAD_UINT16  nDRCSetting;
    WMAD_UINT16  nDecoderFlags;
    WMAD_UINT32  nDstChannelMask;
    WMAD_UINT32  nInterpResampRate;
    WMAD_UINT16  nMBRTargetStream;

    WMAD_UINT16 us16NumSamples;
    WMAD_UINT32 us32OutputBufSize;
    WAVEFORMATEXTENSIBLE *pWfx;

} WMADDecoderParams;

typedef struct {
    WMAD_INT32              s32NumReqs;
    WMADMemAllocInfoSub	    sMemInfoSub [WMAD_MAX_NUM_MEM_REQS];
} WMADMemAllocInfo;

typedef struct WMADDecoderConfig
{
    WMADMemAllocInfo		sWMADMemInfo;
    void			*psWMADecodeInfoStructPtr; // Global_struct

    tWMAFileStatus (*app_swap_buf)(void *state,
                 WMAD_UINT64 offset,
                 WMAD_UINT32 *num_bytes,
                 WMAD_UINT8  **ppData,
                 void *pAppContext,
                 WMAD_UINT32 *compress_payload);

    void                        *pContext;
    WMADDecoderParams		*sDecodeParams; //for Decoder Params
    int         watermark;
} WMADDecoderConfig;


//***********************************************************************
//  API function declaration
//***********************************************************************



tWMAFileStatus eWMADQueryMem    (WMADDecoderConfig *psDecConfig);

tWMAFileStatus eInitWMADecoder  (WMADDecoderConfig *psDecConfig,
                                 WMADDecoderParams *sDecParams,
                                 WMAD_UINT8 *pus8InputBuffer,
                                 WMAD_INT32 ps32InputBufferLength);

tWMAFileStatus eWMADecodeFrame  (WMADDecoderConfig *psDecConfig,
				 WMADDecoderParams *sDecParams,
				 WMAD_INT16 *iOUTBuffer,WMAD_INT32 lLength);



/*============================================================================*/
/* WMA 10 decoder version information API function.                           */
/*============================================================================*/
const WMAD_INT8 * WMA10DoderVersionInfo();

#ifdef __cplusplus
}
#endif

#endif // if ifdef h file
/* End of file. */
