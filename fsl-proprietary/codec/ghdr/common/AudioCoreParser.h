/**
 *  Copyright (c) 2009-2012, Freescale Semiconductor, Inc.
 *  All Rights Reserved.
 *
 *  The following programs are the sole property of Freescale Semiconductors Inc.,
 *  and contain its proprietary and confidential information.
 *
 */

/**
 *  @file AudioCoreParser.h
 *  @brief Audio core parser.
 *  @ingroup AudioCoreParser
 */


#ifndef AudioCoreParser_h
#define AudioCoreParser_h

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "fsl_types.h"

/** Audio parser return value */
typedef enum AUDIO_PARSERRETURNTYPE {
    AUDIO_PARSERRETURNSUCESS = 0,
    AUDIO_PARSERRETURNFAIL
} AUDIO_PARSERRETURNTYPE;
 
typedef enum PCM_MODE {
    PCM_MODE_LINEAR = 0,
    PCM_MODE_ALAW,
	PCM_MODE_MULAW,
	PCM_MODE_UNKNOW
} PCM_MODE;

/** Audio file information */
typedef struct AUDIO_FILE_INFO {
	bool bIsCBR;
	bool bSeekable;
	bool bGotDuration;
	uint32 nFrameHeaderSize;    /*< For overlay search */
	int64 nDuration;
	uint64 nBeginPointOffset;
	uint64 nBitStreamLen;
	uint64 nTotalSample;
	uint32 nChannels;
	uint32 nSamplingRate;
	uint32 nBitRate;
	uint32 nBitPerSample;
	uint32 nBlockSize;
	uint32 nMinBlockSize;
	PCM_MODE ePCMMode;
} AUDIO_FILE_INFO;

typedef struct FRAME_INFO
{
	uint32 frm_size;
	uint32 index;
	uint32 b_rate;
	uint32 flags;
	uint32 total_frame_num;
	uint32 total_bytes;
	uint32 sampling_rate;
	uint32 sample_per_fr;
	uint32 samples;
	uint32 layer;
	uint32 version;
	uint32 xing_exist;
	uint32 vbri_exist;
    uint32 channels;
	uint8  TOC[100];
}FRAME_INFO;

/** Audio frame information */
typedef struct AUDIO_FRAME_INFO {
	bool bGotOneFrame;
	bool bIsCBR;
	uint32 nFrameCount;
	uint32 nFrameHeaderConsumed;
	uint32 nFrameSize;
	uint32 nBitRate;
	uint32 nSamplesPerFrame;
	uint32 nSamplingRate;
	FRAME_INFO FrameInfo;
} AUDIO_FRAME_INFO;


/** Audio core parser need implement below two function */
/*
 * AUDIO_PARSERRETURNTYPE ParserFileHeader(AUDIO_FILE_INFO *pFileInfo, fsl_osal_u8 *pBuffer, \
 *										uint32 nBufferLen);
 * AUDIO_PARSERRETURNTYPE ParserFrame(AUDIO_FRAME_INFO *pFrameInfo, fsl_osal_u8 *pBuffer, \
 *										uint32 nBufferLen);
 *
 */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
/* File EOF */
