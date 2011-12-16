
/*##############################################################################
             Copyright(C) 2001-2002, Motorola India Electronics Pvt Ltd.            
                       Motorola Confidential Proprietary.
                              All rights reserved.
--------------------------------------------------------------------------------
Filename    : interface.h

Description : This file contains all the functions and the data structures
                exposed in the API to the application. Application code
                just needs to include this header file for calling the
                JPEG encoder. The application is not expected to include
                any other header file of the codec.
			  			  
Author(s)   : Harsha Deeph G (harshad@miel.mot.com)

Context     : 

Caution     : 

**********************************************************************
 * 
 * (C) 2004 MOTOROLA INDIA ELECTRONICS LTD.
 * 
 * CHANGE HISTORY
 * 
 * dd/mm/yy   Description                                Author
 * --------   -----------                                ------
 * 16/03/04   Created.                                   Harsha Deeph G
 * 18/03/04   Added other functions and 
 *            parameters  in API                         Harsha Deeph G
 * 21/03/04   Added a void pointer
 *            in jpeg_enc_object
 * 21/03/04   Made YUV format as enum                    Ganesh Kumar C
 * 22/03/04   Removed interleaved flag from API          Harsha Deeph G 
 *            The necessary inforamtion is anyway
 *            present in yuv_format
 * 28/04/04   Changed MAX_MEMORY_INFO_ENTRIES to 5       Harsha Deeph G
 *            Added more error codes
 * 09/11/04   Added exif file format support             Gauri Deshpande
 *            Added exif parameter structures and flag
 * 04/12/04   Added MCU row level function APIs          Harsha Deeph G
 *            Added push_output function ptr to object
 *            Introduced 'mode' and 'compression_method'
 * 10/12/04   Modified function 'find_length_position'   Harsha Deeph G
 *            to support multiple lengths and offsets.
 *            Added primary/thumb image widhts & heights
 *            in params
 * 10/12/04   Added IFD1 info                            Gauri Deshpande
 * 26/12/04   Added ALIGN_64bit. Added new error codes   Harsha Deeph G
 *            for streaming output function failure.
 *            Added JFIF params in the params structure
 * 21/12/04   Added Static and Scratch memories           Harsha Deeph G
 * 29/12/04   Added Codec error types to enum list       Ganesh Kumar C  
***********************************************************************/
	
/************************************************************************
 * Copyright 2005-2011 by Freescale Semiconductor, Inc.
 * All modifications are confidential and proprietary information
 * of Freescale Semiconductor, Inc. 
 * 15/12/08   ENGR00102600: add cropping and raw data output    Eagle Zhou
 * 01/11/10   ENGR00133257: allow user add some non-mandatory tag info into exif header   Eagle Zhou
 * 03/28/11                            add tags: orientation/flash/whitebalance 	Eagle Zhou
 ************************************************************************/

#ifndef JPEG_ENC_INTERFACE_H
#define JPEG_ENC_INTERFACE_H

typedef unsigned char JPEG_ENC_UINT8;
typedef unsigned short JPEG_ENC_UINT16;
typedef unsigned long JPEG_ENC_UINT32;
typedef char JPEG_ENC_INT8;
typedef short JPEG_ENC_INT16;
typedef long JPEG_ENC_INT32;

#define JPEG_ENC_FAST_MEMORY 0
#define JPEG_ENC_SLOW_MEMORY 1
#define JPEG_ENC_STATIC_MEMORY 2
#define JPEG_ENC_SCRATCH_MEMORY 3

/* Debug Level : "0" - No Debug Logs 
 * Bit position 0 - Debug Level 0 -  Function entry/exit
 * Bit position 1 - Debug Level 1 -  Image Level
 * Bit position 2 - Debug Level 2 -  MCU level
 * Bit position 3 - Debug Level 3 -  DCT Huffmann Level
 * Bit position 4 - Debug Level 4 -  Error/Warning Level
 */
#define JPEG_ENC_DBG_LVL 0x0

typedef enum
{
      JPEG_ENC_YUV_444_NONINTERLEAVED, 
      JPEG_ENC_YUV_422_NONINTERLEAVED,
      JPEG_ENC_YUV_420_NONINTERLEAVED,
      JPEG_ENC_YU_YV_422_INTERLEAVED,
      JPEG_ENC_YV_YU_422_INTERLEAVED,
      JPEG_ENC_UY_VY_422_INTERLEAVED,
      JPEG_ENC_VY_UY_422_INTERLEAVED
}JPEG_ENC_YUV_FORMAT;

#define JPEG_ENC_ALIGN_8BIT 0     /* Align start of buffe to 8 bit boundary */
#define JPEG_ENC_ALIGN_16BIT 1    /* Align start of buffer to a 16 bit boundary */
#define JPEG_ENC_ALIGN_32BIT 2    /* Align start of buffer to a 32 bit boundary */
#define JPEG_ENC_ALIGN_64_BIT 3    /* Align start of buffer to a 64 bit boundary */
                         /* Double word alignment */

/* These defines are used for setting the compression_method
 * in the params structure */
#define JPEG_ENC_SEQUENTIAL 0
#define JPEG_ENC_PROGRESSIVE 1
                                   
#define JPEG_ENC_NUM_OF_OFFSETS 6

/* This dictates the maximum size of the array of jpeg_enc_memory_info.
 * The codec is not expected to request more than JPEG_ENC_MAX_MEMORY_INFO_ENTRIES
 * buffers */
#define JPEG_ENC_MAX_MEMORY_INFO_ENTRIES 5

typedef enum
{
    /* Successfull return values */
    JPEG_ENC_ERR_NO_ERROR = 0,
    JPEG_ENC_ERR_ENCODINGCOMPLETE,

    /*Application Erors */
    JPEG_ENC_ERR_RECL_START = 101,
    JPEG_ENC_ERR_INVALID_YUV_FORMAT,
    JPEG_ENC_ERR_INVALID_QUALITY,
    JPEG_ENC_ERR_INVALID_RESTART_MARKERS,
    JPEG_ENC_ERR_INVALID_MODE,
    JPEG_ENC_ERR_INVALID_COMPMETHOD,
    JPEG_ENC_ERR_INVALID_WIDTH,
    JPEG_ENC_ERR_INVALID_HEIGHT,
    JPEG_ENC_ERR_MEMORY_PTRS_PASSED_TO_ENC_NULL,
    JPEG_ENC_ERR_IMAGE_PTRS_PASSED_TO_ENC_NULL,
    JPEG_ENC_ERR_OUTPUT_PTR_PASSED_TO_ENC_NULL,
    JPEG_ENC_ERR_OUTPUT_LEN_PASSED_TO_ENC_ZERO,
    JPEG_ENC_ERR_OUTPUT_CALLBACK_FAIL,
    JPEG_ENC_ERR_THUMB_SIZE_TOO_BIG,
    JPEG_ENC_ERR_PROGRESSIVE_NOT_COMPILED,
    JPEG_ENC_ERR_EXIF_NOT_COMPILED,
    JPEG_ENC_ERR_COEF_BUFFERS_UNALIGNED,
    JPEG_ENC_ERR_RECL_END,

    /*Codec Errors*/
    JPEG_ENC_ERR_FATAL_START = 151,
    JPEG_ENC_ERR_INSUFFICIENT_MEMORY_REQUESTED_BY_ENC,
    JPEG_ENC_ERR_INVALID_MCUROW,
    JPEG_ENC_ERR_ARITH_NOTIMPL,
    JPEG_ENC_ERR_BAD_BUFFER_MODE, 
    JPEG_ENC_ERR_BAD_DCT_COEF, 
    JPEG_ENC_ERR_BAD_HUFF_TABLE, 
    JPEG_ENC_ERR_BAD_IN_COLORSPACE, 
    JPEG_ENC_ERR_BAD_J_COLORSPACE, 
    JPEG_ENC_ERR_BAD_LENGTH, 
    JPEG_ENC_ERR_BAD_LIB_VERSION,
    JPEG_ENC_ERR_BAD_MCU_SIZE, 
    JPEG_ENC_ERR_BAD_PRECISION, 
    JPEG_ENC_ERR_BAD_PROG_SCRIPT,
    JPEG_ENC_ERR_BAD_SAMPLING, 
    JPEG_ENC_ERR_BAD_SCAN_SCRIPT, 
    JPEG_ENC_ERR_BAD_STATE, 
    JPEG_ENC_ERR_BAD_STRUCT_SIZE,
    JPEG_ENC_ERR_CANT_SUSPEND, 
    JPEG_ENC_ERR_COMPONENT_COUNT, 
    JPEG_ENC_ERR_DQT_INDEX, 
    JPEG_ENC_ERR_EMPTY_IMAGE, 
    JPEG_ENC_ERR_HUFF_CLEN_OVERFLOW,
    JPEG_ENC_ERR_HUFF_MISSING_CODE,
    JPEG_ENC_ERR_IMAGE_TOO_BIG, 
    JPEG_ENC_ERR_MISSING_DATA, 
    JPEG_ENC_ERR_NOT_COMPILED, 
    JPEG_ENC_ERR_NO_HUFF_TABLE, 
    JPEG_ENC_ERR_NO_QUANT_TABLE, 
    JPEG_ENC_ERR_OUT_OF_MEMORY, 
    JPEG_ENC_ERR_TOO_LITTLE_DATA, 
    JPEG_ENC_ERR_WIDTH_OVERFLOW, 
    JPEG_ENC_ERR_FATAL_END,
}JPEG_ENC_RET_TYPE;

/* JPEG_ENC_ERR_COEF_BUFFERS_UNALIGNED - This is the error  returned
 * by the codec if the COEF buffers passed by the application are not
 * aligned. The codec will not return such an error if the other buffers
 * are not aligned. Except the COEF buffers, the codec internally aligns
 * all other memory chunks passed to it. COEF buffers are requested 
 * by codec only in JPEG_ENC_PROGRESSIVE compression mode */


typedef enum
{
	JPEGE_ENC_SET_HEADER_MAKE=0,
	JPEGE_ENC_SET_HEADER_MAKERNOTE,
	JPEGE_ENC_SET_HEADER_MODEL,
	JPEGE_ENC_SET_HEADER_DATETIME,	
	JPEGE_ENC_SET_HEADER_FOCALLENGTH,
	JPEGE_ENC_SET_HEADER_GPS,
	JPEGE_ENC_SET_HEADER_ORIENTATION,
	JPEGE_ENC_SET_HEADER_FLASH,
	JPEGE_ENC_SET_HEADER_WHITEBALANCE,
}JPEG_ENC_SETHEADER_TYPE;

#define MAX_GPS_PROCESSING_BYTES	256
#define MAX_MAKERNOTE_BYTES	256
#define MAX_MODEL_BYTES	256
#define MAX_MAKE_BYTES   256
typedef struct 
{
    JPEG_ENC_UINT32 version;			//GPSVersionID
    JPEG_ENC_UINT8 latitude_ref[2];		//GPSLatitudeRef: "N " is positive; "S " is negative
    JPEG_ENC_UINT8 longtitude_ref[2];	//GPSLongtitudeRef: "E " is positive; "W " is negative
    JPEG_ENC_UINT32 latitude_degree[2];//GPSLatitude
    JPEG_ENC_UINT32 latitude_minute[2];
    JPEG_ENC_UINT32 latitude_second[2];
    JPEG_ENC_UINT32 longtitude_degree[2];//GPSLongitude
    JPEG_ENC_UINT32 longtitude_minute[2];
    JPEG_ENC_UINT32 longtitude_second[2];
    JPEG_ENC_UINT8 altitude_ref;		//GPSAltitudeRef: 0 or 1(negative)
    JPEG_ENC_UINT32 altitude[2];		//GPSAltitude: unit is meters
    JPEG_ENC_UINT32 hour[2];			//GPSTimeStamp
    JPEG_ENC_UINT32 minute[2];
    JPEG_ENC_UINT32 seconds[2];
    JPEG_ENC_UINT8 processmethod[MAX_GPS_PROCESSING_BYTES]; //GPSProcessingMethod
    JPEG_ENC_UINT8 processmethod_bytes;
    JPEG_ENC_UINT8 datestamp[11];		//GPSDateStamp: "YYYY:MM:DD "
}jpeg_enc_gps_info;

typedef struct
{
    JPEG_ENC_UINT8 make_bytes;
    JPEG_ENC_UINT8 make[MAX_MAKE_BYTES];
}jpeg_enc_make_info;

typedef struct
{
    JPEG_ENC_UINT8 makernote_bytes;
    JPEG_ENC_UINT8 makernote[MAX_MAKERNOTE_BYTES];
}jpeg_enc_makernote_info;

typedef struct
{
    JPEG_ENC_UINT8 model_bytes;
    JPEG_ENC_UINT8 model[MAX_MODEL_BYTES];	
}jpeg_enc_model_info;

typedef struct
{
    JPEG_ENC_UINT8 datetime[20];	// "YYYY:MM:DD HH:MM:SS" with time shown in 24-hour format
}jpeg_enc_datetime_info;

typedef struct
{
    JPEG_ENC_UINT32 numerator;
    JPEG_ENC_UINT32 denominator;	
}jpeg_enc_focallength_info;

typedef struct
{
    JPEG_ENC_UINT8 alignment;                 /* JPEG_ENC_ALIGN_8BIT OR 16 or 32  or 64*/
    JPEG_ENC_UINT32 size;                     /* Size in number of bytes */
    /* JPEG_ENC_FAST_MEMORY (OR) JPEG_ENC_SLOW_MEMORY  - Only a Recommendation from codec */
    JPEG_ENC_UINT16 memtype_fast_slow;      
    /* STATIC memory or SCRATCH Memory. It is mandatory that application 
     * allocates static memory as requested. However, for the ones that 
     * are requested as 'scratch', the application can choose to allocate 
     * either static or scratch */
    JPEG_ENC_UINT16 memtype_static_scratch;  
    /* priority of meory chunk */
    JPEG_ENC_UINT8 priority;
    /* ptr to the memory allocated by application */
    void * memptr;      
}jpeg_enc_memory_info;

/* Current JPEG implementation does not request multiple memory chunks. 
 * One single memory chunk for FAST and one single chunk for SLOW is being 
 * requested. So, now, priority is not of importance
 * However, during system integration, if the application has only limited 
 * FAST memory available, then we will divide the codec FAST memory requests
 * into multiple smaller memory chunks and appropriate priority will
 * be given */

/* In the current JPEG Encoder implemenation, all the memory requested is
 * of type STATIC. */

typedef struct
{
    JPEG_ENC_UINT8 no_entries;
    jpeg_enc_memory_info mem_info[JPEG_ENC_MAX_MEMORY_INFO_ENTRIES];
}jpeg_enc_memory_infos;

typedef enum
{
    JPEG_ENC_MAIN_ONLY = 0,
    JPEG_ENC_MAIN,
    JPEG_ENC_THUMB
}JPEG_ENC_MODE;

typedef struct 
{
    JPEG_ENC_UINT32 count;  /* count is size of the jpeg_enc_tag in bytes */
    void* ptr;
} jpeg_enc_tag;

typedef struct
{
    JPEG_ENC_UINT32 x_resolution[2];
    JPEG_ENC_UINT32 y_resolution[2];
    JPEG_ENC_UINT16 resolution_unit;
    JPEG_ENC_UINT16 ycbcr_positioning;
} jpeg_enc_IFD0_appinfo;

typedef struct
{
    /* currently empty. further tags/variables can be added if req */
    void * ptr;
} jpeg_enc_exifIFD_appinfo;

typedef struct
{
    JPEG_ENC_UINT32 x_resolution[2];
    JPEG_ENC_UINT32 y_resolution[2];
    JPEG_ENC_UINT16 resolution_unit;
} jpeg_enc_IFD1_appinfo;

/* No error checking is done on the jpeg_enc_exif_parameters
 * and the application is expected to have passed valid
 * values */
typedef struct
{
    jpeg_enc_IFD0_appinfo IFD0_info;
    jpeg_enc_exifIFD_appinfo exififd_info;
    jpeg_enc_IFD1_appinfo IFD1_info;
} jpeg_enc_exif_parameters;

/* No error checking is done on the jpeg_enc_jfif_parameters
 * and the application is expected to have passed valid
 * values */

/* 
 * These three values are not used by the JPEG code, merely copied
 * into the JFIF APP0 marker.  density_unit can be 0 for unknown, 
 * 1 for dots/inch, or 2 for dots/cm.  Note that the pixel aspect 
 * ratio is defined by X_density/Y_density even when density_unit=0
 */
typedef struct
{
    /* JFIF code for pixel size units */
    JPEG_ENC_UINT8 density_unit;
    /* Horizontal pixel density */
    JPEG_ENC_UINT16 X_density;
    /* Vertical pixel density */
    JPEG_ENC_UINT16 Y_density;
} jpeg_enc_jfif_parameters;


/* Refer API doc for description of these parameters */
typedef struct
{
    JPEG_ENC_YUV_FORMAT yuv_format;
    JPEG_ENC_UINT8 quality;
    /* 1   JFIF (Send restart markers every MCU row), 
     *     EXIF (Send restart markers for every 4 MCUs )
     * 0 - No restart markers */
    JPEG_ENC_UINT8 restart_markers;
    JPEG_ENC_UINT8 compression_method;  /* Baseline or Progressive */
    JPEG_ENC_MODE mode;     
    /* Primary image widht/height should be set in
     * all the modes */
    JPEG_ENC_UINT16 primary_image_height;
    JPEG_ENC_UINT16 primary_image_width;
    JPEG_ENC_UINT16 y_height;
    JPEG_ENC_UINT16 u_height;
    JPEG_ENC_UINT16 v_height;
    JPEG_ENC_UINT16 y_width;
    JPEG_ENC_UINT16 u_width;
    JPEG_ENC_UINT16 v_width;

    /* cropping */	
    JPEG_ENC_UINT16 y_left;
    JPEG_ENC_UINT16 y_top;
    JPEG_ENC_UINT16 y_total_width;
    JPEG_ENC_UINT16 y_total_height;

    JPEG_ENC_UINT16 u_left;
    JPEG_ENC_UINT16 u_top;
    JPEG_ENC_UINT16 u_total_width;
    JPEG_ENC_UINT16 u_total_height;

    JPEG_ENC_UINT16 v_left;
    JPEG_ENC_UINT16 v_top;
    JPEG_ENC_UINT16 v_total_width;
    JPEG_ENC_UINT16 v_total_height;	

    /* raw data output ?*/		
    JPEG_ENC_UINT8 raw_dat_flag;
	
    /* 1 - EXIF.... 0 - JFIF */
    JPEG_ENC_UINT8 exif_flag; 
    jpeg_enc_exif_parameters exif_params;
    jpeg_enc_jfif_parameters jfif_params;
}jpeg_enc_parameters;

typedef struct
{
    jpeg_enc_parameters parameters;
    jpeg_enc_memory_infos mem_infos;
    /* The application should not change the function pointer
     * once the init routine is called */
    JPEG_ENC_UINT8 (*jpeg_enc_push_output) (JPEG_ENC_UINT8 ** out_buf_ptrptr,JPEG_ENC_UINT32 *out_buf_len_ptr, 
    JPEG_ENC_UINT8 flush, void * context, JPEG_ENC_MODE enc_mode);
    /* The application should not bother about the object entries below
     * and should not modify them */
    void *cinfo;
    void * context; // used by application
}jpeg_enc_object;

#ifdef __SYMBIAN32__
#define EXPORT_C __declspec(dllexport)
#else
#define EXPORT_C
#endif
#ifdef __cplusplus
extern "C"
{
#endif
 JPEG_ENC_RET_TYPE jpeg_enc_query_mem_req(jpeg_enc_object * enc_obj);
 JPEG_ENC_RET_TYPE jpeg_enc_init(jpeg_enc_object * enc_obj);
 JPEG_ENC_RET_TYPE jpeg_enc_flush_outputbuffer(jpeg_enc_object * obj_ptr);
 /* Application has to write the value at the offset.
  * See the application.c and API doc for more details.
  * The size of the arrays is JPEG_ENC_NUM_OF_OFFSETS 6 */
 JPEG_ENC_RET_TYPE jpeg_enc_find_length_position(jpeg_enc_object * obj_ptr, 
                                   JPEG_ENC_UINT32 offset[], JPEG_ENC_UINT8 value[],
                                   JPEG_ENC_UINT8 *num_entries);
 /* Row level APIs */
 JPEG_ENC_RET_TYPE jpeg_enc_encodemcurow (jpeg_enc_object * enc_obj, JPEG_ENC_UINT8 * i_buff, 
                           JPEG_ENC_UINT8 * y_buff, JPEG_ENC_UINT8 * u_buff, JPEG_ENC_UINT8 * v_buff);
 JPEG_ENC_RET_TYPE jpeg_enc_encodepassmcurow (jpeg_enc_object * enc_obj);
 /* Frame Level API. This can be used for both Baseline and Progressive */
 JPEG_ENC_RET_TYPE jpeg_enc_encodeframe (jpeg_enc_object * enc_obj, JPEG_ENC_UINT8 * i_buff, 
                           JPEG_ENC_UINT8 * y_buff, JPEG_ENC_UINT8 * u_buff, JPEG_ENC_UINT8 * v_buff);
/* set additional exif header info */
JPEG_ENC_RET_TYPE jpeg_enc_set_exifheaderinfo(jpeg_enc_object * enc_obj,JPEG_ENC_SETHEADER_TYPE type,JPEG_ENC_UINT32 para);
/*query lib version*/
const char *  jpege_CodecVersionInfo(void);
#ifdef __cplusplus
}
#endif

#endif /* JPEG_ENC_INTERFACE_H */
