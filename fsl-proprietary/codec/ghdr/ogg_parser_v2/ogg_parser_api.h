/************************************************************************
*  Copyright (c) 2010-2012, Freescale Semiconductor, Inc
  * All modifications are confidential and proprietary information
  * of Freescale Semiconductor, Inc. ALL RIGHTS RESERVED.
  ************************************************************************/

/*=============================================================================
                                                                               
    Module Name:  ogg_parser_api.h  

    General Description:  Definitions and Declarations for Ogg Parser.                         
                            
===============================================================================
                           Freescale Confidential Proprietary
                                   WMSG - Multimedia
                   (c) Copyright Freescale 2005, All Rights Reserved
  
Revision History:
                               Modification  Tracking
Author                         Date          Number      Description of Changes
-----------------------------  -----------  ----------  -----------------------
Zhongsong Lin                  19-May-10     ENGR123611  Initial Draft Version.
===============================================================================
*/

#ifndef OGG_VORBIS_H

#define OGG_VORBIS_H

#include "fsl_types.h"
#include "fsl_parser.h"
#include "fsl_media_types.h"


typedef enum
{
    OGG_ERR_WRONG_FILE_SIZE = -111,
    
    OGG_ERR_NOT_OGG_FILE = -120, /* This is not an Ogg file. No RIFF Ogg header found */
    OGG_ERR_UNKNOWN_STREAM_FORMAT = -121,
    OGG_ERR_WRONG_MEDIA_TYPE = -122, /* An API is called on a stream of wrong media type. */
    OGG_ERR_WRONG_VIDEO_FORMAT = -123,
    OGG_ERR_WRONG_AUDIO_FORMAT = -124,

	OGGPARSER_NO_CHACHEDPACKETS = -130,
	OGGPARSER_PACKET_NOTENOUGHDATA = -131
}OGGPARSER_ERROR_CODE_ENUM;

typedef int32 OGGPARSER_ERR_CODE;



/***************************************************************************************
*                  API Funtions
* For calling sequence, please refer to the end of this file.
***************************************************************************************/

#ifdef __cplusplus
#define EXTERN extern "C"
#else
#define EXTERN 
#endif

EXTERN int32 FslParserQueryInterface(uint32 id, void ** func);

/**
 * function to get the Ogg core parser version.
 *  
 * @return Version string.
 */
EXTERN const char * OggParserVersionInfo();

/**
 * function to create the Ogg core parser.
 * 
 * @param stream [in]   Source stream of the Ogg file.
 *                      It implements functions to open, close, tell, read and seek a file.
 *
 * @param memOps [in]   Memory operation callback table.
 *                      It implements the functions to malloc, calloc, realloc and free memory.
 *
 * @param context [in]  Wrapper context for the callback functions. Ogg parser never modify it.
 * @param parserHandle [out] Handle of the Ogg core parser if succeeds. NULL for failure.
 * @return
 */
 
EXTERN int32     OggCreateParser(bool          isLive,
                                FslFileStream * streamOps,                                                        
                                ParserMemoryOps * memOps,
                                ParserOutputBufferOps * outputBufferOps,
                                void * context,
                                FslParserHandle * parserHandle);

/**
 * Function to delete the Ogg core parser.
 *
 * @param parserHandle Handle of the Ogg core parser.
 * @return
 */
EXTERN int32 OggDeleteParser(FslParserHandle parserHandle);


/**
 * Function to tell whether the movie is seekable. 
 * @param parserHandle [in] Handle of the Ogg core parser.
 * @param seekable [out] true for seekable and false for non-seekable 
 * @return 
 */ 
EXTERN int32 OggIsSeekable(FslParserHandle parserHandle, bool * seekable);


/**
 * Function to tell how many tracks in the movie. 
 *
 * @param parserHandle [in] Handle of the Ogg core parser.
 * @param numTracks [out] Number of tracks.
 * @return 
 */ 
EXTERN int32 OggGetNumTracks(FslParserHandle parserHandle, uint32 * numTracks);


/**
 * Function to tell the user data information (title, artist, genre etc) of the movie. User data API.
 * The information is usually a null-terminated ASCII string.
 *
 * @param parserHandle [in] Handle of the Ogg core parser.
 * @param userDataId [in] User data ID. Type of the user data.
 * @param buffer [out] Buffer containing the information. The core parser manages this buffer and the user shall NOT free it.
 *                               If no such info is availabe, this value will be set to NULL.
 * @param size [out] Length of the information in bytes. 
 *                               If no such info is available, this value will be set to 0.
 * @return
 */
EXTERN int32 OggGetUserData(FslParserHandle parserHandle, uint32 userDataId, uint8 ** buffer, uint32 *size);

/*
*/
EXTERN int32 OggGetMetaData (FslParserHandle parserHandle, 
                             UserDataID userDataId,
                             UserDataFormat * userDataFormat,
                             uint8 ** userData,
                             uint32 * userDataLength);

/**
 * Function to tell the movie duration. 
 *
 * @param parserHandle [in] Handle of the Ogg core parser.
 * @param usDuration [out] Duration in us.
 * @return 
 */ 
EXTERN int32 OggGetDuration(FslParserHandle parserHandle,  uint64 * usDuration);


/**
 * Function to tell a track's duration. 
 * The tracks may have different durations. 
 * And the movie's duration is usually the video track's duration (maybe not the longest one).
 * 
 * If a track's duration is 0, this track is empty! Application can read nothing from an empty track.
 *
 * @param parserHandle [in] Handle of the Ogg core parser.
 * @param trackNum [in] Number of the track, 0-based.
 * @param usDuration [out] Duration in us.
 * @return 
 */ 
EXTERN int32 OggGetTrackDuration(FslParserHandle parserHandle, uint32 trackNum, uint64 * usDuration);


/**
 * Function to tell the type of a track. 
 *
 * @param parserHandle [in] Handle of the Ogg core parser.
 * @param trackNum [in] Number of the track, 0-based.
 *
 * @param mediaType [out] Media type of the track. (video, audio, subtitle...)
 *                        "MEDIA_TYPE_UNKNOWN" means the media type is unknown.
 *
 * @param decoderType [out] Decoder type of the track if available. (eg. MPEG-4, H264, AAC, MP3, AMR ...)
 *                          "UNKNOWN_CODEC_TYPE" means the decoder type is unknown.
 *
 * @param decoderSubtype [out] Decoder Subtype type of the track if available. (eg. AMR-NB, AMR-WB ...)
 *                             "UNKNOWN_CODEC_SUBTYPE" means the decoder subtype is unknown.
 * @return 
 */
EXTERN int32 OggGetTrackType(  FslParserHandle parserHandle, 
                                uint32 trackNum, 
                                uint32 * mediaType,
                                uint32 * decoderType,
                                uint32 * decoderSubtype);

/**
 * Function to tell the average bitrate of a track.
 * If the average bitrate is not available in the file header, 0 is given.
 *
 * @param parserHandle [in] Handle of the Ogg core parser.
 * @param trackNum [in] Number of the track, 0-based.
 * @param bitrate [out] Average bitrate, in bits per second. 
 * @return 
 */
EXTERN int32 OggGetBitRate(FslParserHandle parserHandle, uint32 trackNum, uint32 *bitrate);


/**
 * Function to tell the sample duration in us of a track.
 * If the sample duration is not a constant (eg. audio, subtitle), 0 is given.
 * For a video track, the frame rate can be calculated from this information.
 *
 * @param parserHandle [in] Handle of the Ogg core parser.
 * @param trackNum [in] Number of the track, 0-based. 
 * @param usDuration [out] Sample duration in us. If sample duration is not a constant, this value is 0.
 * @return 
 */
 
 EXTERN int32 OggGetVideoFrameRate( FslParserHandle parserHandle, 
                                                uint32 trackNum, 
                                                uint32 * rate, 
                                                uint32 * scale);

//EXTERN int32 OggGetVideoFrameDuration(FslParserHandle parserHandle, uint32 trackNum, uint64 *usDuration);

/**
 * Function to tell the width in pixels of a video track. 
 * @param parserHandle [in] Handle of the Ogg core parser.
 * @param trackNum [in] Number of the track, 0-based. It must point to a video track.
 * @param width [out] Width in pixels.
 * @return 
 */
EXTERN int32 OggGetVideoFrameWidth(FslParserHandle parserHandle, uint32 trackNum, uint32 *width) ;

/**
 * Function to tell the height in pixels of a video track. 
 * @param parserHandle [in] Handle of the Ogg core parser.
 * @param trackNum [in] Number of the track, 0-based. It must point to a video track.
 * @param height [out] Height in pixels.
 * @return 
 */
EXTERN int32 OggGetVideoFrameHeight(FslParserHandle parserHandle, uint32 trackNum, uint32 *height);


/**
 * Function to tell how many channels in an audio track.
 *
 * @param parserHandle [in] Handle of the Ogg core parser.
 * @param trackNum [in] Number of the track, 0-based. It must point to an audio track.
 * @param numchannels [out] Number of the channels. 1 mono, 2 stereo, or more for multiple channels.
 * @return 
 */
EXTERN int32 OggGetAudioNumChannels(FslParserHandle parserHandle, uint32 trackNum, uint32 *numChannels);

/**
 * Function to tell the audio sample rate (sampling frequency) of an audio track.
 * Warning: 
 * The audio sample rate from the file header may be wrong. And if the audio decoder specific information 
 * is available (for AAC), the decoder can double check the audio sample rate from this information.
 *
 * @param parserHandle [in] Handle of the Ogg core parser.
 * @param trackNum [in] Number of the track, 0-based. It must point to an audio track.
 * @param sampleRate [out] Audio integer sample rate (sampling frequency).
 * @return 
 */
EXTERN int32 OggGetAudioSampleRate(FslParserHandle parserHandle, uint32 trackNum, uint32 * sampleRate);


/**
 * Function to tell the bits per sample for an audio track.
 *
 * @param parserHandle [in] Handle of the Ogg core parser.
 * @param trackNum [in] Number of the track, 0-based. It must point to an audio track.
 * @param bitsPerSample [out] Bits per PCM sample.
 * @return 
 */
EXTERN int32 OggGetAudioBitsPerSample(FslParserHandle parserHandle, uint32 trackNum, uint32 * bitsPerSample);

/**
 * Function to tell the width of a text track.
 * The text track defines a window to display the subtitles. 
 * This window shall be positioned in the middle of the screen. 
 * And the sample is displayed in the window.How to position the sample within the window is defined by the sample data.
 * The origin of window is always (0, 0).
 *
 * @param parserHandle [in] Handle of the Ogg core parser.
 * @param trackNum [in] Number of the track, 0-based. It must point to a text track.
 * @param width [out] Width of the text track, in pixels.
 * @return 
 */
EXTERN int32 OggGetTextTrackWidth(FslParserHandle parserHandle, 
                                    uint32 trackNum, 
                                    uint32 * width);
                                                
/**
 * Function to tell the height of a text track.
 * The text track defines a window to display the subtitles. 
 * This window shall be positioned in the middle of the screen. 
 * And the sample is displayed in the window.How to position the sample within the window is defined by the sample data.
 * The origin of window is always (0, 0).
 *
 * @param parserHandle [in] Handle of the Ogg core parser.
 * @param trackNum [in] Number of the track, 0-based. It must point to a text track.
 * @param height [out] Height of the window, in pixels.
 * @return 
 */
EXTERN int32 OggGetTextTrackHeight(FslParserHandle parserHandle, 
                                    uint32 trackNum,
                                    uint32 * height);


/**
 * Function to set the mode to read media samples, file-based or track-based. 
 *  a. File-based sample reading. 
 *      The reading order is same as that of track interleaving in the file. 
 *      Mainly for streaming application.
 *
 *  b. Track-based sample reading. 
 *      Each track can be read and seeked independently from each other.
 *
 * Warning:
 *  - The parser may support only one reading mode.Setting a not-supported reading mode will fail.
 *  - Once selected, the reading mode can no longer change.
 *
 * @param parserHandle [in] Handle of the Ogg core parser.
 * @param trackNum [in] Number of the track, 0-based. It must point to a text track.
 * @param readMode [in] Sample reading mode.
 *
 *                      READ_MODE_FILE_BASED
 *                      Default mode.Linear sample reading. The reading order is same as that of 
 *                      track interleaving in the file.
 *
 *                      READ_MODE_TRACK_BASED  
 *                      Track-based sample reading. Each track can be read independently from each other.
 * @return 
 * PARSER_SUCCESS   The reading mode is set successfully.
 * PARSER_NOT_IMPLEMENTED   The reading mode is not supported.
 * 
 */
EXTERN int32 OggSetReadMode(FslParserHandle parserHandle, 
                            uint32 readMode);

/**
 * Function to get the mode to read media samples, file-based or track-based. * 
 * And the parser has a default read mode.
 *
 * @param parserHandle [in] Handle of the Ogg core parser.
 * @param trackNum [in] Number of the track, 0-based. It must point to a text track.
 * @param readMode [out] Current Sample reading mode.
 *
 *                      READ_MODE_FILE_BASED
 *                      Default mode.Linear sample reading. The reading order is same as that of 
 *                      track interleaving in the file.
 *
 *                      READ_MODE_TRACK_BASED  
 *                      Track-based sample reading. Each track can be read independently from each other.
 * @return  
 */
EXTERN int32 OggGetReadMode(FslParserHandle parserHandle, 
                            uint32 * readMode);


/**
 * Function to enable or disable track.
 * The parser can only output samples from enabled tracks.
 * To avoid unexpected memory cost or data output from a track, the application can disable the track. 
 *
 * @param parserHandle [in] Handle of the Ogg core parser.
 * @param trackNum [in] Number of the track, 0-based. It must point to a text track.
 * @param enable [in] TRUE to enable the track and FALSE to disable it.
 * @return 
 */
EXTERN int32 OggEnableTrack(FslParserHandle parserHandle, 
                                uint32 trackNum,
                                bool enable);


/**
 * Function to read the next sample from the file, only for file-based reading mode.
 * The parser will tell which track is outputting now and disabled track will be skipped. 
 *
 * In this function, the parser may use callback to request buffers to output the sample.
 * And it will tell which buffer is output on returning. But if the buffer is not available or too small,
 * this function will fail.
 *
 * It supports partial output of large samples:
 * If the entire sample can not be output by calling this function once, its remaining data  
 * can be got by repetitive calling the same function.
 *
 * BSAC audio track is somewhat special: 
 * Parser does not only read this BSAC track. But it will read one sample from each BSAC track 
 * in the proper order and make up a "big sample" for the user. 
 * Partial output is still supported and the sample flags describe this "big sample".
 * So the user shall take all BSAC tracks as one track and use any BSAC track number to call this function.
 *
 * @param parserHandle [in] Handle of the Ogg core parser.
 * @param trackNum [out] Number of the track to read, 0-based.
 * @param sampleBuffer [out]   Buffer to hold the sample data. 
 *                             If the buffer is not big enough, only part of sample is output.
 * @param bufferContext [out] Buffer context from application, got on requesting the buffer.
 *
 * @param dataSize [out]    If a sample or part of sample is output successfully (return value is PARSER_SUCCESS ), 
 *                          it's the size of the data actually got.                              
 *
 * @param usStartTime [out] Start time of the sample in us (timestamp)
 * @param usDuration [out] Duration of the sample in us. PARSER_UNKNOWN_DURATION for unknown duration.
 *
 * @param sampleFlags [out] Flags of this sample, if a sample or part of it is got successfully.
 *
 *                            FLAG_SYNC_SAMPLE    
 *                                  Whether this sample is a sync sample (video key frame, random access point). 
 *                                  For non-video media, the application can take every sample as sync sample.
 *                          
 *                            FLAG_SAMPLE_NOT_FINISHED
 *                                  Sample data output is not finished because the buffer is not big enough.                                 
 *                                  Need to get the remaining data by repetitive calling this func.
 *
 *
 * @return  PARSER_SUCCESS     An entire sample or part of it is got successfully.
 *          PARSER_EOS     No sample is got because of end of the track.
 *          PARSER_INSUFFICIENT_MEMORY Buffer is not availble, or too small to output any data at all.                                
 *          PARSER_READ_ERROR  File reading error. No need for further error concealment. 
 *          Others ...
 */

EXTERN int32 OggGetFileNextSample(  FslParserHandle parserHandle, 
                                    uint32 * trackNum,
                                    uint8 ** sampleBuffer,
                                    void  ** bufferContext,
                                    uint32 * dataSize, 
                                    uint64 * usStartTime, 
                                    uint64 * usDuration,
                                    uint32 * sampleFlags);


/**
 * Function to seek a track to a target time, for both track-based mode and file-based mode.
 * The parser handles the mode difference internally.
 * 
 * It will seek to a sync sample of the time stamp 
 * matching the target time. Due to the scarcity of the video sync samples (key frames), 
 * there can be a gap between the target time and the timestamp of the matched sync sample. 
 * So this time stamp will be output to as the accurate start time of the following playback segment.
 *
 * BSAC audio track is somewhat special: 
 * Parser does not only seek this BSAC track. But it will seek all BSAC tracks to the target time
 * and align their reading position.
 * So the user shall take all BSAC tracks as one track and use any BSAC track number to call this function.
 *
 * @param parserHandle [in] Handle of the Ogg core parser.
 * @param trackNum [in] Number of the track to seek, 0-based.
 * @param usTime [in/out]  Target time to seek as input, in us. 
 *                         Actual seeking time, timestamp of the matched sync sample, as output.
 *
 * @param flag [in]  Control flags to seek.
 *
 *                      SEEK_FLAG_NEAREST   
 *                      Default flag.The matched time stamp shall be the nearest one to the target time (may be later or earlier).
 *                           
 *                      SEEK_FLAG_NO_LATER  
 *                      The matched time stamp shall be no later than the target time.
 *                                                              
 *                      SEEK_FLAG_NO_EARLIER
 *                      The matched time stamp shall be no earlier than the target time.
 *
 * @return  PARSER_SUCCESS    Seeking succeeds.
 *          PARSER_EOS  Can NOT to seek to the target time because of end of stream.
 *          PARSER_ERR_NOT_SEEKABLE    Seeking fails because the movie is not seekable (index not available or no sync samples)            
 *          Others      Seeking fails for other reason.
 */
EXTERN  int32 OggSeek(FslParserHandle parserHandle,
                     uint32 trackNum,
                     uint64 * usTime,
                     uint32 flag);

 EXTERN int32 OggParserGetDecSpecificInfo(FslParserHandle parserHandle, 
												  uint32 streamNum, 
												  uint8 ** data,
												  uint32 * size);


#endif