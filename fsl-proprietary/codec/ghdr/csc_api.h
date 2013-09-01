/*
 ***********************************************************************
 * Copyright 2007-2008 by Freescale Semiconductor, Inc.
 * All modifications are confidential and proprietary information
 * of Freescale Semiconductor, Inc. ALL RIGHTS RESERVED.
 ***********************************************************************
 */
 
/*
****************************************************************************  
 * Freescale ShangHai Video Codec Team Change History

  Version    Date                   Author		     CRs                       Comments
  01.01.00   03/Jan/2008            Bo Zhao                                  The draft version
  01.02.00   02/Jul/2008            Bo Zhao                                  Add get viersion information API        
****************************************************************************  
*/

/*
*Define the API for color space conversion.
*At this moment, only yuv4:2:0 to rgb565 supported compatible with ITU 601-5 standard.
*/

#ifndef __CSC_API_H
#define __CSC_API_H

#ifdef __cplusplus
extern "C"{
#endif

typedef enum
{
	E_CSC_OK = 0,  
	E_CSC_NOT_SUPPORTED,   		  	
	E_CSC_UNKNOWN_ERROR         
} eCSCRetType;

typedef enum
{
	E_CSC_CF_420 = 0,  
	E_CSC_CF_422, 
	E_CSC_CF_444, 
	E_CSC_CF_400, 		  	
	E_CSC_CF_LAST         
} eCSCChromFmt;

typedef enum
{
	E_CSC_RANGE_240 = 0,  
	E_CSC_RANGE_235, 
	E_CSC_RANGE_255, 	  	
	E_CSC_RANGE_LAST         
} eCSCRange;


typedef enum
{
	E_CSC_STANDARD_601 = 0,  
	E_CSC_STANDARD_709_NTSC, 
	E_CSC_STANDARD_709_PAL, 
	E_CSC_STANDARD_YUV, 		  	
	E_CSC_STANDARD_LAST         
} eCSCStandard;

typedef enum
{
	E_CSC_RGB565 = 0,  
	E_CSC_RGB555, 
	E_CSC_RGB888, 	  	
	E_CSC_RGB_LAST         
} eCSCRGBFmt;

typedef struct tagCSCYUV
{
	unsigned char *pY;   /* pointer to luminance */
	unsigned char *pU;   /* pointer to chrominance cb */
	unsigned char *pV;   /* pointer to chrominance cr */
	int width;       /* the image horizontal size in pixels */
	int height;      /* the image vertical size in pixels */
	int stride_y;    /* yuv buffer horizontal stride for luminance */
	int stride_uv;   /* yuv buffer horizontal stride for chrominance */
	eCSCChromFmt chrom_fmt;   /* chrominance format.*/
	                          /* 0:                 4:2:0;     */
	                          /* 1:                 4:2:2;     */
	                          /* 2:                 4:4:4;     */
	                          /* 3:                 4:0:0;     */
	                          /* others:            reserved.  */ 
	                  
	eCSCRange range;          /* range of pixel value.*/
	                          /* 0:          16-240;           */
	                          /* 1:          16-235;           */
	                          /* 2:          0-255;            */
	                          /* others:     reserved.         */
	 
	eCSCStandard standard;    /* the international standard the sampling process compatible with */
	                          /* 0:          ITU 601;          */
	                          /* 1:          ITU 709 NTSC;     */
	                          /* 2:          ITU 709 PAL;      */
	                          /* 3:          YUV standard;     */
	                          /* others:     reserved.         */
               
}CSCYUV;


typedef struct tagCSCRGB
{
	void *pRGB;       /* base address of video display buffer */
	int stride;       /* horizontal stride of the video display buffer in pixels */	
	eCSCRGBFmt RGBfmt;       /* format of RGB */
	                         /* 0:          RGB565;   */
	                         /* 1:          RGB555;   */
	                         /* 2:          RGB888;   */
	                         /* others:     reserved. */	                  
}CSCRGB;



/* API for color space conversion */
eCSCRetType csc_yuv2rgb( CSCYUV *pCSCYUV, CSCRGB *pCSCRGB );
const unsigned char * csc_version_info(void);

#ifdef __cplusplus
}
#endif


#endif  /*__CSC_API_H*/

