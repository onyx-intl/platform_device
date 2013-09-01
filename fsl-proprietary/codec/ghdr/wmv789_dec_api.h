
/**********************************************************************
*
* Motorola Inc.
* (c) Copyright 2005 Motorola, Inc.
* ALL RIGHTS RESERVED.
*
***********************************************************************
*
* File Name: wmv9_dec_api.h
*
* Description: This header file describes all the enumerations, data types,
*              structures, macros and functions to be exposed to the
*              application developers.
*
****************************** Change History**************************
*
*    DD/MMM/YYYY     Code Ver     Description            Author
*    -----------     --------     -----------            ------
* 01 Feb 2005        0.1       Intial version            Debashis Sarkar
* 04 Feb 2005        0.2       First version that runs   Debashis
* 16 Feb 2005        0.3       Review comments           Debashis
* 23 Aug 2006        0.4       Updated for UYVY          Prachi/Pavan
*                              support:TLSbo75126
* 24 Nov 2006        0.5       Increased the maximum     Abhishek M
*                              number of mem requests
*                              from 256 to 512.
*                              Added an memory type
*                              to indicate
*                              whether buffer holds the
*                              output (TLSbo79957)
* 2 Jan 2007         0.6       Changes for getting       Abhishek M
*                              padded/non-padded o/p
* 19 June 2008      0.7   add demo protection and api version    Eagle Zhou: ENGR00080797
***********************************************************************/
 /************************************************************************
  * Copyright 2005-2010 by Freescale Semiconductor, Inc.
  * All modifications are confidential and proprietary information
  * of Freescale Semiconductor, Inc.
  ************************************************************************/


#ifndef WMV9_DEC_API_H
#define WMV9_DEC_API_H


/*********** Basic data types ***********/

typedef void               WMV9D_Void;

typedef int                WMV9D_S32;
typedef unsigned int       WMV9D_U32;

typedef short int          WMV9D_S16;
typedef short unsigned int WMV9D_U16;

typedef char               WMV9D_S8;
typedef unsigned char      WMV9D_U8;


/******** Call back function pointer type, used in data retrieving *********/

typedef WMV9D_S32 (*FpWmv9DecReadCbkType) (WMV9D_S32 s32BufLen,
                                           WMV9D_U8* pu8Buf,
                                           WMV9D_S32* bEndOfFrame,
                                           WMV9D_Void* pvAppContext);


/**************        Macro definitions        *****************/

/* memory types not exactly a bitfield, but could have been */

/* Slow memory is reasonable, and expected */
#define WMV9D_SLOW_MEMORY       0x0001

/* Fast memory is adviced and desirable. It will have impact on performance */
#define WMV9D_FAST_MEMORY       0x0002

/* Memory content is used over API calls, and can not be reused in between */
#define WMV9D_STATIC_MEMORY     0x0004

/* Memory content is not used over API calls, and can be reused in between */
#define WMV9D_SCRATCH_MEMORY    0x0008

/* Memory required can change, depending of the frame size, or sequence */
#define WMV9D_SIZE_DEPENDENT    0x0010

/* Memory size has changed after last allocation, or it is being initialized */
#define WMV9D_SIZE_CHANGED      0x0020

/* Memory needs to be copied to new location, if reallocation happens.
 * The size to be copied is minimum of old size and current size */
#define WMV9D_COPY_AT_RESIZE    0x0040

//#ifdef OUTPUT_BUFFER_CHANGES
/*memory req for output buffers*/
#define WMV9D_OUTPUT_MEMORY    0x0080
//#endif



/****** macros to extract memory types ******/

/* Returns true if the memory required is fast */
#define WMV9D_IS_FAST_MEMORY(memType)       ((memType) & WMV9D_FAST_MEMORY)

/* Returns true if the memory reuired can be slow */
#define WMV9D_IS_SLOW_MEMORY(memType)       ((memType) & WMV9D_SLOW_MEMORY)


/* Returns true if the memory usage is static type */
#define WMV9D_IS_STATIC_MEMORY(memType)     ((memType) & WMV9D_STATIC_MEMORY)

/* Returns true if the memory content is not used over API calls */
#define WMV9D_IS_SCRATCH_MEMORY(memType)    ((memType) & WMV9D_SCRATCH_MEMORY)


/* Returns true, if the buffer size depends on frame size and/or sequence */
#define WMV9D_IS_SIZE_DEPENDENT_MEMORY(memType) \
                                            ((memType) & WMV9D_SIZE_DEPENDENT)

/* Returns true if the buffer size has changed after last allocation */
#define WMV9D_IS_SIZE_CHANGED(memType)      ((memType) & WMV9D_SIZE_CHANGED)

/* Returns true, if the buffer needs to be copied while reallocating */
#define WMV9D_NEEDS_COPY_AT_RESIZE(memType) ((memType) & WMV9D_COPY_AT_RESIZE)

/* Returns true, if the buffer holds output data */
//#ifdef OUTPUT_BUFFER_CHANGES
#define WMV9D_IS_OUTPUT_MEMORY(memType)     ((memType) & WMV9D_OUTPUT_MEMORY)
//#endif
/*
 * Define to control the loging level. Can be set from build command or here.
 * The debug levels are currently defined at 4 levels, sequence layer [bit0],
 * frame layer [bit1], macroblock layer [bit3] and block layer [bit4]. There
 * is no debug level for each pixel, as it is too much of data to handle. To
 * enable debug at any level, set the corresponding bit to 1. To enable
 * function entry and exit, use bit7. Please note that function entry and
 * exit will be loged only for the levels, where the debug is on.
 */

//#ifndef WMV9_DEBUG_LEVEL
#define WMV9_DEBUG_LEVEL  0x00    /* no debugging is set */
//#endif


/*
 * Maximum number of memory requests that can be made by the decoder. Do not
 * modify this value.
 */
//#ifndef WMV9_SIMPLE_ONLY
//#define WMV9D_MAX_NUM_MEM_REQS              512
//#else
#define WMV9D_MAX_NUM_MEM_REQS              256
//#endif

/*
 * Bit buffer size used by the decoder. The memory required for this is
 * allocated through memquery API as fast memory. Do not make it huge, as
 * it is never required to hold more than one frame worth data at any given
 * time. It may contain part of one frames data, if frame data size is larger.
 */

#define WMV9D_BIT_BUFFER_LENGTH    256


/*********** enumeration types ***********/

/*
 * Return types from all of the decoder API's, except the format converter
 */

typedef enum
{
    /* Successfull return values */
    E_WMV9D_SUCCESS = 0,          /* Successful completion                  */

    /* Successful return with a warning, no action needs to be taken */
    E_WMV9D_ERROR_CONCEALED = 11, /* Error in the bit stream, but concealed */
    E_WMV9D_ENDOF_BITSTREAM,      /* End of Bit Stream                      */

    /* Successful return with a warning, correct the situation and continue */
    E_WMV9D_NOT_ENOUGH_BITS=31,   /* Not enough bits are provided           */
    E_WMV9D_BAD_MEMORY,           /* Out of memory                          */
    E_WMV9D_WRONG_ALIGNMENT,      /* Incorrect memory alignment             */
    E_WMV9D_SIZE_CHANGED,         /* Image size changed                     */
    E_WMV9D_NO_OUTPUT,            /* No output frame is available           */
    E_WMV9D_BROKEN_FRAME,         /* Should have more data in this frame    */
    E_WMV9D_DEMO_PROTECT,         /* the output is corrupted by demo protection    */

    /* irrecoverable error type, may need re-initialization to continue */
    E_WMV9D_CORRUPTED_BITS=51,    /* Error bit stream                       */
    E_WMV9D_FAILED,               /* Failure                                */
    E_WMV9D_UNSUPPORTED,          /* Unsupported format                     */
    E_WMV9D_NO_KEYFRAME_DECODED,  /* first frame is not an I frame          */
    E_WMV9D_SIZE_NOT_FOUND,       /* Frame size not found in bit stream     */
    E_WMV9D_NOT_INITIALIZED,      /* Decoder is not initialized             */
    E_WMV9D_INVALID_ARGUMENTS     /* Argument to the API is invalid         */
} eWmv9DecRetType;


/*
 * Memory alignment types enumeration.
 */

typedef enum
{
    E_WMV9D_ALIGN_NONE = 0,       /* buffer can start at any place          */
    E_WMV9D_ALIGN_HALF_WORD,      /* address's last bit has to be 0         */
    E_WMV9D_ALIGN_WORD,           /* address's last 2 bits has to be 0      */
    E_WMV9D_ALIGN_DWORD,          /* address's last 3 bits has to be 0      */
    E_WMV9D_ALIGN_QWORD,          /* address's last 4 bits has to be 0      */
    E_WMV9D_ALIGN_OCTAWORD        /* address's last 5 bits has to be 0      */
} eWmv9DecMemAlignType;


/*
 * Type of the VOP decoded last.
 */

typedef enum
{
    E_WMV9D_INTRA_VOP,           /* Intra VOP or I-VOP	                    */
    E_WMV9D_INTER_VOP,           /* Inter VOP or P-VOP	                    */
    E_WMV9D_BIDIR_VOP,           /* Bidirectional VOP or B-VOP              */
    E_WMV9D_UNKNOWN_VOP,         /* Unknown, should not happen              */
} eWmv9DecVOPType;


/*
 * Defines the encoding bitstream. It does not cover all of the possible asf
 * string. Use the converter function to convert the asf string to this type,
 * in case multiple types are supported by same application. Otherwise (only
 * one format is guranteed at the input) application can use the corresponding
 * value directly, without trying to use asf format string.
 */

typedef enum
{
    E_WMV9D_COMP_FMT_WMV9,       /* WMV9 encoded bitstream                  */
    E_WMV9D_COMP_FMT_WMV8,       /* WMV8 encoded bitstream                  */
    E_WMV9D_COMP_FMT_WMV7,       /* WMV7 encoded bitstream                  */
    E_WMV9D_COMP_FMT_UNSUPPORTED /* Unsupported encoded bitstream           */
} eWmv9DecCompFmtType;



/************ Decoder data structures ***********/

/* Data structure to define each memory block request */

typedef struct
{
    WMV9D_S32            s32Size;     /* Current size requirement            */
    WMV9D_S32            s32MemType;  /* Memory type description             */
    WMV9D_S32            s32Priority; /* determines impact on the performance */
    eWmv9DecMemAlignType eMemAlign;   /* Memory alignment of the buffer      */
    WMV9D_S32            s32OldSize;  /* Old size, in case being reallocated */
    WMV9D_S32            s32MaxSize;  /* Maximum size that can be asked for  */
    WMV9D_Void*          pvUnalignedBuffer;  /* unaligned buffer pointer     */
    WMV9D_Void*          pvBuffer;    /* buffer start address with alignment */
} sWmv9DecMemBlockType;


/*
 * Data structure to define the complete memmory requests
 */

typedef struct
{
    WMV9D_S32             s32NumReqs;  /* Number of valid requests           */
    sWmv9DecMemBlockType  asMemBlks[WMV9D_MAX_NUM_MEM_REQS]; /* requests     */
} sWmv9DecMemAllocInfoType;


/*Added to support UYVY and IYUV and IYUV padded data*/

typedef enum tagVideoFormat_WMC
{
    IYUV_WMV=0,

    //#ifdef OUTPUT_BUFFER_CHANGES
    IYUV_WMV_PADDED,
    //#endif

    //#ifndef WMV9_SIMPLE_ONLY
    //UYVY_WMV
    //#endif

} tVideoFormat_WMC;



/*
 * Structure to hold the decoded frame information.
 * Please note that currently the row size for Cb and Cr contains same value
 */

typedef struct
{
    WMV9D_U8* pu8YBuf;      /* Y component data buffer start address  */
    WMV9D_U8* pu8CbBuf;     /* Cb component data buffer start address */
    WMV9D_U8* pu8CrBuf;     /* Cr component data buffer start address */

    WMV9D_S32       s32YRowSize;  /* Row size of Y data buffer  (padded width Luma)            */
    WMV9D_S32       s32CbRowSize; /* Row size of Cb data buffer (padded width Chroma)          */
    WMV9D_S32       s32CrRowSize; /* Row size of Cr data buffer (padded width Chroma)          */
    //#ifdef OUTPUT_BUFFER_CHANGES
    tVideoFormat_WMC tOutputFormat;
    //#endif
} sWmv9DecYCbCrBufferType;


/*
 * Structure to hold the parameters that are passed from application to
 * decoder and vice versa. Frame rate and bitrate, though set by application
 * initialy, can be corrected by decoder while initilizing.
 */

typedef struct
{
    sWmv9DecYCbCrBufferType sOutputBuffer;      /* decoded frame information */
    eWmv9DecCompFmtType     eCompressionFormat; /* encoding format info      */
    WMV9D_S32               s32FrameRate;       /* Frame rate in fps         */
    WMV9D_S32               s32BitRate;         /* Bit rate in bps           */
    WMV9D_U16               u16FrameWidth;      /* Frame width in pixels     */
    WMV9D_U16               u16FrameHeight;     /* Frame hight in pixels     */
    WMV9D_U32               u32PrevFrameNum;    /* Please see the API doc    */
    WMV9D_U32               u32CurrFrameNum;    /* Last decoded frame number */
    eWmv9DecVOPType         eVopType;           /* Last decoded frame's type */
} sWmv9DecParamsType;


/*
 * Main WMV9 decoder object. This is used in all decoder API.
 */

typedef struct
{
    sWmv9DecMemAllocInfoType sMemInfo;     /* memory requirements            */
    sWmv9DecParamsType       sDecParam;    /* sequence/frame paramters       */
    WMV9D_Void*              pvWmv9Obj;    /* internal decoder object        */
    WMV9D_Void*              pvBitBuffer;  /* buffer for bitstream           */
    WMV9D_Void*              pvAppContext; /* application context for cbk    */
    FpWmv9DecReadCbkType     pfCbkBuffRead;/* Callback function pointer      */
} sWmv9DecObjectType;




/************  function definitions *****************/

/* Small utility functions, helpful to the application */

/*
 * Returns the compression format type used in API, given the ASF file
 * compression format string. Right now, only WMV[123] strings are supported.
 * For the rest types, it returns unsupported format type.
 */

#ifdef __cplusplus
#define EXTERN extern "C"
#else
#define EXTERN
#endif

EXTERN eWmv9DecCompFmtType eWMV9DCompFormat (const WMV9D_U8* format);


/***********  main API functions **********/

/*
 * Query for the memory requirement, given width and height of frame
 * The decoder sets the Meminfo structure with the required memory buffer
 * requests.
 * TODO : The object already has width and height, do we need to pass
 *        it separately ?
 */

EXTERN eWmv9DecRetType eWMV9DQuerymem (sWmv9DecObjectType* psWmv9Obj,
                                WMV9D_S32 s32Height, WMV9D_S32 s32Width);



/*
 * Initialise the decoder object and parses the sequence header, if required.
 * The memory requested should be met and the buffer pointers are provided.
 * Decoder, after actual initialization, parses the sequence header and sets
 * few decoder parameters (like frame rate, bitrate). It can potentially call
 * the callback function, so set the function callback before calling API.
 */

EXTERN eWmv9DecRetType eWMV9DInit (sWmv9DecObjectType* psWmv9DecObj);



/*
 * Decode one frame from the bitstream,
 * This function gets the data using the callback function, so make sure that
 * it is properly set. The decoded data will be available as read only in the
 * output frame buffer structure. If no frames has been skipped, the
 * u32CurFrameNumber will provide the frame number for this frame.
 */

EXTERN eWmv9DecRetType eWMV9DDecode (sWmv9DecObjectType* psWmv9Obj,
                              WMV9D_U32 u32FrameDataSize);



/*
 * Free the decoder structure (mainly reset the decoder internals)
 */

EXTERN eWmv9DecRetType eWMV9DFree (sWmv9DecObjectType *psWmv9Obj);

//#ifdef OUTPUT_BUFFER_CHANGES
/*! API to get the output frame*/
EXTERN eWmv9DecRetType  eWMV9DecGetOutputFrame (sWmv9DecObjectType *psWmv9Obj);
//#endif

EXTERN const char * WMV9DecCodecVersionInfo();

#endif /* WMV9_DEC_API_H  */
