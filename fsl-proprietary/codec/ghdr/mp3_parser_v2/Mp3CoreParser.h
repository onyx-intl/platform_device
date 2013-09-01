/**
 *  Copyright (c) 2010, Freescale Semiconductors Inc.,
 *  All Rights Reserved.
 *
 *  The following programs are the sole property of Freescale Semiconductors Inc.,
 *  and contain its proprietary and confidential information.
 *
 */

/**
 *  @file Mp3CoreParser.h
 *  @brief MP3 core parser.
 *  @ingroup Mp3CoreParser
 */


#ifndef Mp3CoreParser_h
#define Mp3CoreParser_h

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "AudioCoreParser.h"

AUDIO_PARSERRETURNTYPE Mp3ParserFileHeader(AUDIO_FILE_INFO *pFileInfo, uint8 *pBuffer, \
 										uint32 nBufferLen);
AUDIO_PARSERRETURNTYPE Mp3ParserFrame(AUDIO_FRAME_INFO *pFrameInfo, uint8 *pBuffer, \
										uint32 nBufferLen);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
/* File EOF */
