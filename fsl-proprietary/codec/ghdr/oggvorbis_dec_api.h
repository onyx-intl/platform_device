
 /************************************************************************
  * Copyright 2005-2010 by Freescale Semiconductor, Inc.
  * All modifications are confidential and proprietary information
  * of Freescale Semiconductor, Inc. ALL RIGHTS RESERVED.
  ************************************************************************/

#ifndef _OGG_DEC_API_H_
#define _OGG_DEC_API_H_

#ifdef __cplusplus
#define EXTERN extern "C"
#else
#define EXTERN 
#endif

#include "oggvorbis_dec_os_types.h" //DSPhl28176

typedef struct {

    void *datasource; /* Pointer to a FILE *, etc. */
    int current_section;
    char *initial_buffer;
    int buffer_length;

    void *pvOggDecObj;  /*!< decoder library object   */
    unsigned int OggDecObjSize;
    void *pvAppContext; /*!< Anything app specific    */
    size_t (*read_func)  (void *ptr, size_t size, size_t nmemb, void *datasource);
    int    (*seek_func)  (void *datasource, ogg_int64_t offset, int whence);
    int    (*close_func) (void *datasource);
    long   (*tell_func)  (void *datasource);

    //Output
    char *pcmout;
    int output_length;

    //Internal Buffer for decoder
    unsigned char *decoderbuf;
    unsigned int buf_size;

    //Misc
    int TotalCodeBookEntries;
    int NoOfChannels;
    int SampleRate;
    int max_bitrate;
    int ave_bitrate;
    int min_bitrate;

    int mPacketCount;   //indicate the packetCount
    int byteConsumed;
    int outNumSamples;  // indicate output sample in each channel
} sOggVorbisDecObj;

EXTERN int OggVorbisDecoderInit(sOggVorbisDecObj *psOVDecObj);
EXTERN int OggVorbisDecoderReLocate(sOggVorbisDecObj *psOVDecObj);
EXTERN int OggVorbisDecode(sOggVorbisDecObj *psOVDecObj);
EXTERN int OggVorbisCleanup(sOggVorbisDecObj *psOVDecObj);
EXTERN int OggVorbisQueryMem(sOggVorbisDecObj *psOVDecObj);
EXTERN const char * OggVorbisVerInfo();

/* Vorbis ERRORS and return codes ***********************************/

/*
typedef enum
{
 OGGV_SUCCESS       =   0
,OGGV_FALSE         =   -1
,OGGV_EOF           =   -2
,OGGV_HOLE          =   -3
,OGGV_EREAD         =   -128
,OGGV_EFAULT        =   -129
,OGGV_EIMPL         =   -130
,OGGV_EINVAL        =   -131
,OGGV_ENOTVORBIS    =   -132
,OGGV_EBADHEADER    =   -133
,OGGV_EVERSION      =   -134
,OGGV_ENOTAUDIO     =   -135
,OGGV_EBADPACKET    =   -136
,OGGV_EBADLINK      =   -137
,OGGV_ENOSEEK       =   -138
}OggVorbisDecRetType;
*/
typedef enum {
    VORBIS_DATA_OK = 0,
    VORBIS_HEADER_OK,
    VORBIS_COMMENT_OK,
    VORBIS_CODEBOOK_OK,
    VORBIS_ERROR_MIN = 64,
    VORBIS_HEADER_BAD,
    VORBIS_COMMENT_BAD,
    VORBIS_CODEBOOK_BAD,
    VORBIS_SYNTH_FAILED,
    VORBIS_BLOCKIN_FAILED,
    VORBIS_OUTBUF_OVFLOW
}eVorbisResult ; //enum eVorbisResult
#endif
