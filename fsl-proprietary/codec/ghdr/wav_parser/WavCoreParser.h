/**
 *  Copyright (c) 2010, Freescale Semiconductors Inc.,
 *  All Rights Reserved.
 *
 *  The following programs are the sole property of Freescale Semiconductors Inc.,
 *  and contain its proprietary and confidential information.
 *
 */

/**
 *  @file WavCoreParser.h
 *  @brief WAV core parser.
 *  @ingroup WavCoreParser
 */


#ifndef WavCoreParser_h
#define WavCoreParser_h

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "AudioCoreParser.h"

AUDIO_PARSERRETURNTYPE WavParserFileHeader(AUDIO_FILE_INFO *pFileInfo, uint8 *pBuffer, \
 										uint32 nBufferLen);
AUDIO_PARSERRETURNTYPE WavParserFrame(AUDIO_FRAME_INFO *pFrameInfo, uint8 *pBuffer, \
										uint32 nBufferLen);
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
/* File EOF */
