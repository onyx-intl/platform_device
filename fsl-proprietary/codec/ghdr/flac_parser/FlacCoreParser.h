/**
 *  Copyright (c) 2010, Freescale Semiconductors Inc.,
 *  All Rights Reserved.
 *
 *  The following programs are the sole property of Freescale Semiconductors Inc.,
 *  and contain its proprietary and confidential information.
 *
 */

/**
 *  @file FlacCoreParser.h
 *  @brief FLAC core parser.
 *  @ingroup FlacCoreParser
 */


#ifndef FlacCoreParser_h
#define FlacCoreParser_h

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "AudioCoreParser.h"

enum {
  FLAG_SUCCESS,
  FLAG_NEEDMORE_DATA
};

AUDIO_PARSERRETURNTYPE FlacParserFileHeader(AUDIO_FILE_INFO *pFileInfo, uint8 *pBuffer, \
 										uint32 nBufferLen);
AUDIO_PARSERRETURNTYPE FlacParserFrame(AUDIO_FRAME_INFO *pFrameInfo, uint8 *pBuffer, \
										uint32 nBufferLen);
FRAME_INFO DoFlacParserFrame(uint8 *pBuffer, uint32 nBufferLen, AUDIO_FILE_INFO *pFileInfo);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
/* File EOF */
