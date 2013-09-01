
/***********************************************************************
* Copyright (c) 2011-2012, Freescale Semiconductor, Inc.
* All modifications are confidential and proprietary information
* of Freescale Semiconductor, Inc. ALL RIGHTS RESERVED.
***********************************************************************/
 
/*
 *
 *  History :
 *  Date             Author              Version    Description
 *
 *  Apr, 2011        Lou Zhan            1.0        Initial Version
 *  Sep, 2011        Fang Hui            1.0.1      Fix ENGR157476. Support long duration.
 *  Oct, 2011        Fang Hui            1.0.2      Add FslMuxerGetTrailerSize, Fix ENGR160218 
 *	May, 2012        Fang Hui            1.0.3      Support geographic location meta data	 
 */

#ifndef _FSL_MUXER_H
#define _FSL_MUXER_H


#ifdef __cplusplus
#define EXTERN extern "C"
#else
#define EXTERN 
#endif

#include "fsl_types.h"

#define MUXER_API_VERSION_STR "MUXER_API_01.00.03"


/* Warning:
 * It's not recommended to use any enum types as API arguments or return value!
 * Please use data types that can explicitly tell the data length and asign 
 * them the listed enum values. It's because different compilers can treat enum 
 * as different types such as integer or unsinged char. If the muxer library 
 * and plug-in(filter) are built by different compliers, the data length 
 * mismatch will cause error.
 */


typedef void * FslMuxerHandle;

#define MUXER_UNKNOWN_DURATION 0    /* Unknown sample duration */
                                       
#define MUXER_UNKNOWN_TIME_STAMP (-1) /* Unknown time stamp */ 
                                       
#define MUXER_UNKNOWN_TRACK_ID (0xFFFFFFFF) /* Unknown track id */ 
 

/*
 * Common error codes of muxers, 
 * within the range [-100 , +100].
 * Different muxers can extend the format specific errors OUTSIDE this range, 
 * in their own API header files. 
 */

enum
{
    MUXER_SUCCESS  = 0,
   
    /* errors */
    MUXER_ERR_UNKNOWN = -1, /* Unknow error, not captured by muxer logic */

    MUXER_ERR_INVALID_API = -2, /* Some common API is not implemented properly */
    
    MUXER_NOT_IMPLEMENTED = -3, /* No support for some feature. */
    MUXER_ERR_INVALID_PARAMETER = -4, /* parameters are invalid */
    MUXER_ERR_INVALID_STATE_OPT = -5, /* api operation in wrong muxer state*/

    MUXER_INSUFFICIENT_MEMORY = -6, /* memory not enough, causing general memory allocation failure */
    MUXER_INSUFFICIENT_DATA = -7, /* data not enough, muxer need more data to go ahead */
    
    MUXER_FILE_OPEN_ERROR = -8, /* Can not open the movie file. */
    MUXER_WRITE_ERROR = -9, /* Error on file writing. */
    MUXER_SEEK_ERROR = -10, /* file system seeking error */

    MUXER_ERR_INVALID_MEDIA = -11, /* invalid or unsupported media format */
    MUXER_ERR_INVALID_CODEC = -12, /* invalid or unsupported codec format */

    MUXER_WRITE_HEADER_FAILURE = -13, /* can not write movie header. */
    MUXER_WRITE_INDEX_FAILURE = -14, /* can not write index table */

    MUXER_ERR_TRACK_EXISTS = -15, /* track ID has already existed */
    MUXER_ERR_INVALID_TRACK_ID = -16, /* invalid track ID or inexistent track  */
    
};




/********************************************************************* 
 * sample flags : 
 * 32-bit long, properties of a sample read.
 * The low 16 bits is reserved for common flag.
 * Muxers can use high 16 bits to define their own flags.
 ********************************************************************/
#define FLAG_SYNC_SAMPLE         0x00000001  /* This is a sync sample */
#define FLAG_SAMPLE_NOT_FINISHED 0X00000008  /* only partial sample in the input buffer */



/********************************************************************* 
 * Property Type
*********************************************************************/
typedef enum FSL_MUXER_PROPERTY_TYPE
{
    /* common */
    PROPERTY_MODE = 0,              /* muxer mode. */
    PROPERTY_TIMESCALE,             /* time-scale of track or movie. this is 
                                     * the number of time units that pass in 
                                     * one second. For example, a time 
                                     * coordinate system that measures time in 
                                     * sixtieths of a second has a time scale 
                                     * of 60. Default is 1,000,000 */
    PROPERTY_DURATION,              /* movie or track duration in time-scale */
    PROPERTY_AVERAGE_BIT_RATE,      /* average bit rate of movie or track */
    PROPERTY_CODEC_SPECIFIC_INFO,   /* codec specific information */
    
    /* video/text */
    PROPERTY_FRAME_WIDTH = 64,      /* width of video frame or text window */
    PROPERTY_FRAME_HEIGHT,          /* height of video frame or text window */
    PROPERTY_FRAME_RATE,
    
    /* audio */
    PROPERTY_CHANNEL_NUMBER = 128,  /* audio channel number */
    PROPERTY_SAMPLE_RATE,           /* audio sample rate */
    PROPERTY_BIT_DEPTH,             /* audio sample bit depth */
    PROPERTY_BLOCK_ALIGNMENT,       /* audio block alignment */
    PROPERTY_BITS_PER_FRAME,        /* bits per audio frame */
    PROPERTY_CHANNEL_MASK           /* audio channel mask */
} PropertyID;


/********************************************************************* 
 * Metadata Type
*********************************************************************/
typedef enum FSL_MUXER_METADATA_TYPE
{
    METADATA_TITLE = 0,        /* title of the content */
    METADATA_LANGUAGE,         /* language of movie or track, ISO 639-2/T code (DATA_FORMAT_UTF8) */
    METADATA_GENRE,            /* genre of the content, mainly music */   
    METADATA_ARTIST,           /* main artist and performer */
    METADATA_COPYRIGHT,        /* copyright statement */
    METADATA_COMMENTS,         /* comments of the content */
    METADATA_CREATION_DATE,    /* date the movie content was created */
    METADATA_RATING,           /* rating */
    METADATA_ALBUM,            /* album name of music content */
    METADATA_VCODECNAME,       /* video codec name */
    METADATA_ACODECNAME = 10,  /* audio codec name */
    METADATA_ARTWORK,          /* artwork of movie or music */
    METADATA_COMPOSER,         /* name of composer */
    METADATA_DIRECTOR,         /* name of movie's director */
    METADATA_INFORMATION,      /* information about the movie */
    METADATA_CREATOR,          /* name of the file creator or maker */
    METADATA_PRODUCER,         /* name of producer */
    METADATA_PERFORMER,        /* name of performer */
    METADATA_REQUIREMENTS,     /* special hardware and software requirements */
    METADATA_SONGWRITER,       /* name of songwriter */
    METADATA_MOVIEWRITER = 20, /* name of movie's writer */
    METADATA_TOOL,             /* writing application */
    METADATA_DESCRIPTION,      /* movie description */
    METADATA_LOCATION,         /* Geographic point location by coordinates as defined in ISO 6709:2008.*/
    
    METADATA_MAX
} MetadataID;

/********************************************************************* 
 * User data format
*********************************************************************/
typedef enum FSL_DATA_FORMAT
{
    DATA_FORMAT_UTF8 = 0,       /* all strings in stream should be 
                                 * convert to UTF-8 and output */

    DATA_FORMAT_INT8,           /* signed 8-bit integer */
    DATA_FORMAT_INT16,          /* signed 16-bit integer */
    DATA_FORMAT_INT32,          /* signed 32-bit integer */
    DATA_FORMAT_INT64,          /* signed 64-bit integer */
    DATA_FORMAT_UINT8,          /* unsigned 8-bit integer */
    DATA_FORMAT_UINT16,         /* unsigned 16-bit integer */
    DATA_FORMAT_UINT32,         /* unsigned 32-bit integer */
    DATA_FORMAT_UINT64,         /* unsigned 64-bit integer */
    DATA_FORMAT_FLOAT32,        /* floating 32-bit point */
    DATA_FORMAT_FLOAT64,        /* floating 64-bit point */
    DATA_FORMAT_FRACTION,       /* fraction. shall be istance of FractionData */

    DATA_FORMAT_JPEG,           /* JPEG picture */
    DATA_FORMAT_PNG,            /* PNG picture */
    DATA_FORMAT_BMP,            /* BMP picture */
    DATA_FORMAT_GIF,            /* GIF picture */

    DATA_FORMAT_GENERAL_BINARY, /* general binary */
    
    DATA_FORMAT_MAX
} DataFormat;


/********************************************************************* 
 * Fraction structure
*********************************************************************/
typedef struct _FSL_FRACTION_DATA
{
    int32 numerator;
    int32 denominator;
} FractionData;


/********************************************************************* 
 * file I/O interface on a file or live source. 

open
    Open a local file or URL.
    Arguments:
        fileName [in] File name or url to open. 
                      To open the movie source file, just set file name to NULL.
                      To open another external file for some track (eg. MP4), set the url. 
                      
        mode [in] Open mode, same as libc. Such as "rb".
        
    Return value:
        Handle of the opened file. NULL for failure.

read
    Read data from the file.
    Arguments:
        handle [in] Handle of the file.
        buffer [in] Pointer to a block of memory, to receive the data.
        size[in] Data size to read, in bytes.

    Return value:
        The total number of bytes successfully read.
        If this number differs from the size parameter, either an error occured or the EOF was reached.


seek    
    Seek the stream.
    Arguments:
        handle [in] Handle of the file.
        offset [in] The offset.
                    To move to a position before the end-of-file, you need to pass a negative value in offset and set whence to SEEK_END. 

        whence in]  The new position, measured in bytes from the beginning of the file, 
                    is obtained by adding offset to the position specified by whence. 
                    SEEK_SET - Set position equal to offset bytes. 
                    SEEK_CUR - Set position to current location plus offset . 
                    SEEK_END - Set position to end-of-file plus offset.
    Return value:
        Upon success, returns 0; otherwise, returns -1. 

tell
    Tell the position of the file pointer 
    Arguments:
        handle [in] Handle of the file.

    Return value:
        Returns the position of the file pointer in bytes; i.e., its offset into the file stream.
        If error occurs or this feature can not be supported (eg. broadcast application), returns -1.        

size
    Tell the size of the entire file.
    Arguments:
        handle [in] Handle of the file.
    Return value:
        Returns the file size in bytes.
        If error occurs or this feature can not be supported (eg. broadcast application), returns -1.

check_available_bytes
    Tell the availble bytes of the file. Especially useful for a live source file (streaming).
    The muxer can decide not to read if cached data is not enough and so avoid reading failure in unexpected context.
    For a local file, any bytes request from the muxer can be met as long as it's within the file range.
    
    Arguments:
        handle [in] Handle of the file.
        bytes_requested [in]    Bytes requested for further parsing. This information can help the application 
                                to cache enough data before calling muxer API next time.
                                If the muxer can not know the exact data size needed, set it to 0.
        
    Return value:
        If the file source can always meet the data reading request unless EOF (eg. a local file or a pull-mode live source),
        returns the data size from the current file pointer to the file end.

        Otherwise (eg. a push-mode live source), returns the cached data size.        
        If error occurs or this feature can not be supported (eg. broadcast application), returns -1.

close
    Close the file.
    Arguments:
        handle [in] Handle of the file.        
        
    Return value:
        Upon success, returns 0; otherwise, returns -1. 
*/

typedef void * FslFileHandle;

/* Seek origin, position from where offset is added, same as libc */
#ifndef FSL_SEEK_SET
#define FSL_SEEK_SET 0 /* SEEK_SET, Beginning of file */
#endif
#ifndef FSL_SEEK_CUR
#define FSL_SEEK_CUR 1  /* SEEK_CUR, Current position of file pointer */
#endif
#ifndef FSL_SEEK_END
#define FSL_SEEK_END 2  /* SEEK_END, End of file */
#endif

typedef struct _FslFileStream
{
    FslFileHandle (*Open)(const uint8 * fileName, 
                          const uint8 * mode, 
                          void * context); /* Open a file or URL */
    int32 	(*Close)(FslFileHandle handle, 
                     void * context); /* Close the stream */   
    uint32  (*Write)(FslFileHandle handle, 
                     void * buffer, 
                     uint32 size, 
                     void * context); /* Write data to stream */
    int32 	(*Seek)(FslFileHandle handle, 
                    int64 offset, 
                    int32 whence, 
                    void * context);  /* Seek the stream */
    int64  	(*Tell)(FslFileHandle handle, 
                    void * context); /* Tell the current position from start of the stream */
    
    void * reserved[2];
} FslFileStream;


/********************************************************************* 
 * Core muxer memory callback funtion pointer table.
 *********************************************************************/
typedef struct 
{  
    void* (*Calloc) (uint32 numElements, uint32 size);
    void* (*Malloc) (uint32 size);
    void  (*Free) (void * ptr);     
    void* (*ReAlloc)(void * ptr, uint32 size);
    
    void * reserved[2];

} MuxerMemoryOps; /* callback operation callback table */



/*********************************************************************************************************
 *                  API Funtion Prototypes List
 *
 * There are mandotory and optional APIs.
 * A core muxer must implent the mandory APIs while need not implement the optional one. 
 * And in its DLL entry point "FslMuxerInit", it shall set the not-implemented function pointers to NULL. 
 *
 *********************************************************************************************************/

/***************************************************************************************
 *
 *                Creation & Deletion
 *
 ***************************************************************************************/
/* all mandatory */
typedef const char * (*FslMuxerApiVersionInfo)(uint32 *mainVersion, 
                                                 uint32 *minorVersion);

typedef const char * (*FslMuxerVersionInfo)();

typedef int32 (*FslCreateMuxer)(bool isLive, 
                                FslFileStream *streamOps, 
                                MuxerMemoryOps *memOps, 
                                void *context, 
                                FslMuxerHandle *muxerHandle);

typedef int32 (*FslDeleteMuxer)(FslMuxerHandle muxerHandle); 


/************************************************************************************************************
 *
 *               Movie Level
 *
 ************************************************************************************************************/
/* mandatory */
typedef int32 (*FslMuxerSetMovieProperty)(FslMuxerHandle muxerHandle, 
                                          PropertyID propertyId, 
                                          DataFormat propertyFormat, 
                                          void *propertyData, 
                                          uint32 propertyDataLength);

/* optional */
typedef int32 (*FslMuxerSetMovieMetadata)(FslMuxerHandle muxerHandle, 
                                          MetadataID metadataId, 
                                          DataFormat metadataFormat, 
                                          void *metadata, 
                                          uint32 metadataLength);

/* mandatory */
typedef int32 (*FslMuxerWriteHeader)(FslMuxerHandle muxerHandle);

/* mandatory */
typedef int32 (*FslMuxerWriteTrailer)(FslMuxerHandle muxerHandle);

/* mandatory */
typedef int32 (*FslMuxerAddTrack)(FslMuxerHandle muxerHandle, 
                                  uint32 mediaType, 
                                  uint32 codecType, 
                                  uint32 codecSubType, 
                                  uint32 *trackId);

/* optional */
typedef int32 (*FslMuxerGetTrailerSize)(FslMuxerHandle muxerHandle, uint32 *tailerSize);


/************************************************************************************************************
 *
 *              Track Level
 *
 ************************************************************************************************************/
/* mandatory */
typedef int32 (*FslMuxerSetTrackProperty)(FslMuxerHandle muxerHandle, 
                                          uint32 trackId, 
                                          PropertyID propertyId, 
                                          DataFormat propertyFormat, 
                                          void *propertyData, 
                                          uint32 propertyDataLength);

/* optional */
typedef int32 (*FslMuxerSetTrackMetadata)(FslMuxerHandle muxerHandle, 
                                          uint32 trackId, 
                                          MetadataID metadataId, 
                                          DataFormat metadataFormat, 
                                          void *metadata, 
                                          uint32 metadataLength);

/* mandatory */
typedef int32 (*FslMuxerAddSample)(FslMuxerHandle muxerHandle, 
                                   uint32 trackId, 
                                   uint8 *sampleBuffer, 
                                   uint32 sampleSize, 
                                   uint64 pts, 
                                   uint64 dts, 
                                   uint64 duration, 
                                   uint32 flags);


/************************************************************************************************************
 *
 *               DLL entry point (mandatory) - to query muxer interface
 *
 ************************************************************************************************************/
enum /* API function ID */
{
    MUXER_API_VERSION = 0, 

    /* creation & deletion */
    MUXER_API_GET_VERSION_INFO     = 1,
    MUXER_API_CREATE_MUXER         = 2,
    MUXER_API_DELETE_MUXER         = 3,
    
    /* movie */
    MUXER_API_SET_MOVIE_PROPERTY   = 20,
    MUXER_API_SET_MOVIE_METADATA   = 21,
    MUXER_API_WRITE_MOVIE_HEADER   = 22,
    MUXER_API_WRITE_MOVIE_TRAILER  = 23,
    MUXER_API_GET_MOVIE_TAILER_SIZE = 24,
    
    /* track */
    MUXER_API_ADD_TRACK            = 30,
    MUXER_API_SET_TRACK_PROPERTY   = 31,
    MUXER_API_SET_TRACK_METADATA   = 32,
    MUXER_API_ADD_SAMPLE           = 33,
}; 

/* prototype of entry point */
typedef int32 (*tFslMuxerQueryInterface)(uint32 id, void ** func);

/* 
Every core muxer shall implement this function and tell a specific API function pointer.
If the queried API is not implemented, the muxer shall set funtion pointer to NULL and return MUXER_SUCCESS. */

EXTERN int32 FslMuxerQueryInterface(uint32 id, void ** func);


#endif /* _FSL_MUXER_COMMON_H */

